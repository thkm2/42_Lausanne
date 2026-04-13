## Réseaux

- **IP publique** → accessible depuis Internet (box, VPS, serveur dédié, etc.)
- **IP privée** → accessible uniquement dans son réseau local (Wi-Fi, Docker, etc.)
- **127.0.0.1** → "moi-même" uniquement
- **0.0.0.0** → écoute sur toutes les interfaces (ex: `pnpm dev` accessible depuis un iPhone sur le même Wi-Fi)
- **Docker** → crée un réseau privé isolé, chaque conteneur a sa propre IP. Seuls les conteneurs du même réseau se voient. Couches : Internet → Wi-Fi → réseau Docker

## Bases de données

- Une DB = un programme serveur qui tourne en permanence, écoute sur un port (ex: 3306), stocke les données dans des fichiers sur disque
- Un client (ton app, WordPress…) se connecte au serveur et envoie des requêtes SQL pour lire/écrire
- Neon, Supabase etc. = quelqu'un d'autre gère le serveur pour toi. Dans Inception, c'est toi qui le lances dans un container
- MariaDB ≈ MySQL (même commandes, même SQL) mais open-source (fork libre, pas contrôlé par Oracle)
- `mysqld` = le programme serveur MariaDB (d = daemon), écoute sur le port 3306 et répond aux requêtes SQL
- Daemon = programme qui tourne en arrière-plan, en continu, sans interaction. L'opposé d'un programme "one-shot" comme `ls`
- Un serveur MariaDB peut contenir plusieurs databases séparées, chacune avec ses propres tables
- Port 3306 = convention par défaut de MySQL/MariaDB (comme 80 = HTTP, 443 = HTTPS)
- `50-server.cnf` = convention MariaDB pour le fichier de config serveur (les fichiers sont lus par ordre alphabétique, 50 = priorité standard)

## Dockerfile / Image / Container

- Le Dockerfile c'est ta recette (code source)
- `docker build` → fabrique l'image (l'exécutable compilé)
- `docker run` → lance un container à partir de l'image (le programme en train de tourner)

## Volumes Docker

- Un container est jetable — si tu le supprimes, tout ce qu'il contenait disparaît
- Un volume = un dossier sur ta vraie machine, "branché" dans le container. Les données survivent à la suppression du container

## PHP-FPM

- `php-fpm` = le programme qui exécute du PHP, comme `mysqld` exécute du SQL
- Un pool = un groupe de processus PHP prêts à traiter des requêtes en parallèle (`www` = pool par défaut)
- Syntaxe INI = format de config simple : `[section]` puis `clé = valeur` — utilisé par PHP, MySQL, Git, etc.

## Dossiers Linux

- `/usr` = là où sont installés les programmes et leurs fichiers. `/bin` = commandes vitales, `/usr/bin` = installés par apt-get, `/usr/local/bin` = installés manuellement
- `/etc` = config, `/var` = données variables (DB dans `/var/lib`, sites web dans `/var/www`)

## Users et programmes

- Un programme tourne en tant que l'user qui l'a lancé. Dans Docker, c'est root par défaut
- MariaDB refuse de tourner en root (sécurité) → le paquet `mariadb-server` crée automatiquement un user `mysql` à l'installation

## PID 1 dans Docker

- `docker stop` envoie SIGTERM au **PID 1** du container. Pas de réponse après 10s → kill brutal
- PID 1 = ton service (`mysqld`) → arrêt propre. PID 1 = `sleep infinity` / `tail -f` → ton service ne reçoit rien, corruption possible
- Donc : `CMD ["mysqld"]` en foreground, jamais `service start && tail -f`
