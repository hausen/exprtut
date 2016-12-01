#include "parser.h"
#include "pilha.h"

int parser_precedencia(char operador) {
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

/* SE token é um operador o1 ENTÃO... */
int parser_processa_operador(struct token *op1,
                             struct pilha *saida,
                             struct pilha *operadores) {
  struct token op2;
  /* ENQUANTO existe operador o2 no topo da pilha de
              operadores
              E precedência de o1 ≤ precedência de o2 FAÇA */
  while ( pilha_topo(operadores, &op2)
          && parser_precedencia(op1->valor.operador) 
             <= parser_precedencia(op2.valor.operador) ) {
    /* remove o2 do topo da pilha de operadores */
    pilha_pop(operadores, &op2);
    /* insere o2 no topo da pilha de saída */
    pilha_push(saida, &op2);
  }
  /* insere token o1 no topo da pilha de operadores */
  pilha_push(operadores, op1);
  return 1;
}

/* SE token é parêntese direito ")" ENTÃO */
int parser_processa_fp(struct pilha *saida,
                       struct pilha *operadores) {
  struct token op;
  /* ENQUANTO topo da pilha de operadores não é um
              parêntese esquerdo FAÇA */
  while ( pilha_topo(operadores, &op) &&
          op.tipo != abre_parentese ) {
    /* remove operador do topo da pilha de operadores */
    pilha_pop(operadores, &op);
    /* insere operador no topo da pilha de saída */
    pilha_push(saida, &op);
  }

  /* SE pilha de operadores está vazia ENTÃO */
  if (pilha_vazia(operadores)) {
    /* ERRO */
    return 0;
  }
  /* remove parêntese esquerdo da pilha de operadores */
  pilha_pop(operadores, &op);
  return 1;
}

void parser_limpa(struct pilha *pilha) {
  struct token tok;
  while (!pilha_vazia(pilha)) {
    pilha_pop(pilha, &tok);
  }
}

void parser_inicializa(struct parser *parser) {
  parser->tokens = NULL;
  parser->ntokens = 0;
  parser->erro = NULL;
}

int parser_parse(struct parser *parser, const char *expr) {
  struct tokenizador t;
  struct token tok;
  struct pilha saida;
  struct pilha operadores;
  size_t comprimento;

  if (parser->tokens != NULL) {
    free(parser->tokens);
  }
  parser_inicializa(parser);

  pilha_inicializa(&saida, sizeof(struct token));
  pilha_inicializa(&operadores, sizeof(struct token));

  tokenizador_inicializa(&t, expr);

  /* PARA CADA token na entrada FAÇA */
  while (tokenizador_proximo(&t, &tok) > 0) {
#ifdef DEBUG
    token_imprime(&tok, stderr); fprintf(stderr, " ");
#endif
    switch(tok.tipo) {
    /* SE token é número ENTÃO */
    case numero:
      /* insere token no topo da pilha de saída */ 
      pilha_push(&saida, &tok);
    break;
    /* SE token é um operador o1 ENTÃO... */
    case operador:
      /* (veja função parser_processa_operador) */
      parser_processa_operador(&tok, &saida, &operadores);
    break;
    /* SE token é parêntese esquerdo "(" ENTÃO */
    case abre_parentese:
      /* insere token no topo da pilha de operadores */
      pilha_push(&operadores, &tok);
    break;
    /* SE token é parêntese direito ")" ENTÃO... */
    case fecha_parentese:
      /* (veja função parser_processa_fp) */
      if (parser_processa_fp(&saida, &operadores) == 0) {
        /* limpa pilhas em caso de erro */
        parser->erro = "parentese descasado";
        parser_limpa(&saida);
        parser_limpa(&operadores);
        return 0;
      }
    break;
    default:
      /* token não reconhecido é um erro */
      parser->erro =
              "token nao identificado";
      token_imprime(&tok, stderr);
      parser_limpa(&saida);
      parser_limpa(&operadores);
      return 0;
    }
  }

  /* ENQUANTO pilha de operadores não vazia FAÇA */
  while (!pilha_vazia(&operadores)) {
    struct token tok;
    /* remove operador do topo da pilha de operadores */
    pilha_pop(&operadores, &tok);
    /* SE operador é parêntese ENTÃO */
    if (tok.tipo == abre_parentese ||
        tok.tipo == fecha_parentese) {
      /* ERRO */
      parser->erro = "parentese descasado";
      parser_limpa(&saida);
      parser_limpa(&operadores);
      return 0;
    }
    /* insere operador no topo da pilha de saída */
    pilha_push(&saida, &tok);
  }

  comprimento = pilha_comprimento(&saida);
  parser->tokens = (struct token *)malloc((comprimento)*
                                   sizeof(struct token));
  if (parser->tokens == NULL) {
    parser->erro = "falta de memoria";
    return 0;
  }
  parser->ntokens = comprimento;
  while(comprimento > 0) {
    --comprimento;
    pilha_pop(&saida, &(parser->tokens[comprimento]));
  }
  return 1;
}

void parser_finaliza(struct parser *parser) {
  if (parser->tokens != NULL) {
    free(parser->tokens);
  }
  parser->tokens = NULL;
  parser->ntokens = 0;
  parser->erro = NULL;
}
