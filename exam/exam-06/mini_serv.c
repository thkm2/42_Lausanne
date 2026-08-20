#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int		ids[1024];
char	*stock[1024];
int		sockfd, maxfd, next_id;
fd_set	active, readset;
char	buf[1024], out[64];

/* ==== DÉBUT : fonctions données dans main.c (à recopier telles quelles) ==== */

int	extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int		i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

/* ==== FIN : fonctions données dans main.c ==== */

void	fatal(void)
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

void	send_all(int except, char *str)
{
	for (int fd = 0; fd <= maxfd; fd++)
		if (FD_ISSET(fd, &active) && fd != sockfd && fd != except)
			send(fd, str, strlen(str), 0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		fatal();
	maxfd = sockfd;
	struct sockaddr_in	addr; /* -/ */
	bzero(&addr, sizeof(addr)); /* - */
	addr.sin_family = AF_INET; /* - */
	addr.sin_addr.s_addr = htonl(2130706433); /* - */
	addr.sin_port = htons(atoi(argv[1])); /* -/ */
	if (bind(sockfd, (const struct sockaddr *)&addr, sizeof(addr)) != 0) /* - */
		fatal();
	if (listen(sockfd, 128) != 0)
		fatal();
	FD_ZERO(&active);
	FD_SET(sockfd, &active);
	while (1)
	{
		readset = active;
		if (select(maxfd + 1, &readset, NULL, NULL, NULL) < 0)
			continue;
		for (int fd = 0; fd <= maxfd; fd++)
		{
			if (!FD_ISSET(fd, &readset))
				continue;
			if (fd == sockfd)
			{
				int	c = accept(sockfd, NULL, NULL);
				if (c < 0)
					continue;
				if (c > maxfd)
					maxfd = c;
				ids[c] = next_id++;
				stock[c] = NULL;
				FD_SET(c, &active);
				sprintf(out, "server: client %d just arrived\n", ids[c]);
				send_all(c, out);
			}
			else
			{
				int	r = recv(fd, buf, 1023, 0);
				if (r <= 0)
				{
					sprintf(out, "server: client %d just left\n", ids[fd]);
					send_all(fd, out);
					free(stock[fd]);
					FD_CLR(fd, &active);
					close(fd);
				}
				else
				{
					buf[r] = 0;
					stock[fd] = str_join(stock[fd], buf);
					if (!stock[fd])
						fatal();
					char	*line;
					while (extract_message(&stock[fd], &line) == 1)
					{
						sprintf(out, "client %d: ", ids[fd]);
						send_all(fd, out);
						send_all(fd, line);
						free(line);
					}
				}
			}
		}
	}
}
