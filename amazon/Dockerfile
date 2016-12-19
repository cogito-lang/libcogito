FROM amazonlinux:latest
MAINTAINER oss@localytics.com

RUN yum update
RUN yum install -y gcc44 gcc-c++ libgcc44 rpm-build
RUN yum install -y autoconf automake libtool check
RUN yum install -y bison flex

WORKDIR /data
ADD build /bin/cogito-build
CMD /bin/cogito-build
