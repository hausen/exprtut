#ifndef TOKENIZADOR_H
#define TOKENIZADOR_H
#include <stdio.h>

enum tipo_token {
  numero, operador, abre_parentese, fecha_parentese,
  erro, fim
};

union valor_token {
  double numero;
  char operador;
};

struct token {
  enum tipo_token tipo;
  union valor_token valor;
};

struct tokenizador {
  const char *entrada;
};

/**
 * Imprime uma representação textual para o token.
 */
void 
token_imprime(struct token *tok, FILE *stream);

/**
 * Prepara o tokenizador para chamadas futuras
 * a tokenizador_proximo.
 */
void 
tokenizador_inicializa(struct tokenizador *tok,
                       const char *entrada);

/**
 * Analisa a entrada e atualiza o token passado como
 * parâmetro. Retorna 1 se conseguiu ler um token válido
 * da entrada, 0 caso chegou ao fim sem ler nenhum token,
 * ou -1 em caso de erro.
 */
int 
tokenizador_proximo(struct tokenizador *tok,
                    struct token *token);

#endif
