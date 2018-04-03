
#include <unistd.h>

#define OPRT_MIN	'-'
#define MAXNUMBER	20
#define	VERYLARGEINPUT	0

#define ungtc(x)	*ungetbuf=x;
#define pli_getc()	read(fd,&c,1)?c:EOF

static int fd;
char ungetbuf[1];


