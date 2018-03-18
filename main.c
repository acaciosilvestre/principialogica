// Mon Jan 29 19:43:01 BRST 2018
// Mon Jan 29 19:23:07 BRST 2018
/* 
 *	pli.c - propositional logic interpreter 
 *              main program.
 *
 *	author: acacio silvestre
 */

#include "main.h"
#include <signal.h>
extern	OPTIONS f = {0,0,0,0};
int err_num;

/* 
 * 1. Entry point:
 */
int main(int argc,char *argv[])
{
   _main_ctl ctl = {&ctl,NULL,NULL,pli_open,init_tokens,0,eval};

   char *options;	/* comand line  */
   int flg = 0;		/* options flag */
   int sigh();
   signal(SIGUSR1,sigh);				

    while(--argc>0){
        flg=((*++argv)[0] == '-')?WITH_OPTIONS:NO_OPTIONS;
        switch(flg){
            case WITH_OPTIONS:
                for(options=argv[0]+1;*options != '\0';options++)
                    switch(*options){
                        case 'h':
                              f.h=1;
                        break;

                        case 'q':
                              f.q=1;
                        break;

			case 'd':
			      f.d=1;
			break;

			case 'o':
			      f.o=1;
			break;

                        default:
                        break;
                        }
                break;

                case NO_OPTIONS:
                        ctl.sp->filename=*argv;
                break;

                default:
                break;
        }
    }


   // if(f.q==0)
     // printf("pli1.15 - propositional logic interpreter.\n");


    if(f.d==1)
        printf("1. main\n");

    if(ctl.sp->filename != NULL)
	ctl.sp->fp=ctl.sp->f_open(argv[0]);     
    else
        ctl.sp->fp=ctl.sp->f_open("stdin");

    ctl.sp->inittk();

        while((ctl.sp->r=ctl.sp->evalfunc())!=E_O_I2){        	/* eval while not end of file */
	    if(ctl.sp->r!=E_O_I1){                         	/* end of line */
	        if(f.q==0)                          		/* verbose mode */
		    printf(" = ");                  		/* not end of line yet*/
		
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
        printf("pli1.15 - propositional logic interpreter.\nUsage:"\
	"pli [opts] filename.\noptions are: -h exadecimal output %d\n",err_num);
        return(1);
}

/*
        printf("pli1.15 - propositional logic interpreter.\n");
   Undefined Symbol	
	Operand missing 
	Operator missing
	Unbalanced bracket
	
 */

