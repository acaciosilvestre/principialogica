// Mon Jan 29 19:43:01 BRST 2018
// Mon Jan 29 19:23:07 BRST 2018
/* eval.c */
#include <signal.h>				/* to be replaced to error module */
#include "eval.h"

extern  OPTIONS f;
extern err_num;
static int attrib = 0;
extern SYMB sy;
extern void ungtc(int c);

/* input */
SGNLG eval()
{
    char c;
    int col;
    int lin=1;
    int eoi=0;
    int eof=0;
    SGNLG number;
    int denial=0;
    int neg=0;
    int precedindx;				/* current precedence index */
    int noprnds=0;				/* number of current operands */
    int noprts=0;					/* number of current operators */
    int config=0;
    int opnd[MAXOPERANDS+1];			/* buffer for current operand values */
    int oprt[MAXOPERATORS];			/* buffer for current operators */
    int precedcs[MAXOPERATORS];			/* current precedences buffer */

    TOKENP ret_tk;
    SYMBP sp;
   
    while(!eoi){	        		/* while not end of input (line) */
        c=pli_read();				/* read next char */	
        col++;
        ret_tk=gettoken(c);

        /* select by category */
        switch((ret_tk)?ret_tk->_cat:CATEGORY(c)){

	    case EOF:			
	        eoi=1;				/* partial input end */
	       	eof=1;				/* no more input */
            break;

	    case _BLANK:                        /* exit main loop ... */
	        if(c==TKN_NL){       		/* ... if end of line found */
		    col=0;                      /* reset column counter */
		    ++lin;                      /* increase line counter to current line */
		    eoi=1;           		/* set end of line flag */
		}
	    break;

	    case _COMMENT:
	        while((c=pli_read())!=TKN_NL)
       	        	;                       /* skip comment */
		eoi=1;
	    break;

            case _OPERAND:                      	/* operand found */
                switch(ret_tk->_cls){           	/* select by operand class */

		    case _NUMERIC:              	/* numeric operand */
	    	        ungtc(c);                       /* unget first digit */
        		number=read_number(lbuf);	/* get the whole number */
                    	if(denial){                     /* check if ~number */
            	            number=NOT(number);
                            denial=0;                   /* clear flag */
                        }

       			if(neg){                               /* check if we have -number */
            	          number*=-1;       		       /* two's complement NOT */
                            neg=0;                             /* clear flag */
                        }

                	/* if not attribution and not quiet mode, print number */
                       	if(attrib==0 && f.q==0){        
				if(f.h==1)
			        	printf(" %x ",number);
			    	else
					printf(" %d ",number);         /* decimal */
				
                 	}

                        push(number);	                        /* push into stack */
                        ++noprnds;			        /* increase operands counter */
		    break;

		    case _ALPHA:                                /* name found */
		        ungtc(c);                              	/* unget first non digit char */
                	readname(lbp,sizeof(lbuf));             /* read the whole name */
                        c=pli_read();				/* get next char to check ... */		

			/*defined or ...*/
                	if(c!=OPRT_ATT){                       	/* if we are not doing attribution */
                   	    ungtc(c);                          	/* not attribution, unget last char */
                            sp=search(lbp);                    	/* look up stored name */

                            if(sp!=NULL){	               	/* found */
                                number=atoll(sp->def);         	/* convert to number */
	                        if(denial){                    	/* ceck if we have a denial */
        	                    number=NOT(number);       	/* yes, so number = ~number */
        	                    denial=0;                          /* clear flags */

				    if(attrib==0 && f.q==0)     /* not an attribution and not quiet mode then ... */
				        printf("~");            /* print '~' */
       	                	}

				if(attrib==0 && f.q==0)         /* not an attribution and not quiet mode then ... */
				    printf("%s",sp->name);      /* print symbol name */
				    //printf(" [ %s ] ",sp->def);      /* print symbol name */
								                                  	
        	                push(number);         		/* push symbol value into stack */
        	                ++noprnds;            		/* increase operands counter */

	                    }
                            /* Good place to implement functions.
				else if(readname)
				printf("KW\n");
			    */
			    else



                            {                                   	/* not found, so we have an undefined symbol */
			        //printf("lin %d col %d [[%s ]]",lin,lin-1; col-1,lbp);  /* print error context */
				//handle_error(UNDEFINED_SYMBOL,pe);    /* print error diagnose */
				//_execute(lbp);
						//err_num=77;
                	        	        //raise(SIGUSR1);
				exit(1);                        	/* abort */
        	            }

                        }
                        else                                            /* symbol being defined */
                        {
                            ungtc(c);                                  	/* send back attribution operator*/
			    attrib=1;                                   /* set attribution flag. next step is _ATTRIBUTION _OPERATOR */
                        }              	
                    break;
                }
            	break;

		case _OPERATOR:                                         /* operator found */

	    	    switch(ret_tk->_cls){                              	/* select by class */

		        case _ARITHMETIC:                               /* if sign */
			    neg=1;                                     	/* set flag */
			break;

			case _ATTRIBUTION:                              /* we are doing an attribution */
			    attrib=1;                                   /* set flag */
			    strcpy(lbuf3,lbuf);                         /* save symbol name in lbuf3 because lbuf is not preserved */
			    number=eval();                      	/* eval symbol numeric definition */
			    if(neg==1){
				number+=-1;
				neg=0;
			    }
			    strcpy(lbuf,lbuf3);                        	/* restore symbol name from lbuf3 to lbuf */
			    int2str(number,lbuf2);                     	/* convert numeric definition to string */
                	    reg(lbuf,lbuf2);	                       	/* so we can register symbol */
			    attrib=0;                                  	/* clear attribution flag */
              		break;

			case _LOGIC:                                   	/* logic operator */

			    switch(ret_tk->_type){                     	/* select by type */

     			        case _UNARY:                           	/* if denial ... */
               			    denial=1-denial;          		/* ... apply two's complement NOT */
				break;

                    		case _BINARY:                           /* logic binary operator */
                        	    if(attrib==0 && f.q==0)             /* not an attribution and not quiet mode */
       					printf("%c",c);                	/* print operator */

                    	        	++noprts;                      	/* increase operators counter */
                    	        	++precedindx;                  	/* increase index of precedences array */
					precedcs[precedindx]=
					ret_tk->_flg;   		/* store current symbol precedence */
					pushoprt(c);                   	/* push into operators stack */
                    		break;
                    	}
                	break;
                }
        	break;

		case _DELIMITER:                                        /* delimiter found */
	            //_ROUND,_SQUARE,_CURLY                             /* TODO: implement delimiters classes and types */
	            //_OPEN                                             /* to have coherence, but redundant */
       		    switch(c){                                         	/* select by symbol  */

			case OSQR_BKT:                                  /* open square bracket */
			    attrib=1;                                   /* set attrib flag*/

        	    	case ORND_BKT:                                  /* open round bracket */
                            if(attrib==0 && f.q==0)                     /* not an attribution and not quiet mode */
				printf(denial?"~(":"(");               	/* print delimiter */

            		    ++noprnds;                                 	/* increase operands counter */
       			    number=eval();                      	/* operand is a subformula. eval() it  */

       			    if(denial){                                	/* negative? */
	               		number=NOT(number);           		/* yes */
                       		denial=0;                              	/* clear flag */
       			    }

            		    push(number);                              	/* push to stack */
            		break;

	                //_ROUND,_SQUARE,_CURLY
	                //_CLOSE
        	    	
                        case CSQR_BKT:                                  /* close square bracket delimiter */
			    attrib=0;                                   /* attribution is over */
			    eoi=1;                                     	/* end of subformula */
			break;

            		case CRND_BKT:                                  /* close round bracket */
               		    if(attrib==0 && f.q==0)                     /* not an attribution and not quiet mode */
            			printf(")");                            /* then print delimiter */
           		    eoi=1;                                     	/* end of a subformula */
            		break;
                		
            		default:
            		break;
            	    }
	    	break;

        	default:                                                /* symbol belongs to no category. unknown symbol */
		    //printf("lin %d col %d %c ",lin,col-1,->c);        /* print error context */
		    //handle_error(UNKNOWN_SYMBOL,pe);                  /* print error diagnose and abort */
        	break;
    	    } 

    /* process */
    config=CONFIG();                                            	/* get current configuration */
//    printf("CONFIG  %d\n",config);
        switch(config){                                                	/* select by configuration code */
	    case   0:
	    case 100:  /* X */
	    case 111:  /* X^ */
	    break;

            case XY:		                                        /* highest precedence operator. process it */
                opnd[2]=pop();                                         	/* get operand 2 */
               	opnd[1]=pop();                                         	/* get operand 1 */
               	oprt[0]=popoprt();                                     	/* get operator */
               	--noprts;                                              	/* decrease number of operators */
               	--noprnds;                                             	/* decrease number of operands */

                /* eval operation */
               	number=(oprt[0]==OPRT_AND)?AND(opnd[1],
               			 opnd[2]):EQV(opnd[1],opnd[2]);
               	push(number);                                           /* save result */
	    	precedcs[precedindx]=0;                                 /* clear precedence value */
               	--precedindx;                                           /* decrease precedence counter */
	    break;

            case X_Y:
	        if(eoi==1){	                                        /* process only if end of formula. */
	            opnd[2]=pop();				        /* if not, wait next operation */
               	    opnd[1]=pop();
               	    oprt[0]=popoprt();
               	    --noprts;
               	    --noprnds;
              	    number=(oprt[0]==OPRT_OR)?OR(opnd[1],
                                     opnd[2]):IMP(opnd[1],opnd[2]);
               	    push(number);
		    precedcs[precedindx]=0;
               	    --precedindx;
               	}
            break;

            case X_YZ:
        	opnd[3]=pop();
              	opnd[2]=pop();
               	oprt[1]=popoprt();
               	--noprts;
        	--noprnds;
        	number=(oprt[1]==OPRT_AND)?AND(opnd[2],
        	        	 opnd[3]):EQV(opnd[2],opnd[3]);
        	push(number);
		precedcs[precedindx]=0;
        	--precedindx;
	    break;

            case X_Y_Z:
 	        opnd[3]=pop();
        	opnd[2]=pop();
        	opnd[1]=pop();
        	oprt[1]=popoprt();
        	oprt[0]=popoprt();
        	--noprts;
        	--noprnds;
        	number=(oprt[0]==OPRT_OR)?OR(opnd[1],
        			 opnd[2]):IMP(opnd[1],opnd[2]);
        	push(number);
        	push(opnd[3]);
        	pushoprt(oprt[1]);
		precedcs[precedindx-1]=precedcs[precedindx];
		precedcs[precedindx]=0;
        	--precedindx;
	    break;

            default:
		//TODO: handle
    		config=CONFIG();
		    //fprintf(stderr,"CFG %d\t%d\t%d\n",config,noprnds,noprts);
		   // fprintf(stderr,"%d",readname);
            break;
        }

    	config=CONFIG();
//	if(f.d==1)
	//    printf("CFG %d\n",config);
    }
   	
	
    /* output */
    if(noprnds==1){
   	--noprnds;
   	opnd[1]=pop();
	return(opnd[1]);
    }
	
    if(noprnds==2 && noprts==1){
	opnd[2]=pop();
	opnd[1]=pop();
	oprt[0]=popoprt();
	noprnds=0;
	noprts=0;
	return((oprt[0]==OPRT_OR)?OR(opnd[1],
		opnd[2]):IMP(opnd[1],opnd[2]));
    }
	
    if(eof)
    	return(E_O_I2);

    return(E_O_I1);
}/* end of eval */


/*
int sigh()
{
        printf("signal works\n");
        return 0;
}

*/
