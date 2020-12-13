#include <stdio.h>
#include <stdlib.h>

#include "palavras_chave.h"

#define QUANTIDADE_PADRAO 10


// Struct padrão que armazena uma lista de sites: sendo utilizada para ambas as funções extras
struct _lista_sites {
    WEBSITE **sites;   // Lista de sites
    int qtd_sites;     // Quantidade de sites na lista
    int multiplicador; // Auxiliar para realocaçäo da lista de sites (para que não seja necessário realocar memória a toda nova inserção de sites na lista)
};

/*
    Função lista_sites_criar:
    Inicia uma nova instancia de lista de sites
*/
LISTA_SITES *lista_sites_criar(void) {
    LISTA_SITES *nova_lista = calloc(1, sizeof(LISTA_SITES));
    
    nova_lista->sites = NULL;
    nova_lista->qtd_sites = 0;
    nova_lista->multiplicador = 1;

    return nova_lista;
}

/*
    Função lista_sites_deletar:
    Deleta uma lista de sites enviada como parâmetro para a função 
*/
void lista_sites_deletar(LISTA_SITES **lista_apagada) {
    if(*lista_apagada == NULL) return;

    free((*lista_apagada)->sites);
    (*lista_apagada)->sites = NULL;

    free(*lista_apagada);
    *lista_apagada = NULL;
}

/*
    Função lista_sites_inserir_site:
    A função insere um novo site passado como segundo parâmetro na lista de sites passada como
    primeiro parâmetro
*/
void lista_sites_inserir_site(LISTA_SITES *l, WEBSITE *site) {
    if(l == NULL || site == NULL) return;

    if(l->qtd_sites % QUANTIDADE_PADRAO == 0) {
        long int tamanho = QUANTIDADE_PADRAO * (++(l->multiplicador) * sizeof(WEBSITE *));
        l->sites = realloc(l->sites, tamanho);
    }

    l->sites[l->qtd_sites] = site;
    ++l->qtd_sites;
}

/*
    Função lista_sites_consulta_num_sites:
    Retorna o inteiro correspondente ao número de sites que aquela lista, enviada como parâmetro, armazena
*/
int lista_sites_consulta_num_sites(LISTA_SITES *l) {
    if(l == NULL) return ERRO;

    return l->qtd_sites;
}

/*
    Função printar_lista_encontrada:
    Função que printa os sites encontrados, mostrando o nome de cada site, sua relevância e sua URL
*/
void printar_lista_encontrada(LISTA_SITES *sites_encontrados){
    if(sites_encontrados == NULL) return;

    if(sites_encontrados->qtd_sites == 0 || sites_encontrados->sites == NULL) 
        return;
    
    printf("\n+---------------------------------------------------------------+\n");
    for(int i = 0; i < sites_encontrados->qtd_sites ; ++i) {
        printf("| [%d] %s\n", i, website_consulta_nome(sites_encontrados->sites[i]));
        printf("|\tRelevância: %d \n|\tURL: %s\n",  website_consulta_relevancia(sites_encontrados->sites[i]), website_consulta_url(sites_encontrados->sites[i]));
        if(i + 1 != sites_encontrados->qtd_sites) printf("|\n");
    }
    
    printf("+---------------------------------------------------------------+\n");

}

/*
    Função lista_sites_retorna_websites:
    A partir de uma lista de sites dada como parâmetro, retorna o ponteiro para a lista de websites
    A função é útil para que outras funções necessárias em outros arquivos tenham acesso a lista de sites sem
    quebrar a estruturação do TAD LISTA_SITES 
*/
WEBSITE **lista_sites_retorna_websites(LISTA_SITES *lista) {
    if(lista == NULL) return NULL;

    return lista->sites;
}

/*
    Função min_heapify:
    Posiciona o nó de menor valor no final da lista, de forma a criar uma estrutura de min heap
    Utilizada como auxiliar para o algoritmo de ordenação heapsort
*/
static void min_heapify(WEBSITE **s, int indice, int n) {
    
    int menor = indice;
    int filho_esquerda = indice * 2 + 1; 
    int filho_direita = indice * 2 + 2;
    
    
    if(filho_esquerda < n && website_consulta_relevancia(s[filho_esquerda]) < website_consulta_relevancia(s[menor])) 
        menor = filho_esquerda;
    
    if(filho_direita < n && website_consulta_relevancia(s[filho_direita]) < website_consulta_relevancia(s[menor])) 
        menor = filho_direita;
        
    if(menor != indice) {
        WEBSITE *tmp = s[indice];
        s[indice] = s[menor];
        s[menor] = tmp;

        min_heapify(s, menor, n);
    }

}

/*
    Função heapsort:
    Algoritmo de ordenação de complexidade O(n log n) que realiza a ordenação com base na comparação e criação
    de vetores com propriedades de heap
    Realiza a ordenação decrescente (neste caso)
*/
static void heapsort(WEBSITE **s, int n) {
    for(int i = n/2 - 1; i >= 0; --i)
        min_heapify(s, i, n);

    for(int i = n - 1; i >= 0; --i){
        WEBSITE *tmp = s[0];
        s[0] = s[i];
        s[i] = tmp;

        min_heapify(s, 0, i);
    }
}

/*
    Função lista_sites_ordenar:
    Realiza a ordenação decrescente por relevância dos sites, ordenando a partir do algoritmo heapsort, a lista de sites
    enviada como parâmetro
*/
void lista_sites_ordenar(LISTA_SITES *lista_sites) {
    if(lista_sites == NULL) return;

    heapsort(lista_sites->sites, lista_sites->qtd_sites);
}
