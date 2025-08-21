#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tad.h"


Apresentadores* menu_Programas(Programas** raiz,Apresentadores* lista,Stream* stream, Categorias* categoria){
    int op;
    do{
        printf("-------- Menu --------\n");
        printf("1- Adicionar Programa.\n");
        printf("2- Listar Programas.\n");
        printf("3- Buscar Programa.\n");
        printf("4- Excluir programa.\n");
        printf("5- Sair");
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
                    printf("Nome:%s\n", result->nomeprograma);
                    printf("Tipo:%s\n", result->tipo);
                }
                break;
            }
            case 4:{
                char nomePrograma[50];
                printf("Informe o nome do Programa a remover: ");
                scanf("%49[^\n]", nomePrograma);
                getchar();
                if(busca_Programa(categoria->programas, nomePrograma)){
                    categoria->programas = removePrograma(categoria->programas, nomePrograma);
                    printf("Programa removido com sucesso!\n");
                }
                else{
                    printf("Programa não encontrado na categoria.\n");
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

Apresentadores* menu_Categorias(Categorias** raiz,Apresentadores* lista,Stream* stream){
    int op = 1;
    do{
        printf("-------- Menu --------\n");
        printf("1- Adicionar Categoria.\n");
        printf("2- Listar Categorias.\n");
        printf("3- Buscar Categorias.\n");
        printf("4- Acessar Categorias.\n");
        printf("5- Excluir categoria.\n");
        printf("6- Sair.\n");
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
                    printf("Nome:%s\n", result->nomecategoria);
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
            case 5: {
                char nome[50];
                printf("Nome da categoria a remover: ");
                scanf("%49[^\n]", nome);
                getchar();
                
                (*raiz) = removeCategoria(*raiz, nome);
                break;
            }
            case 6:
                printf("Voltando...\n");
                break;
            default:
                printf("Voce digitou um caractere invalido.\n");
                break;
        }
    }while(op!=6);
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
                    printf("Nome:%s\n", result->nomestream);
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
                libera_Stream(raiz);
                libera_apresentadores(lista);
                printf("Encerrando...\n");
                break;
            default:
                printf("Você escreveu um valor inválido.\n");
                break;
        }

    }while(op!=3);
    return 0;
}