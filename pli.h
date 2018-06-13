#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

typedef long	BASETYPE;

/* 1. Function Prototypes */
int		pli_read   ();
int		readname   (char *p, int lim);
void		int2str   (int n, char *buf);
void		invert    (char *s);
BASETYPE	read_number(char *p);
FILE           *pli_open(char *name);
int		popoprt    ();
void		pushoprt  (int op);
char           *aloca();
void		libera    ();
BASETYPE	pop    ();
BASETYPE	push   (BASETYPE n);

/* 2. Global Constants */
#define WORDBUFFER	20	/* word buf len in chars */
#define LINEBUFFER	80	/* line buf len in chars */
#define MAXNAME	20
#define MAXLINE	80
#define	WITH_OPTIONS	1
#define	NO_OPTIONS	0
#define	__EOI	65536
#define	___EOI	2828
#define STACK_LEN	1024
#define TAMHASH 100
/* configurations */
#define X	100
#define XY	211		/* X and Y */
#define X_Y	212		/* X or Y */
#define X_YZ	321		/* X or Y and Z */
#define X_Y_Z	322		/* X or Y or Z */
/* Global Macros */
#define NOT2(X)          (1-X)
#define NOT(X)			(-X-1)
#define AND(X,Y)        ((X) & (Y))
#define OR(X,Y)         ((X) | (Y))
#define IMP(X,Y)        ((NOT(X)) | (Y))
#define EQV(X,Y)        AND((IMP((X),(Y))),(IMP((Y),(X))))

#define	SUBJECT1(X,Y)	AND((X),(Y))	/* x & y */
#define PREDICATE1(X,Y)	EQV((X),(Y))	/* x = y */

#define SUBJECT2(X,Y)	PREDICATE1(X,Y)	/* x = y */
#define	PREDICATE2(X,Y)	IMP((X),(Y))	/* x > y */

#define	SUBJECTC(X,Y)	SUBJECT1(X,Y)	/* x & y */
#define PREDICATEC(X,Y)	PREDICATE2(X,Y)	/* x > y */

#define	MINOR_PREMISE(X,Y)	IMP(SUBJECT1(X,Y),PREDICATE1(X,Y))	/* (X1 & Y1) => (X1 =
									 * Y1) */
#define	MAJOR_PREMISE(X,Y)	IMP(SUBJECT2(X,Y),PREDICATE2(X,Y))	/* (X2 = Y2) => (X2 >
									 * Y2) */
#define	CONCLUSION(X,Y)		IMP(SUBJECT1(X,Y),PREDICATE2(X,Y))	/* (X3 & Y3) => (X3 >
									 * Y3) */

#define	AX_1(X,Y)	IMP(AND((X),(Y)),EQV((X),(Y)))
#define AX_2(X,Y)	IMP(EQV((X),(Y)),IMP((X),(Y)))
#define AX_3(X,Y,Z)	IMP(AND(IMP((X),(Y)),IMP((Y),(Z))),IMP((X),(Z)))

#define	T1(X,Y)		IMP(AND((X),(Y)),IMP((X),(Y)))	/* (x & y) -> (x > y) */
