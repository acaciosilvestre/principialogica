#include "pli.h"
#include "io.h"
#include "token.h"
#define pli_isnumber(x)	x=='-'?1:isdigit(x)
/*
 * 1. pli_read: read a single char from current fd
 */
static int	cmdbuf_p = 0;
extern char	mainbuf[];
extern OPTIONS	f;

int
pli_read()
{
	char		c;	/* common part */
	if ((c = ungetbuf[0]) != 0) {
		ungetbuf[0] = 0;
		return (c);
	}
	if (f.d == 1) {
		if ((c = mainbuf[cmdbuf_p]) != NULL) {
			++cmdbuf_p;
			return (c);
		} else {
			mainbuf[0] = '\0';
			return (EOF);
		}

	}
	if (f.d == 0)
		return (pli_getc());
}


/*
 * 2. pli_open: open fname. Return fd or NULL.
 */

FILE           *
pli_open(char *fname)
{
	FILE           *fp;
	if (strcmp(fname, "stdin") == 0) {
		fp = stdin;
		fd = fp->_file;
	} else {
		if ((fp = fopen(fname, "r")) != NULL)
			fd = fp->_file;
	}
	return (fp);
}


/*
 * 4. readname: read from current fp and copy symbol name in pointer p
 * appending '\0'.
 */
int
readname(char *p, int lim)
{
	int		c         , t;
	if (isalpha(c = *p++ = pli_read()) == 0) {
		*p = '\0';
		return (c);
	}
	while (--lim > 0) {
		t = isalnum(c = *p++ = pli_read());
		if (t == 0) {
			ungtc(c);
			break;
		}
	}
	*(p - 1) = '\0';
	return ('a');
}

/*
 * 5. read_number: read next number from fp.
 */

BASETYPE
read_number(char *p)
{
	long		v;
	int		i         , c, j;
	v = 0;
	i = 1;
	j = 0;

	c = *p++ = pli_read();
	if (c == OPRT_MIN)
		i = -1;
	else
		v = 10 * v + (c - '0');

	while (isdigit(c = *p++ = pli_read())) {
		if (j++ < MAXNUMBER)
			v = 10 * v + (c - '0');
		else
			return (VERYLARGEINPUT);
	}
	ungtc(c);
	*(p - 1) = '\0';
	return (v * i);
}

/* 
 * 6. int2str: convert integer to string.
 */

void int2str(BASETYPE n,char *buf)
{
    int i,sgn;
    if((sgn=n)<0)
	    n=-n;
 
    i=0;
    do{
        buf[i++]=n % 10 +'0';
    }while((n/=10)>0);

    if(sgn<0)
	    buf[i++]='-';

    buf[i]='\0';
    invert(buf);
}

/* 
 * 7. invert: invert string in s
 */

void invert(char *s)
{
    int c,i,j;
    for(i=0,j=strlen(s)-1;i<j;i++,j--){
        c=s[i];
        s[i]=s[j];
        s[j]=c;
    }
}

