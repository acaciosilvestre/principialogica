/*
 * p l i - Propositional Logic Interpreter
 * 
 * By acacio silvestre: acacio.silvestre@hotmail.com
 */

#include <signal.h>
#include "main.h"

int		sigh       ();
extern OPTIONS	f = {0, 0, 0, 0};
int		err_num;
_main_ctl	ctl = {&ctl, NULL, NULL, pli_open, 0, eval};
char		mainbuf   [80];

int
main(int argc, char *argv[])
{
	/* Initialization */
	signal(SIGUSR1, sigh);
	parseargs(argc, argv);
	reg("x", "85");
	reg("y", "51");
	reg("z", "15");
	reg("x0","6148914691236517205");
	reg("x1","3689348814741910323");
	reg("x2","1085102592571150095");
	reg("x3","71777214294589695");
	reg("x4","281470681808895");
	reg("x5","4294967295");

	mainbuf[0] = '\0';
	if (f.d == 1) {
		strcpy(mainbuf, argv[2]);
	} else if (ctl.sp->filename != NULL) {
		ctl.sp->fp = ctl.sp->f_open(ctl.sp->filename);
	} else {
		ctl.sp->fp = ctl.sp->f_open(stdin);
	}


	while ((ctl.sp->r = ctl.sp->evalfunc()) != ___EOI) {	/* eval while not end of
								 * file */
		if (ctl.sp->r != __EOI) {	/* end of line */
			if (f.q == 0)	/* verbose mode */
				printf(" = ");	/* not end of line yet */
			if (f.h)
				printf("%llx\n", ctl.sp->r);
			else if (f.o)
				printf("%llo\n", ctl.sp->r);
			else
				printf("%lld\n", ctl.sp->r);
		}
	}
}

int
sigh()
{
	printf("error %s\n", geterrmsg(err_num));
	exit(1);
}
