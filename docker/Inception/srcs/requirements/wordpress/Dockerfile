FROM debian:11

RUN apt-get update && apt-get upgrade

# DOWNLOADING PHP
RUN apt-get install -y wget unzip php7.4 php-fpm php-mysql mariadb-client
RUN apt-get install -y php-gd curl php-dom php-imagick php-mbstring php-zip php-intl

COPY ./conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf

# DOWNLOADING WORDPRESS
RUN wget https://wordpress.org/wordpress-6.4.1.zip -P /var/www
RUN cd /var/www && unzip wordpress-6.4.1.zip && rm wordpress-6.4.1.zip

# DOWNLOADING WORDPRESS CLIENT
RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar &&\
	chmod +x wp-cli.phar && mv wp-cli.phar /usr/local/bin/wp

# SETTING UP WORDPRESS / SKIPPING INSTALLATION PAGE

COPY ./tools/script.sh /var/www/wordpress/script.sh
RUN chmod +x /var/www/wordpress/script.sh

RUN mkdir -p /run/php

CMD [ "/var/www/wordpress/script.sh" ]
