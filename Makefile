PROG    = pli
MAN=
SRCS    = main.c  args.c eval.c register.c io.c stack.c  pli_err.c token.c

install:
	cp pli ~/bin/pli2

.include <bsd.prog.mk>

