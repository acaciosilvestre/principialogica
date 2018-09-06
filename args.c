#include "main.h"
#include <signal.h>

extern OPTIONS	f;
extern _main_ctl ctl;
int
parseargs(int argc, char *argv[])
{
	char           *options;/* comand line  */
	int		flg = 0;/* options flag */

	while (--argc > 0) {
		flg = ((*++argv)[0] == '-') ? WITH_OPTIONS : NO_OPTIONS;
		switch (flg) {
		case WITH_OPTIONS:
			for (options = argv[0] + 1; *options != '\0'; options++)
				switch (*options) {
				case 'h':
					f.h = 1;
					break;

				case 'q':
					f.q = 1;
					break;

				case 'd':
					f.d = 1;
					break;

				case 'o':
					f.o = 1;
					break;

				case 'H':
					f.H = 1;
					break;

				case 'n':
					f.n = 1;
					break;

				default:
					break;
				}
			break;

		case NO_OPTIONS:
			ctl.sp->filename = *argv;
			break;

		default:
			break;
		}
	}

	//if (f.q == 0)
		//printf("pli1.15 - propositional logic interpreter.\n");


}
