// Mon Jan 29 19:43:01 BRST 2018
// Mon Jan 29 19:23:07 BRST 2018
#include <ctype.h>      
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

/* 
 * 1. Pointers for every data type *
 */

typedef char		*char_p;
typedef unsigned char	*uchar_p;
typedef short		*short_p;
typedef unsigned short	*ushort_p;
typedef int		*int_p;
typedef unsigned int	*uint_p;
typedef long		*long_p;
typedef unsigned long	*ulong_p;


/* Pointers to pointers */
typedef char_p	*char_p_p;


/*
 * 2. Pointers to functions that returns basic types *
 */

typedef char	(*char_f)();	/* pointer to char function  */

/*
 * 3. Pointers to functions that returns pointers to
 *    basic types *
 */
typedef char_p (*char_p_f)();

/*
 * 4. Pointer for a function that returns a pointer to
 *    another function;
 */
typedef char_p_f	(*char_p_f_f)();		

				
#define WORDBUFFER	20	/* word buf len in chars */
#define LINEBUFFER	80	/* line buf len in chars */
#define MAXNAME         20
#define MAXLINE		80

#define	WITH_OPTIONS	1
#define	NO_OPTIONS	0

/* logic operations */
#define NOT(X)          (1-X)
#define NOT2(X)		(-X)
#define AND(X,Y)        ((X) & (Y))
#define OR(X,Y)         ((X) | (Y))
#define IMP(X,Y)        ((NOT(X)) | (Y))
#define EQV(X,Y)        AND((IMP((X),(Y))),(IMP((Y),(X))))

/* pairs */
#define P0(X,Y)		AND(X,Y)
#define P1(X,Y)		AND((NOT(X)),Y)
#define P2(X,Y)		AND((NOT(Y)),X)
#define P3(X,Y)		AND((NOT(X)),(NOT(Y)))

/* L0 */
#define F1(X,Y)		P0(X,Y)
#define F2(X,Y)		P1(X,Y)
#define F3(X,Y)		OR(F1(X,Y),F2(X,Y))
#define F4(X,Y)		P2(X,Y)
#define F5(X,Y)		OR(F1(X,Y),F4(X,Y))
#define F6(X,Y)		OR(F2(X,Y),F4(X,Y))
#define F7(X,Y)		OR(F3(X,Y),F4(X,Y))
#define F8(X,Y)		P3(X,Y)
#define F9(X,Y)		OR(F1(X,Y),F8(X,Y))
#define FA(X,Y)		OR(F2(X,Y),F8(X,Y))
#define FB(X,Y)		OR(F3(X,Y),F8(X,Y))
#define FC(X,Y)		OR(F4(X,Y),F8(X,Y))
#define FD(X,Y)		OR(F5(X,Y),F8(X,Y))
#define FE(X,Y)		OR(F6(X,Y),F8(X,Y))
#define FF(X,Y)		OR(F7(X,Y),F8(X,Y))

#define	E_O_I1		'\n'
#define	E_O_I2		2828
typedef long       	SGNLG;

/* prototypes */
int pli_read();
int readname(char *p,int lim);
int TIPO(int c);
SGNLG read_number(char *p);
FILE *pli_open(char *name);
void int2str(int n,char *buf);
void invert(char *s);

#define STACK_LEN       1024
SGNLG pop();
int popoprt();
SGNLG push(SGNLG n);
void pushoprt(int op);
char *aloca();
void libera();

#define TAMHASH 100

/* configurations */
#define XY	211	/* X and Y */
#define X_Y	212	/* X or Y */
#define X_YZ   	321	/* X or Y and Z */
#define X_Y_Z	322	/* X or Y or Z */


