#include "parser.h"
#include "tokenizador.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  struct parser parser;
  if (argc == 1) {
    fprintf(stderr, "Uso: analisador \"expressao\"\n");
    return 1;
  }
  parser_inicializa(&parser);
  if (parser_parse(&parser, argv[1])) {
    size_t i;
    for (i = 0; i < parser.ntokens; ++i) {
      struct token *tok = &parser.tokens[i];
      token_imprime(tok, stderr);
      fprintf(stderr, " ");
    }
    fprintf(stderr, "\n");
    parser_finaliza(&parser);
    return 0;
  } else {
    fprintf(stderr, "ERRO: %s\n", parser.erro);
    parser_finaliza(&parser);
    return 1;
  }
}
