CFLAGS   = -g -Wall -lfl
CLEAN    = rm -f

cogito: clean lex.yy.c parser.tab.c parser.tab.h
	gcc lex.yy.c parser.tab.c src/*.c -o cogito $(CFLAGS)

lex.yy.c:
	flex cogito.lex

parser.tab.c parser.tab.h:
	bison -d parser.y

clean:
	$(CLEAN) cogito
	$(CLEAN) lex.yy.c
	$(CLEAN) parser.tab.c parser.tab.h

test:
	[ "$$(./cogito test-files/input.iam)" = "$$(cat test-files/output.json)" ] && echo 'Passed.' || (echo 'Failed.' && exit 1)
