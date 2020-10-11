#ifndef _WEBSITE_H_
#define _WEBSITE_H_

#define boolean int
#define TRUE 1
#define FALSE 0
#define ERRO -32000

typedef struct _website WEBSITE;

WEBSITE *website_criar();
boolean website_insere_nome(WEBSITE *site, char *nome);
char *website_consulta_nome(WEBSITE *site);



#endif