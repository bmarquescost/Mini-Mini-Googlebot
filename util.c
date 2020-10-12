#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listaencadeada.h"
#include "website.h"
#include "util.h"

#define TAM 128
#define TOKEN ','
#define ARQUIVO_GOOGLEBOT "googlebot.txt"

char *leitura_de_linha(FILE *stream){
    char *linha = NULL;
    int pos = 0, multi = 1;
    char caractere;
    do{
        if(pos % TAM == 0) linha = realloc(linha, (multi++)*TAM); 
        caractere = (int) fgetc(stream);
        if(caractere != '\r') {
            linha[pos] = caractere;
            pos++;
        }
    }while(caractere != '\n' && !feof(stream)); 

    linha = realloc(linha, pos);
    
    linha[pos - 1] = '\0'; 
    
    return linha;
}

char *particiona_string_pelo_token(char *linha_inteira, int inicio, boolean *acabou){
    
    int final = inicio;    

    while(linha_inteira[final] != TOKEN && linha_inteira[final] != '\0')
        final++;

    if(linha_inteira[final] == '\0') *acabou = TRUE;

    int tamanho_auxiliar = final - inicio + 1;

    char *auxiliar = calloc(tamanho_auxiliar, sizeof(char));
    
    for(int i = inicio, j = 0; i < final; ++i, ++j)
        auxiliar[j] = linha_inteira[i]; 

    return auxiliar;
}

WEBSITE *cria_website_pelos_dados(char *linha_inteira){
    
    if(linha_inteira == NULL) return NULL;

    WEBSITE *novo_site = website_criar();
    
    int inicio = 0;
    boolean final_da_linha = FALSE;
    
    
    char *codigo_string = particiona_string_pelo_token(linha_inteira, inicio, &final_da_linha);
    inicio += strlen(codigo_string) + 1;
    int codigo = atoi(codigo_string);
    website_insere_codigo(novo_site, codigo);


    char *nome = particiona_string_pelo_token(linha_inteira, inicio, &final_da_linha);
    inicio += strlen(nome) + 1;
    website_insere_nome(novo_site, nome);

    char *relevancia_string = particiona_string_pelo_token(linha_inteira, inicio, &final_da_linha);
    inicio += strlen(relevancia_string) + 1;
    int relevancia = atoi(relevancia_string);

    website_insere_relevancia(novo_site, relevancia);
    
    char *url = particiona_string_pelo_token(linha_inteira, inicio, &final_da_linha);
    inicio += strlen(url) + 1;
    website_insere_url(novo_site, url);
    
    int num_chaves = 0;
    char **palavras_chaves = NULL;
    
    while(final_da_linha == FALSE && num_chaves < 10){
        
        palavras_chaves = realloc(palavras_chaves,(num_chaves+1) * sizeof(char*));
        palavras_chaves[num_chaves] = particiona_string_pelo_token(linha_inteira, inicio, &final_da_linha);
        
        website_insere_palavra_chave(novo_site, palavras_chaves[num_chaves]);
        
        inicio += strlen(palavras_chaves[num_chaves]) + 1;
        ++num_chaves;
    }    

    free(codigo_string);
    free(relevancia_string);

    return novo_site;
}

char **leitura_csv(char *nome_csv, int *num_linhas){
    
    FILE *ponteiro_csv = NULL;
    
    printf("Realizando a leitura do arquivo %s\n",nome_csv);
   
    if(!(ponteiro_csv = fopen(nome_csv, "r"))){
        printf("Erro na abertura do arquivo CSV\n");
        exit(1);
    }
    
    char caracter;
    int numero_linhas = 0;
    while(!feof(ponteiro_csv)){
        caracter = fgetc(ponteiro_csv);
        if(caracter == '\n') 
            ++numero_linhas;
    }

    char **dados_csv = NULL;
    dados_csv = calloc(numero_linhas, sizeof(char* ));
    
    fseek(ponteiro_csv, 0, SEEK_SET);

    for(int i = 0;i < numero_linhas; ++i)
        dados_csv[i] = leitura_de_linha(ponteiro_csv);

    *num_linhas = numero_linhas;
    
    fclose(ponteiro_csv);
    
    return dados_csv;    
}

void preenche_lista_dados_csv(LISTA *l){
    if(l == NULL) return;
    
    int num_linhas = 0;
    char **dados_csv = leitura_csv(ARQUIVO_GOOGLEBOT, &num_linhas);
    
    WEBSITE *site_auxiliar;

    for(int i = 0; i < num_linhas; ++i){
        site_auxiliar = cria_website_pelos_dados(dados_csv[i]);
        if(lista_procurar_codigo(l, website_consulta_codigo(site_auxiliar))){
            printf("!! Leitura de codigos semelhantes no arquivo CSV !!\n");
            website_deletar(&site_auxiliar);
        }
        
        else lista_inserir(l, site_auxiliar);
    }
        
    for(int i = 0; i < num_linhas; ++i)
        free(dados_csv[i]);
    free(dados_csv);
}