#include <stdio.h>
#include <stdlib.h>

#define TAM 128
#define TOKEN ','

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
                   
char *particiona_string_pelo_token(char *linha_inteira, int inicio){
    char *auxiliar;
    int final = inicio;
    
    while(linha_inteira[final] != TOKEN && linha_inteira[final] != '\0')
        ++final;

    int tamanho_auxiliar = final - inicio + 1;

    auxiliar = calloc(tamanho_auxiliar, sizeof(char));
    
    for(int i = inicio, j = 0; i < final; ++i, ++j)
        auxiliar[j] = linha_inteira[i]; 

    auxiliar[final] = '\0';

    return auxiliar;
}

char **leitura_csv(char *nome_csv, int *num_linhas){
    FILE *ponteiro_csv = NULL;
    printf("[%s]",nome_csv);
   
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

    return dados_csv;    
}

