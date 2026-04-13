# Inception — Grille d'évaluation (Correction Sheet)

---

## 0. Préliminaires

L'évaluateur commence par un nettoyage total de Docker sur la VM :

```bash
docker stop $(docker ps -qa); docker rm $(docker ps -qa); docker rmi -f $(docker images -qa); docker volume rm $(docker volume ls -q); docker network rm $(docker network ls -q) 2>/dev/null
```

---

## 1. Vérifications générales (fail instantané)

- [ ] Tous les fichiers de config sont dans `srcs/` à la racine du repo
- [ ] Un `Makefile` est à la racine
- [ ] **Pas de `network: host`** dans docker-compose.yml
- [ ] **Pas de `links:`** dans docker-compose.yml
- [ ] **Présence de `network(s)`** dans docker-compose.yml
- [ ] **Pas de `--link`** dans le Makefile ni les scripts
- [ ] **Pas de `tail -f`**, ni de commande en background dans les ENTRYPOINT des Dockerfiles
- [ ] **Pas de `bash` ou `sh`** utilisé seul (seulement pour lancer un script)
- [ ] Si l'entrypoint est un script, il ne lance **rien en background** (ex: `nginx & bash` interdit)
- [ ] **Aucune boucle infinie** dans les scripts (`sleep infinity`, `tail -f /dev/null`, `tail -f /dev/random` interdits)
- [ ] Le `make` build et lance tout correctement

---

## 2. Questions théoriques

L'étudiant doit expliquer simplement :

- [ ] Comment Docker et docker-compose fonctionnent
- [ ] La différence entre une image Docker utilisée avec/sans docker-compose
- [ ] L'avantage de Docker par rapport aux VMs
- [ ] La pertinence de la structure de répertoires demandée

---

## 3. Simple Setup (fail = fin de l'éval)

- [ ] NGINX accessible **uniquement par le port 443**
- [ ] Un **certificat SSL/TLS** est utilisé
- [ ] Le site WordPress est **installé et configuré** (on ne doit PAS voir la page d'installation)
- [ ] `https://login.42.fr` affiche le site WordPress configuré
- [ ] `http://login.42.fr` ne doit **PAS fonctionner** (pas d'accès HTTP)

---

## 4. Docker Basics (fail = fin de l'éval)

- [ ] **Un Dockerfile par service**, non vide
- [ ] Les Dockerfiles sont écrits par l'étudiant (pas d'images prêtes de DockerHub)
- [ ] Chaque conteneur est basé sur **l'avant-dernière version stable** d'Alpine ou Debian
- [ ] Les **images Docker ont le même nom** que leur service correspondant
- [ ] Le Makefile utilise docker-compose, les conteneurs ne crash pas

---

## 5. Docker Network (fail = fin de l'éval)

- [ ] `docker-network` est utilisé (vérifié dans docker-compose.yml)
- [ ] `docker network ls` montre un réseau visible
- [ ] L'étudiant explique le fonctionnement de docker-network

---

## 6. NGINX avec SSL/TLS (fail = fin de l'éval)

- [ ] Un Dockerfile existe
- [ ] `docker-compose ps` montre le conteneur créé
- [ ] L'accès via **HTTP (port 80) est impossible**
- [ ] `https://login.42.fr/` affiche le site WordPress (pas la page d'installation)
- [ ] Le certificat **TLS v1.2/v1.3** est démontré (auto-signé accepté)

---

## 7. WordPress + php-fpm et son Volume (fail = fin de l'éval)

- [ ] Un Dockerfile existe
- [ ] **Pas de NGINX** dans le Dockerfile WordPress
- [ ] `docker-compose ps` montre le conteneur créé
- [ ] **Volume vérifié** : `docker volume ls` puis `docker volume inspect <volume>` → le chemin contient `/home/login/data/`
- [ ] On peut **ajouter un commentaire** avec l'utilisateur WordPress
- [ ] Connexion au compte **admin** → le username **ne contient PAS "admin"/"Admin"** (admin, administrator, Admin-login, admin-123 tous interdits)
- [ ] Depuis le dashboard admin, **modifier une page** → le changement est visible sur le site

---

## 8. MariaDB et son Volume (fail = fin de l'éval)

- [ ] Un Dockerfile existe
- [ ] **Pas de NGINX** dans le Dockerfile MariaDB
- [ ] `docker-compose ps` montre le conteneur créé
- [ ] **Volume vérifié** : `docker volume inspect` → chemin `/home/login/data/`
- [ ] L'étudiant explique comment se connecter à la base de données
- [ ] **Login root SANS mot de passe** → doit **ÉCHOUER** (root doit avoir un password)
- [ ] **Login avec le user** et son password → la base ne doit **PAS être vide**

---

## 9. Persistence (fail = fin de l'éval)

- [ ] **Reboot de la VM**
- [ ] Relancer docker-compose
- [ ] Tout est fonctionnel
- [ ] Les **modifications précédentes** (commentaire, page éditée) sont **toujours là**

---

## 10. Bonus (seulement si le mandatory est parfait)

- [ ] **Redis cache** pour WordPress
- [ ] **Serveur FTP** pointant vers le volume WordPress
- [ ] **Site web statique** (dans un langage autre que PHP)
- [ ] **Adminer** (outil de gestion de BDD)
- [ ] **Service au choix** (l'étudiant doit expliquer son utilité)

---

## Points critiques / Pièges courants

| Point | Détail |
|-------|--------|
| Chemins des volumes | `docker volume inspect` doit montrer `/home/login/data/` — utiliser `driver_opts` avec `type: none`, `o: bind`, `device: /home/login/data/...` |
| Nom des images | Doit être identique au nom du service dans docker-compose |
| Root MariaDB | Doit avoir un mot de passe — connexion sans password doit échouer |
| Username admin WP | Ne doit contenir aucune variante de "admin" |
| Persistence | Après reboot de la VM, toutes les données doivent persister |
| Pas de HTTP | Le port 80 ne doit pas répondre du tout |
| Boucles infinies | Vérifier tous les scripts — aucun `while true`, `sleep infinity`, etc. |
