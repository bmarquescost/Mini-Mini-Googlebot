# <div align="center"> Projeto – Mini Googlebot(Parte II)
## <div align="center"> SCC0202 - Algoritmos e Estruturas de Dados
#### <div align="center"> Aluno: Bernardo Marques Costa - Número USP: 11795551

#### <div align="center"> Aluno: Fernando Henrique Paes Generich - Número USP: 11795342

#### **Compilador utilizado:** 
GNU Compiler Collection

### **Planejamento**
Mudar a estrutura geral para uma árvore AVL, que guarda de maneira ordenada e balanceada todos os sites que são inseridos.

As palavras chaves de cada site são armazenadas em um vetor de palavras, um char ** .

Uma vez que são 10 palavras (no máximo), não é relevante realizar uma ordenação destas palavras para ter a possibilidade de utilizar buscas binárias.

### **Para a primeira função nova a ser implementada**
A nova função deverá receber uma palavra e conferir em cada um dos sites se esta palavra existe entre suas palavras chaves.

Construiremos um vetor, armazenando ponteiros para estes sites que possuem tal palavra.

Será ordenado este vetor de maneira decresente em relação a relevância dos sites.

### **Para a segunda função nova a ser implementada**
A nova função deverá receber uma palavra e conferir em cada um dos sites se esta palavra existe entre suas palavras chaves.

Encontrado todos os sites que possuem tal palavra entre suas palavras chaves, devemos recolher todas suas palavras chave, construindo uma estrutura de dados com todas estas palavras.

Voltar para a AVL inicial que contém todos os sites, e procurar todos os sites que possuem entre suas palavras-chave ao menos uma das palavras que foram armazenadas anteriormente.

#### **Solução encontrada**
Iremos construir uma lista de sites (como na primeira função de busca por palavra chave) que contém a palavra fornecida inicialmente.

Construiremos uma trie, e para cada site desta lista, inseriremos cada uma de suas palavras na trie

Em seguida criaremos uma lista de sites para sugestão
Finalmente, voltaremos para a estrutura que armazena todos os sites do programa, e para cada um deles verificaremos se ao menos uma de suas palavras está contida na trie, caso contenha, acrescentaremos um ponteiro à ele na lista de sugestões. Obteremos no final, a lista de sites para sugestão a partir de uma palavra fornecida inicialmente pelo usuário.

Ordenaremos a lista de sites com o algoritmo de ordenação heapsort.

**O.B.S**: algumas questões sobre a complexidade desta funcionalidade. 

Considerando n como o número de sites obtidas no programa:

devemos primeiramente percorrer toda a árvore, para verificar se o site contem à palavra chave inicialmente fornecida - complexidade O(n). A criação da lista de sites e a inserção desordenada possui complexidade O(1).

A partir da lista de sites completa, construiremos a trie: percorreremos na lista cada site e acessamos cada uma de suas palavras chave, inserindo-a na trie, o que resulta em uma complexidade (no pior caso de 10 palavras chave em todos os n sites) 10nc operações, sendo c o tamanho da palavra chave.

Em seguida, para cada nó na árvore, verificaremos para cada palavra-chave deste site, se ela está presente na trie: complexidade (no pior caso todos os sites com 10 palavras chave) 10nc, sendo c o tamanho da maior palavra entre todas as palavras chave da estrutura trie. 

Ordenação com algoritmo heapsort de complexidade O(nlog(n))

## **Estruturas de Dados utilizada no decorrer do projeto:** 
### AVL:
A estrutura de dados escolhida para armazenar todas as informações referentes aos sites foi a AVL, Árvore Binária de Busca Balanceada. A escolha foi feita com as seguintes considerações: cada site possui uma chave única (id), o que é de grande importância para uma árvore binária de busca, possibilitando a criação da árvore com nós em ordem crescente de ids; inserção, remoção e busca possuem complexidades logarítmicas.

##### Inserção:
A inserção de nós (campos que armazenam os sites) em uma árvore binária de busca balanceada (do tipo AVL) possui complexidade O(log(n)), sendo n o número de nós  da árvore.

A inserção de um novo site é realizada a partir do nó raiz da árvore verificando para qual subárvore o nó inserido deverá ser encaminhado: caso o id seja maior do que o id do nó consultado, a inserção prosseguirá para a subárvore direita, caso contrário, prosseguirá para a subárvore esquerda, de modo recursivo, até que seja encontrada uma posição vazia para sua inserção.

Caso o estado de balanceamento da árvore seja afetado após a inserção, são realizadas medidas para retornar ao estado balanceado, por meio de rotações (rotação simples a esquerda, simples a direita, dupla esquerda direita, dupla direita esquerda, cada uma dependendo da situação).

##### Remoção: 
Assim como a inserção, a remoção em uma Árvore Binária de Busca do tipo AVL possui complexidade O(log(n)).

A remoção possui o mesmo principio de balancemento da inserção, sendo necessário considerar cada possibilidade de rotação

##### Busca: 
A busca por id em uma Árvore Binária de Busca do tipo AVL possui complexidade O(log(n)), uma vez que a sua propriedade de balanceamento e de organização dos nós em ordem, permite a utilização da busca binária em árvore.

### Trie:
A estrutura escolhida para armazenar as palavras chaves obtidas na função de sugerir sites foi a estrutura em árvore Trie.

Constitui uma árvore em que cada nó possui 26 filhos (um array de índice 0-25) cada um correspondente a uma letra do alfabeto.

A trie armazena, a partir de suas possibilidades de caminhos e indicadores de final de cadeia de caracteres, as palavras-chave.

##### Inserção
A inserção de uma nova palavra na trie demanda percorrer, no pior caso, o tamanho da maior palavra chave que armazena, o que resulta em uma complexidade de O(c), sendo c o tamanho desta palavra

##### Busca
A busca ou verificação da existência de uma palavra na trie, demanda percorrer, no pior caso, o tamanho da maior palavra chave que armazena, o que resulta, mais uma vez, em uma complexidade de O(c), sendo c o tamanho da desta palavra

**O.B.S**: não há operação de remoção em estrutura trie.

### Lista de Sites:
Para armazenar os sites que possuem alguma propriedade (neste projeto em específico: a palavra chave desejada ou estão entre os sites sugeridos), utilizaremos um vetor de registros quem contem um vetor de sites, um inteiro que representa o número de sites armazenados e um número que auxilia o processo de realocação deste vetor (sendo este definido como QUANTIDADE_PADRAO = 10).

Optamos por esta implementação uma vez que possibilita utilizar algoritmos de ordenação rápidos para que sejam ordenados decrescentemente (sendo escolhido o heapsort, de complexidade O(nlog(n))) e sua complexidade de inserção de um novo site de maneira desordenada é constante.

Além disso, como não se trata de uma estrutura de dados complexa, minimiza relativamente a utilização de memória, já que não são necessários ponteiros para nós da estrutura.

## **Funções:**
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



