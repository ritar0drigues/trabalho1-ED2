#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#ifndef _MSC_VER
// Garante que strdup e strcasecmp fiquem declaradas no MinGW/GCC
char *strdup(const char *s);
int strcasecmp(const char *s1, const char *s2);
#endif

//1686 linhas de código


typedef struct Historico{
    char* nomestream;
    char* data_inicio;
    char* data_fim;
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
    Historico historico[2000];
    int inicio_historico;
    int fim_historico;
    int tamanho_historico;
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



//Apresentador
Apresentadores* criar_Apresentador(const char* nome);
void inserir_Apresentador(Apresentadores** lista, Apresentadores* novo);
void cadastrar_Apresentador(Apresentadores** lista,char* nome, int* flag);
void Mostra_Apresentador(Apresentadores* lista);
Apresentadores* Busca_Apresentador(const char* nome, Apresentadores* lista);
void atualizarFimHistorico(Apresentadores* apresentador);
void adicionarHistorico(Apresentadores* apresentador, const char* nomestream);
void Associar_Stream(Stream* stream, Apresentadores* apresentador, Categorias* novaCategoria,int* flag);
void ExibeApresentadoresPorCategoria(Apresentadores* lista, char* categoria, int* encontrou);
void Exibe_Historico(Apresentadores* apresentador);
void libera_apresentadores(Apresentadores* lista);

//Categoria
void Cadastra_Categoria(Categorias** lista, char* nome, char* tipo,int* cadastrou) ;
Categorias* busca_Categorias(Categorias* lista, char* nome);
void mostra_Categoria(Categorias* lista);
void removeNoListaCircular(Categorias** lista, Categorias* anterior, Categorias* remover,int* removeu);
void buscaCategoriaEAnterior(Categorias* lista, char* nome, Categorias** anterior, Categorias** remover);
void removeCategoria(Categorias** lista, char* nomeCategoria,int* removeu);
void libera_Categoria(Categorias* lista); 

//Programa
void lerDadosPrograma(char* periodicidade, char* duracao, char* inicio, char* tipo, char* apresentador);
Programas* criarPrograma(const char* nome, const char* periodicidade, const char* duracao, const char* inicio, const char* tipo, Apresentadores* apresentador);
void Cadastra_Programa(Programas** raiz, char* nome, Apresentadores* lista, Stream* stream, Categorias* categoria,int* flag,int* tem_prog,char* periodicidade, char* duracao, char* inicio, char* tipo, char* apresentadorNome);
Programas* busca_Programa(Programas* raiz, char* nome);
void mostra_Programa(Programas* raiz);
void copiarDadosPrograma(Programas* destino, Programas* origem);
Programas* maior_esquerda(Programas* Maior, Programas** Pai_Maior);
int eh_folha(Programas* no);
int SotemUm_Filho(Programas* no, Programas** filho);
void removePrograma(Programas** raiz, char* nomePrograma, int* achou);
void mostrarProgramasPorDiaSemana(Programas* raiz, const char* dia);
void mostrarDadosPrograma(Programas* programa);
void libera_Programa(Programas* raiz);
void liberardadosPrograma(Programas* prog);

//Stream
void mostra_Stream(Stream* raiz);
void Cadastra_stream(Stream** raiz, char* nome, char* site,int* flag);
Stream* busca_Stream(Stream* raiz, char* nome);
void FiltraStreamsporCategoria(Stream* raiz, char* nome,int* flag);
void FiltraStreamsporTipo(Stream* raiz, char* tipo,int* flag);
void ExibeApresentadoresDeUmaStream (Apresentadores*lista, char* nomeStream,int* flag);
void percorrerProgramasDiaHorario(Programas* raiz, const char* dia, const char* horario, int* encontrou);
void mostrarProgramasStreamDiaHorario(Stream* stream, const char* dia, const char* horario,int* encontrou);
void libera_Stream(Stream* raiz);

//Utils
int validarAssociacao(Stream* stream, Apresentadores* apresentador );
int validarTipoCategoria(const char* tipo);
int validarPeriodicidade(const char* periodicidade);
int validarDiaSemana(const char* dia);
int validarTipoPrograma(const char* tipo);
int validarURL(const char* url);
int validarFormatoHorario(const char* horario);
int validarDuracao(const char* duracao);
int programaAconteceNoDia(Programas* prog, const char* dia);
Apresentadores* validarApresentador(const char* nome, Apresentadores* lista, Stream* stream, Categorias* categoria);
int apresentadorTemProgramaNosProgramas(Programas* prog, Apresentadores* apresentador);
int apresentadorTemProgramaNaStream(Categorias* cat, Apresentadores* apresentador);
