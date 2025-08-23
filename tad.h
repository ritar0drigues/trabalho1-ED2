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
    struct Categorias* prox;
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
Categorias* Cadastra_Categoria(Categorias* lista, char* nome, char* tipo);
Categorias* busca_Categorias(Categorias* lista, char* nome);
void mostra_Categoria(Categorias* lista);
Apresentadores* criar_Apresentador(const char* nome, Stream* streamAtual, Categorias* categoria);
Apresentadores* inserir_Apresentador(Apresentadores* lista, Apresentadores* novo);
Apresentadores* cadastrar_Apresentador(Apresentadores* lista, Stream* raizStreams);
void Mostra_Apresentador(Apresentadores* lista);
Apresentadores* Busca_Apresentador(const char* nome, Apresentadores* lista);
void lerDadosPrograma(char* periodicidade, char* duracao, char* inicio, char* tipo, char* apresentador);
Programas* criarPrograma(const char* nome, const char* periodicidade, const char* duracao, const char* inicio, const char* tipo, Apresentadores* apresentador);
Apresentadores* validarApresentador(const char* nome, Apresentadores* lista, Stream* stream, Categorias* categoria);
Programas* Cadastra_Programa(Programas* raiz,char* nome,Apresentadores* lista, Stream* stream, Categorias* categoria);
Programas* busca_Programa(Programas* raiz, char* nome);
void mostra_Programa(Programas* raiz);
void atualizarFimHistorico(Historico* historico);
void liberarPrograma(Programas* prog);
void copiarDadosPrograma(Programas* destino, Programas* origem);
Programas* removePrograma(Programas* raiz, char* nomePrograma);
void Exibe_Historico(Apresentadores* apresentador);
Categorias* removeNoListaCircular(Categorias* lista, Categorias* anterior, Categorias* remover);
void buscaCategoriaEAnterior(Categorias* lista, char* nome, Categorias** anterior, Categorias** remover);
Categorias* removeCategoria(Categorias* lista, char* nomeCategoria);
int apresentadorTemProgramaNosProgramas(Programas* prog, Apresentadores* apresentador);
int apresentadorTemProgramaNaStream(Categorias* cat, Apresentadores* apresentador);
int validarAssociacao(Stream* stream, Apresentadores* apresentador );
void adicionarHistorico(Apresentadores* apresentador, const char* nomestream);
void Associar_Stream(Stream* stream, Apresentadores* apresentador, Categorias* novaCategoria);
void libera_Programa(Programas* raiz);
void libera_Categoria(Categorias* lista); 
void libera_Stream(Stream* raiz);
void libera_Historico(Historico* lista);
void libera_apresentadores(Apresentadores* lista);