#include <stdio.h>

#include "comp.h"

int main(int argc, char *argv[]) {
	if(argc < 2) {printf("usage: %s <file>\n", argv[0]); exit(1);}
	char         *content;
	int           sz;
	struct token *tokens;
	struct node  *tree;

	printf("\nreading file %s\n", argv[1]);
	content = _file_read(argv[1]);
	printf("\nfile read\n\nlexing content\n");
	tokens = _lex(content, &sz);
	printf("\nfile lexed, tokens:\n\n");
	for(int i = 0; i < sz; i++)
		_token_rep(tokens[i]);
	printf("\nparsing tokens:\n");
	tree = parse(tokens, sz);
	node_rep(&tree, 0);
}
