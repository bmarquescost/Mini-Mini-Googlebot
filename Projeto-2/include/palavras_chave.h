#ifndef _PALAVRAS_CHAVE_H_
#define _PALAVRAS_CHAVE_H_

#include "website.h"

typedef struct _palavras_chave PALAVRAS_CHAVE;

PALAVRAS_CHAVE *palavras_chave_criar(void);

void palavras_chave_deletar(PALAVRAS_CHAVE **sites_encontrados);

void palavras_chave_alterar_palavra(PALAVRAS_CHAVE *lista, char *palavra_chave);

void palavras_chave_inserir_site(PALAVRAS_CHAVE *palavra_chave, WEBSITE *site_encontrado);

void printar_lista_encontrada(PALAVRAS_CHAVE *sites_encontrados);

void palavras_chave_ordenar(PALAVRAS_CHAVE *sites_encontrados);





#endif
