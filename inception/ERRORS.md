# Erreurs rencontrées

## 1. `mysqld: Please run mysqld as root!`
MariaDB refuse de tourner en root par sécurité. Ajouté `--user=mysql` à `mysql_install_db` et `mysqld`.

## 2. `[pool www] user has not been defined`
php-fpm a besoin de savoir sous quel user exécuter les processus PHP. Ajouté `user = www-data`, `group = www-data` et les directives `pm` dans `www.conf`.

## 3. `Can't start server : Bind on unix socket: No such file or directory`
MariaDB a besoin de `/run/mysqld/` pour son fichier socket, mais ce dossier n'existe pas dans le container. Ajouté `RUN mkdir -p /run/mysqld && chown mysql:mysql /run/mysqld` dans le Dockerfile.

## 4. `Host is not allowed to connect to this MariaDB server`
Le `mysqld --bootstrap` avait échoué silencieusement — aucun user créé. Remplacé par : lancer mysqld en arrière-plan, attendre qu'il soit prêt avec `mysqladmin ping`, exécuter le SQL avec `mysql -u root`, puis shutdown.

## 5. `WordPress files seem to already be present here`
Le volume contenait les fichiers d'un test précédent. `wp core download` refuse si des fichiers existent déjà.

## 6. WordPress bloqué sur la wait loop
La wait loop utilisait `mariadb-admin ping` qui échouait car le user n'existait pas encore. Remplacé par `mysql -h mariadb -u $MYSQL_USER -p$DB_PASSWORD -e "SELECT 1;"`.

## 7. Volumes bind mount ne fonctionnent pas sur Mac
Les `driver_opts` avec `type: none, o: bind` ne marchent pas avec Docker Desktop (VM cachée). Simplifié en volumes Docker normaux pour le dev. Bind mounts à remettre pour la VM à 42.

## Leçon
Dans un container Docker il n'y a pas de système complet — les dossiers, users et services qui existent normalement sur un vrai Debian ne sont pas là. Il faut tout créer soi-même.
