/* Sun Mar 4 07:20:40 -03 2018 */
// Mon Jan 29 19: 43:01 BRST 2018
// Mon Jan 29 19: 23:07 BRST 2018
/* token.c */

#include <stdio.h>
#include <string.h>
#include "token.h"

/* registered tokens */
TOKEN reg_token[] = {
	{
		OPRT_NOT, _OPERATOR, _LOGIC, _UNARY, NULL
	},
	{
		OPRT_AND, _OPERATOR, _LOGIC, _BINARY, _PRECEDENCE1
	},
	{
		OPRT_OR, _OPERATOR, _LOGIC, _BINARY, _PRECEDENCE2
	},
	{
		OPRT_EQV, _OPERATOR, _LOGIC, _BINARY, _PRECEDENCE1
	},
	{
		OPRT_IMP, _OPERATOR, _LOGIC, _BINARY, _PRECEDENCE2
	},
	{
		OPRT_ATT, _OPERATOR, _ATTRIBUTION, NULL, NULL
	},
	{
		OPRT_MIN, _OPERATOR, _ARITHMETIC, _UNARY, NULL
	},
	{
		OPRT_PLS, _OPERATOR, _ARITHMETIC, _BINARY, NULL
	},
	{
		OPRT_MUL, _OPERATOR, _ARITHMETIC, _BINARY, NULL
	},
	{
		OPRT_DIV, _OPERATOR, _ARITHMETIC, _BINARY, NULL
	},
	{
		OPRT_MOD, _OPERATOR, _ARITHMETIC, _BINARY, NULL
	},
	{
		ORND_BKT, _DELIMITER, _ROUND, _OPEN, NULL
	},
	{
		CRND_BKT, _DELIMITER, _ROUND, _CLOSE, NULL
	},
	{
		OSQR_BKT, _DELIMITER, _SQUARE, _OPEN, NULL
	},
	{
		CSQR_BKT, _DELIMITER, _SQUARE, _CLOSE, NULL
	},
	{
		OCRL_BKT, _DELIMITER, _CURLY, _OPEN, NULL
	},
	{
		CCRL_BKT, _DELIMITER, _CURLY, _CLOSE, NULL
	},
	{
		DBLE_QT, _DELIMITER, NULL, NULL, NULL
	},
	{
		TKN_HSH, _COMMENT, NULL, NULL, NULL
	},
	{
		TKN_A, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_B, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_C, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_D, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_E, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_F, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_G, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_H, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_I, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_J, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_K, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_L, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_M, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_N, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_O, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_P, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_Q, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_R, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_S, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_T, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_U, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_V, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_W, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_X, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_Y, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_Z, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_a, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_b, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_c, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_d, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_e, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_f, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_g, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_h, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_i, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_j, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_k, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_l, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_m, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_n, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_o, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_p, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_q, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_r, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_s, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_t, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_u, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_v, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_w, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_x, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_y, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_z, _OPERAND, _ALPHA, NULL, NULL
	},
	{
		TKN_0, _OPERAND, _NUMERIC, NULL, NULL
	},
	{
		TKN_1, _OPERAND, _NUMERIC, NULL, NULL
	},
	{
		TKN_2, _OPERAND, _NUMERIC, NULL, NULL
	},
	{
		TKN_3, _OPERAND, _NUMERIC, NULL, NULL
	},
	{
		TKN_4, _OPERAND, _NUMERIC, NULL, NULL
	},
	{
		TKN_5, _OPERAND, _NUMERIC, NULL, NULL
	},
	{
		TKN_6, _OPERAND, _NUMERIC, NULL, NULL
	},
	{
		TKN_7, _OPERAND, _NUMERIC, NULL, NULL
	},
	{
		TKN_8, _OPERAND, _NUMERIC, NULL, NULL
	},
	{
		TKN_9, _OPERAND, _NUMERIC, NULL, NULL
	},
	/* blank */
	{
		TKN_SPC, _BLANK, _EOTK, NULL, NULL
	},
	{
		TKN_TAB, _BLANK, _EOTK, NULL, NULL
	},
	{
		TKN_NL, _BLANK, _EOI, _EOL, NULL
	},
	{
		EOF, _BLANK, _EOI, _EOF, NULL
	},
	{
		-1, NULL, NULL, NULL, NULL
	}
};

TOKENP
gettoken(int int_t)
{
	TOKENP		struct_t = &reg_token[0];
	int		i;
	int		struct_t_offset = -1;

	for (i = 0; struct_t[i].int_t != -1; ++i) {
		if (struct_t[i].int_t == int_t) {
			struct_t_offset = i;
			break;
		}
	}

	if (struct_t_offset != -1) {
		return (&struct_t[struct_t_offset]);
	} else {
		return (NULL);
	}

}
