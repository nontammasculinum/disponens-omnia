#include "comp.h"

int node_new(struct node **node, int id) {
	*node = malloc(sizeof(struct node));
	(*node)->children = malloc(sizeof(struct node *));
	(*node)->children[0] = NULL;
	(*node)->id = id;
	return 0;
}
int tree_delete(struct node **tree) {
	while(*(*tree)->children != NULL) {
		tree_delete( &(*(*tree)->children) );
		(*tree)->children++;
	}
	free((*tree)->children);
	free(*tree);
	*tree = NULL;
	return 0;
}
int node_add_child(struct node **parent, struct node **child) {
	int count = 0;
	for(count = 0; (*parent)->children[count] != NULL; count++);
	(*parent)->children[count] = *child;
	(*parent)->children = realloc((*parent)->children, (count + 2) * sizeof(struct node *));
	(*parent)->children[count + 1] = NULL;
	return 0;
}
int node_add_val(struct node **node, union _value val) {
	(*node)->value = val;
	return 0;
}
int node_add_valwt(struct node **node, void *value, int type) {
	switch(type) {
	case _int:   ((*node)->value).i = *((int*)  value); break;
	case _char:  ((*node)->value).c = *((char*) value); break;
	case _float: ((*node)->value).f = *((float*)value); break;
	case _str:   ((*node)->value).s = *((char**)value); break;
	default: return -1;
	}
	return 0;
}

static int _itoa(int num, char *str) {
	if(str == NULL)
		return -1;
	sprintf(str, "%d", num);
	return 0;
}

int node_rep(struct node **node, int level) {
	char *idname; int alloced;
	switch((*node)->id) {
		case _t_int:     idname = "int";     break;
		case _t_char:    idname = "char";    break;
		case _t_program: idname = "program"; break;
		case _t_i_const: idname = malloc(50);
						 _itoa((*node)->value.i, idname);
						 alloced = 1;
						                     break;
		case _t_c_const: idname = malloc(2);
						 idname[0] = (*node)->value.c;
						 idname[1] = '\0';
						 alloced = 1;
						                     break;
		default:         idname = "NULL";    break;
	}
	printf("|%s", idname);
	if(alloced) free(idname);
	int i = 0;
	for(i = 0; (*node)->children[i] != NULL; i++) {
		printf(", \n");
		for(int i = 0; i < level + 1; i++)
			printf("\t");
		node_rep(&((*node)->children[i]), level + 1);
	}
	if(i > 0) printf("\n");
	printf("|");
	if(level == 0) printf("\n");
	fflush(stdout);
}


static struct node *_CONST(struct token *tok, int index) {
	switch(tok[index].type) {
	case _t_i_const:
	case _t_c_const:
		struct node *ret;
		node_new(&ret, tok[index].type);
		node_add_val(&ret, tok[index].value);
		return ret;
	default: return NULL;
	}
}

static struct node *_TYPE(struct token *tok, int index) {
	struct node *ret;
	if(tok[index].type == _t_int)
		node_new(&ret, _t_int);
	else if(tok[index].type == _t_char)
		node_new(&ret, _t_char);
	else
		return NULL;
	return ret;
}

static struct node *_PROGRAM(struct token *tok, int *index, int len) {
	struct node *ret,
				*tmp;
	node_new(&ret, _t_program);
	while(*index < len) {
		_token_rep(tok[*index]);
		printf("\n");
		if((tmp = _TYPE(tok, *index)) != NULL)
			node_add_child(&ret, &tmp);
		else if((tmp = _CONST(tok, *index)) != NULL)
			node_add_child(&ret, &tmp);
		printf("\n");
		(*index)++;
	}
	return ret;
}

struct node *parse(struct token *tok, int len) {
	int index = 0;
	return _PROGRAM(tok, &index, len);
}


















