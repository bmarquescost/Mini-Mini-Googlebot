#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

struct _no {
    NO **nos_filhos;          // Vetor de filhos, com 26 filhos possíveis (números de letras do alfabeto) 
    boolean indicador_final;  // Indicador do final da string
};

struct _trie {
    NO *raiz;                 // Estrutura inicial com raiz inicial
};

/*
    Função privada _trie_criar_no:
    Constrói um nó para a trie
    Este nó é criado com 26 filhos, que apontam para nulo
*/
static NO *_trie_criar_no(void) {
    NO *novo_no = calloc(1, sizeof(NO));
    novo_no->nos_filhos = calloc(ALFABETO, sizeof(NO));

    return novo_no;
}

/*
    Função trie_criar:
    Instacia uma nova trie para ser utilizada
    Ja é criada com um nó raiz que possui 26 filhos, todos apontando para nulo
*/
TRIE *trie_criar(void) {
    TRIE *nova_trie = calloc(1, sizeof(TRIE));
    nova_trie->raiz = _trie_criar_no();

    return nova_trie;
}

/*
    Função privada _trie_deletar_recursiva:
    Realiza, a partir de um nó passado como parâmetro, a liberação de toda suas sub-árvore 
    Deleta também, o nó passado como parâmetro
*/
static void _trie_deletar_recursiva(NO **raiz) {
    if(*raiz == NULL) return;

    for(int i = 0; i < ALFABETO; ++i)
        _trie_deletar_recursiva(&(*raiz)->nos_filhos[i]);
    
    free((*raiz)->nos_filhos);
    (*raiz)->nos_filhos = NULL;
    free(*raiz);
    *raiz = NULL;
}

/*
    Função trie_deletar:
    Função de chamada para iniciar a deleção da trie inteira a parte de seu nó raiz
*/
void trie_deletar(TRIE **trie_deletada) {
    if(*trie_deletada == NULL)
        return;
    _trie_deletar_recursiva(&(*trie_deletada)->raiz);
    
    free(*trie_deletada);
    *trie_deletada = NULL;
}

/*
    Função privada _retornar_indice_trie:
    Retorna o índice de cada caractere em relação ao vetor de nós, correspondente ao intervalo 0-25
*/
static int _retornar_indice_trie(char caractere) {
    if(caractere >= 'a' && caractere <= 'z')
        return caractere - 'a';
    if(caractere >= 'A' && caractere <= 'Z')
        return caractere - 'A';
    
    return -1;
}

/*
    Função trie_insert_palavra
    Inserção de uma string na estrurura TRIE
    Funcionamento:
        A partir da raiz da arvore trie, para cada letra da cadeia de caracteres, verificamos qual o indice
        correspondente ao filho que este caractere representa (a partir da função _retornar_indice_trie)
        A partir disto, construimos (caso nao exista) ou percorremos (caso ja exista tal  caminho) pelos nós
        da árvore até o último caractere da palavra chave
        Neste passo final, acrescentamos um indicador de final de linha, indicando que a palavra se inicia desde a 
        raíz da árvore, até este nó em questão.

        O.B.S: 
        1. perceba que a profundidade da árvore trie corresponde à 1 mais a quantidade de caracteres da maior palavra-chave inserida
        2. não é possível criar caminhos que não façam parte do intervalo 0-25 quando subtraido de 'a' ou 'A' 
*/
void trie_inserir_palavra(TRIE *trie, const char *palavra) {
    int tamanho_string = strlen(palavra);

    NO *no_atual = trie->raiz;
    for(int i = 0; i < tamanho_string; ++i) {
        int indice = _retornar_indice_trie(palavra[i]);
       
        if(indice != -1) {
            if(no_atual->nos_filhos[indice] == NULL)
                no_atual->nos_filhos[indice] = _trie_criar_no();
            no_atual = no_atual->nos_filhos[indice];
        }
    }
    no_atual->indicador_final = TRUE;
}

/*
    Função trie_procurar_palavra:
    Verificação da existência de uma string na estrutura trie
    Para verificar se uma string existe, percorre um caminho nó a nó (cada nó correspondente a um caractere
    do alfabeto português), se existe tal caminho e se esta settado que é o fim da palavra, a string pertence
    ao dicionário.
*/
boolean trie_procurar_palavra(TRIE *trie, char *palavra) {
    int tamanho_string = strlen(palavra);

    NO *no_atual = trie->raiz;
    for(int i = 0; i < tamanho_string; ++i) {
        int indice = _retornar_indice_trie(palavra[i]);

        if(indice != -1) {
            if(no_atual->nos_filhos[indice] == NULL)
                return FALSE;
            no_atual = no_atual->nos_filhos[indice];
        }
    }

    return (no_atual != NULL && no_atual->indicador_final);
}

/*
    Função construir_trie_com_lista_sites:
    A função realiza a contruição de uma trie completa a partir de uma lista de sites
    Para cada site desta lista, percorremos o vetor de palavras-chave do site e acrescentamos tal palavra na trie
    criada
    Retornamos o ponteiro para a estrura trie que armazena, então, todas as palavras-chave dos sites da lista enviada 
*/
TRIE *construir_trie_com_lista_sites(LISTA_SITES *l) {
    if(l == NULL) return NULL;

    TRIE *palavras_chave = trie_criar();
    
    WEBSITE **websites = lista_sites_retorna_websites(l);

    for(int i = 0; i < lista_sites_consulta_num_sites(l); ++i) {
        char **palavras_do_site = website_consulta_palavras_chave(websites[i]);
        
        for(int j = 0; j < website_consulta_num_palavras_chave(websites[i]); ++j)
            trie_inserir_palavra(palavras_chave, palavras_do_site[j]);
    }

    return palavras_chave;
}