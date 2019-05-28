FROM amazonlinux:latest
MAINTAINER kevin.deisz@gmail.com

RUN yum -y update
RUN yum -y install gcc44 gcc-c++ libgcc44 rpm-build
RUN yum -y install autoconf automake libtool check
RUN yum -y install bison flex

WORKDIR /data
ADD build /bin/libcogito-build
CMD /bin/libcogito-build
