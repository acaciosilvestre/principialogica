// Mon Jan 29 19:43:01 BRST 2018
// Mon Jan 29 19:23:07 BRST 2018
#include <stdio.h>
#include <string.h>
#include "pli_err.h"

ERRORMESS pli_errormess[]={
    {UNDEFINED_SYMBOL,"Undefined symbol"   ,NULL},
    {      OPEN_ERROR,"Error openning file",NULL},
    {  UNKNOWN_SYMBOL,"Unknown symbol"     ,NULL},
    {              -1,                 NULL,NULL}
    };

int handle_error(int errstat,struct errormess * errormess)
{
    int i;
    int emess_offset = -1;
    char * message,messagebuff[100];

    for(i = 0 ; errormess[i].errstat != -1 ; ++i){
        if(errormess[i].errstat == errstat){
            emess_offset = i;
            break;
        }
    }

    message = messagebuff;
    if(emess_offset != -1){
        strcpy(message,errormess[emess_offset].message);
        if(errormess[emess_offset].build){
            (*errormess[emess_offset].build)(message);
        }
    }
    else{
        sprintf(message,"Error %d.",errstat);
    }

    puts("\n");
    puts(message);
    return(0);
}


