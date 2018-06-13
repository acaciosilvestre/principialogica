// Mon Jan 29 19: 43:01 BRST 2018
// Mon Jan 29 19: 23:07 BRST 2018
typedef struct __stck {
	struct __stck  *_stck;
			SGNLG         (*_push) ();
			SGNLG         (*_pop) ();
	void            (*_pushoprt) ();
	int             (*_popoprt) ();
}		_STCK;
