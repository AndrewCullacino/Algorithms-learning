CC = clang
CFLAGS = -Wall -Werror -g -fsanitize=address,leak,undefined

.PHONY: all
all: runBst testJoin

runBst: runBst.c bst.c
testJoin: testJoin.c bst.c

.PHONY: clean
clean:
	rm -rf *.dSYM
	rm -f *.o runBst testJoin