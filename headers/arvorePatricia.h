#ifndef ARVOREPATRICIA_H
#define ARVOREPATRiCIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*             STRUCTS          */

// Struct para nó da árvore patrícia.
typedef struct no{
    char* string;
    int numFilhos; //Número de filhos
    struct no* filhos[26]; //Alocado de maneira estatíca
    int final; //Representa o final de uma palavra
} arvore_PATRICIA;

// Struct para lista encadeada com os nós da árvore patrícia.
typedef struct lista{
    char string[51];
    int nivel;  
    int numFilhos;
    struct lista* prox;
} arvore_LISTA;
/*             FIM STRUCTS          */

// Verifica se um nó da árvore patrícia está vazio.
// Entrada: Ponteiro para nó da árvore patrícia.
// Saida: 1 se a arvore estiver vazia e 0 caso contrário.
// Pré-condição: Nenhuma.
// Pós-condição: Nenhuma.
int vazia(arvore_PATRICIA* no);

// Inicializa vetor de filhos de um nó da árvore patrícia.
// Entrada: Vetor de ponteiros para nós arvore patrícia.
// Saida: Nenhuma.
// Pré-condição: Nenhuma.
// Pós-condição: Nenhuma.
void iniciaFilhos(arvore_PATRICIA* vetor[]);

// Cria no da árvore patrícia.
// Entrada: Inteiro que representa se é o final da palavra e string do nó.
// Saida: Ponteiro para nó da árvore patrícia.
// Pré-condição: Nenhuma.
// Pós-condição: Nenhuma. 
arvore_PATRICIA* criaNo(int final, char* string);

// Insere palavra na árvore patrícia recursivamente.
// Entrada: Ponteiro para nó da árvore patrícia e palavra a ser inserida.
// Saida: Ponteiro para nó da árvore patrícia.
// Pré-condição: Raiz inicializada.
// Pós-condição: Palavra inserida na árvore patrícia.
arvore_PATRICIA* inserirPalavra_recursiva(arvore_PATRICIA *no, char* string);

// Insere palavra na árvore patrícia.
// Entrada: Ponteiro para raiza da árvore patrícia e string com palavra a ser inserida.
// Saida: Ponnteiro para raiz da árvore patrícia.
// Pré-condição: Nenhuma.
// Pós-condição: Palavra inserida na árvore patrícia.
arvore_PATRICIA* inserirPalavra(arvore_PATRICIA* raiz, char* string);

// Junta dois nós quando nó 1 tem apenas 1 nó filho.
// Entrada: Ponteiro para nó da árvore patrícia.
// Saida: Ponteiro para nó da árvore patrícia.
// Pré-condição: Arvore patrícia inicializada.
// Pós-condição: Nó concatenado com nó filho.
arvore_PATRICIA* mergeNo(arvore_PATRICIA* no);

// Remove uma palavra da árvore patrícia recursivamente.
// Entrada: Ponteiro para nó da árvore patrícia e string com palavra a ser removida.
// Saida: Ponteiro para nó da árvore patrícia.
// Pré-condição: Raiz da árvore patricia inicializada.
// Pós-condição: Palavra removida se existir na árvore patrícia.
arvore_PATRICIA* removerPalavra_recursiva(arvore_PATRICIA* no, char* string);

// Remove uma palavra da árvore patrícia.
// Entrada: Ponteiro para raiza da árvore patrícia e string com palavra a ser removida.
// Saida: Ponteiro para raiz da árvore patrícia.
// Pré-condição: Nenhuma.
// Pós-condição: Palavra removida, se esta existir na árvore patrícia.
arvore_PATRICIA* removerPalavra(arvore_PATRICIA* raiz, char* string);

// Imprime o dicionario de palavras contidas na árvore patrícia recursivamente.
// Entrada: Ponteiro para nó da árvore patrícia, string concatenada dos nós ancestrais, string auxiliar para concatenação, flag que indica quantas palavras foram impressas.
// Saida: Nenhuma.
// Pré-condição: Nenhuma.
// Pós-condição: Dicionário impresso em ordem alabética.
void imprimeDicionarioRecursivo(arvore_PATRICIA* no, char* string, char* aux, int* prim);

// Imprime o dicionario de palavras contidas na árvore patrícia.
// Entrada: Ponteiro para raiz da árvore patrícia.
// Saida: Nenhuma.
// Pré-condição: Nenhuma.
// Pós-condição: Dicionário impresso em ordem alabética.
void imprimirDicionario(arvore_PATRICIA* raiz);

