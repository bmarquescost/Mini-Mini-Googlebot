# PROJETO MINI GOOGLE BOT - PARTE 2

## Planejamento
Pensamos em mudar a estrutura geral para uma árvore AVL, que guardaria de maneira ordenada e balanceada todos os sites que são inseridos.
As palavras chaves serão armazenadas em um vetor de palavras, um char **
Uma vez que são 10 palavras (no máximo), não é relevante realizar uma ordenação destas palavras para ter a possibilidade de utilizar buscas binárias.

## Para a primeira função nova a ser implementada
A nova função deverá receber uma palavra, e conferir em cada um dos sites se esta palavra existe entre suas palavras chaves.
Construiremos um vetor, armazenando ponteiros para estes sites que possuem tal palavra.
Será ordenado este vetor de maneira decresente em relação a relevância dos sites.

## Para a segunda função nova a ser implementada
A nova função deverá receber uma palavra e conferir em cada um dos sites se esta palavra existe entre suas palavras chaves.
Encontrado todos os sites que possuem tal palavra entre suas palavras chaves, devemos recolher todas suas palavras chave, construindo uma estrutura de dados com todas estas palavras
Para cada palavra chave nesta nova estrutura, devemos ir na árvore avl incicial de todos os sites, e procurar todos os sites que possuem ao menos uma das palavras que foram armazenadas anteriormente.

### Solução encontrada
Iremos procurar normalemente a palavra chave em todos os nós da árvore
Caso seja encontrada a palavra entre as palavras chaves do site, construiremos uma estrutura de dados "trie" para armazenar suas palavras chave
Iremos adicionar nesta mesma trie todas as palavras chaves dos sites que possuem a palavra chave inicalemente buscada (de forma a não inserir palavras chaves iguais)
Após completa, iremos voltar na árvore inicial e conferir todas as palavras chaves dos sites, verificando a existência dela na estrutura trie. Caso esteja, acrescentaremos um ponteiro para este site em um vetor, que em seguida será ordenado com um algoritmo de ordenação estável (quicksort ??)

# <div align="center"> Projeto – Mini Googlebot(Parte I)
## <div align="center"> SCC0202 - Algoritmos e Estruturas de Dados
#### <div align="center"> Aluno: Bernardo Marques Costa - Número USP: 11795551

#### <div align="center"> Aluno: Fernando Henrique Paes Generich - Número USP: 11795342

#### **Compilador utilizado:** 
GNU Compiler Collection


#### **Estrutura de Dados utilizada:** 
##### AVL:
A estrutura de dados escolhida para armazenar todas as informações referentes aos sites foi a AVL, Árvore Binária de Busca Balanceada. A escolha foi feita com as seguintes considerações: cada site possui uma chave única (id), o que é de grande importância para uma árvore binária de busca, possibilitando a criação da árvore com nós em ordem crescente de ids; inserção, remoção e busca possuem complexidades logarítmicas.

###### Inserção:
A inserção de nós(campos que armazenam os sites) em uma árvore binária de busca balanceada(do tipo AVL) possui complexidade O(log(n)).
A inserção de um novo site é realizada a partir do nó raiz da árvore verificando para qual subárvore o nó inserido deverá ser encaminhado: caso o id seja maior do que o id do nó consultado, a inserção prosseguirá para a subárvore direita, caso contrário, prosseguirá para a subárvore esquerda, de modo recursivo, até que seja encontrada uma posição vazia para sua inserção.

###### Remoção: 

###### Busca: 

##### Trie:

##### Lista de Sites:

#### **Funções:**
As funções são acessadas através de um menu que é imprimido ao abrir o programa e após a chamada de cada função que não seja a função de finalização do programa.

|Número do Comando| Função|Nome no código       |O que faz                                                                                 |
|:---------------:|:-----:|:-------------------:|:----------------------------------------------------------------------------------------:|
|0| Inserir um site       |inserir_site         |Permite a inserção de um novo site                                                        |
|1| Remover um site       |remover_site         |Permite a remoção se um site já existente na lista                                        |
|2| Inserir palavra-chave |inserir_palavra_chave|Permite adicionar uma nova palavra-chave a um site já existente na lista                  |
|3| Atualizar relevância  |atualizar_relevancia |Permite alterar a relevância de um site já existente na lista                             |
|4| Mostrar lista         |lista_mostrar        |Imprime a lista na tela site por site                                                     |
|5| Ler arquivo CSV       |carrega_dados_csv    |Permite a leitura de dados de outros sites a partir de um arquivo txt passado pelo usuário|
|6| Buscar palavra-chave  |buscar_palavra       |A partir de uma palavra inicial dada pelo stdin, coleta todos os sites que contém esta como uma de suas palavras-chave|
|7| Sugerir sites         |sugerir_sites        |A partir de uma palavra inicial, cria uma lista de todos os sites que possuem esta como uma de suas palavras-chave, coleta todas as palavras-chave dessa lista e sugere sites relacionáveis à pelo menos uma palavra dessa lista de palavras-chave obtida|
|8| Sair                  |-                    |Fecha o programa                                                                          |



