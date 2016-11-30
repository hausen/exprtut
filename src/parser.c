#include "parser.h"
#include "pilha.h"

int precedencia(char operador) {
  switch(operador) {
  case '*':
  case '/':
    return 3;
  case '+':
  case '-':
    return 2;
  case '(':
    return 0;
  }
  return -1;
}

int processa_operador(struct token *op1,
                      struct pilha *saida,
                      struct pilha *operadores) {
  struct token op2;
  while ( pilha_topo(operadores, &op2)
          && precedencia(op1->valor.operador) 
             <= precedencia(op2.valor.operador) ) {
    pilha_pop(operadores, &op2);
    pilha_push(saida, &op2);
  }
  pilha_push(operadores, op1);
  return 1;
}

int processa_fecha_parentese(struct pilha *saida,
                             struct pilha *operadores) {
  struct token op;
  while ( pilha_topo(operadores, &op) &&
          op.tipo != abre_parentese ) {
    pilha_pop(operadores, &op);
    pilha_push(saida, &op);
  }

  if (pilha_vazia(operadores)) {
    fprintf(stderr, "Unmatched parenthesis!\n");
    return 0;
  }
  pilha_pop(operadores, &op);
  return 1;
}

void limpa(struct pilha *pilha) {
  struct token tok;
  while (!pilha_vazia(pilha)) {
    pilha_pop(pilha, &tok);
  }
}

/* teste com "3 + 4 * 2 / ( 1 - 5 ) * 2 + 3" */
struct token *parse(const char *expr) {
  struct tokenizador t;
  struct token tok;
  struct pilha saida;
  struct pilha operadores;
  struct token *retorno;
  size_t comprimento;

  pilha_inicializa(&saida, sizeof(struct token));
  pilha_inicializa(&operadores, sizeof(struct token));

  tokenizador_inicializa(&t, expr);

  while (tokenizador_proximo(&t, &tok) > 0) {
#ifdef DEBUG
    token_imprime(&tok, stderr); fprintf(stderr, " ");
#endif
    switch(tok.tipo) {
    case numero:
      pilha_push(&saida, &tok);
    break;
    case operador:
      processa_operador(&tok, &saida, &operadores);
    break;
    case abre_parentese:
      pilha_push(&operadores, &tok);
    break;
    case fecha_parentese:
      if (processa_fecha_parentese(&saida, &operadores) == 0) {
        limpa(&saida);
        limpa(&operadores);
        return NULL;
      }
    break;
    default:
      fprintf(stderr,
              "ERRO FATAL! Token nao identificado!\n");
      token_imprime(&tok, stderr);
      limpa(&saida);
      limpa(&operadores);
      return NULL;
    }
  }

  while (!pilha_vazia(&operadores)) {
    struct token tok;
    pilha_pop(&operadores, &tok);
    if (tok.tipo == abre_parentese ||
        tok.tipo == fecha_parentese) {
      fprintf(stderr, "Parentese descasado!\n");
      limpa(&saida);
      limpa(&operadores);
      return NULL;
    }
    pilha_push(&saida, &tok);
  }

  comprimento = pilha_comprimento(&saida);
  retorno = (struct token *)malloc((comprimento+1)*
                                   sizeof(struct token));
  retorno[comprimento].tipo = fim;
  while(comprimento > 0) {
    --comprimento;
    pilha_pop(&saida, &retorno[comprimento]);
  }
  return retorno;
}
