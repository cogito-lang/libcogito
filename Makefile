CFLAGS   = -g -Wall -lfl -ljson-c
CLEAN    = rm -f

cogito: clean lex.yy.c parser.tab.c parser.tab.h
	gcc main.c lex.yy.c parser.tab.c src/*.c -o cogito $(CFLAGS)

lex.yy.c:
	flex cogito.l

parser.tab.c parser.tab.h:
	bison -d parser.y

clean:
	$(CLEAN) cogito
	$(CLEAN) lex.yy.c
	$(CLEAN) parser.tab.c parser.tab.h

test:
	test-files/test
