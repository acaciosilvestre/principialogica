/* Sun Mar 4 07:20:40 -03 2018 */
// Mon Jan 29 19: 43:01 BRST 2018
// Mon Jan 29 19: 23:07 BRST 2018
#include "register.h"
#include "pli.h"

/* tokens */
/* operators */
#define OPRT_NOT        '~'
#define OPRT_AND        '&'
#define OPRT_OR        '|'
#define OPRT_IMP        '>'
#define OPRT_EQV        '='
#define OPRT_ATT        ':'
#define OPRT_MIN        '-'
#define OPRT_PLS	'+'
#define OPRT_MUL	'*'
#define OPRT_DIV	'/'
#define OPRT_MOD	'%'

/* delimiters */
#define OCRL_BKT	'{'
#define CCRL_BKT	'}'
#define OSQR_BKT	'['
#define CSQR_BKT	']'
#define ORND_BKT	'('
#define CRND_BKT	')'
#define DBLE_QT		'"'
#define TKN_HSH		'#'
#define TKN_NL		'\n'

#define TKN_A		'A'
#define TKN_B		'B'
#define TKN_C		'C'
#define TKN_D		'D'
#define TKN_E		'E'
#define TKN_F		'F'
#define TKN_G		'G'
#define TKN_H		'H'
#define TKN_I		'I'
#define TKN_J		'J'
#define TKN_K		'K'
#define TKN_L		'L'
#define TKN_M		'M'
#define TKN_N		'N'
#define TKN_O		'O'
#define TKN_P		'P'
#define TKN_Q		'Q'
#define TKN_R		'R'
#define TKN_S		'S'
#define TKN_T		'T'
#define TKN_U		'U'
#define TKN_V		'V'
#define TKN_W		'W'
#define TKN_X		'X'
#define TKN_Y		'Y'
#define TKN_Z		'Z'
/* digits */
#define TKN_1		'1'
#define TKN_2		'2'
#define TKN_3		'3'
#define TKN_4		'4'
#define TKN_5		'5'
#define TKN_6		'6'
#define TKN_7		'7'
#define TKN_8		'8'
#define TKN_9		'9'
#define TKN_0		'0'

#define TKN_a		'a'
#define TKN_b		'b'
#define TKN_c		'c'
#define TKN_d		'd'
#define TKN_e		'e'
#define TKN_f		'f'
#define TKN_g		'g'
#define TKN_h		'h'
#define TKN_i		'i'
#define TKN_j		'j'
#define TKN_k		'k'
#define TKN_l		'l'
#define TKN_m		'm'
#define TKN_n		'n'
#define TKN_o		'o'
#define TKN_p		'p'
#define TKN_q		'q'
#define TKN_r		'r'
#define TKN_s		's'
#define TKN_t		't'
#define TKN_u		'u'
#define TKN_v		'v'
#define TKN_w		'w'
#define TKN_x		'x'
#define TKN_y		'y'
#define TKN_z		'z'
/* blanks */
#define TKN_SPC		' '
#define TKN_TAB		'\t'

/* category  */
enum {
	_COMMENT = 0, _OPERAND, _OPERATOR, _DELIMITER, _BLANK, _UNKNOWN
};

/* class - applies to _OPERAND, _OERATOR and _DELIMITER */
enum {
	_NUMERIC = 1, _ALPHA, _ATTRIBUTION, _LOGIC, _ARITHMETIC, _EOTK, _EOI, _ROUND, _SQUARE, _CURLY
};

/* type */
enum {
	_UNARY = 5, _BINARY, _EOL, _EOF, _OPEN, _CLOSE
};

/* flgs */
enum {
	_PRECEDENCE1 = 1, _PRECEDENCE2
};

#define MAXOPERANDS	 4	/* max number of current operands  <=3 */
#define MAXOPERATORS	 3	/* max number of current operators <=2 */

typedef struct _token {
	char		int_t;	/* token char */
	char		_cat;	/* token category */
	char		_cls;	/* token class */
	char		_type;	/* token type */
	char		_flg;	/* aditional information about current token */
}		TOKEN       , *TOKENP;

#ifndef _OPTIONS_F
#define _OPTIONS_F
typedef struct {
	unsigned	h:	1;	/* hex output */
	unsigned	q:	1;	/* quiet: only numeric output */
	unsigned	d:	1;	/* debug purposes */
	unsigned	o:	1;	/* octal output */
}		OPTIONS;
#endif
