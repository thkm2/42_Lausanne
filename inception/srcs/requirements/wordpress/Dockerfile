FROM debian:bookworm
RUN apt-get update && apt-get install -y php-fpm curl mariadb-client php-mysql php-curl php-xml php-mbstring
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && chmod +x wp-cli.phar && mv wp-cli.phar /usr/local/bin/wp
COPY conf/www.conf /etc/php/8.2/fpm/pool.d/www.conf
RUN mkdir -p /run/php
COPY tools/init_wp.sh /tools/init_wp.sh
RUN chmod +x /tools/init_wp.sh
CMD ["/tools/init_wp.sh"]
