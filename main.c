#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "website.h"

enum comando{ INSERIR_SITE = 0, REMOVER, INSERIR_PALAVRA, ATUALIZAR, SAIR};

void imprime_menu_complexo(){
    printf("Digite o comando desejado de acordo com a seguinte enumeração:\n");
    printf("\t[0] - Importar dados de um arquivo CSV\n");
    printf("\t[1] - Imprimir lista obtida pelo programa\n");
    printf("\t[2] - Inserir novo dado na lista\n");
    printf("\t[3] - Alterar valor de relevancia de um site\n");
    printf("\t[4] - Consultar elemento da lista\n");
    printf("\t[6] - Inserir palavra-chave de um site\n");
    printf("\t[7] - Remover um site da lista\n");
    printf("\t[8] - Sair do programa\n");
}

void imprime_menu(){
    printf("Digite o comando desejado de acordo com a seguinte enumeração\n");
    printf("\t[0] - Inserir um site na lista\n");
    printf("\t[1] - Remover um site da lista\n");
    printf("\t[2] - Inserir palavra-chave para um site\n");
    printf("\t[3] - Atualizar relevância de um site\n");
    printf("\t[4] - Sair\n");
}

void executa_comando(){
    int escolha = 0;
    
    while(1){
        printf("> Digite o código: ");
        scanf("%d", &escolha);
        if(escolha == SAIR) break;
        
        while(escolha < 0 || escolha > 5){
            printf("Por favor, escolha corretamente o comando desejado\n");
            imprime_menu();
            printf("> Digite o código: ");
            scanf("%d", &escolha);
        }

        // if(escolha == INSERIR_SITE)
        //     inserir_site();
        // else if(escolha == REMOVER)
        //     remover_site();
        // else if(escolha == INSERIR_PALAVRA)
        //     inserir_palavra();
        // else if(escolha == ATUALIZAR)
        //     atualizar_relevancia();
    }

}

int main(int argc, char *argv[]){
    printf("\nGOOGLE BOT\n\n");
    int escolha = 0;

    // imprime_menu();

    // executa_comando();

    return 0;
}