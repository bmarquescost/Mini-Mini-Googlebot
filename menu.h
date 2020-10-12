#ifndef _MENU_H_
#define _MENU_H_

#include "listaencadeada.h"

void imprime_menu_complexo();
void executa_programa();
void imprime_menu();
boolean cria_site_insere_na_lista(LISTA *l, int codigo, char *nome,  char *url, int relevancia, char **pc, int n_pc);

#endif