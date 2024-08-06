#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../headers/arvorePatricia.h"

// Opções do menu.
#define CARREGARARQ 1
#define CONSULTARPALAVRA 2
#define IMPRIMIRDIC 3
#define CARREGARSTOPWORDS 4
#define IMPRIMIRNIVEIS 5
#define SAIR 0

// Verifica se os caracters de uma string são alfabéticos.
// Entrada: String a ser consultada.
// Saida: 0 caso encontre um caracter não albético e 1 caso contrário.
// Pré-condição: Nenhuma.
// Pós-condição:  Nenhuma.
int verificaChar (char* s);

// Coverte caracteres de uma string para caracteres afabéticos minusculos.
// Entrada: String a ser convertida.
// Saida: Nenhhuma.
// Pré-condição: Nenhuma.
// Pós-condição: String convertida para caracters alfabéticos minusculos.
void strToLower (char* s);

// Realiza a leitura do arquivo de entrada com as palavras.
// Entrada: Ponteiro para arquivo, ponteiro para raiz da árvore patrícia.
// Saida: Ponteiro para raiz da árvore patrícia.
// Pré-condição: Arquivo aberto em modo leitura.
// Pós-condição: Palavras inseridas na árvore patrícia.
arvore_PATRICIA* lerArquivo(FILE* arq, arvore_PATRICIA* raiz);

// Carregar arquivo contendo as palavras a serem inseridas na árvore patrícia.
// Entrada: Ponteiro para raiz da árvore patrícia.
// Saida: Ponteiro para raiz da árvore patrícia.
// Pré-condição: Nenhuma.
// Pós-condição: Palavras inseridas na árvore patrícia.
arvore_PATRICIA* carregarArquivo(arvore_PATRICIA* raiz);

// Imprime as palavras que correspondem a um prefixo, limitado a 10 palavras.
// Entrada: Ponteiro para raiz da árvore patrícia.
// Saida: Nenhuma.
// Pré-condição: Nenhuma.
// Pós-condição: Palavras com o prefixo impressas na tela, caso prefixo esteja contido na árvore patrícia.
void consultarPalavra(arvore_PATRICIA *raiz);

// Le as palavras do arquivo de remoção.
// Entrada: Ponteiro para arquivo aberto, ponteiro para raiz da árvore patrícia.
// Saida: Ponteiro para raiz da árvore patrícia.
// Pré-condição: Arquivo aberto em modo leitura.
// Pós-condição: Palavras removidas da árvore patrícia, se existirem.
arvore_PATRICIA* lerPalavra(FILE* arq, arvore_PATRICIA* raiz);

// Carrega arquivos de Stopwords, com palavras a serem removidas da árvore patrícia.
// Entrada: Ponteiro para raiz da árvore patrícia.
// Saida: Ponteiro para raiza da árvore patrícia.
// Pré-condição: Árvore patrícia inicializada.
// Pós-condição: Palavras do arquivo removidas da árvore patrícia, se existirem.
arvore_PATRICIA* carregarStopwords(arvore_PATRICIA* raiz);

// Imprime o menu principal de funcionalidades.
// Entrada: Nenhuma.
// Saida: Nenhuma.
// Pré-condição: Nenhuma. 
// Pós-condição: Menu impresso na tela.
void printMenuPrincipal();

// Menu principal de funcionalidades.
// Entrada: Nenhuma.
// Saida: Nenhuma.
// Pré-condição: Nenhuma.
// Pós-condição:  Nenhuma.
void menuPrincipal();

#endif