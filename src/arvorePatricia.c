#include "../headers/arvorePatricia.h"

// Verifica se um nó da árvore patrícia está vazio.
// Entrada: Ponteiro para nó da árvore patrícia.
// Saida: 1 se a arvore estiver vazia e 0 caso contrário.
// Pré-condição: Nenhuma.
// Pós-condição: Nenhuma.
int vazia(arvore_PATRICIA* no){
    return (no == NULL);
}

// Inicializa vetor de filhos de um nó da árvore patrícia.
// Entrada: Vetor de ponteiros para nós arvore patrícia.
// Saida: Nenhuma.
// Pré-condição: Nenhuma.
// Pós-condição: Nenhuma.
void iniciaFilhos(arvore_PATRICIA* vetor[]){
    int i;
    for(i = 0; i < 26; i++){
        vetor[i] = NULL;
    }
}

// Cria no da árvore patrícia.
// Entrada: Inteiro que representa se é o final da palavra e string do nó.
// Saida: Ponteiro para nó da árvore patrícia.
// Pré-condição: Nenhuma.
// Pós-condição: Nenhuma.
arvore_PATRICIA* criaNo(int final, char* string){
        arvore_PATRICIA* no = (arvore_PATRICIA*) malloc(sizeof(arvore_PATRICIA));
        iniciaFilhos(no->filhos);
        no->final = final;
        no->numFilhos = 0;
        no->string = (char*) malloc(strlen(string) + 1);
        strcpy(no->string, string);
        return no;
}

// Insere palavra na árvore patrícia recursivamente.
// Entrada: Ponteiro para nó da árvore patrícia e palavra a ser inserida.
// Saida: Ponteiro para nó da árvore patrícia.
// Pré-condição: Raiz inicializada.
// Pós-condição: Palavra inserida na árvore patrícia.
arvore_PATRICIA* inserirPalavra_recursiva(arvore_PATRICIA *no, char* string){
    if(vazia(no)) return criaNo(1, string); //Caso base na criação de folha
    else{
        int i;

        char* aux = (char*) malloc(strlen(no->string) + 1);
        strcpy(aux, no->string);
        
        //Passagem pela string do nó
        for(i = 0; *string != '\0' && *aux != '\0'; i++, aux++, string++){
            if(*string != *aux) break; //Encontrou divergência
        }

        if(*aux == *string) no->final = 1; // a string já corresponde a desse nó (caso 1)
        else if(*string != '\0' &&  *aux == '\0'){ // A string nova não acabou, mas a do nó sim (caso 2)
            if(vazia(no->filhos[*string - 'a'])) no->numFilhos++;
            no->filhos[*string - 'a'] = inserirPalavra_recursiva(no->filhos[*string - 'a'], string);
        }
        else{ // (caso 3)
            
            //Modificação da string
            char aux2[50]; 
            strcpy(aux2, no->string);
            aux2[i] = '\0';

            //Criação do novo nó intermediário
            arvore_PATRICIA* novoNo = criaNo((*string == '\0'), aux2);
            strcpy(no->string, aux);

            if(*string != '\0'){
                novoNo->filhos[*string - 'a'] = inserirPalavra_recursiva(novoNo->filhos[*string - 'a'], string);
                novoNo->numFilhos++;
            }

            novoNo->filhos[*aux - 'a'] = no;
            novoNo->numFilhos++;
            return novoNo;
        }
        return no;
    }
}

// Insere palavra na árvore patrícia.
// Entrada: Ponteiro para raiza da árvore patrícia e string com palavra a ser inserida.
// Saida: Ponnteiro para raiz da árvore patrícia.
// Pré-condição: Nenhuma.
// Pós-condição: Palavra inserida na árvore patrícia.
arvore_PATRICIA* inserirPalavra(arvore_PATRICIA* raiz, char* string){
    if(vazia(raiz)) raiz = criaNo(0, "-"); //Caso base para inicialização da raiz

    if(vazia(raiz->filhos[*string - 'a'])) raiz->numFilhos++; //Se for inserir em uma vazia, temos certeza que é novo filho
    raiz->filhos[*string - 'a'] = inserirPalavra_recursiva(raiz->filhos[*string - 'a'], string);

    return raiz;
}

