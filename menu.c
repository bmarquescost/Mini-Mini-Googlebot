#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "website.h"
#include "util.h"
#include "listaencadeada.h"

enum comando { INSERIR_SITE = 0, REMOVER, INSERIR_PALAVRA, ATUALIZAR_RELEVANCIA, MOSTRA_LISTA, SAIR};

void imprime_menu(){
    printf("\n_______________________________________________________________\n");
    printf("Digite o comando desejado de acordo com a seguinte enumeração\n");
    printf("\t[0] - Inserir um site na lista\n");
    printf("\t[1] - Remover um site da lista\n");
    printf("\t[2] - Inserir palavra-chave para um site\n");
    printf("\t[3] - Atualizar relevância de um site\n");
    printf("\t[4] - Mostrar a lista obtida ate agora\n");
    printf("\t[5] - Sair\n");
    printf("_______________________________________________________________\n");
}

boolean cria_site_insere_na_lista(LISTA *l, int codigo, char *nome,  char *url, int relevancia, char **pc, int n_pc){
    if(l == NULL) {
        printf("Lista inexistente\n");
        return FALSE;
    }
    WEBSITE *novo_site = website_criar();
    
    boolean inseriu_codigo = website_insere_codigo(novo_site, codigo);
    boolean inseriu_nome = website_insere_nome(novo_site, nome);
    boolean inseriu_relevancia = website_insere_relevancia(novo_site, relevancia);
    boolean inseriu_url = website_insere_url(novo_site, url);
    boolean inseriu_pc = FALSE;
    
    for(int i = 0; i < n_pc; ++i)
       inseriu_pc += website_insere_palavra_chave(novo_site, pc[i]);

    int inseriu_site = inseriu_codigo + inseriu_nome + inseriu_relevancia + inseriu_url + inseriu_pc;
    if(inseriu_site == n_pc + 4){
        lista_inserir(l, novo_site);
        return TRUE;
    }

    return FALSE;

}

void inserir_site(LISTA *lista){
    printf("\n\nVocê escolheu inserir um novo site\n");
    printf("Digite o código do site: ");
    
    int codigo;
    scanf("%d", &codigo);
    getchar();
    
    while(lista_procurar_codigo(lista, codigo)){
        printf("Código já existente, não é possível adicionar site com mesmo código.\n");
        printf("Digite um novo código (ou digite -1 para cancelar a inserção): ");
        scanf("%d", &codigo);
        getchar();    
        if(codigo == -1) return;
    }

    while(codigo <= 0){
        printf("O codigo deve ser um número maior que 0.\n");
        printf("Digite novamente (ou digite -1 para cancelar a inserção):   ");
        scanf("%d", &codigo);
        getchar();
        if(codigo == -1) return;
    }


    printf("Digite o nome do site que será inserido: ");
    char *nome = leitura_de_linha(stdin);

    printf("Digite agora a url do site: ");
    char *url = leitura_de_linha(stdin);

    printf("Digite a relevância do site (deve ser entre 0 e 1000): ");
    int relevancia;
    scanf("%d", &relevancia);
    getchar();
    
    while(relevancia < 0 && relevancia > 1000){
        printf("Por favor, digite uma relevancia entre 0 e 1000\n.");
        scanf("%d", &relevancia);
        getchar();
    }

    printf("Quantas palavras chave irá relacionar a este site? ");
    int num_palavras_chave;
    scanf("%d", &num_palavras_chave);
    getchar();
    
    if(num_palavras_chave > 10) printf("O número máximo de palavras chaves permitido é de 10, permitiremos então 10 palavras\n");
    char **palavras_chaves = calloc(num_palavras_chave, sizeof(char*));
    
    for(int i = 0; i < num_palavras_chave; ++i){ 
        printf("> [%d]: ", i);
        palavras_chaves[i] = leitura_de_linha(stdin);
        printf("\n");
    }

    boolean site_inserido = cria_site_insere_na_lista(lista, codigo, nome, url, relevancia, palavras_chaves, num_palavras_chave);

    if(site_inserido) 
        printf("Inserção bem sucedida!\n");
    
    else {
        printf("Algum erro ocorreu durante a inserção do site.\n");
        printf("Algum dado pode ter sido perdido.\n");
    }
    
    WEBSITE* s = lista_busca(lista,codigo);
    mostrar_site(s);
    printf("\n");
    
    /*
    free(nome);
    
    for(int i = 0; i < num_palavras_chave; ++i)
        free(palavras_chaves[i]);
    
    free(palavras_chaves);
    free(url);
    */
}

void remover_site(LISTA *lista){
    printf("\n\nVocê escolheu remover um site da lista\n");
    printf("Digite o código do site que deseja remover: ");
    int codigo;
    scanf("%d", &codigo);

    if(lista_remover(lista, codigo)){
        printf("Site removido com sucesso.\n");
        return;
    }
    printf("Erro ao remover site: código não encontrado\n");
    printf("\n");
}

void inserir_palavra_chave(LISTA *lista){
    printf("Você selecionou inserir uma palavra-chave\n");
    printf("Digite qual o código do site em que deseja inserir a nova palavra\n");
    int codigo;
    scanf("%d", &codigo);
    
}

void executa_programa(LISTA *lista){
    int escolha = 0;
    imprime_menu();
    while(1){
        printf("> Digite o comando: ");
        scanf("%d", &escolha);
        
        
        while(!(escolha >= 0 || escolha <= 5)){
            printf("Por favor, escolha corretamente o comando desejado\n");
            imprime_menu();
            printf("> Digite o comando: ");
            scanf("%d", &escolha);
        }

        if(escolha == INSERIR_SITE)
           inserir_site(lista);
        
        
        else if(escolha == REMOVER)
            remover_site(lista);
        
        else if(escolha == INSERIR_PALAVRA)
            inserir_palavra(lista);
        
        /*
        else if(escolha == ATUALIZAR_RELEVANCIA)
             atualizar_relevancia(lista);
        */

        else if(escolha == MOSTRA_LISTA)
            lista_mostrar(lista);

        else if(escolha == SAIR) 
            break;
    }

    lista_mostrar(lista);

}