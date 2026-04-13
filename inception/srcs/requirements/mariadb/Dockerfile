FROM debian:bookworm
RUN apt-get update && apt-get install -y mariadb-server
RUN mkdir -p /run/mysqld && chown mysql:mysql /run/mysqld
COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
COPY tools/init_db.sh /tools/init_db.sh
RUN chmod +x /tools/init_db.sh
CMD ["/tools/init_db.sh"]
