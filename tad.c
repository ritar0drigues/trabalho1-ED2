#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.h"


void mostra_Stream(Stream* raiz){
    if(raiz){
        mostra_Stream(raiz->esquerda);
        printf("Nome: %s | Site: %s\n", raiz->nomestream, raiz->site);
        mostra_Stream(raiz->direita);
    }
}

Stream* Cadastra_stream(Stream* raiz, char* nome, char* site) {
    if(raiz == NULL){
        Stream* novo = (Stream*) malloc(sizeof(Stream));
        novo->nomestream = strdup(nome);
        novo->site = strdup(site);
        novo->categoria = NULL;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    if(strcmp(nome, raiz->nomestream) < 0){
        raiz->esquerda = Cadastra_stream(raiz->esquerda, nome, site);
    }
    else if(strcmp(nome, raiz->nomestream) > 0){
        raiz->direita = Cadastra_stream(raiz->direita, nome, site);
    }
    else{
        printf("Já existe uma Stream de nome '%s' cadastrada.\n", nome);
    }
    return raiz;
}

Stream* busca_Stream(Stream* raiz, char* nome) {
    Stream* aux = NULL;
    if (raiz){
        int cmp = strcmp(nome, raiz->nomestream);

        if (cmp == 0 ){
            aux = raiz;
        }
        else if(cmp < 0){
            aux = busca_Stream(raiz->esquerda, nome);
        }
        else{
            aux = busca_Stream(raiz->direita, nome);
        }
    }
    return aux;
}

Categorias* Cadastra_Categoria(Categorias* raiz, char* nome, char* tipo) {
    if(raiz == NULL){
        Categorias* novo = (Categorias*) malloc(sizeof(Categorias));
        novo->nomecategoria = strdup(nome);
        novo->tipo = strdup(tipo);
        novo->programas = NULL;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    if(strcmp(nome, raiz->nomecategoria) < 0){
        raiz->esquerda = Cadastra_Categoria(raiz->esquerda, nome, tipo);
    }
    else if(strcmp(nome, raiz->nomecategoria) > 0){
        raiz->direita = Cadastra_Categoria(raiz->direita, nome, tipo);
    }
    else{
        printf("Já existe uma categoria com o nome '%s' cadastrada.\n", nome);
    }
    return raiz;
}

Categorias* busca_Categorias(Categorias* raiz, char* nome){
    Categorias* aux = NULL;
    if (raiz){
        int cmp = strcmp(nome, raiz->nomecategoria);

        if (cmp == 0 ){
            aux = raiz;
        }

        else if(cmp < 0){
            aux = busca_Categorias(raiz->esquerda, nome);
        }
        else {
            aux = busca_Categorias(raiz->direita, nome);
        }
    }
    return aux;
}

void mostra_Categoria(Categorias* raiz){
    if(raiz){
        mostra_Categoria(raiz->esquerda);
        printf("Nome: %s | Tipo: %s\n", raiz->nomecategoria, raiz->tipo);
        mostra_Categoria(raiz->direita);
    }
}

Apresentadores* cadastrar_Apresentador(Apresentadores* lista, Stream* raizStreams) {
    char nome[50], nomeStream[50], nomeCategoria[50];
    printf("Nome do apresentador: ");
    scanf("%49[^\n]", nome);
    getchar();

    Apresentadores* novo = malloc(sizeof(Apresentadores));
    novo->nomeapresentador = strdup(nome);
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
    if (lista == NULL || strcmp(novo->nomeapresentador, lista->nomeapresentador) < 0) {
        novo->prox = lista;
        if (lista)
            lista->ant = novo;
        return novo;
    }
    Apresentadores* atual = lista;
    while (atual->prox && strcmp(novo->nomeapresentador, atual->prox->nomeapresentador) > 0) {
        atual = atual->prox;
    }
    novo->prox = atual->prox;
    if (atual->prox) {
        atual->prox->ant = novo;
    }
    atual->prox = novo;
    novo->ant = atual;

    return lista;
}

void Mostra_Apresentador(Apresentadores* lista){
    Apresentadores* atual = lista;
    if(atual){
        while(atual!=NULL){
            printf("%s\n", atual->nomeapresentador);
            atual = atual->prox;
        }
    }
    else{
        printf("Nenhum apresentador Cadastrado.\n");
    }
}

Apresentadores* Busca_Apresentador(char* nome, Apresentadores* lista){
    Apresentadores* atual = lista;
    while(atual!=NULL && strcmp(nome,atual->nomeapresentador)!=0){
        atual = atual->prox;
    }
    return atual;
}

Programas* Cadastra_Programa(Programas* raiz,char* nome,Apresentadores* lista, Stream* stream, Categorias* categoria) {
    if(raiz == NULL){
        char periodicidade[50], duracao[50],inicio[50],tipo[50],apresentador[50];
        Programas* novo = (Programas*) malloc(sizeof(Programas));
        novo->nomeprograma = strdup(nome);
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
        if (strcmp(aux->categoria->nomecategoria, categoria->nomecategoria) != 0 ||strcmp(aux->streamatual->nomestream, stream->nomestream) != 0) {
            printf("ERRO!! Apresentador não corresponde à categoria ou stream.\n");
            return NULL;
        }
        novo->apresentador = aux;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    if(strcmp(nome, raiz->nomeprograma) < 0){
        raiz->esquerda = Cadastra_Programa(raiz->esquerda, nome,lista,stream,categoria);
    }
    else if(strcmp(nome, raiz->nomeprograma) > 0){
        raiz->direita = Cadastra_Programa(raiz->direita, nome,lista,stream,categoria);
    }
    else{
        printf("Já existe um Programa com o nome '%s' cadastrada.\n", nome);
    }
    return raiz;
}

Programas* busca_Programa(Programas* raiz, char* nome) {
    Programas* aux = NULL;

    if (raiz){
        int cmp = strcmp(nome, raiz->nomeprograma);
        if (cmp == 0 ){
            aux = raiz;
        }

        else if(cmp < 0){
            aux = busca_Programa(raiz->esquerda, nome);
        }
        else {
            aux = busca_Programa(raiz->direita, nome);
        }
    }
    return aux;
}

void mostra_Programa(Programas* raiz){
    if(raiz){
        mostra_Programa(raiz->esquerda);
        printf("Nome: %s | Tipo: %s\n", raiz->nomeprograma, raiz->tipo);
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
}

int apresentadorTemProgramaNosProgramas(Programas* prog, Apresentadores* apresentador){
    int aux = 0;
    if(prog){
        if(prog->apresentador == apresentador){
            aux = 1;
        }
        if(apresentadorTemProgramaNosProgramas(prog->esquerda, apresentador)){
            aux = 1;
        }
        if(apresentadorTemProgramaNosProgramas(prog->direita, apresentador)){
            aux = 1;
        }
    }
    return aux;
}

int apresentadorTemProgramaNaStream(Categorias* cat, Apresentadores* apresentador) {
    int aux = 0;
    if (cat){
        if(apresentadorTemProgramaNaStream(cat->esquerda, apresentador)){
            aux = 1;
        }
        Programas* prog = cat->programas;
        if (prog && apresentadorTemProgramaNosProgramas(prog, apresentador)){
            aux = 1;
        }
        if (apresentadorTemProgramaNaStream(cat->direita, apresentador)){
            aux = 1;
        }
    }
    return aux;
}

void Associar_Stream(Stream* stream, Apresentadores* apresentador) {
    if (!stream) {
        printf("Stream inválida.\n");
    }
    else if (apresentadorTemProgramaNaStream(stream->categoria, apresentador)) {
        printf("Erro: Apresentador já possui programa nesta stream.\n");
    }
    else{
        Historico* novo = (Historico*) malloc(sizeof(Historico));
        novo->nomestream = strdup(stream->nomestream);
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
}