// Junta dois nós quando nó 1 tem apenas 1 nó filho.
// Entrada: Ponteiro para nó da árvore patrícia.
// Saida: Ponteiro para nó da árvore patrícia.
// Pré-condição: Arvore patrícia inicializada.
// Pós-condição: Nó concatenado com nó filho.
arvore_PATRICIA* mergeNo(arvore_PATRICIA* no){
    int i;

    for(i = 0; i < 26 && vazia(no->filhos[i]); i++); //Procura o filho que sobrou

    arvore_PATRICIA* novoNo;
    novoNo = no->filhos[i];
    novoNo->string = (char*) realloc(novoNo->string, strlen(novoNo->string) + strlen(no->string) + 1);
    strcpy(novoNo->string, strcat(no->string, novoNo->string));
    
    free(no->string);
    free(no);

    return novoNo;
}

// Remove uma palavra da árvore patrícia recursivamente.
// Entrada: Ponteiro para nó da árvore patrícia e string com palavra a ser removida.
// Saida: Ponteiro para nó da árvore patrícia.
// Pré-condição: Raiz da árvore patricia inicializada.
// Pós-condição: Palavra removida se existir na árvore patrícia.
arvore_PATRICIA* removerPalavra_recursiva(arvore_PATRICIA* no, char* string){
    int flagCorresponde = 0;
    char* aux = (char*) malloc(strlen(no->string) + 1);
    strcpy(aux, no->string);

    for( ; *string != '\0' && *aux != '\0'; aux++, string++){
        if(*string != *aux){ //String incompatível
            break;
        }
    }
    if(*aux == '\0' && *string != '\0'){ // Caso de continuação da remoção
        if(!vazia(no->filhos[*string - 'a'])){
            int posi = *string - 'a';

            no->filhos[posi] = removerPalavra_recursiva(no->filhos[posi], string);
            if(vazia(no->filhos[posi]) && no->numFilhos == 2){ // Verifica se ocoreu 
                no = mergeNo(no);
            }
            else if(vazia(no->filhos[posi])) no->numFilhos--; // Verifica se realmente ocorreu a remoção antes de diminuir o número de filhos
            
            return no;
        }
        else flagCorresponde = 1;
    }
    else if(*string == '\0' &&  *aux != '\0' || flagCorresponde || no->final == 0){ // Caso de invalidação da remoção
        return no;
    }
    else { // Caso de remoção
        if(no->numFilhos == 0){
            free(no->string);
            free(no);

            return NULL;
        }
        else if(no->numFilhos == 1){
            no = mergeNo(no);
        }
        else{
            no->final = 0;
        }
        return no;
    }
}

// Remove uma palavra da árvore patrícia.
// Entrada: Ponteiro para raiza da árvore patrícia e string com palavra a ser removida.
// Saida: Ponteiro para raiz da árvore patrícia.
// Pré-condição: Nenhuma.
// Pós-condição: Palavra removida, se esta existir na árvore patrícia.
arvore_PATRICIA* removerPalavra(arvore_PATRICIA* raiz, char* string){
    if(vazia(raiz)) printf("Arvore vazia\n"); // Árvore não iniciada
    else if(!vazia(raiz->filhos[*string - 'a'])){
        int i = *string - 'a';
        raiz->filhos[i] = removerPalavra_recursiva(raiz->filhos[i], string);
        if(vazia(raiz->filhos[i])) raiz->numFilhos--; //Nó se transformou em nulo
    }
    else printf("Não há correspondência!\n"); // Filho não correspondente
    
    return raiz;
}

