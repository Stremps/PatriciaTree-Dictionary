#include "../headers/interface.h"

// Verifica se os caracters de uma string são alfabéticos.
// Entrada: String a ser consultada.
// Saida: 0 caso encontre um caracter não albético e 1 caso contrário.
// Pré-condição: Nenhuma.
// Pós-condição:  Nenhuma.
int verificaChar (char* s){
    for (int i = 0; s[i] != '\0'; i++){
        if (!isalpha(s[i])){
            return 0;
        }
    }

    return 1;
}   

// Coverte caracteres de uma string para caracteres afabéticos minusculos.
// Entrada: String a ser convertida.
// Saida: Nenhhuma.
// Pré-condição: Nenhuma.
// Pós-condição: String convertida para caracters alfabéticos minusculos.
void strToLower (char* s){
    for (int i = 0; s[i] != '\0'; i++)
        s[i] = tolower(s[i]);
}

// Realiza a leitura do arquivo de entrada com as palavras.
// Entrada: Ponteiro para arquivo, ponteiro para raiz da árvore patrícia.
// Saida: Ponteiro para raiz da árvore patrícia.
// Pré-condição: Arquivo aberto em modo leitura.
// Pós-condição: Palavras inseridas na árvore patrícia.
arvore_PATRICIA* lerArquivo (FILE* arq, arvore_PATRICIA* raiz){
    char palavra[51];

    
    while (fscanf(arq,"%[^\n]%*c",palavra) != EOF){ 
        if (verificaChar(palavra)){
            strToLower(palavra);
            raiz = inserirPalavra(raiz, palavra);
        }      
    }

    return raiz;
}

// Carregar arquivo contendo as palavras a serem inseridas na árvore patrícia.
// Entrada: Ponteiro para raiz da árvore patrícia.
// Saida: Ponteiro para raiz da árvore patrícia.
// Pré-condição: Nenhuma.
// Pós-condição: Palavras inseridas na árvore patrícia.
arvore_PATRICIA* carregarArquivo (arvore_PATRICIA* raiz){
    if(!vazia(raiz)){
        char confirma;

        printf("Arvore já inicializada, deseja apaga-la? (s/n)");
        scanf("%c%*c", &confirma);

        if(confirma == 's') raiz = NULL; //Libera memória depois
    }
    
    FILE* arq = NULL;
    char caminho[100];
 
    printf("Digite o caminho do arquivo: ");
    scanf("%[^\n]%*c", caminho);
    printf("\n");
 
    arq = fopen(caminho, "r");
    
    if(arq == NULL){
        printf("-> Falha no carregamento do arquivo. Tente novamente!\n\n");
    }
    else{
        raiz = lerArquivo(arq, raiz);
        printf("\n-> Arquivo carregado com sucesso.\n\n");
        fclose(arq);
    }

    return raiz;
}

// Imprime as palavras que correspondem a um prefixo, limitado a 10 palavras.
// Entrada: Ponteiro para raiz da árvore patrícia.
// Saida: Nenhuma.
// Pré-condição: Nenhuma.
// Pós-condição: Palavras com o prefixo impressas na tela, caso prefixo esteja contido na árvore patrícia.
void consultarPalavra(arvore_PATRICIA* raiz){
    int flag = 0;
    char string[51];
    printf("Digite o prefixo a ser consultado: ");
    scanf("%s%*c", string);

    printf ("\n");

    if(vazia(raiz)) {
        printf("Arvore vazia!\n");
        return;
    }
    if(!vazia(raiz->filhos[*string - 'a'])){
        arvore_PATRICIA* noAux;
        char stringAux[51];
        strcpy(stringAux,"");
        noAux = buscaNo(raiz->filhos[*string - 'a'], string, stringAux);
        if(!vazia(noAux)){
            imprimirPalavrasPrefixo(noAux, stringAux);
        }
        else flag = 1;
    }
    else flag = 1;
    if(flag){
        printf("Préfixo não encontrado!\n");
    }
}

