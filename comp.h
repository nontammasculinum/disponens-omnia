#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *_file_read(char *path);

enum token_types {
	_t_char,       _t_int,       _t_float,
	_t_func,
	_t_enum,       _t_struct,    _t_union,
	_t_mut,        _t_unsigned,  _t_signed,
	_t_short,      _t_if,        _t_else,
	_t_return,     _t_sizeof,    _t_i_const,
	_t_c_const,    _t_f_const,   _t_add,
	_t_sub,        _t_ast,       _t_div, 
	_t_ob,         _t_cb,        _t_oB,
	_t_cB,         _t_oS,        _t_cS,
	_t_dot,        _t_com,       _t_semi,
	_t_colon,      _t_iden,      _t_ws,
	_t_equ,        _t_grt,       _t_les,
	_t_not,        _t_program,
};
union _value { int i; float f; char *s, c; };
struct token {
	enum  token_types type;
	union _value      value;
};

struct token *_lex      (char *content, int *sz);
int           _token_rep(struct token t);


struct node {
	int          id;
	struct node **children;
	union _value value;
};
enum _type { _int, _char, _float, _str };
int node_new      (struct node **node, int id);
int tree_delete   (struct node **tree);
int node_add_child(struct node **parent, struct node **child);
int node_add_val  (struct node **node, union _value val);
int node_add_valwt(struct node **node, void *val, int type);
int node_rep      (struct node **node, int level);

struct node *parse(struct token *tok, int len);
