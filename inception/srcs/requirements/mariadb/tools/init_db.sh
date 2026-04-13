#!/bin/bash

if [ ! -d "/var/lib/mysql/wordpress" ]; then
	mysql_install_db --user=mysql --datadir=/var/lib/mysql

	DB_PASSWORD=$(cat /run/secrets/db_password)
	DB_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)

	cat > /tmp/init.sql << EOF
CREATE DATABASE IF NOT EXISTS $MYSQL_DATABASE;
CREATE USER IF NOT EXISTS '$MYSQL_USER'@'%' IDENTIFIED BY '$DB_PASSWORD';
GRANT ALL PRIVILEGES ON $MYSQL_DATABASE.* TO '$MYSQL_USER'@'%';
ALTER USER 'root'@'localhost' IDENTIFIED BY '$DB_ROOT_PASSWORD';
FLUSH PRIVILEGES;
EOF

	exec mysqld --user=mysql --init-file=/tmp/init.sql
fi

exec mysqld --user=mysql
