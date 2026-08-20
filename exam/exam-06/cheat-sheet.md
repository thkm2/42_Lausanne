# 🧠 Cheat-sheet — mini_serv (exam06)

Serveur de chat : les clients se connectent et se parlent entre eux.

---

## 1) Les étapes en mots simples

**A. Préparer le serveur (une seule fois)**
1. Vérifier qu'il y a **exactement 1 argument** (le port). Sinon → `Wrong number of arguments` + `exit(1)`.
2. Créer le **socket** d'écoute.
3. Remplir l'adresse : IPv4, IP = `127.0.0.1`, port = `argv[1]`.
4. **`bind`** (attacher) puis **`listen`** (écouter). Toute erreur système → `Fatal error` + `exit(1)`.
5. Mettre le socket d'écoute dans l'ensemble de fd `active`.

**B. La boucle infinie**
6. Copier `active` dans `readset` (car **`select` modifie** l'ensemble qu'on lui passe).
7. **`select`** : attendre qu'un fd soit prêt à lire.
8. Parcourir tous les fd de `0` à `maxfd`. Si le fd est prêt (`FD_ISSET`) :

   **Cas 1 — c'est le socket d'écoute** → nouveau client :
   - `accept` → nouveau fd `c`.
   - lui donner un id : `ids[c] = next_id++` (0, puis 1, puis 2…).
   - l'ajouter à `active`.
   - prévenir les autres : `server: client %d just arrived\n`.

   **Cas 2 — c'est un client existant** → `recv` :
   - **si `recv <= 0`** (il part) : prévenir les autres `server: client %d just left\n`, `free` son tampon, `FD_CLR`, `close`.
   - **sinon** (message) : empiler dans `stock[fd]` avec `str_join`, puis tant qu'il y a une **ligne complète** (`extract_message`), l'envoyer aux autres avec le préfixe `client %d: ` **devant chaque ligne**.

**Idée-clé à retenir** : `ids[fd]` et `stock[fd]` = deux **tableaux indexés par le fd**. Pas de liste chaînée !

---

## 2) Les choses à retenir

### Les 3 messages EXACTS (à recopier sans faute)
```
server: client %d just arrived\n
server: client %d just left\n
client %d:         ← préfixe mis DEVANT CHAQUE ligne reçue
```
Erreurs (sur **stderr** = fd 2) :
```
Wrong number of arguments\n   (pas 1 argument)  → exit(1)
Fatal error\n                 (syscall/malloc KO) → exit(1)
```

### Les variables globales
```c
int   ids[1024];       // ids[fd] = id du client
char *stock[1024];     // texte reçu en attente d'un '\n', par fd
int   sockfd, maxfd, next_id;
fd_set active, readset;
char  buf[1024], out[64];
```

### Les fonctions helpers fournies (à recopier depuis main.c)
- **`extract_message(&stock[fd], &line)`** → renvoie **1** si une ligne complète est extraite (met la ligne dans `line`, garde le reste dans `stock`), **0** si pas de `\n`, **-1** si malloc KO. → boucler avec `== 1`.
- **`str_join(stock[fd], buf)`** → renvoie `stock[fd] + buf` (et libère l'ancien). NULL si malloc KO → `fatal()`.

### Le squelette du socket (par cœur)
```c
sockfd = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in addr;
bzero(&addr, sizeof(addr));
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = htonl(2130706433);   // 127.0.0.1
addr.sin_port = htons(atoi(argv[1]));
bind(sockfd, (const struct sockaddr *)&addr, sizeof(addr));
listen(sockfd, 128);
```

### `select` — le cœur du non-bloquant
```c
readset = active;                              // TOUJOURS recopier avant
select(maxfd + 1, &readset, NULL, NULL, NULL); // +1 !  readset seul
```
Les 4 macros : `FD_ZERO` (vider), `FD_SET` (ajouter), `FD_CLR` (retirer), `FD_ISSET` (tester).

### Diffuser à tous
```c
void send_all(int except, char *str) {
    for (int fd = 0; fd <= maxfd; fd++)
        if (FD_ISSET(fd, &active) && fd != sockfd && fd != except)
            send(fd, str, strlen(str), 0);     // on IGNORE le retour
}
```

### ⚠️ Pièges qui font rater
- **Pas de `#define`** (les macros `FD_*` viennent des headers, elles sont OK).
- **Ne jamais tester `EAGAIN`**, **ne jamais déconnecter un client lent** → on ignore juste le retour de `send`.
- `select(maxfd **+ 1**, …)` (oubli fréquent du `+1`).
- **Recopier `active` dans `readset` à chaque tour** (select écrase le set).
- Préfixe `client %d: ` devant **CHAQUE** ligne, pas seulement la première.
- Une ligne **incomplète** (sans `\n`) doit rester dans `stock[fd]` jusqu'au prochain `recv`.
- **Fuites** : `free(line)` à chaque ligne, `free(stock[fd])` + `close(fd)` à la déconnexion.
- `recv(fd, buf, 1023, 0)` puis `buf[r] = 0` (borne = taille - 1).

### 🧪 Tester
```
cc -Wall -Wextra -Werror mini_serv.c -o mini_serv
./mini_serv 8080
# dans d'autres terminaux :
nc 127.0.0.1 8080     # (plusieurs fois pour simuler plusieurs clients)
```

---

## Ordre de récitation express (pour mémoriser)
**args → socket → addr(bzero, family, 127.0.0.1, port) → bind → listen → FD_ZERO/FD_SET →
boucle{ readset=active → select → for fd{ FD_ISSET? → si sockfd: accept+id+arrived ;
sinon: recv → si ≤0: left+free+close ; sinon: str_join+while extract_message(préfixe+ligne) } } }**
