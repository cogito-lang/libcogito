FROM debian:jessie
MAINTAINER oss@localytics.com

ENV DEBIAN_FRONTEND noninteractive
ENV USER localytics

RUN apt-get update
RUN apt-get install -y --fix-missing build-essential
RUN apt-get install -y --fix-missing dh-make
RUN apt-get install -y --fix-missing bzr-builddeb

WORKDIR /data

CMD ["ls", "/data"]
