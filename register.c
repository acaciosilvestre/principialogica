/* Sun Mar 4 07:20:40 -03 2018 */
// Mon Jan 29 19: 43:01 BRST 2018
// Mon Jan 29 19: 23:07 BRST 2018
#include "register.h"
#include "malloc_np.h"

SYMB sy;

static SYMBP	tabhash[TAMHASH];

int
hash(char *s)
{
	int		valhash;
	for (valhash = 0; *s != '\0';)
		valhash += *s++;

	return (valhash % TAMHASH);
}

SYMBP
search(char *s)
{
	SYMBP		as;
	for (as = tabhash[hash(s)]; as != NULL; as = as->next)
		if (strcmp(s, as->name) == 0)
			return (as);
	return (NULL);
}

SYMBP
reg(char *name, char *def)
{
	SYMBP		as;
	int		valhash;
	if ((as = search(name)) == NULL) {
		as = (SYMBP) malloc(sizeof(*as));
		if (as == NULL)
			return (NULL);

		if ((as->name = store(name)) == NULL)
			return (NULL);

		valhash = hash(as->name);
		as->next = tabhash[valhash];
		tabhash[valhash] = as;

	} else
		free(as->def);

	if ((as->def = store(def)) == NULL)
		return (NULL);

	return (as);
}

char *
store(char *s)
{
	char *ap;
	if ((ap = malloc(strlen(s) + 1)) != NULL)
		strcpy(ap, s);
	return (ap);
}
