FROM debian:11

RUN apt-get update -y && apt-get upgrade -y

RUN apt-get install -y nginx
RUN mkdir -p /etc/nginx/ssl && apt-get install -y openssl
RUN openssl req -x509 -nodes -out /etc/nginx/ssl/inception.crt -keyout /etc/nginx/ssl/inception.key -subj "/C=DE/L=Berlin/O=42/OU=student/CN=agrun.42.fr" &&\
	mkdir -p /var/run/nginx

COPY conf/nginx.conf /etc/nginx/sites-enabled/default

RUN chmod 755 /var/www/html && chown -R www-data:www-data /var/www/html

# This command is used to start the nginx-webserver in the foreground to keep it connected to the terminal
CMD [ "nginx","-g","daemon off;" ]
