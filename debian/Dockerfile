FROM debian:jessie
MAINTAINER kevin.deisz@gmail.com

ENV DEBIAN_FRONTEND noninteractive
ENV USER kddeisz

RUN apt-get update
RUN apt-get install -y --fix-missing build-essential
RUN apt-get install -y --fix-missing dh-make
RUN apt-get install -y --fix-missing autotools-dev flex bison
RUN apt-get install -y --fix-missing pkg-config check

WORKDIR /data
CMD dpkg-buildpackage -us -uc && mkdir -p pkg/ && mv ../*.deb pkg/
