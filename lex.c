#include "comp.h"

int _token_rep(struct token t) {
	switch(t.type) {
	case _t_char: printf("char "); break;
	case _t_int: printf("int "); break;
	case _t_float: printf("float "); break;
	case _t_func: printf("func "); break;
	case _t_enum: printf("enum "); break;
	case _t_struct: printf("struct "); break;
	case _t_union: printf("union "); break;
	case _t_mut: printf("mut "); break;
	case _t_unsigned: printf("unsigned "); break;
	case _t_signed: printf("signed "); break;
	case _t_short: printf("short "); break;
	case _t_if: printf("if"); break;
	case _t_else: printf("else "); break;
	case _t_return: printf("return "); break;
	case _t_sizeof: printf("sizeof"); break;
	case _t_i_const: printf("%d", t.value.i); break;
	case _t_c_const: printf("%c", t.value.c); break;
	case _t_f_const: printf("%f", t.value.f); break;
	case _t_add: printf(" + "); break;
	case _t_sub: printf(" - "); break;
	case _t_ast: printf(" * "); break;
	case _t_div: printf(" / "); break;
	case _t_ob: printf("("); break;
	case _t_cb: printf(")"); break;
	case _t_oB: printf("{\n"); break;
	case _t_cB: printf("}\n"); break;
	case _t_oS: printf("["); break;
	case _t_cS: printf("]"); break;
	case _t_dot: printf("."); break;
	case _t_com: printf(", "); break;
	case _t_semi: printf(";\n"); break;
	case _t_colon: printf(":\n"); break;
	case _t_equ: printf(" = "); break;
	case _t_grt: printf(" > "); break;
	case _t_les: printf(" < "); break;
	case _t_not: printf("!");
	case _t_iden: printf("%s", t.value.s); break;
	}
}

char *_file_read(char *path) {
	char *ret;
	FILE *fp = fopen(path, "r");
	int sz;
	ret = malloc(sz = (fseek(fp, 0L, SEEK_END), ftell(fp)));
	rewind(fp);
	fread(ret, 1, sz, fp);
	fclose(fp);
	return ret;
}

static int op(char c) {
	switch(c) {
	case '+': return _t_add;
	case '-': return _t_sub;
	case '*': return _t_ast;
	case '/': return _t_div;
	case '(': return _t_ob;
	case ')': return _t_cb;
	case '{': return _t_oB;
	case '}': return _t_cB;
	case '[': return _t_oS;
	case ']': return _t_cS;
	case ';': return _t_semi;
	case ':': return _t_colon;
	case '.': return _t_dot;
	case ',': return _t_com;
	case '=': return _t_equ;
	case '>': return _t_grt;
	case '<': return _t_les;
	case '!': return _t_not;
	case ' ':
	case '\n':
	case '\t': return _t_ws;
	default:  return -1;
	}
}

#define IFNCMP(b, c) if(!strcmp(b, c))
#define ELNCMP(b, c) else if(!strcmp(b, c))
static int check(char *buff, int *b_pos) {
	int type = -1;
	if(buff[0] == '\0') return -1;
	IFNCMP(buff, "int")      type = _t_int;
	ELNCMP(buff, "char")     type = _t_char;
	ELNCMP(buff, "float")    type = _t_float;
	ELNCMP(buff, "enum")     type = _t_enum;
	ELNCMP(buff, "struct")   type = _t_struct;
	ELNCMP(buff, "union")    type = _t_union;
	ELNCMP(buff, "unsigned") type = _t_unsigned;
	ELNCMP(buff, "signed")   type = _t_unsigned;
	ELNCMP(buff, "short")    type = _t_short;
	ELNCMP(buff, "mut")      type = _t_mut;
	ELNCMP(buff, "if")       type = _t_if;
	ELNCMP(buff, "else")     type = _t_else;
	ELNCMP(buff, "return")   type = _t_return;
	ELNCMP(buff, "sizeof")   type = _t_sizeof;
	ELNCMP(buff, "func")     type = _t_func;
	else if(buff[0] == '\'') type = _t_c_const;
	else {
		int isn = 1;
		for(int i = 0; buff[i] != '\0'; i++) {
			if(!isdigit(buff[i])) {
				if(buff[i] == '.') type = _t_f_const;
				else type = _t_iden;
				isn = 0;
			}
		}
		if(isn) {
			type = _t_i_const;
		}
	}
	*b_pos = 0;
	return type;
}

struct token *_lex(char *content, int *sz) {
	struct token *ret = malloc(1); int rsz = 0;
	char buff[1024] = {0}; int b_pos = 0;
	int checked = 0;
	for(int i = 0; i < strlen(content); i++) {
		int operation = op(content[i]);
		if(operation != -1) {
			int type = check(buff, &b_pos);
			if(type != -1 && !checked) {
				ret = realloc(ret, (rsz + 1) * sizeof(struct token));
				ret[rsz].type = type;
				switch(type) {
				case _t_c_const: ret[rsz].value.c = buff[1];      break;
				case _t_f_const: ret[rsz].value.f = atof(buff);   break;
				case _t_i_const: ret[rsz].value.i = atoi(buff);   break;
				case _t_iden:    ret[rsz].value.s = strdup(buff); break;
				}
				checked = 1;
				rsz++;
			}
			if(operation != _t_ws) {
                ret = realloc(ret, (rsz + 1) * sizeof(struct token));
                ret[rsz].type = operation;
                rsz++;
            }
			continue;
		}
		if(b_pos == 1023) {
			buff[b_pos] = '\0';
			printf("token %s invalid (must be less than 1023 characters)", buff);
			exit(0);
		}
		checked = 0;
		buff[b_pos] = content[i];
		buff[b_pos + 1] = '\0';
		b_pos++;
	}
	*sz = rsz;
	return ret;
}
