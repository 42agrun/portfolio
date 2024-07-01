#!/bin/bash

# BUILT-IN DELAY TO ENSURE THAT MARIADB WILL BE SET UP BEFORE WORDPRESS TO AVOID ISSUES
sleep 10

cd /var/www/wordpress
rm -f wp-config.php --allow-root

wp config create --allow-root --dbname=$MYSQL_DATABASE --dbuser=$MYSQL_USER --dbpass=$MYSQL_PASSWORD --dbhost=mariadb:3306 --path='/var/www/wordpress'

wp core install --url=$DOMAIN_NAME --title=$WP_TITLE --admin_user=$WP_ADMIN_USR --admin_password=$WP_ADMIN_PWD --admin_email=$WP_ADMIN_EMAIL --skip-email --allow-root

wp user create $WP_USR $WP_EMAIL --role=author --user_pass=$WP_PWD --allow-root

wp option update home --allow-root "https://agrun.42.fr"
wp option update siteurl --allow-root "https://agrun.42.fr"

wp theme install astra --allow-root --activate
wp plugin delete --allow-root $(wp plugin list --allow-root --status=inactive --field=name)
wp theme delete --allow-root $(wp theme list --allow-root --status=inactive --field=name)

chown -R www-data:www-data /var/www/wordpress --allow-root

# The -F flag tells PHP-FPM to run in the foreground, rather than as a daemon in the background.
# This way it stays connected to the terminal!
php-fpm7.4 -F
