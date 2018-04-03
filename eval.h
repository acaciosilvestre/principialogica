/* Sun Mar 4 07:20:40 -03 2018 */
// Mon Jan 29 19:43:01 BRST 2018
// Mon Jan 29 19:23:07 BRST 2018
#include "token.h"
#include "io.h"

extern TOKENP gettoken(int t);

char lbuf[WORDBUFFER], *lbp =lbuf;
char lbuf2[WORDBUFFER],*lbp2=lbuf2;
char lbuf3[WORDBUFFER],*lbp3=lbuf3;

#define	CONFIG()	100*noprnds+10*noprts+precedcs[precedindx]
#define CATEGORY(x)     (x==EOF)?EOF:(isspace(x))?_BLANK:_UNKNOWN



