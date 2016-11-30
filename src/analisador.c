#include "parser.h"
#include "tokenizador.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc == 1) {
    fprintf(stderr, "Uso: analisador \"expressao\"\n");
    return 1;
  }
  struct token *tokens = parse(argv[1]);
  if (tokens != NULL) {
    int i=0;
    while (tokens[i].tipo != fim) {
      token_imprime(tokens+i, stderr);
      fprintf(stderr, " ");
      ++i;
    }
    fprintf(stderr, "\n");
    free(tokens);
    return 0;
  }
  return 1;
}
