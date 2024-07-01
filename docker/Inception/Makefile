# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 12:18:11 by agrun             #+#    #+#              #
#    Updated: 2023/11/13 12:59:32 by agrun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Inception

all : up

up :
	@if [ ! -d "/home/adrian/data" ]; then \
		sudo mkdir -p /home/adrian/data/; \
		sudo chmod ugo=rwx /home/adrian/data; \
	fi
	@if [ ! -d "/home/adrian/data/mariadb" ]; then \
		sudo mkdir -p /home/adrian/data/mariadb; \
		sudo chmod ugo=rwx /home/adrian/data/mariadb; \
	fi
	@if [ ! -d "home/adrian/data/wordpress" ]; then \
		sudo mkdir -p /home/adrian/data/wordpress; \
		sudo chmod ugo=rwx /home/adrian/data/wordpress; \
	fi
	@docker-compose -f ./srcs/docker-compose.yml up -d #--build

down :
	@docker-compose -f ./srcs/docker-compose.yml down

stop :
	@docker-compose -f ./srcs/docker-compose.yml stop

start :
	@docker-compose -f ./srcs/docker-compose.yml start

status:
	@docker ps
	
clean:
	@docker-compose -f ./srcs/docker-compose.yml down
	@-docker stop `docker ps -qa`
	@-docker rm `docker ps -qa`
	@-docker rmi -f `docker images -qa`
	@-docker volume rm `docker volume ls -q`
	@-docker network rm `docker network ls -q`
	@sudo rm -r /home/adrian/data/

.PHONY: all up down stop start clean status