// Le as palavras do arquivo de remoção.
// Entrada: Ponteiro para arquivo aberto, ponteiro para raiz da árvore patrícia.
// Saida: Ponteiro para raiz da árvore patrícia.
// Pré-condição: Arquivo aberto em modo leitura.
// Pós-condição: Palavras removidas da árvore patrícia, se existirem.
arvore_PATRICIA* lerPalavra(FILE* arq, arvore_PATRICIA* raiz){
    char palavra[51], palavraAchada[51], aux[51];
    strcpy(palavra, "");
    strcpy(palavraAchada, "");

    
    while (fscanf(arq,"%[^\n]%*c",palavra) != EOF){ 
        if (verificaChar(palavra)){
            aux[0] = '\0';
            strToLower(palavra);
            strcpy(palavraAchada, palavra);
            if(buscaNo(raiz->filhos[palavra[0] - 'a'], palavra, aux) != NULL){
                raiz = removerPalavra(raiz, palavraAchada);
            }
        }      
    }

    return raiz;
}

// Carrega arquivos de Stopwords, com palavras a serem removidas da árvore patrícia.
// Entrada: Ponteiro para raiz da árvore patrícia.
// Saida: Ponteiro para raiza da árvore patrícia.
// Pré-condição: Árvore patrícia inicializada.
// Pós-condição: Palavras do arquivo removidas da árvore patrícia, se existirem.
arvore_PATRICIA* carregarStopwords(arvore_PATRICIA* raiz){
    FILE* arq = NULL;
    char caminho[100];
 
    printf("Digite o caminho do arquivo: ");
    scanf("%[^\n]%*c", caminho);
    printf("\n");
 
    arq = fopen(caminho, "r");
    
    if(arq == NULL){
        printf("-> Falha no carregamento do arquivo. Tente novamente!\n\n");
    }
    else{
        raiz = lerPalavra(arq, raiz);
        printf("\n-> Arquivo carregado com sucesso.\n\n");
        fclose(arq);
    }
    return raiz;
}

// Imprime o menu principal de funcionalidades.
// Entrada: Nenhuma.
// Saida: Nenhuma.
// Pré-condição: Nenhuma. 
// Pós-condição: Menu impresso na tela.
void printMenuPrincipal (){
    printf("\n  ---   MENU PRINCIPAL  ---\n\n");
	printf("1 - Carregar arquivo texto\n");
    printf("2 - Consultar palavra\n");
    printf("3 - Imprimir dicionario\n");
    printf("4 - Carregar arquivo de stopwords\n");
    printf("5 - Imprimir subarvore de niveis\n");
    printf("0 - Sair\n");
	printf("Selecione uma opcao acima: ");
}

// Menu principal de funcionalidades.
// Entrada: Nenhuma.
// Saida: Nenhuma.
// Pré-condição: Nenhuma.
// Pós-condição:  Nenhuma.
void menuPrincipal (){
    int op;
    arvore_PATRICIA* raiz = NULL;
    printMenuPrincipal();
    scanf("%d%*c", &op);

    system("cls");

    while(op != 0){
        switch(op){
            case CARREGARARQ:
                // Carregar arquivo texto.
                printf("\n-> Carregar arquivo texto\n\n");
                raiz = carregarArquivo(raiz);
                break;
            
            case CONSULTARPALAVRA:
                // Consultar palavra.
                printf("\n-> Consultar palavra\n\n");
                consultarPalavra(raiz);
                printf ("\n");
                break;

            case IMPRIMIRDIC:
                // Imprimir dicionario.
                printf("\n-> Imprimir dicionario\n\n");
                imprimirDicionario(raiz);
                break;

            case CARREGARSTOPWORDS:
                // Carregar arquivo de stopwords.
                printf("\n-> Carregar arquivo de stopowords\n\n");
                raiz = carregarStopwords(raiz);
                // raiz = testaRemocao(raiz);
                break;

            case IMPRIMIRNIVEIS:
                // Imprimir subarvore de niveis.
                printf("\n-> Imrpimir subarvores de niveis\n\n");
                imprimirPorNiveis(raiz);
                break;
            
            case SAIR:
                // Sair do programa.
                printf("\nEncerrando programa...\n");
                exit(0);
                break;
            
            default:
                // Nenhuma opção encontrada.
                printf("Opcao invalida.\n");
                break;
        }
       
        printf("\nAperte enter para continuar...");
        scanf("%*c");
        system("cls");
        
        printMenuPrincipal();
        scanf("%d%*c", &op);
        
        system("cls");
    }
}