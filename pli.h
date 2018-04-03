#include <ctype.h>      
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

typedef long       	BASETYPE;

/* 1. Function Prototypes */
int pli_read();
int readname(char *p,int lim);
int TYPE(int c);
void int2str(int n,char *buf);
void invert(char *s);
BASETYPE read_number(char *p);
FILE *pli_open(char *name);
int popoprt();
void pushoprt(int op);
char *aloca();
void libera();
BASETYPE pop();
BASETYPE push(BASETYPE n);

/* 2. Global Constants */
#define WORDBUFFER	20	/* word buf len in chars */
#define LINEBUFFER	80	/* line buf len in chars */
#define MAXNAME	20
#define MAXLINE	80
#define	WITH_OPTIONS	1
#define	NO_OPTIONS	0
#define	__EOI	'\n'
#define	___EOI	2828
#define STACK_LEN	1024
#define TAMHASH 100
/* configurations */
#define XY	211		/* X and Y */
#define X_Y	212		/* X or Y */
#define X_YZ	321	/* X or Y and Z */
#define X_Y_Z	322	/* X or Y or Z */
/* Global Macros */
#define NOT2(X)          (1-X)
#define NOT(X)		(-X-1)
#define AND(X,Y)        ((X) & (Y))
#define OR(X,Y)         ((X) | (Y))
#define IMP(X,Y)        ((NOT(X)) | (Y))
#define EQV(X,Y)        AND((IMP((X),(Y))),(IMP((Y),(X))))


