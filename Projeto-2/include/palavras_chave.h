#ifndef _PALAVRAS_CHAVE_H_
#define _PALAVRAS_CHAVE_H_

typedef struct _lista_sites LISTA_SITES;
typedef struct _sugestoes SUGESTOES;
typedef struct _mesmas_palavra_chave MSM_PALAVRA;

#define NUMERO_SUGESTOES  5

#include "website.h"
#include "trie.h"

LISTA_SITES *lista_sites_criar(void);
void lista_sites_deletar(LISTA_SITES **sites);
void lista_sites_inserir_site(LISTA_SITES *sites_encontrados, WEBSITE *site);
void lista_sites_ordenar(LISTA_SITES *lista_sites);
void printar_lista_encontrada(LISTA_SITES *sites_encontrados, int num_sites);
int lista_sites_consulta_num_sites(LISTA_SITES *l);
WEBSITE **lista_sites_retorna_websites(LISTA_SITES *lista);

#endif
