#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "website.h"
#include "util.h"

struct _website {
    char *nome;
    char *url;
    char **palavras_chaves;
    int codigo;
    int relevancia;
    int num_palavras_chave;
};

WEBSITE *website_criar(){
    WEBSITE *novo_site = NULL;
    novo_site = calloc(1,sizeof(WEBSITE));

    novo_site->codigo = 0;
    novo_site->url = NULL;
    novo_site->palavras_chaves = NULL;
    novo_site->relevancia = 0;
    novo_site->nome = NULL;
    novo_site->num_palavras_chave = 0;

    return novo_site;
}

boolean website_insere_nome(WEBSITE *site, char *nome){
    
    if(site == NULL || nome == NULL){
        printf("Impossível inserir no campo nome: site ou nome inexistentes\n");
        return FALSE;
    }

    int tamanho_nome = strlen(nome) + 1;
    site->nome = calloc(tamanho_nome, sizeof(char));

    for(int i = 0; i < tamanho_nome; ++i)
        site->nome[i] = nome[i];
    
    if(site->nome == NULL) return FALSE;
    
    return TRUE;
}

char *website_consulta_nome(WEBSITE *site){
    if(site == NULL){
        printf("Impossível encontrar nome: site inexistente\n");
        return NULL;
    }

    return site->nome;
}

boolean website_insere_url(WEBSITE *site, char *url){
    if(site == NULL || url == NULL){
        printf("Impossível inserir no campo url: site ou url inexistentes\n");
        return FALSE;
    }

    int tamanho_url = strlen(url) + 1;
    site->url = calloc(tamanho_url, sizeof(char));

    for(int i = 0; i < tamanho_url; ++i)
        site->url[i] = url[i];
    
    if(site->url == NULL) return FALSE;
    
    return TRUE;
}

char *website_consulta_url(WEBSITE *site){
    if(site == NULL){
        printf("Impossível encontrar url: site inexistente\n");
        return NULL;
    }

    return site->url;
}

boolean website_insere_relevancia(WEBSITE *site, int relevancia){
    if(site == NULL){
        printf("Impossível inserir no campo relevancia: site inexistente");
        return FALSE;
    }
    site->relevancia = relevancia;
    return TRUE;
}

int website_consulta_relevancia(WEBSITE *site){
    if(site == NULL){
        printf("Impossível encontrar relevância: site inexistente\n");
        return FALSE;
    }
    return site->relevancia;
}

