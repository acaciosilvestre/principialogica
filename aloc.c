// Mon Jan 29 19:43:01 BRST 2018
// Mon Jan 29 19:23:07 BRST 2018
#include "pli.h"
#include "aloc.h"


static char bufaloc[TAMALOC];

_ALOC aloc={&aloc,aloca,libera,&bufaloc[0]};

char *aloca(int n)
{

    if(aloc._aloc->alocp+n<bufaloc+TAMALOC){
        aloc._aloc->alocp+=n;
        return(aloc._aloc->alocp-n);
    }else
        return(NULL);
}

void libera(char *p)
{
    if(p>=aloc._aloc->alocp && p< aloc._aloc->alocp+TAMALOC)
        aloc._aloc->alocp=p;
}

