SUBDIRS         = src . tests
ACLOCAL_AMFLAGS = -I m4

debian-build:
	docker build -t libcogito:debian debian
	docker run -it -v `pwd`:/data libcogito:debian

amazon-build:
	autoreconf -i
	./configure
	docker build -t libcogito:amazon amazon
	docker run -it -v `pwd`:/data libcogito:amazon
