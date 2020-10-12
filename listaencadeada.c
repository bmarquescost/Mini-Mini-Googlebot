#include <stdio.h>
#include <stdlib.h>

#include "listaencadeada.h"
#include "website.h"

typedef struct _no NO;

struct _no {
    WEBSITE *site; 
    NO *proximo;
};

struct _lista {
    NO* inicio;    
    int num_nos;
};

NO *criar_no(WEBSITE *site) {
    
    NO *no_novo = calloc(1,sizeof(NO));
    no_novo->site = site;
    no_novo->proximo = NULL;
    
    return no_novo;
}

boolean deletar_no(NO *no_deletado){
    if(no_deletado == NULL)
        return FALSE;
    
    website_deletar(&no_deletado->site);
    
    no_deletado->site = NULL;
    
    free(no_deletado);
    no_deletado = NULL;
    
    return TRUE;
}

LISTA *lista_criar(void) {
    LISTA *nova_lista = calloc(1, sizeof(LISTA));
   
    nova_lista->inicio = NULL;
    nova_lista->num_nos = 0;
    
    return nova_lista;
}

boolean lista_deletar(LISTA **lista) {
    if(lista == NULL){
        printf("Erro ao apagar lista (lista inexistente).\n");
        return FALSE;
    }
    if(*lista == NULL)
            free((*lista));
    
    else {
        NO *no_apagado = (*lista)->inicio;
        
        while(no_apagado != NULL) {
            (*lista)->inicio = no_apagado->proximo;
            deletar_no(no_apagado);
            
            no_apagado = (*lista)->inicio;
        }
        free(*lista);
    }
    return TRUE;
}

boolean lista_inserir(LISTA *lista, WEBSITE *site) {
    if(lista == NULL || site == NULL) {
        printf("Erro ao inserir site na lista (site ou lista inexistente).\n");
        return FALSE;
    }

    NO *no_novo = criar_no(site); 
    
    if(lista->num_nos == 0) {
        no_novo->proximo = lista->inicio;
        lista->inicio = no_novo;
    }

    else {
        NO *anterior = NULL;
        NO *atual = lista->inicio;
        
        int codigo_site = website_consulta_codigo(site);
        int codigo_atual = website_consulta_codigo(atual->site);
        
        while(atual != NULL && codigo_site > codigo_atual) {
            codigo_atual = website_consulta_codigo(atual->site);
            anterior = atual;
            atual = atual->proximo;
        }

        if(atual == lista->inicio) {
            no_novo->proximo = lista->inicio;
            lista->inicio = no_novo;
        }

        else {
            no_novo->proximo = anterior->proximo;
            anterior->proximo = no_novo;
        }
    }
    ++lista->num_nos;

    return TRUE;
}

boolean lista_remover(LISTA *lista, int codigo) {
    if(lista == NULL) {
        printf("Erro ao remover nó de uma lista (lista inexistente).\n");
        return FALSE;
    }
    
    NO *no_atual = lista->inicio;
    NO *no_anterior = NULL;
    
    int codigo_no;

    while(no_atual != NULL) {
        codigo_no = website_consulta_codigo(no_atual->site);        
        
        if(codigo_no == codigo) {
            if(no_anterior != NULL) no_anterior->proximo = no_atual->proximo;
            else lista->inicio = no_atual->proximo;
            
            website_deletar(&no_atual->site);
            free(no_atual);   
            --lista->num_nos;
            return TRUE; 
        }

        no_anterior = no_atual;
        no_atual = no_atual->proximo;
    }
    return FALSE;
}   

WEBSITE *lista_busca(LISTA *lista, int codigo) {
    if(lista == NULL) {
        printf("Erro ao buscar codigo em lista (lista vazia).\n");
        return NULL;
    }
    
    NO *auxiliar = lista->inicio;
    int codigo_no;
    while(auxiliar != NULL){
        codigo_no = website_consulta_codigo(auxiliar->site);
        if(codigo_no == codigo) break;
        auxiliar = auxiliar->proximo;
    }

    return auxiliar->site;
}   

boolean lista_procurar_codigo(LISTA *lista, int codigo){
    if(lista == NULL){
        printf("Lista inexistente, impossivel buscar a codigo\n");
        return FALSE;
    }
    
    NO *no_aux = lista->inicio;

    while (no_aux != NULL){
        if(codigo == website_consulta_codigo(no_aux->site))
            return TRUE;
        no_aux = no_aux->proximo;
    }

    return FALSE;    
}

int lista_tamanho(LISTA *lista){
    if(lista == NULL) {
        printf("Erro ao ler tamanho da lista (lista inexistente).\n");
        return ERRO;
    }

    return lista->num_nos;
}

boolean lista_vazia(LISTA *lista){
    if(lista == NULL) {
        printf("Erro ao verificar se a lista está vazia (lista inexistente).\n");
        return FALSE;
    }
    return  lista->num_nos == 0;
}

boolean lista_cheia(LISTA *lista){
    return FALSE; // Nunca é uma lista cheia, já que é alocada dinamicamente
}

void lista_mostrar(LISTA *l){
    if(l == NULL){
        return;
    }
    NO *aux = l->inicio;
    while(aux != NULL){
        mostrar_site(aux->site);    
        aux = aux->proximo;
    }
}
