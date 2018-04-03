/* Sun Mar 4 07:20:40 -03 2018 */
// Mon Jan 29 19:43:01 BRST 2018
// Mon Jan 29 19:23:07 BRST 2018
#include <stdio.h>
#include <string.h>

char *errmsg[]={"0","Undefined symbol","Unknown Symbol","Missing operator"};

char *geterrmsg(int errnum)
{
    return(errmsg[errnum]);
}


