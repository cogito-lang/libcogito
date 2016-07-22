CFLAGS   = -g -Wall -lfl -ljson-c
CLEAN    = rm -f

cogito: clean src/lex.yy.c src/parser.tab.c src/parser.tab.h
	gcc main.c src/*.c -o cogito $(CFLAGS)

src/lex.yy.c:
	flex -o src/lex.yy.c src/cogito.l

src/parser.tab.c src/parser.tab.h:
	bison -d src/parser.y -o src/parser.tab.c

clean:
	$(CLEAN) cogito
	$(CLEAN) src/lex.yy.c
	$(CLEAN) src/parser.tab.c src/parser.tab.h

test:
	test-files/test
