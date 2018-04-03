/* Sun Mar 4 07:20:40 -03 2018 */
// Mon Jan 29 19:43:01 BRST 2018
// Mon Jan 29 19:23:07 BRST 2018
#define TAMALOC 2000

typedef struct __aloc{
    struct __aloc *_aloc;
    char *(*aloc)();
    void (*lib)();
    char *alocp;
}_ALOC;
