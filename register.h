/* Sun Mar 4 07:20:40 -03 2018 */
// Mon Jan 29 19: 43:01 BRST 2018
// Mon Jan 29 19: 23:07 BRST 2018
#include <string.h>
#define TAMHASH 100

int		hash       (char *s);
char           *store(char *s);

typedef struct symb {
	char           *name;
	char           *def;
	struct symb    *next;
}		SYMB        , *SYMBP;



SYMBP		search   (char *s);
SYMBP		reg      (char *name, char *definition);
