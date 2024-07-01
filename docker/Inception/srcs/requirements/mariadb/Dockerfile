FROM debian:11

RUN apt-get -y update && apt-get -y upgrade

RUN apt-get -y install mariadb-server
COPY /conf/mariadb.cnf /etc/mysql/mariadb.cnf

COPY ./tools/script.sh /script.sh
RUN chmod +x /script.sh

CMD ["/script.sh"]
