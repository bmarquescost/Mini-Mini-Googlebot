#ifndef _LISTA_ENCADEADA_H_
#define _LISTA_ENCADEADA_H_

typedef struct _no NO;
typedef struct _lista LISTA;

#include "website.h"

LISTA *lista_criar();
boolean lista_deletar(LISTA **lista);

boolean lista_inserir(LISTA *lista, WEBSITE *site);

boolean lista_remover(LISTA *lista, int chave_removida);

WEBSITE *lista_busca(LISTA *lista, int codigo);
boolean lista_procurar_codigo(LISTA *lista, int codigo);

int lista_tamanho(LISTA *lista); 
boolean lista_vazia(LISTA *lista);
boolean lista_cheia(LISTA *lista);

void lista_mostrar(LISTA *lista);

#endif