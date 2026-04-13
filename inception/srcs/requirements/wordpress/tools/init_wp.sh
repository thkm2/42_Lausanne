#!/bin/bash

if [ ! -f "/var/www/html/wp-config.php" ]; then

wp core download --path=/var/www/html --allow-root

while ! mysqladmin -h mariadb ping --silent 2>/dev/null; do
	sleep 2
done

DB_PASSWORD=$(cat /run/secrets/db_password)

wp config create \
	--dbname=$MYSQL_DATABASE \
	--dbuser=$MYSQL_USER \
	--dbpass=$DB_PASSWORD \
	--dbhost=mariadb:3306 \
	--path=/var/www/html \
	--allow-root

WP_ADMIN_PASSWORD=$(cat /run/secrets/credentials)
WP_USER_PASSWORD=$(cat /run/secrets/credentials)

wp core install \
	--url=https://$DOMAIN_NAME \
	--title="Inception" \
	--admin_user=$WP_ADMIN_USER \
	--admin_password=$WP_ADMIN_PASSWORD \
	--admin_email=$WP_ADMIN_EMAIL \
	--path=/var/www/html \
	--allow-root

wp user create $WP_USER $WP_USER_EMAIL \
	--role=author \
	--user_pass=$WP_USER_PASSWORD \
	--path=/var/www/html \
	--allow-root

fi

exec php-fpm8.2 --nodaemonize
