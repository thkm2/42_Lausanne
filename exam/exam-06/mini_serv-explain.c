/* ========================================================================
   mini_serv.c — EXPLIQUÉ ligne par ligne (le code est IDENTIQUE au rendu)
   Serveur de chat non-bloquant : les clients discutent entre eux.
   ======================================================================== */

#include <string.h>       // strlen, strcpy, strcat, memset...
#include <stdlib.h>       // malloc, calloc, free, atoi, exit
#include <unistd.h>       // write, close
#include <sys/socket.h>   // socket, bind, listen, accept, send, recv
#include <netinet/in.h>   // struct sockaddr_in, htons, htonl
#include <stdio.h>        // sprintf

/* --- VARIABLES GLOBALES (mises à zéro automatiquement au démarrage) --- */
int		ids[1024];     // ids[fd] = numéro (id) du client branché sur ce fd
char	*stock[1024];  // stock[fd] = texte reçu en attente d'un '\n' (par fd)
int		sockfd, maxfd, next_id; // socket d'écoute ; plus grand fd ; prochain id
fd_set	active, readset;        // 'active' = tous les fd ouverts ; copie de travail
char	buf[1024], out[64];   // tampon de lecture ; tampon des messages sortants

/* ------------------------------------------------------------------------
   extract_message : copié du main.c fourni.
   Cherche le premier '\n' dans *buf. Si trouvé : met la ligne (avec le '\n')
   dans *msg, laisse le reste dans *buf, renvoie 1.
   Pas de '\n' -> renvoie 0.   Échec calloc -> renvoie -1.
   ------------------------------------------------------------------------ */
int	extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int		i;

	*msg = 0;                    // par défaut : aucune ligne extraite
	if (*buf == 0)               // rien en attente
		return (0);
	i = 0;
	while ((*buf)[i])            // on parcourt le tampon caractère par caractère
	{
		if ((*buf)[i] == '\n')   // fin de ligne trouvée
		{
			// on alloue un nouveau tampon pour tout ce qui suit le '\n'
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1); // on y copie le "reste"
			*msg = *buf;                  // la ligne = l'ancien tampon...
			(*msg)[i + 1] = 0;            // ...coupée juste après le '\n'
			*buf = newbuf;                // *buf ne garde que le reste
			return (1);
		}
		i++;
	}
	return (0);                   // pas de '\n' : ligne incomplète, on garde tout
}

/* ------------------------------------------------------------------------
   str_join : copié du main.c fourni.
   Renvoie un NOUVEAU tampon = buf + add, et libère l'ancien buf.
   Sert à empiler ce qu'on reçoit dans stock[fd]. NULL si malloc échoue.
   ------------------------------------------------------------------------ */
char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)                // longueur de l'ancien contenu (0 si vide)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;               // chaîne vide au départ (strcat a besoin d'un '\0')
	if (buf != 0)
		strcat(newbuf, buf);     // ancien contenu
	free(buf);                   // on libère l'ancien tampon (pas de fuite)
	strcat(newbuf, add);         // puis le nouveau morceau
	return (newbuf);
}

/* ------------------------------------------------------------------------
   fatal : message d'erreur imposé par le sujet puis on quitte.
   ------------------------------------------------------------------------ */
void	fatal(void)
{
	write(2, "Fatal error\n", 12); // fd 2 = stderr ; 12 = longueur du texte
	exit(1);
}

/* ------------------------------------------------------------------------
   send_all : envoie 'str' à TOUS les clients ouverts...
   ...sauf le socket d'écoute (sockfd) et l'émetteur (except).
   On ignore le retour de send (le sujet interdit de tester EAGAIN et de
   déconnecter un client lent).
   ------------------------------------------------------------------------ */
void	send_all(int except, char *str)
{
	for (int fd = 0; fd <= maxfd; fd++)
		if (FD_ISSET(fd, &active) && fd != sockfd && fd != except)
			send(fd, str, strlen(str), 0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)               // il faut exactement le port en argument
	{
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0); // crée le socket TCP d'écoute
	if (sockfd < 0)
		fatal();
	maxfd = sockfd;              // pour l'instant le plus grand fd = le socket

	struct sockaddr_in	addr;    // structure d'adresse (IP + port)
	bzero(&addr, sizeof(addr));  // on met toute la structure à zéro
	addr.sin_family = AF_INET;                 // famille IPv4
	addr.sin_addr.s_addr = htonl(2130706433);  // 2130706433 = 127.0.0.1
	addr.sin_port = htons(atoi(argv[1]));      // port converti en ordre réseau

	// on attache le socket à l'adresse 127.0.0.1:port
	if (bind(sockfd, (const struct sockaddr *)&addr, sizeof(addr)) != 0)
		fatal();
	if (listen(sockfd, 128) != 0)  // on se met en écoute (file d'attente = 128)
		fatal();

	FD_ZERO(&active);            // ensemble de fd vide
	FD_SET(sockfd, &active);     // on y ajoute le socket d'écoute

	while (1)                    // boucle principale du serveur
	{
		readset = active;        // copie : select MODIFIE le set qu'on lui donne
		// select attend qu'un fd soit "prêt à lire" (nouvelle connexion ou message)
		if (select(maxfd + 1, &readset, NULL, NULL, NULL) < 0)
			continue;            // erreur passagère -> on retente

		for (int fd = 0; fd <= maxfd; fd++) // on regarde chaque fd
		{
			if (!FD_ISSET(fd, &readset))    // ce fd n'a rien de prêt -> suivant
				continue;

			if (fd == sockfd)               // le socket d'écoute est prêt =
			{                               // -> un nouveau client se connecte
				int	c = accept(sockfd, NULL, NULL); // on accepte, c = son fd
				if (c < 0)
					continue;
				if (c > maxfd)              // on tient maxfd à jour
					maxfd = c;
				ids[c] = next_id++;         // on lui donne le prochain id (0,1,2...)
				stock[c] = NULL;            // son tampon d'attente est vide
				FD_SET(c, &active);         // on l'ajoute à l'ensemble des fd
				// on prévient les AUTRES clients de son arrivée
				sprintf(out, "server: client %d just arrived\n", ids[c]);
				send_all(c, out);           // 'c' exclu : il ne se voit pas arriver
			}
			else                            // sinon : un client déjà connecté
			{                               // a envoyé quelque chose (ou s'est déco)
				int	r = recv(fd, buf, 1023, 0); // on lit ses données
				if (r <= 0)                 // 0 = déconnexion, <0 = erreur
				{
					// on prévient les autres de son départ
					sprintf(out, "server: client %d just left\n", ids[fd]);
					send_all(fd, out);
					free(stock[fd]);        // on libère son tampon (pas de fuite mémoire)
					FD_CLR(fd, &active);    // on le retire de l'ensemble
					close(fd);              // on ferme le fd (pas de fuite de fd)
				}
				else                        // il a envoyé un vrai message
				{
					buf[r] = 0;             // on termine la chaîne reçue
					stock[fd] = str_join(stock[fd], buf); // on l'empile dans son tampon
					if (!stock[fd])         // malloc a échoué -> erreur fatale (sujet)
						fatal();
					char	*line;
					// tant qu'une ligne complète (finie par '\n') existe...
					while (extract_message(&stock[fd], &line) == 1)
					{
						sprintf(out, "client %d: ", ids[fd]); // préfixe imposé
						send_all(fd, out);   // on envoie le préfixe aux autres
						send_all(fd, line);  // puis la ligne elle-même
						free(line);          // on libère la ligne (pas de fuite)
					}
				}
			}
		}
	}
}
