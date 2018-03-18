// Mon Jan 29 19:43:01 BRST 2018
// Mon Jan 29 19:23:07 BRST 2018
/* token.c */

#include <stdio.h>
#include <string.h>
#include "token.h"

/* registered tokens */
TOKEN reg_token[86];

int init_tokens()
{

    TOKENP struct_t=&reg_token[0];
    int fd;
    if((fd=open("tokens",O_RDONLY))==-1){
	printf("tokens load error\n");
	exit(1);
	}
    read(fd,struct_t,sizeof(reg_token));
}

TOKENP gettoken(int int_t)
{
    TOKENP struct_t=&reg_token[0];
    int i;
    int struct_t_offset = -1;

    for(i = 0 ; struct_t[i].int_t != -1 ; ++i){
        if(struct_t[i].int_t== int_t){
            struct_t_offset = i;
            break;
        }
    }

    if(struct_t_offset != -1){
    	return(&struct_t[struct_t_offset]);
    }
    else{
        return(NULL);
    }

}


