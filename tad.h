#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Historico{
    char* nomestream;
    char* data_inicio;
    char* data_fim;
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

void mostra_Stream(Stream* raiz);
Stream* Cadastra_stream(Stream* raiz, char* nome, char* site);
Stream* busca_Stream(Stream* raiz, char* nome);
Categorias* Cadastra_Categoria(Categorias* raiz, char* nome, char* tipo);
Categorias* busca_Categorias(Categorias* raiz, char* nome);
void mostra_Categoria(Categorias* raiz);
Apresentadores* cadastrar_Apresentador(Apresentadores* lista, Stream* raizStreams);
void Mostra_Apresentador(Apresentadores* lista);
Apresentadores* Busca_Apresentador(char* nome, Apresentadores* lista);
Programas* Cadastra_Programa(Programas* raiz,char* nome,Apresentadores* lista, Stream* stream, Categorias* categoria);
Programas* busca_Programa(Programas* raiz, char* nome);
void mostra_Programa(Programas* raiz);
Programas* removePrograma(Programas* raiz, char* nomePrograma);
void Exibe_Historico(Apresentadores* apresentador);
Categorias* removeCategoria(Categorias* raiz, char* nomeCategoria);
int apresentadorTemProgramaNosProgramas(Programas* prog, Apresentadores* apresentador);
int apresentadorTemProgramaNaStream(Categorias* cat, Apresentadores* apresentador);
void Associar_Stream(Stream* stream, Apresentadores* apresentador);
void libera_Programa(Programas* raiz);
void libera_Categoria(Categorias* raiz);
void libera_Stream(Stream* raiz);
void libera_Historico(Historico* lista);
void libera_apresentadores(Apresentadores* lista);