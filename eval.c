/* eval.c */

#include "eval.h"

#define	not(x)	x=NOT(x);

extern  OPTIONS f;
static int attrib = 0;
extern SYMB sy;

void skipline(char c)
{
	while((c=pli_read())!=TKN_NL)
      	;  								/* skip comment */
}


/* 
 *  1. Input	
 */
 
BASETYPE eval()
{
char c;
int col;
int lin=1;
int eoi=0;
int eof=0;
int neg=0;
int precedindx;
int denial=0;
int noprnds=0;
int noprts=0;
int config=0;
BASETYPE number;
BASETYPE opnd[MAXOPERANDS+1];
int oprt[MAXOPERATORS];
int precedcs[MAXOPERATORS];
TOKENP ret_tk;
SYMBP sp;

/* while not end of input (line) */   
while(!eoi){
    c=pli_read();
    col++;
    ret_tk=gettoken(c);
    /* select by category */
    switch((ret_tk)?ret_tk->_cat:CATEGORY(c)){
    	case EOF:			
	    	eoi=1;
	    	eof=1;
        	break;
        	
		case _BLANK:
	    	if(c==TKN_NL){ 
			    col=0;     
			    ++lin;     
			    eoi=1;     
	    	}
			break;
			
		case _COMMENT:
			skipline(c);
			eoi=1;
			break;

        case _OPERAND:
            switch(ret_tk->_cls){	
				case _NUMERIC:     	
	    	    	ungtc(c);       
        	    	number=read_number(lbuf); 

                    if(denial){ 
            	        not(number);
                        denial=0; /* clear flag */
                    }
       		    	if(neg){  
            	       	number*=-1;
                        neg=0;    
                    }
                        
                    if(attrib==0 && f.q==0){        
						if(f.h==1)
			    			printf(" %x ",number);
						else
			    			printf(" %d ",number);
                 	}	
                    push(number);
                    ++noprnds;   
		    	    break;

	    		case _ALPHA: 
	        		ungtc(c);
               		readname(lbp,sizeof(lbuf));
        	        c=pli_read();  
					/*defined or ...*/
	      		if(c!=OPRT_ATT){ 
               	    	ungtc(c);    
                       	sp=search(lbp);
                       	if(sp!=NULL){  
			char syname[80];
			strcpy(syname,sp->name);
//				if(attrib==0 && f.q==0)
//	    				printf("%s",sp->name); 

                           	number=atoll(sp->def);
                       		if(denial){           
   	                    		not(number);
   	                    		denial=0;          
	    				if(attrib==0 && f.q==0)
	        				printf("~"); 
       	                	}
	
				if(attrib==0 && f.q==0)
				    printf("%s",syname);
       	                	push(number); 
       	                	++noprnds;    
	                    }
		    		else{
					exit(1);
        	        	}
                    }
                    else{
                        ungtc(c); 	
		    	    attrib=1;   
                    }              	
                    break;
                }
            	break;
            	
			case _OPERATOR: 
	    	    switch(ret_tk->_cls){ 
		        	case _ARITHMETIC: 
			    		neg=1;        
						break;
						
					case _ATTRIBUTION:
			    		attrib=1;     
					strcpy(lbuf2,lbuf); 

			    		number=eval(); 
			    		if(neg==1){
							number+=-1;
							neg=0;
			    		}
						int2str(number,lbuf);
				        reg(lbuf2,lbuf);
			    		attrib=0;                                  	
              			break;
              			
				    case _LOGIC:  
			    	    switch(ret_tk->_type){ 
     			            case _UNARY:  
               			        denial=1-denial; 
						        break;
						    
                   		    case _BINARY:
		                	    /* not an attribution and not quiet mode */
                        	    if(attrib==0 && f.q==0)
       							    printf("%c",c);
                    	        ++noprts; 
                    	        ++precedindx;
							    precedcs[precedindx]=ret_tk->_flg;   
							    pushoprt(c);   	/* push into operators stack */
                    	        break;
                    	    
                    	    default:
                    	        break;
                    	}
                	break;
            	}
        	    break;
        	    
			case _DELIMITER: 
       		    switch(c){ 
					case OSQR_BKT: 
			    		attrib=1;  
			    		
        	    	case ORND_BKT: 
						/* not an attribution and not quiet mode */
                        if(attrib==0 && f.q==0) 
							printf(denial?"~(":"(");
            		    ++noprnds;  
       			    	number=eval(); 
       			    	if(denial){	
	               			not(number);
                       		denial=0;           
       			    	}
            		    push(number); /* push to stack */
            		    break;
            		    
                    case CSQR_BKT: 
			    		attrib=0;  
			    		eoi=1;     
					    break;
					    
            		case CRND_BKT: 
						/* not an attribution and not quiet mode */
               		    if(attrib==0 && f.q==0)
            				printf(")"); 
           		    	eoi=1;           
            		    break;
            		    
            		default:
            		    break;
           		}
	    	    break;
	    	    
        	default:  /* symbol belongs to no category. unknown symbol */
        	break;
    	} 
    	/* 2. Process */
    	config=CONFIG();
	//printf("\n");
    	//printf("config %d\n",config); 
        switch(config){ 
	    	case   0:
	    	case 100:  	/* X */
	    	case 111:  	/* X^ */
	    	    break;

	    case 200:
		    printf("Binary operator missing\n");
	        break;	    	    
            case XY:
                opnd[2]=pop();
               	opnd[1]=pop();
               	oprt[0]=popoprt();
               	--noprts;         
               	--noprnds;        
                /* eval operation */
               	number=(oprt[0]==OPRT_AND)?AND(opnd[1],
               			 opnd[2]):EQV(opnd[1],opnd[2]);
               	push(number);     
	    		precedcs[precedindx]=0; 
               	--precedindx;          
	    	    break;
	    	    
            case X_Y:
	        	if(eoi==1){  
	            	opnd[2]=pop();	
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
			    /* if not end of formula, wait next operation */
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
				//TODO: handle invalid/unknown configurations
    			config=CONFIG();
                break;
        }
    	config=CONFIG();
    }
   	/* End of main while */
	
    /* Output */
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
    	return(___EOI);
    return(__EOI);
}/* end of eval */


