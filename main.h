// Mon Jan 29 19:43:01 BRST 2018
// Mon Jan 29 19:23:07 BRST 2018
#include "token.h"

typedef FILE *FP;
typedef FP (*FOPEN)();
typedef long SGNLG;


FILE *pli_open(char *fname);
int init_tokens();
SGNLG eval();
//int sigh();

typedef union __lbl{
	union __lbl *_lbl;
	char *_char;
	short _short;
	int	_int;
	long	_long;
}_LBL;


typedef struct _struct{
    struct _struct *sp;
    char_p filename;
    FP fp;
    FOPEN f_open;
    int (*inittk)();    
    SGNLG r;
    SGNLG (*evalfunc)();
    _LBL lbl;
}_main_ctl,*_main_ctlp;


