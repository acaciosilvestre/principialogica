/* Sun Mar 4 07:20:40 -03 2018 */
// Mon Jan 29 19: 43:01 BRST 2018
// Mon Jan 29 19: 23:07 BRST 2018
#include "pli.h"

static BASETYPE	intstack[STACK_LEN];
static int	oprtstack[STACK_LEN];
BASETYPE	intsp = 0;
int		oprtsp = 0;


BASETYPE
push(BASETYPE n)
{
	if (intsp < STACK_LEN)
		return (intstack[intsp++] = n);
}

BASETYPE
pop()
{
	if (intsp > 0)
		return (intstack[--intsp]);
	else
		return (0);
}

void
pushoprt(int op)
{
	if (oprtsp < STACK_LEN)
		oprtstack[oprtsp++] = op;
}

int
popoprt()
{
	if (oprtsp > 0)
		return (oprtstack[--oprtsp]);
	else
		return (0);
}
