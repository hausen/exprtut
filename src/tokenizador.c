#include "tokenizador.h"
#include <ctype.h>

void
token_imprime(struct token *tok, FILE *stream) {
  switch (tok->tipo) {
  case numero:
    fprintf(stream, "[numero %g]", tok->valor.numero);
  break;
  case operador:
    fprintf(stream, "[operador %c]", tok->valor.operador);
  break;
  case abre_parentese:
    fprintf(stream, "[abre parentese]");
  break;
  case fecha_parentese:
    fprintf(stream, "[fecha parentese]");
  break;
  case fim:
    fprintf(stream, "[fim]");
  break;
  case erro:
    fprintf(stream, "[ERRO]");
  break;
  default:
    fprintf(stream, "TOKEN NÃO IDENTIFICADO!");
  break;
  }
}

void
tokenizador_inicializa(struct tokenizador *tok,
                       const char *entrada) {
  tok->entrada = entrada;
}

/* funções usadas em tokenizador_proximo */
void tokenizador_processa_numero(struct tokenizador *tok,
                                 struct token *token);
void tokenizador_processa_operador(struct tokenizador *tok,
                                   struct token *token);
void tokenizador_processa_parentese(struct tokenizador *tok,
                                   struct token *token);
void tokenizador_processa_erro(struct tokenizador *tok,
                               struct token *token);

int
tokenizador_proximo(struct tokenizador *tok,
                    struct token *token) {
  while ( isspace(*(tok->entrada)) ) ++(tok->entrada);
  if ( *(tok->entrada) == '\0' ) return 0;
  if ( isdigit(*(tok->entrada)) ) {
    tokenizador_processa_numero(tok, token);
    return 1;
  } else if ( *(tok->entrada) == '+' || *(tok->entrada) == '-'
              || *(tok->entrada) == '*'
              || *(tok->entrada) == '/' ) {
    tokenizador_processa_operador(tok, token);
    return 1;
  } else if ( *(tok->entrada) == '('
              || *(tok->entrada) == ')' ) {
    tokenizador_processa_parentese(tok, token);
    return 1;
  } else {
    tokenizador_processa_erro(tok, token);
    return -1;
  }
}

void
tokenizador_processa_numero(struct tokenizador *tok,
                            struct token *token) {
  double valor = 0.0;
  token->tipo = numero;
  while (isdigit(*(tok->entrada))) {
    char digito = *(tok->entrada);
    valor = (digito - '0') + valor*10.0;
    ++(tok->entrada);
  }

  if (*(tok->entrada) == '.') {
    double potencia = 0.1;
    ++(tok->entrada);
    while (isdigit(*(tok->entrada))) {
      char digito = *(tok->entrada);
      valor += (digito - '0') * potencia;
      potencia /= 10;
      ++(tok->entrada);
    }
  }
  token->valor.numero = valor;
}

void
tokenizador_processa_operador(struct tokenizador *tok,
                              struct token *token) {
  token->tipo = operador;
  token->valor.operador = *(tok->entrada);
  ++(tok->entrada);
}

void
tokenizador_processa_parentese(struct tokenizador *tok,
                               struct token *token) {
  if (*(tok->entrada) == '(') {
    token->tipo = abre_parentese;
  } else {
    token->tipo = fecha_parentese;
  }
  token->valor.operador = *(tok->entrada);
  ++(tok->entrada);
}

void
tokenizador_processa_erro(struct tokenizador *tok,
                          struct token *token) {
  token->tipo = erro;
  ++(tok->entrada);
}
