FROM debian:jessie
MAINTAINER oss@localytics.com

ENV DEBIAN_FRONTEND noninteractive
ENV USER localytics

RUN apt-get update
RUN apt-get install -y --fix-missing build-essential
RUN apt-get install -y --fix-missing dh-make
RUN apt-get install -y --fix-missing autotools-dev flex bison

WORKDIR /data
CMD dpkg-buildpackage -us -uc && mv ../*.deb .

# Building and running on mac:
# docker build -t libcogito .
# docker run -it -v /path/to/libcogito:/data libcogito
