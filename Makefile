CFLAGS   = -g -Wall -lfl
CLEAN    = rm -f

cogito: clean src/lex.yy.c src/parser.tab.c src/parser.tab.h
	gcc src/*.c src/ccan/ccan/json/*.c -o cogito $(CFLAGS)

src/lex.yy.c:
	flex -o src/lex.yy.c src/cogito.l

src/parser.tab.c src/parser.tab.h:
	bison -d src/parser.y -o src/parser.tab.c

clean:
	$(CLEAN) cogito
	$(CLEAN) src/lex.yy.c
	$(CLEAN) src/parser.tab.c src/parser.tab.h

test: clean src/lex.yy.c src/parser.tab.c src/parser.tab.h
	gcc main.c src/*.c src/ccan/ccan/json/*.c -o cogito $(CFLAGS)
	test-files/test
