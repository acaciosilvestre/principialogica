// Mon Jan 29 19:43:01 BRST 2018
// Mon Jan 29 19:23:07 BRST 2018
#include <unistd.h>

#define OPRT_MIN	'-'
#define MAXNUMBER	20
#define	VERYLARGEINPUT	0

#define pli_getc()	read(fd,&c,1)?c:EOF

static int fd;
static char ungetbuf[1];
void ungtc(int c);


