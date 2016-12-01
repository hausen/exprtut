#include "tokenizador.h"

struct parser {
  struct token *tokens;
  size_t ntokens;
  const char *erro;
};

void parser_inicializa(struct parser *parser);

int parser_parse(struct parser *parser, const char *expr);

void parser_finaliza(struct parser *parser);
