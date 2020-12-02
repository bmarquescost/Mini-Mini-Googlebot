#include <stdio.h>
#include <stdlib.h>

#include "palavras_chave.h"

#define QUANTIDADE_PADRAO 10

struct _palavras_chave {
    WEBSITE **lista_de_sites;
    int num_sites;
    int multiplicador;
    char *palavra_chave;
};

PALAVRAS_CHAVE *palavras_chave_criar() {
    PALAVRAS_CHAVE *nova_lista = calloc(1, sizeof(PALAVRAS_CHAVE));

    nova_lista->lista_de_sites = calloc(QUANTIDADE_PADRAO, sizeof(WEBSITE *));
    nova_lista->num_sites = 0;
    nova_lista->palavra_chave = NULL;
    nova_lista->multiplicador = 1;

    

    return nova_lista;
}

void palavras_chave_deletar(PALAVRAS_CHAVE **sites_encontrados) {
    for(int i = 0; i < (*sites_encontrados)->num_sites ; ++i) {
        free((*sites_encontrados)->lista_de_sites[i]);
        (*sites_encontrados)->lista_de_sites[i] = NULL;
    }

    (*sites_encontrados)->palavra_chave = NULL;
    free(*sites_encontrados);
    *sites_encontrados = NULL;
}

void palavras_chave_alterar_palavra(PALAVRAS_CHAVE *lista, char *palavra_chave) {
    if(lista == NULL || palavra_chave == NULL) return;

    lista->palavra_chave = palavra_chave;
}

void palavras_chave_inserir_site(PALAVRAS_CHAVE *palavra_chave, WEBSITE *site_encontrado) {
    if(palavra_chave == NULL || site_encontrado == NULL) return;

    if(palavra_chave->num_sites % QUANTIDADE_PADRAO == 0) {
        long int tamanho = QUANTIDADE_PADRAO*(++(palavra_chave->multiplicador)*sizeof(WEBSITE *));
        palavra_chave->lista_de_sites = realloc(palavra_chave->lista_de_sites, tamanho);
    }

    palavra_chave->lista_de_sites[palavra_chave->num_sites] = site_encontrado;
    ++palavra_chave->num_sites;
}

void printar_lista_encontrada(PALAVRAS_CHAVE *sites_encontrados){
    if(sites_encontrados == NULL) return;

    if(sites_encontrados->num_sites == 0 || sites_encontrados->lista_de_sites == NULL) {
        printf("Nenhum site encontrado!\n");
        return;
    }

    printf("Os sites encontrados com a palavra-chave %s são:\n", sites_encontrados->palavra_chave);
    for(int i = 0; i < sites_encontrados->num_sites ; ++i) {
        printf("%s - %d\n", website_consulta_nome(sites_encontrados->lista_de_sites[i]), website_consulta_relevancia(sites_encontrados->lista_de_sites[i]));
    }
}

static void min_heapify(PALAVRAS_CHAVE *s, int indice, int n) {
    int menor = indice;

    int filho_esquerda = (indice*2) + 1; 
    int filho_direita = (indice*2) + 2;

    if(filho_esquerda < n && website_consulta_relevancia(s->lista_de_sites[filho_esquerda]) < website_consulta_relevancia(s->lista_de_sites[menor]))
        menor = filho_esquerda;
    
    if(filho_direita < n && website_consulta_relevancia(s->lista_de_sites[filho_direita]) < website_consulta_relevancia(s->lista_de_sites[menor]))
        menor = filho_direita;
    
    if(menor != indice) {
        WEBSITE *tmp = s->lista_de_sites[indice];
        s->lista_de_sites[indice] = s->lista_de_sites[menor];
        s->lista_de_sites[menor] = tmp;

        min_heapify(s, menor, n);
    }

}

static void heapsort(PALAVRAS_CHAVE *s, int n) {
    for(int i = n/2 - 1; i >= 0; --i)
        min_heapify(s, i, n);

    for(int i = n - 1; i >= 0; --i){
        WEBSITE *tmp = s->lista_de_sites[0];
        s->lista_de_sites[0] = s->lista_de_sites[i];
        s->lista_de_sites[i] = tmp;
    }
}

void palavras_chave_ordenar(PALAVRAS_CHAVE *sites_encontrados) {
    if(sites_encontrados == NULL) return;

    heapsort(sites_encontrados, sites_encontrados->num_sites);
    
}
