CFLAGS   = -g -Wall -lfl
CLEAN    = rm -f

cogito: clean lex.yy.c parser.tab.c parser.tab.h
	gcc lex.yy.c parser.tab.c src/linked-list.c -o cogito $(CFLAGS)

lex.yy.c:
	flex cogito.lex

parser.tab.c parser.tab.h:
	bison -d parser.y

clean:
	$(CLEAN) cogito
	$(CLEAN) lex.yy.c
	$(CLEAN) parser.tab.c parser.tab.h