// Imprime o dicionario de palavras contidas na árvore patrícia recursivamente.
// Entrada: Ponteiro para nó da árvore patrícia, string concatenada dos nós ancestrais, string auxiliar para concatenação, flag que indica quantas palavras foram impressas.
// Saida: Nenhuma.
// Pré-condição: Nenhuma.
// Pós-condição: Dicionário impresso em ordem alabética.
void imprimeDicionarioRecursivo(arvore_PATRICIA* no, char* string, char* aux, int* prim){
    int i, j;
    
    char* aux2 = (char*) malloc(51); //Criação de auxiliar para não modificar a string
    strcpy(aux2, string); //Cópia da string
    strcat(aux2, no->string); //Cocatenação com a string do nó atual
    strcpy(aux, aux2);
    
    if(no->numFilhos > 0){
        if(no->final) {
            if(*prim>0) printf(", ");
            printf("%s", aux); //Caso o nó interno seja uma palavra
            (*prim)++;
        }
        
        for(i = j = 0; j < no->numFilhos; i++){ 
            if(!vazia(no->filhos[i])){
                imprimeDicionarioRecursivo(no->filhos[i], aux2, aux, prim);
                j++;
            }
        }
    }else{
        if(*prim>0) printf(", ");
        printf("%s", aux);
        (*prim)++;
        aux[0] = '\0';
    }
    free(aux2); //Libera memória alocada
}

// Imprime o dicionario de palavras contidas na árvore patrícia.
// Entrada: Ponteiro para raiz da árvore patrícia.
// Saida: Nenhuma.
// Pré-condição: Nenhuma.
// Pós-condição: Dicionário impresso em ordem alabética.
void imprimirDicionario(arvore_PATRICIA* raiz){
    if(vazia(raiz) || raiz->numFilhos == 0){
        printf("Arvore vazia!\n");
        return;
    }

    int i,j, prim=0;
    char *str= (char*) malloc(51);
    strcpy(str, "\0");

    for(i = j = 0; j < raiz->numFilhos; i++){
        if(!vazia(raiz->filhos[i])){
            imprimeDicionarioRecursivo(raiz->filhos[i], str, str, &prim);
            j++;
        }
    }
    printf("\n");
}

// Busca um nó na árvore patrícia que contenha o final de um prefixo inserido.
// Entrada: Ponteiro para nó da árvore patrícia, string com o prefixo, string auxiliar para concatenação.
// Saida: Ponteiro com o nó onde finaliza o prefixo, ou NULL caso prefixo não encontrado.
// Pré-condição: Nenhuma.
// Pós-condição: Nenhuma.
arvore_PATRICIA* buscaNo(arvore_PATRICIA* no, char* string, char* stringAux){
    if(vazia(no)){
        return NULL;
    }else{
        char* aux = (char*) malloc(strlen(no->string) + 1);
        strcpy(aux, no->string);

        for( ; *string != '\0' && *aux != '\0'; aux++, string++){
            if(*string != *aux){ 
                return NULL;
            }
        }
        if(*string == '\0'){
            return no;
        }else{
            if(!vazia(no->filhos[*string - 'a'])){
                strcat(stringAux, no->string);
                return buscaNo(no->filhos[*string - 'a'], string, stringAux);
            }else{
                return NULL;
            }
        }
    }
}

// Imprime as palavras com o prefixo informado formatadas conforme especificação.
// Entrada: Ponteiro para nó da árvore patrícia, string com o prefixo, string com o prefixo cancatenado a string do nó anteiros, inteiro com flag para quantidade de palavras.
// Saida: Nenhuma.
// Pré-condição: Nenhuma.
// Pós-condição: Palavras com o prefixo impressas na tela.
void imprimirPalavrasPrefixoRecursivo(arvore_PATRICIA* no, char* string, char* aux, int* prim){
    int i, j;
    
    char* aux2 = (char*) malloc(51); //Criação de auxiliar para não modificar a string
    strcpy(aux2, string); //Cópia da string
    strcat(aux2, no->string); //Cocatenação com a string do nó atual
    strcpy(aux, aux2);

    if(no->numFilhos > 0){
        if(no->final) {
            if(*prim>0) printf(", ");
            printf("%s", aux); //Caso o nó interno seja uma palavra
            (*prim)++;
        }
        
        for(i = j = 0; j < no->numFilhos; i++){ 
            if(!vazia(no->filhos[i])){
                if(*prim == 10) return;
                imprimirPalavrasPrefixoRecursivo(no->filhos[i], aux2, aux, prim);
                j++;
            }
        }
    }else{
        if(*prim>0) printf(", ");
        printf("%s", aux);
        (*prim)++;
        aux[0] = '\0';
    }
    free(aux2); //Libera memória alocada
}

