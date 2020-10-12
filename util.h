#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <stdlib.h>

#include "listaencadeada.h"

char *leitura_de_linha(FILE *stream);
char **leitura_csv(char *nome_csv, int *num_linhas);
char *particiona_string_pelo_token(char *linha_inteira, int inicio, boolean *acabou);
WEBSITE *cria_website_pelos_dados(char *linha_inteira);
void preenche_lista_dados_csv(LISTA *l);

#endif