// Mon Jan 29 19:43:01 BRST 2018
// Mon Jan 29 19:23:07 BRST 2018
/*
 *   io.c : pli_read, pli_open, readname, read_number
 *        : fd
 */
#include "pli.h"
#include "io.h"


/* 1.
 * pli_read: read a single char from current fd
 */
int pli_read()
{
    char c;
    if((c=ungetbuf[0])!=0){
        ungetbuf[0]=0;
        return(c);
    }
    return(read(fd,&c,1)?c:EOF);
}

/* 2.
 * pli_open: open fname. If success, fd is set.
 * If fails, return fp=NULL.
 */
FILE *pli_open(char *fname)
{
    FILE *fp;

    if(fname=="stdin"){
        fp=stdin;
        fd=fp->_file;        
    }else{
	if((fp=fopen(fname,"r"))!=NULL)
            fd=fp->_file;
        }
    return(fp);
}

/* 3.
 * TIPO: return 'a' (char) or '0' (digit)
 */
int TIPO(int c)
{

    if((c>='a' && c<='z') || (c>='A' && c<='Z'))
        return('a');
    else if (c>='0' && c<='9')
        return('0');

    else
        return(c);
}

/* 4.
 * readname: read from current fp and copy symbol name in 
 * pointer p appending '\0'.
 */
int readname(char *p,int lim)
{
    int c,t;
    if(TIPO(c=*p++=pli_read())!='a'){
        *p='\0';
    return(c);
    }

    while(--lim>0){
        t=TIPO(c=*p++=pli_read());
        if(t!='a' && t!='0'){
            ungtc(c);
            break;
        }
    }
    *(p-1)='\0';
    return('a');
}

/* 5.
 * read_number: read next number.
 */
SGNLG read_number(char *p)
{
    long v;
    int i,c,j;
    v=0;
    i=1;
    j=0;

    c=*p++=pli_read();
    if(c==OPRT_MIN)
        i=-1;
    else
        v=10*v+(c-'0');

    while(isdigit(c=*p++=pli_read())){
        if(j++<MAXNUMBER)
            v=10*v+(c-'0');
        else
            return(VERYLARGEINPUT);
        }        
    ungetbuf[0]=c;
    *(p-1)='\0';

/*
    if(v<=255)
	printf("CHAR\n");
    if(v>=256 && v<=65535)
	printf("SHORT\n");
    if(v>=65536)
	printf("INTEGER\n");
*/
    return(v*i);
}

/* 6. 
 * ungetc: unget last char.
 */
void ungtc(int c)
{
    ungetbuf[0]=c;
}

/* 7.
 * int2str: convert integer to string.
 */
void int2str(int n,char *buf)
{
    int i,sgn;

    if((sgn=n)<0)
	n=-n;
 
    i=0;
    do{
        buf[i++]=n % 10 +'0';
    }while((n/=10)>0);

    if(sgn<0)
	buf[i++]='-';

    buf[i]='\0';
    invert(buf);
}

/* 8.
 * invert: invert string in s
 */
void invert(char *s)
{
    int c,i,j;
    for(i=0,j=strlen(s)-1;i<j;i++,j--){
        c=s[i];
        s[i]=s[j];
        s[j]=c;
    }
}