// Imprime as palavras contidas na subárvores a partir de um prefixo.
// Entrada: Ponteiro para nó da árvore patricia e string com o prefixo. 
// Saida: Nenhuma.
// Pré-condição: Arvore patrícia inicializada e prefixo encontrado.
// Pós-condição: Palavras com o prefixo inserido impressas na tela.
void imprimirPalavrasPrefixo(arvore_PATRICIA* no, char* string){
    int prim = 0;
    char aux[51];
    strcpy(aux, string);
    strcat(aux, no->string);
    imprimirPalavrasPrefixoRecursivo(no, string, aux, &prim);
}

// Verifica se uma lista encadeada está vazia.
// Entrada: Ponteiro para lista encadeada.
// Saida: 1 se a lista estiver vazia e 0 caso contrário.
// Pré-condição: Nenhuma.
// Pós-condição: Nenhuma.
int vaziaLista (arvore_LISTA*l){
    return (l == NULL);
}

// Insere um nó da árvore em uma lista encadeada ordenada por níveis.
// Entrada: Ponteiro para lista encadeada, string do nó que será copiado, nivel do nó que será copiado, numero de filhos do nó que será copiado.
// Saida: Ponteiro para cabeça da lista encadeada.
// Pré-condição: Nenhuma.
// Pós-condição: Nó copiado para lista encadeada.
arvore_LISTA* inserirLista (arvore_LISTA* l, char* string, int nivel, int numFilhos){
    if (vaziaLista(l)){
        arvore_LISTA* aux = (arvore_LISTA*) malloc (sizeof(arvore_LISTA));
        
        strcpy(aux->string, string);
        aux->nivel = nivel;
        aux->numFilhos = numFilhos;
        aux->prox = NULL;

        return aux;
    }
    else if (l->nivel > nivel){
        arvore_LISTA* aux = (arvore_LISTA*) malloc (sizeof(arvore_LISTA));
        
        strcpy(aux->string, string);
        aux->nivel = nivel;
        aux->numFilhos = numFilhos;
        aux->prox = l;

        return aux;
    }
    else{
        l->prox = inserirLista(l->prox, string, nivel, numFilhos);
        return l;
    }

    return l;
}

// Insere filhos de um nó, caso este tenha filhos, em uma lista encadeada ordenada.
// Entrada: Ponteiro para nó da árvore patrícia, ponteiro para lista encadeada, inteiro com o nível do nó na árvore.
// Saida: Ponteiro para cabeça da lista encadeada.
// Pré-condição: Nós da subárvore com o prefixo da palavra consultada inseridos na lista.
// Pós-condição: Filhos do nó inseridos na lista encadeda, caso tenha filhos.
arvore_LISTA* inserirFilhosRecursivo(arvore_PATRICIA* no, arvore_LISTA* l, int nivel){
    int i, j = 0;

    if (!vazia(no)){
        l = inserirLista (l, no->string, nivel, no->numFilhos);
        
        if (no->numFilhos > 0){
            for (i = 0; j < no->numFilhos; i++){
                if (!vazia(no->filhos[i])){
                    l = inserirFilhosRecursivo (no->filhos[i], l, nivel+1);
                    j++;
                }
            }
        }

        return l;
    }

    return l;
}

