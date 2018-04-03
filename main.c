/* 
 *				p l i - Propositional Logic Interpreter 
 *
 *									By
 *
 *				acacio silvestre: acacio.silvestre@hotmail.com
 */

#include <signal.h>
#include "main.h"

int sigh();
extern	OPTIONS f = {0,0,0,0};
int err_num;
_main_ctl ctl = {&ctl,NULL,NULL,pli_open,0,eval};


int main(int argc,char *argv[])
{
    /* Initialization */
    signal(SIGUSR1,sigh);				
    parseargs(argc,argv);
    if(f.d==1)
        printf("1. main\n");

    if(ctl.sp->filename != NULL)
		ctl.sp->fp=ctl.sp->f_open(ctl.sp->filename);     
    else
        ctl.sp->fp=ctl.sp->f_open(stdin);

    while((ctl.sp->r=ctl.sp->evalfunc())!=___EOI){ /* eval while not end of file */
    	if(ctl.sp->r!=__EOI){                      /* end of line */
	        if(f.q==0)                             /* verbose mode */
		    	printf(" = ");                     /* not end of line yet*/
		    if(f.h)
			    printf("%x\n",ctl.sp->r);
			else if (f.o)
		    	printf("%o\n",ctl.sp->r);
			else
		    	printf("%d\n",ctl.sp->r);
	   	}
	}
}

int sigh()
{
        printf("error %s\n",geterrmsg(err_num));
        exit(1);
}

