#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <stdlib.h>

char *leitura_de_linha(FILE *stream);
char **leitura_csv(char *nome_csv, int *num_linhas);
char *particiona_string_pelo_token(char *linha_inteira, int inicio);

#endif