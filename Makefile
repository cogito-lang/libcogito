CFLAGS   = -g -Wall -lfl
CLEAN    = rm -f

cogito: clean lex.yy.c
	gcc lex.yy.c -o cogito $(CFLAGS)

lex.yy.c:
	flex cogito.lex

clean:
	$(CLEAN) lex.yy.c