// Insere nós da subárvore a partir de um prefixo, em uma lista encadeada ordenada por níveis. 
// Entrada: Ponteiro para nó da árvore patrícia, ponteiro para lista encadeada, nível do nó, string com prefixo, flag que indica prefixo não encontrado.
// Saida: Ponteiro para cabeça da lista encadeada. 
// Pré-condição: Árvore patrícia inicializada.
// Pós-condição: Nós da subárvore inseridos em uma lista encadeada ordenado.
arvore_LISTA* inserirListaRecursivo(arvore_PATRICIA* no, arvore_LISTA* l, int nivel, char* string, int* flagNF){

    if(vazia(no)){
        return l;
    }
    else{
        char* aux = (char*) malloc(strlen(no->string) + 1);
        strcpy(aux, no->string);

        for( ; *string != '\0' && *aux != '\0'; aux++, string++){
            if(*string != *aux){ 
                *flagNF = 1;
                return l;
            }
        }

        free(aux);

        if(*string == '\0'){
            return inserirFilhosRecursivo (no, l, nivel);
        }
        else{
            if(!vazia(no->filhos[*string - 'a'])){
                l = inserirLista (l, no->string, nivel, no->numFilhos);
                return inserirListaRecursivo(no->filhos[*string - 'a'], l, nivel+1 , string, flagNF);
            }else{
                return l;
            }
        }
    }

    return l;
}

// Desaloca lista encadeada.
// Entrada: Ponteiro para lista encadeada.
// Saida: Ponteiro nulo para lista encadeada.
// Pré-condição: Nenhuma.
// Pós-condição: Lista desalocada.
arvore_LISTA* liberaLista (arvore_LISTA* l){
    arvore_LISTA* aux;

    while (!vaziaLista(l)){
        aux = l->prox;
        free(l);
        l = aux;
    }

    return aux;
}

// Imprimi a lista encadeada da subárvore formatada conforme especificações.
// Entrada: Ponteiro para lista e nível da raiz.
// Saida: Nenhuma.
// Pré-condição: Árvore patrícia inicializada.
// Pós-condição: Lista com subárvore impressa na tela.
void imprimirLista (arvore_LISTA* l, int nivel){
    int i;

    printf ("\nnivel %d:", nivel);
    printf (" (%s:%d)", l->string, l->numFilhos);
    
    if (l->numFilhos > 0){
        l = l->prox;

        while (!vaziaLista(l)){
            if (l->nivel > nivel){
                nivel += 1;
                printf ("\nnivel %d:", nivel);
            }
                
            printf (" (%s:%d)", l->string, l->numFilhos);
            l = l->prox;
        }  
    }

    printf ("\n");
}

// Imprime a subárvore da árvore patrícia a partir de um prefixo.
// Entrada: Ponteiro para raiz da árvore patrícia.
// Saida: Nenhuma.
// Pré-condição: Nenhuma.
// Pós-condição: Subárvore impressa na tela, desde que o prefixo exista na árvore.
void imprimirPorNiveis (arvore_PATRICIA* raiz){
    arvore_LISTA* arv = NULL;
    int flagNF = 0, nivel = 0;

    // Copia os nós da arvore patrícia para uma lista encadeada.
    if (vazia(raiz) || raiz->numFilhos == 0){
        printf ("-> Arvore Vazia!\n");
        return;
    }
    else{
        char string[51];
        
        printf("Digite o prefixo a ser consultado: ");
        scanf("%s%*c", string);

        arv = inserirLista (arv, raiz->string, nivel, raiz->numFilhos); // insere o nó da raiz na lista.

        if (raiz->numFilhos){ // Insere na lista nós filhos da raiz, caso existam.
            arv = inserirListaRecursivo(raiz->filhos[*string - 'a'], arv, nivel+1, string, &flagNF);
        }
    }

    if (flagNF){ // Verifica se o prefixo eciste na árvore.
        printf("\nPrefixo nao encontrado.\n");
    }    
    else{
        // Imprimir lista gerada
        imprimirLista(arv, nivel);
    }    
    // Desaloca lista gerada
    arv = liberaLista(arv);
}

