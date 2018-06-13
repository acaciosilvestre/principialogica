#include "pli.h"
#include "token.h"

typedef FILE   *FP;
typedef		FP     (*FOPEN) ();
BASETYPE	eval   ();

typedef struct _struct {
	struct _struct *sp;
	char           *filename;
	FP		fp;
	FOPEN		f_open;
	BASETYPE	r;
			BASETYPE      (*evalfunc) ();
}		_main_ctl   , *_main_ctlp;