// Busca um nó na árvore patrícia que contenha o final de um prefixo inserido.
// Entrada: Ponteiro para nó da árvore patrícia, string com o prefixo, string auxiliar para concatenação.
// Saida: Ponteiro com o nó onde finaliza o prefixo, ou NULL caso prefixo não encontrado.
// Pré-condição: Nenhuma.
// Pós-condição: Nenhuma.
arvore_PATRICIA* buscaNo(arvore_PATRICIA* no, char* string, char* stringAux);

// Imprime as palavras com o prefixo informado formatadas conforme especificação.
// Entrada: Ponteiro para nó da árvore patrícia, string com o prefixo, string com o prefixo cancatenado a string do nó anteiros, inteiro com flag para quantidade de palavras.
// Saida: Nenhuma.
// Pré-condição: Nenhuma.
// Pós-condição: Palavras com o prefixo impressas na tela.
void imprimirPalavrasPrefixoRecursivo(arvore_PATRICIA* no, char* string, char* aux, int* prim);

// Imprime as palavras contidas na subárvores a partir de um prefixo.
// Entrada: Ponteiro para nó da árvore patricia e string com o prefixo. 
// Saida: Nenhuma.
// Pré-condição: Arvore patrícia inicializada e prefixo encontrado.
// Pós-condição: Palavras com o prefixo inserido impressas na tela.
void imprimirPalavrasPrefixo(arvore_PATRICIA* no, char* string);

// Verifica se uma lista encadeada está vazia.
// Entrada: Ponteiro para lista encadeada.
// Saida: 1 se a lista estiver vazia e 0 caso contrário.
// Pré-condição: Nenhuma.
// Pós-condição: Nenhuma.
int vaziaLista (arvore_LISTA*l);

// Insere um nó da árvore em uma lista encadeada ordenada por níveis.
// Entrada: Ponteiro para lista encadeada, string do nó que será copiado, nivel do nó que será copiado, numero de filhos do nó que será copiado.
// Saida: Ponteiro para cabeça da lista encadeada.
// Pré-condição: Nenhuma.
// Pós-condição: Nó copiado para lista encadeada.
arvore_LISTA* inserirLista (arvore_LISTA* l, char* string, int nivel, int numFilhos);

// Insere filhos de um nó, caso este tenha filhos, em uma lista encadeada ordenada.
// Entrada: Ponteiro para nó da árvore patrícia, ponteiro para lista encadeada, inteiro com o nível do nó na árvore.
// Saida: Ponteiro para cabeça da lista encadeada.
// Pré-condição: Nós da subárvore com o prefixo da palavra consultada inseridos na lista.
// Pós-condição: Filhos do nó inseridos na lista encadeda, caso tenha filhos.
arvore_LISTA* inserirFilhosRecursivo(arvore_PATRICIA* no, arvore_LISTA* l, int nivel);

// Insere nós da subárvore a partir de um prefixo, em uma lista encadeada ordenada por níveis. 
// Entrada: Ponteiro para nó da árvore patrícia, ponteiro para lista encadeada, nível do nó, string com prefixo, flag que indica prefixo não encontrado.
// Saida: Ponteiro para cabeça da lista encadeada. 
// Pré-condição: Árvore patrícia inicializada.
// Pós-condição: Nós da subárvore inseridos em uma lista encadeada ordenado.
arvore_LISTA* inserirListaRecursivo(arvore_PATRICIA* no, arvore_LISTA* l, int nivel, char* string, int* flagNF);

// Desaloca lista encadeada.
// Entrada: Ponteiro para lista encadeada.
// Saida: Ponteiro nulo para lista encadeada.
// Pré-condição: Nenhuma.
// Pós-condição: Lista desalocada.
arvore_LISTA* liberaLista (arvore_LISTA* l);

// Imprimi a lista encadeada da subárvore formatada conforme especificações.
// Entrada: Ponteiro para lista e nível da raiz.
// Saida: Nenhuma.
// Pré-condição: Árvore patrícia inicializada.
// Pós-condição: Lista com subárvore impressa na tela.
void imprimirLista (arvore_LISTA* l, int nivel);

// Imprime a subárvore da árvore patrícia a partir de um prefixo.
// Entrada: Ponteiro para raiz da árvore patrícia.
// Saida: Nenhuma.
// Pré-condição: Nenhuma.
// Pós-condição: Subárvore impressa na tela, desde que o prefixo exista na árvore.
void imprimirPorNiveis(arvore_PATRICIA* raiz);

#endif