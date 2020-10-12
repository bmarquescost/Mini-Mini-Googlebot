#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "website.h"
#include "util.h"
#include "menu.h"
#include "listaencadeada.h"

int main(int argc, char *argv[]){
    printf("______________________________________________________________\n");
    printf("\n\t\t\tGOOGLEBOT\n");
    printf("______________________________________________________________\n\n");
    printf("Obtendo dados do arquivo padrão inicial ...\n\n");    
    
    LISTA *lista_sites;
    lista_sites = lista_criar();
    preenche_lista_dados_csv(lista_sites, ARQUIVO_GOOGLEBOT);
    if(lista_sites != NULL) printf("Leitura de dados de Googlebot.txt bem sucedida.\n");
    
    executa_programa(lista_sites);

    lista_deletar(&lista_sites);

    return 0;
}