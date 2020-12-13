#ifndef _TRIE_H_
#define _TRIE_H_


#define ALFABETO 26
typedef struct _trie TRIE;
typedef struct _no NO;

#include "util.h"
#include "palavras_chave.h"

TRIE *trie_criar(void);
void trie_deletar(TRIE **trie_deletada);
void trie_inserir_palavra(TRIE *trie, const char *palavra);
boolean trie_procurar_palavra(TRIE *trie, char *palavra);

TRIE *construir_trie_com_lista_sites(LISTA_SITES *l);


#endif