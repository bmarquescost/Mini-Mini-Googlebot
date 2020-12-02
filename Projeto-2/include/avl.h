/*
    SCC0202 - ALGORITMOS E ESTRUTURAS DE DADOS I
    Docente: Rudinei Goularte 

    Aluno: Bernardo Marques Costa                    Número USP: 11795551
    Aluno: Fernando Henrique Paes Generich           Número USP: 11795342

    MINI GOOGLEBOT 
*/

#ifndef _AVL_H_
#define _AVL_H_

#include "website.h"
#include "palavras_chave.h"

typedef struct _no NO;
typedef struct _avl AVL;

AVL *avl_criar(void);
void avl_deletar(AVL **arvore);
int avl_altura(NO *no);
boolean avl_inserir_site(AVL *arvore, WEBSITE *site);
boolean avl_procurar_codigo(AVL *arvore, int codigo);
boolean avl_remover_site(AVL *arvore, int codigo);
WEBSITE *avl_buscar_site(AVL *arvore, int codigo);
boolean avl_vazia(AVL *arvore);
void avl_imprimir_em_ordem(AVL *arvore);
void avl_imprimir_pre_ordem(AVL *arvore);
int avl_num_sites(AVL *arvore);
PALAVRAS_CHAVE *avl_buscar_palavra_chave( AVL *arvore, char *palavra_chave);

#endif
