#include "pilha.h"
#include <stdlib.h>
#include <string.h>

void pilha_inicializa(struct pilha *p, size_t tam_dado) {
  p->topo = NULL;
  p->tam_dado = tam_dado;
  p->comprimento = 0;
}

int pilha_push(struct pilha *p, void *dado) {
  struct no_pilha *novo = (struct no_pilha *)
                             malloc(sizeof(struct no_pilha));
  if (novo == NULL) return 0;
  novo->dado = malloc(p->tam_dado);
  if (novo->dado == NULL) {
    free(novo);
    return 0;
  }
  novo->prox = p->topo;
  memcpy(novo->dado, dado, p->tam_dado);
  p->topo = novo;
  ++p->comprimento;
  return 1;
}

int pilha_pop(struct pilha *p, void *dado) {
  struct no_pilha *antigo_topo;

  if (p->topo == NULL) return 0;
  memcpy(dado, p->topo->dado, p->tam_dado);
  antigo_topo = p->topo;
  p->topo = p->topo->prox;
  free(antigo_topo->dado);
  free(antigo_topo);
  --p->comprimento;
  return 1;
}

int pilha_vazia(struct pilha *p) {
  return (p->topo == NULL);
}

int pilha_topo(struct pilha *p, void *dado) {
  if (p->topo == NULL) return 0;
  memcpy(dado, p->topo->dado, p->tam_dado);
  return 1;
}

size_t pilha_comprimento(struct pilha *p) {
  return p->comprimento;
}
