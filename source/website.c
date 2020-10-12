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

boolean website_deletar(WEBSITE **site){
    if(site == NULL){
        printf("Site não existe\n");
        return FALSE;
    }
    if(*site == NULL){
        printf("Site sem informações\n");
        return FALSE;
    }

    free((*site)->url);
    (*site)->url = NULL;

    free((*site)->nome);
    (*site)->nome = NULL;
    
    for(int i = 0; i < (*site)->num_palavras_chave; ++i){
        free((*site)->palavras_chaves[i]);
        (*site)->palavras_chaves[i] = NULL;
    }

    free((*site)->palavras_chaves);
    (*site)->palavras_chaves = NULL;
    
    free((*site));
    *site = NULL;

    return TRUE;
}

boolean website_insere_nome(WEBSITE *site, char *nome){
    
    if(site == NULL || nome == NULL){
        printf("Impossível inserir no campo nome: site ou nome inexistentes\n");
        return FALSE;
    }
    
    site->nome = nome;

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
        
    site->url = url;
    
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

boolean website_insere_codigo(WEBSITE *site, int codigo){

    if(site == NULL){
        printf("Website inexsitente\n");
        return FALSE;
    }
    site->codigo = codigo;
    return TRUE;
}

int website_consulta_codigo(WEBSITE *site){
    if(site == NULL){
        printf("Impossível buscar código do site (site inexistente)\n");
        return ERRO;
    }
    return site->codigo;
}

boolean website_insere_palavra_chave(WEBSITE *site, char *palavra_chave){   
    if(site == NULL || palavra_chave == NULL){
        printf("Impossível inserir palavra chave no site solicitado\n");
        return FALSE;
    }
    if(site->num_palavras_chave < 10){
        site->palavras_chaves = realloc(site->palavras_chaves, (site->num_palavras_chave + 1) * sizeof(char*));
        
        site->palavras_chaves[site->num_palavras_chave] = palavra_chave;    
        
        ++site->num_palavras_chave;
        
        return TRUE;
    }

    printf("Número de palavras chave não pode ser maior que 10\n");
    return FALSE;
}

int website_consulta_num_palavras_chave(WEBSITE *site){
    if(site == NULL){
        printf("Site inexistente, não é possível acessar o número de palavras chave\n");
        return FALSE;
    }
    return site->num_palavras_chave;
}

void mostrar_site(WEBSITE *site){
    if(site == NULL)
        printf("Site inexistente, não existe informações a serem mostradas.\n");
    else {
        printf("---------------------------------------------------------------");   
        printf("\nDados de %s:\n", site->nome);
        printf("Nome: %s\n", site->nome);
        printf("URL: %s\n", site->url);
        printf("Código: %d\n", site->codigo);
        printf("Relevância: %d\n", site->relevancia);
        printf("Palavras-chave:\n");
        
        for(int i = 0; i < site->num_palavras_chave; i++)
            printf("\t[%d] - %s\n", i, site->palavras_chaves[i]);
        printf("---------------------------------------------------------------\n");   
        
    }
    printf("\n");
}