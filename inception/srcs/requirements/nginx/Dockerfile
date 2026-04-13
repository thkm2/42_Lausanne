FROM debian:bookworm
RUN apt-get update && apt-get install -y nginx openssl
COPY conf/nginx.conf /etc/nginx/nginx.conf
COPY tools/init_nginx.sh /tools/init_nginx.sh
RUN chmod +x /tools/init_nginx.sh
CMD ["/tools/init_nginx.sh"]
