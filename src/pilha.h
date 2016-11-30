#ifndef PILHA_H
#define PILHA_H
#include <stdlib.h>

struct no_pilha {
  void *dado;
  struct no_pilha *prox;
};

struct pilha {
  struct no_pilha *topo;
  size_t tam_dado;
  size_t comprimento;
};

void pilha_inicializa(struct pilha *p, size_t tam_dado);

int pilha_push(struct pilha *p, void *dado);

int pilha_pop(struct pilha *p, void *dado);

int pilha_topo(struct pilha *p, void *dado);

int pilha_vazia(struct pilha *p);

size_t pilha_comprimento(struct pilha *p);

#endif
