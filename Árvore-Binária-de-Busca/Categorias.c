#include "tad.h"

void Cadastra_Categoria(Categorias** lista, char* nome, char* tipo,int* cadastrou) {
    Categorias* novo = (Categorias*) malloc(sizeof(Categorias));
    novo->nomecategoria = strdup(nome);
    novo->tipo = strdup(tipo);
    novo->programas = NULL;
    if ((*lista)){
        Categorias* atual = (*lista);
        /* Se o novo no vier antes do no "inicial" na ordem alfabética, o novo no se torna a referência para acessar a lista circular, "insere no inicio"*/
        if (strcmp(nome, (*lista)->nomecategoria) < 0){
            while (atual->prox != (*lista)) {
                atual = atual->prox;
            }
            atual->prox = novo;
            novo->prox = (*lista);
            *lista = novo;
            *cadastrou = 1;
        }
        else {
            /*Percorre até encontrar a posição correta do nó na ordem alfabética*/
            while (atual->prox != (*lista) && strcasecmp(atual->prox->nomecategoria, nome) < 0){
                atual = atual->prox;
            }
            if(strcasecmp(atual->prox->nomecategoria, nome) == 0){///Verifica se já existe categoria com o mesmo nome
                free(novo->nomecategoria);
                free(novo->tipo);
                free(novo);
            }
            else {
                *cadastrou = 1;
                novo->prox = atual->prox;
                atual->prox = novo;
            }
        }
    } 
    else {
        *cadastrou = 1;
        novo->prox = novo;
        *lista = novo;
    }
}

Categorias* busca_Categorias(Categorias* lista, char* nome){
    Categorias* resultado = NULL; 
    Categorias* atual = lista;
    if(lista){
        do {
            if(strcmp(atual->nomecategoria, nome) == 0){
                resultado = atual;
            }
            else{
                atual = atual->prox;
            }
        } while(atual != lista && !resultado);
    }
    return resultado;
}

void mostra_Categoria(Categorias* lista){
    if (lista) {
        Categorias* atual = lista;
        do {
            printf("Nome: %s\n", atual->nomecategoria);
            printf("Tipo: %s\n", atual->tipo);
            atual = atual->prox;
        } while (atual != lista);
    }
}

void removeNoListaCircular(Categorias** lista, Categorias* anterior, Categorias* remover,int* removeu){
    if ((*lista)->prox == *lista){//Se a lista só possui um nó
        (*lista) = NULL;
    }
    else if(remover == *lista){//Se o nó a remover está no início da lista
        Categorias* ultimo = (*lista);
        while (ultimo->prox != *lista){ 
            ultimo = ultimo->prox;
        }
        *lista = remover->prox;
        ultimo->prox = *lista;
    }
    else{//Se o nó está no meio da lista
        anterior->prox = remover->prox;
    }
    free(remover->nomecategoria);
    free(remover->tipo);
    free(remover);
    *removeu = 1;
}

void buscaCategoriaEAnterior(Categorias* lista, char* nome, Categorias** anterior, Categorias** remover){
    *anterior = lista;
    *remover = lista;
    if(lista){
        do{
            *anterior = *remover;
            *remover = (*remover)->prox;
        }while(*remover != lista && strcmp((*remover)->nomecategoria, nome) != 0);

        if(strcmp((*remover)->nomecategoria, nome) != 0){
            /*Se terminou o while e o nome de "remover" ainda é diferente do nome informado a categoria não foi encontrada*/
            *remover = NULL; 
        }
    }
}
 
void removeCategoria(Categorias** lista, char* nomeCategoria,int* removeu){
    if ((*lista)){
        Categorias* anterior = NULL;
        Categorias* remover = NULL;
        buscaCategoriaEAnterior((*lista), nomeCategoria, &anterior, &remover);
        if (remover){
            if (!remover->programas){//verifica se a categoria posssui programas só permite remover se ela não possuir
                removeNoListaCircular(lista, anterior, remover, removeu);
            }
        }
    }
}

void libera_Categoria(Categorias* lista){
    if(lista){
        Categorias* atual = lista->prox;
        while (atual != lista) {
            Categorias* temp = atual;
            atual = atual->prox;
            free(temp->tipo);
            free(temp->nomecategoria);
            libera_Programa(temp->programas);//Libera a árvore de programas da categoria
            free(temp);
        }
        /*Libera as informações do primeiro nó da lista*/
        free(lista->tipo);
        free(lista->nomecategoria);
        libera_Programa(lista->programas);
        free(lista);
    }
}