// Mon Jan 29 19:43:01 BRST 2018
// Mon Jan 29 19:23:07 BRST 2018
#define	UNDEFINED_SYMBOL	0
#define	OPEN_ERROR		1
#define	UNKNOWN_SYMBOL		2

typedef struct errormess{
	int errstat;
	char *message;
	int (*build)();
        int lin;
        int col;
        int chr;
}ERRORMESS,*ERRORMESSP;

int handle_error(int errstat, ERRORMESSP errormess);
