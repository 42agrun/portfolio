#!/bin/bash

# BUILT-IN DELAY TO ENSURE CORRECT SETUP ORDER AMONG APP DEPENDENCIES
sleep 3
service mariadb start;

# WAITING FOR CONNECTION TO SERVER TO BE ESTABLISHED
while ! mysqladmin ping --silent; do
	sleep 1
done

# CREATING MYSQL-DATABASE WITHIN OPENSOURCE APP 'MARIADB'

mariadb -e "CREATE DATABASE IF NOT EXISTS $MYSQL_DATABASE;"
mariadb -e "CREATE USER IF NOT EXISTS '$MYSQL_USER'@'localhost' IDENTIFIED BY '$MYSQL_PASSWORD';"
mariadb -e "GRANT ALL PRIVILEGES ON $MYSQL_DATABASE.* TO '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';"
sleep 1
mariadb -u root -p"$MYSQL_ROOT_PASSWORD" -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD'; FLUSH PRIVILEGES;"
mysqladmin -u root -p"$MYSQL_ROOT_PASSWORD" shutdown
sleep 1

# STARTING THE DATABASE IN SAFEMODE
exec mysqld_safe

# HOW TO ACCESS YOUR FRESHLY CREATED DATABASE

# docker exec -it mariadb bash //enters the docker environment
# mariadb -uroot -p	       //log into database

# Make sure that logging in requires a password!
