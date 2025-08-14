#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

typedef struct Historico{
    char* nomestream;
    char* periodo;
    struct Historico* prox;
}Historico;

typedef struct Categorias{
    char* tipo;
    char* nomecategoria;
    struct Categorias* esquerda;
    struct Categorias* direita;
    struct Programas* programas;
}Categorias;

typedef struct Stream{
    char* nomestream;
    char* site;
    Categorias* categoria;
    struct Stream* esquerda;
    struct Stream* direita;
}Stream;

typedef struct Apresentadores{
    char* nomeapresentador;
    Categorias* categoria;
    Stream* streamatual;
    Historico* lista;
    struct Apresentadores* ant;
    struct Apresentadores* prox;
}Apresentadores;

typedef struct Programas{
    char* nomeprograma;
    char* periodicidade;
    char* duracao;
    char* inicio;
    char* tipo;
    Apresentadores* apresentador;
    struct Programas* direita;
    struct Programas* esquerda;
}Programas;

void mostra_Stream(Stream* raiz){
    if(raiz==NULL){
        return;
    }
    mostra_Stream(raiz->esquerda);
    printf("Nome: %s | Site: %s\n", raiz->nome, raiz->site);
    mostra_Stream(raiz->direita);
}

Stream* Cadastra_stream(Stream* raiz, char* nome, char* site) {
    if(raiz == NULL){
        Stream* novo = (Stream*) malloc(sizeof(Stream));
        novo->nome = strdup(nome);
        novo->site = strdup(site);
        novo->categoria = NULL;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    if(strcmp(nome, raiz->nome) < 0){
        raiz->esquerda = Cadastra_stream(raiz->esquerda, nome, site);
    }
    else if(strcmp(nome, raiz->nome) > 0){
        raiz->direita = Cadastra_stream(raiz->direita, nome, site);
    }
    else{
        printf("Já existe uma Stream de nome '%s' cadastrada.\n", nome);
    }
    return raiz;
}

Stream* busca_Stream(Stream* raiz, char* nome) {
    if (raiz == NULL){
        return NULL;
    }

    int cmp = strcmp(nome, raiz->nome);
    if(cmp == 0){
        return raiz;
    }
    else if(cmp < 0){
        return busca_Stream(raiz->esquerda, nome);
    }
    else{
        return busca_Stream(raiz->direita, nome);
    }
}

Categorias* Cadastra_Categoria(Categorias* raiz, char* nome, char* tipo) {
    if(raiz == NULL){
        Categorias* novo = (Categorias*) malloc(sizeof(Categorias));
        novo->nome = strdup(nome);
        novo->tipo = strdup(tipo);
        novo->programas = NULL;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    if(strcmp(nome, raiz->nome) < 0){
        raiz->esquerda = Cadastra_Categoria(raiz->esquerda, nome, tipo);
    }
    else if(strcmp(nome, raiz->nome) > 0){
        raiz->direita = Cadastra_Categoria(raiz->direita, nome, tipo);
    }
    else{
        printf("Já existe uma categoria com o nome '%s' cadastrada.\n", nome);
    }
    return raiz;
}

Categorias* busca_Categorias(Categorias* raiz, char* nome) {
    if (raiz == NULL){
        return NULL;
    }

    int cmp = strcmp(nome, raiz->nome);
    if(cmp == 0){
        return raiz;
    }
    else if(cmp < 0){
        return busca_Categorias(raiz->esquerda, nome);
    }
    else{
        return busca_Categorias(raiz->direita, nome);
    }
}

void mostra_Categoria(Categorias* raiz){
    if(raiz==NULL){
        return;
    }
    mostra_Categoria(raiz->esquerda);
    printf("Nome: %s | Tipo: %s\n", raiz->nome, raiz->tipo);
    mostra_Categoria(raiz->direita);
}

Apresentadores* cadastrar_Apresentador(Apresentadores* lista, Stream* raizStreams) {
    char nome[50], nomeStream[50], nomeCategoria[50];
    printf("Nome do apresentador: ");
    scanf("%49[^\n]", nome);
    getchar();

    Apresentadores* novo = malloc(sizeof(Apresentadores));
    novo->nome = strdup(nome);
    novo->ant = novo->prox = NULL;
    novo->lista = NULL;

    printf("Stream atual: ");
    scanf("%49[^\n]", nomeStream);
    getchar();
    Stream* streamAtual = busca_Stream(raizStreams, nomeStream);
    if (!streamAtual) {
        printf("Stream não encontrada. Cadastro cancelado.\n");
        free(novo);
        return lista;
    }
    novo->streamatual = streamAtual;

    printf("Categoria que ele trabalha: ");
    scanf("%49[^\n]", nomeCategoria);
    getchar();
    Categorias* catAtual = busca_Categorias(streamAtual->categoria, nomeCategoria);
    if (!catAtual) {
        printf("Categoria não encontrada nessa stream. Cadastro cancelado.\n");
        free(novo);
        return lista;
    }
    novo->categoria = catAtual;
    if (lista == NULL || strcmp(novo->nome, lista->nome) < 0) {
        novo->prox = lista;
        if (lista) lista->ant = novo;
        return novo;
    }
    Apresentadores* atual = lista;
    while (atual->prox && strcmp(novo->nome, atual->prox->nome) > 0) {
        atual = atual->prox;
    }
    novo->prox = atual->prox;
    if (atual->prox) atual->prox->ant = novo;
    atual->prox = novo;
    novo->ant = atual;

    return lista;
}

void Mostra_Apresentador(Apresentadores* lista){
    Apresentadores* atual = lista;
    if(atual==NULL){
        printf("Nenhum apresentador Cadastrado.\n");
    }
    else{
        while(atual!=NULL){
            printf("%s\n", atual->nome);
            atual = atual->prox;
        }
    }
    return;
}

Apresentadores* Busca_Apresentador(char* nome, Apresentadores* lista){
    Apresentadores* atual = lista;
    while(atual!=NULL){
        if(strcmp(nome,atual->nome) == 0){
            break;
        }
        atual = atual->prox;
    }
    return atual;
}

Programas* Cadastra_Programa(Programas* raiz,char* nome,Apresentadores* lista, Stream* stream, Categorias* categoria) {
    if(raiz == NULL){
        char periodicidade[50], duracao[50],inicio[50],tipo[50],apresentador[50];
        Programas* novo = (Programas*) malloc(sizeof(Programas));
        novo->nome = strdup(nome);
        printf("Informe a periodicidade do prgrama:\n");
        scanf("%49[^\n]", periodicidade);
        getchar();
        novo->periodicidade = strdup(periodicidade);
        printf("Informe a duração do prgrama:\n");
        scanf("%49[^\n]", duracao);
        getchar();
        novo->duracao = strdup(duracao);
        printf("Informe o  horário de inicio do prgrama:\n");
        scanf("%49[^\n]", inicio);
        getchar();
        novo->inicio = strdup(inicio);
        printf("Informe o tipo do prgrama:\n");
        scanf("%49[^\n]", tipo);
        getchar();
        novo->tipo = strdup(tipo);
        printf("Informe o nome do apresentador:\n");
        scanf("%49[^\n]", apresentador);
        getchar();
        Apresentadores* aux = Busca_Apresentador(apresentador,lista);
        if(aux==NULL){
            printf("ERRO!! Apresentador não cadastrado.\n");
            return NULL;
        }
        if (strcmp(aux->categoria->nome, categoria->nome) != 0 ||strcmp(aux->streamatual->nome, stream->nome) != 0) {
            printf("ERRO!! Apresentador não corresponde à categoria ou stream.\n");
            return NULL;
        }
        novo->apresentador = aux;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    if(strcmp(nome, raiz->nome) < 0){
        raiz->esquerda = Cadastra_Programa(raiz->esquerda, nome,lista,stream,categoria);
    }
    else if(strcmp(nome, raiz->nome) > 0){
        raiz->direita = Cadastra_Programa(raiz->direita, nome,lista,stream,categoria);
    }
    else{
        printf("Já existe um Programa com o nome '%s' cadastrada.\n", nome);
    }
    return raiz;
}

Programas* busca_Programa(Programas* raiz, char* nome) {
    if (raiz == NULL){
        return NULL;
    }

    int cmp = strcmp(nome, raiz->nome);
    if(cmp == 0){
        return raiz;
    }
    else if(cmp < 0){
        return busca_Programa(raiz->esquerda, nome);
    }
    else{
        return busca_Programa(raiz->direita, nome);
    }
}

void mostra_Programa(Programas* raiz){
    if(raiz!=NULL){
        mostra_Programa(raiz->esquerda);
        printf("Nome: %s | Tipo: %s\n", raiz->nome, raiz->tipo);
        mostra_Programa(raiz->direita);
    }
}

void Exibe_Historico(Apresentadores* apresentador){
    Historico* atual = apresentador->lista;
    if(atual==NULL){
        printf("O histórico está vazio.\n");
    }
    else{
        while(atual!=NULL){
            printf("Stream: %s\n", atual->nomestream);
            printf("Periodo: %s\n", atual->periodo);
            atual = atual->prox;
        }
    }
    return;
}

Apresentadores* menu_Programas(Programas** raiz,Apresentadores* lista,Stream* stream, Categorias* categoria){
    int op;
    do{
        printf("-------- Menu --------\n");
        printf("1- Adicionar Programa.\n");
        printf("2- Listar Programas.\n");
        printf("3- Buscar Programa.\n");
        printf("4- Sair.\n");
        scanf("%d", &op);
        getchar();
        switch(op){
            case 1:{
                char nome[50];
                printf("Informe o nome do programa.\n");
                scanf("%49[^\n]", nome);
                getchar();
                if (busca_Programa((*raiz), nome) != NULL) {
                    printf("ERRO!! Programa '%s' já cadastrado nesta categoria.\n", nome);
                }
                else{
                    (*raiz) = Cadastra_Programa((*raiz),nome,lista,stream,categoria);
                }
                break;
            }
            case 2:
                if((*raiz)){
                    mostra_Programa((*raiz));
                }
                else{
                    printf("Nenhum programa cadastrado.\n");
                }
                break;
            case 3:{
                char nome[50];
                printf("Informe o nome do programa.\n");
                scanf("%49[^\n]", nome);
                getchar();
                Programas* result = busca_Programa((*raiz),nome);
                if(result == NULL){
                    printf("Programa não encontrado.\n");
                }
                else{
                    printf("Nome:%s\n", result->nome);
                    printf("Tipo:%s\n", result->tipo);
                }
                break;
            }
            case 4:
                printf("Voltando...\n");
                break;
            default:
                printf("Voce digitou um caractere invalido.\n");
                break;
        }
    }while(op!=4);
    return lista;
}

Apresentadores* menu_Categorias(Categorias** raiz,Apresentadores* lista,Stream* stream){
    int op = 1;
    do{
        printf("-------- Menu --------\n");
        printf("1- Adicionar Categoria.\n");
        printf("2- Listar Categorias.\n");
        printf("3- Buscar Categorias.\n");
        printf("4- Acessar Categorias.\n");
        printf("5- Sair.\n");
        scanf("%d", &op);
        getchar();
        switch(op){
            case 1:{
                char nome[50],categoria[50];
                printf("Informe o nome da categoria.\n");
                scanf("%49[^\n]", nome);
                getchar();
                printf("Informe o tipo da categoria.\n");
                scanf("%49[^\n]", categoria);
                getchar();
                (*raiz) = Cadastra_Categoria((*raiz),nome,categoria);
                break;
            }
            case 2:
                if((*raiz)==NULL){
                    printf("Arvore vazia.\n");
                }
                else{
                    mostra_Categoria((*raiz));
                }
                break;
            case 3:{
                char nome[50];
                printf("Informe o nome da Categoria.\n");
                scanf("%49[^\n]", nome);
                getchar();
                Categorias* result = busca_Categorias((*raiz),nome);
                if(result == NULL){
                    printf("Categoria não encontrada.\n");
                }
                else{
                    printf("Nome:%s\n", result->nome);
                    printf("Tipo:%s\n", result->tipo);
                }
                break;
            }
            case 4:{
                char nome[50];
                printf("Informe o  nome da Categoria:\n");
                scanf("%49[^\n]", nome);
                getchar();
                Categorias* result = busca_Categorias((*raiz),nome);
                if(result == NULL){
                    printf("Categoria não encontrada.\n");
                }
                else{
                    lista = menu_Programas(&(result->programas),lista,stream, result);
                }
                break;
                }
            case 5:
                printf("Voltando...\n");
                break;
            default:
                printf("Voce digitou um caractere invalido.\n");
                break;
        }
    }while(op!=5);
    return lista;
}

Apresentadores* menu_Stream(Stream** raiz, Apresentadores* lista){
    int op;

    do{
        printf("Menu\n");
        printf("1-Cadastrar Stream\n");
        printf("2- Buscar Stream\n");
        printf("3- listar stream\n");
        printf("4- Editar Categorias.\n");
        printf("5- Sair.\n");
        scanf("%d", &op);
        getchar();
        switch(op){
            case 1: {
                char nome[50];
                char site[50];
                printf("Informe o nome da stream.\n");
                scanf("%49[^\n]", nome);
                getchar();
                printf("Informe o site da stream.\n");
                scanf("%49[^\n]", site);
                getchar();
                (*raiz) = Cadastra_stream((*raiz),nome,site);
                break;
            }
            case 2:{
                char nome[50];
                printf("Informe o nome da stream.\n");
                scanf("%49[^\n]", nome);
                getchar();
                Stream* result = busca_Stream((*raiz),nome);
                if(result == NULL){
                    printf("Stream não encontrada.\n");
                }
                else{
                    printf("Nome:%s\n", result->nome);
                    printf("Site:%s\n", result->site);
                }
                break;
            }
            case 3:
                if((*raiz)==NULL){
                    printf("Arvore vazia.\n");
                }
                mostra_Stream((*raiz));
                break;
            case 4:{
                char nome[50];
                printf("Informe o  nome da Stream:\n");
                scanf("%49[^\n]", nome);
                getchar();
                Stream* result = busca_Stream((*raiz),nome);
                if(result == NULL){
                    printf("Stream não encontrada.\n");
                }
                else{
                    lista = menu_Categorias(&(result->categoria),lista,(*raiz));
                }
                break;
                }
            case 5:
                printf("Encerrando...\n");
                break;
            default:
                printf("Você digitou um caractere inválido.\n");
                break;
        }
    }while(op!=5);
    return lista;
}

int apresentadorTemProgramaNosProgramas(Programas* prog, Apresentadores* apresentador){
    if(prog){
        if(prog->apresentador == apresentador){
            return 1;
        }
        if(apresentadorTemProgramaNosProgramas(prog->esquerda, apresentador)){
            return 1;
        }
        if(apresentadorTemProgramaNosProgramas(prog->direita, apresentador)){
            return 1;
        }
    }
    return 0;
}

int apresentadorTemProgramaNaStream(Categorias* cat, Apresentadores* apresentador) {
    if (cat){
        if(apresentadorTemProgramaNaStream(cat->esquerda, apresentador)){
            return 1;
        }
        Programas* prog = cat->programas;
        if (prog && apresentadorTemProgramaNosProgramas(prog, apresentador)){
            return 1;
        }
        if (apresentadorTemProgramaNaStream(cat->direita, apresentador)){
            return 1;
        }
    }
    return 0;
}

void Associar_Stream(Stream* stream, Apresentadores* apresentador) {
    if (!stream) {
        printf("Stream inválida.\n");
        return;
    }

    if (apresentadorTemProgramaNaStream(stream->categoria, apresentador)) {
        printf("Erro: Apresentador já possui programa nesta stream.\n");
        return;
    }
    Historico* novo = (Historico*) malloc(sizeof(Historico));
    novo->nomestream = strdup(stream->nome);
    novo->periodo = strdup("a");
    novo->prox = NULL;
    if(apresentador->lista == NULL){
        apresentador->lista = novo;
    }
    else{
        Historico* atual = apresentador->lista;
        while(atual->prox != NULL){
            atual = atual->prox;
        }
        atual->prox = novo;
    }
    apresentador->streamatual = stream;
    printf("Stream associada/alterada com sucesso!\n");
}

Apresentadores* menu_Apresentador(Apresentadores* lista, Stream* raiz){
    int op;
    do{
        printf("Menu\n");
        printf("1- Cadastrar Apresentador.\n");
        printf("2- Listar Apresentadores\n");
        printf("3- Associar a uma Stream\n");
        printf("4-Histórico do apresentador.\n");
        printf("5- Sair\n");
        scanf("%d", &op);
        getchar();
        switch(op){
            case 1:
                lista = cadastrar_Apresentador(lista,raiz);
                break;
            case 2:
                Mostra_Apresentador(lista);
                break;
            case 3:{
                char buscarap[50],buscarst[50];
                printf("Informe o nome do apresentador.\n");
                scanf("%49[^\n]",buscarap);
                getchar();
                printf("Informe o nome da stream:\n");
                scanf("%49[^\n]", buscarst);
                getchar();
                Apresentadores* apresentador = Busca_Apresentador(buscarap,lista);
                Stream* stream = busca_Stream(raiz,buscarst);
                if(apresentador==NULL){
                    printf("Apresentador não encontrado.\n");
                }
                if(stream==NULL){
                    printf("Stream não encontrada.\n");
                }
                else{
                    Associar_Stream(stream,apresentador);
                }
                break;
            }
            case 4:{
                char buscar[50];
                printf("Informe o nome do apresentador.\n");
                scanf("%49[^\n]",buscar);
                getchar();
                Apresentadores* apresentador = Busca_Apresentador(buscar,lista);
                if(apresentador==NULL){
                    printf("Apresentador não encontrado.\n");
                }
                else{
                    Exibe_Historico(apresentador);
                }
                break;
            }
            case 5:
                printf("Voltando...\n");
                break;
            default:
                printf("Voce digitou uma opção inválida.\n");
                break;
                
        }
    }while(op!=5);
    return lista;
}

int main(){
    Stream* raiz = NULL;
    Apresentadores* lista = NULL;
    int op;
    do{
        printf(" _________________\n");
        printf("|Menu             |\n");
        printf("|1- Streams       |\n");
        printf("|2- Apresentadores|\n");
        printf("|3- Sair          |\n");
        printf("|_________________|\n");
        scanf("%d", &op);
        getchar();
        switch(op){
            case 1:
                lista = menu_Stream(&raiz,lista);
                break;
            case 2:
                lista = menu_Apresentador(lista,raiz);
                break;
            case 3:
                printf("Encerrando...\n");
                break;
            default:
                printf("Você escreveu um valor inválido.\n");
                break;
        }

    }while(op!=3);
    return 0;
}