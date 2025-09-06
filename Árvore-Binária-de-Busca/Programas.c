#include "tad.h"

void lerDadosPrograma(char* periodicidade, char* duracao, char* inicio, char* tipo, char* apresentador) {
    int periodicidade_valida = 0;
    int duracao_valida = 0;
    int inicio_valido = 0;
    int  tipo_valido = 0;
    do{
        printf("Informe a periodicidade (ex: diário, semanal-segunda, semanal-segunda-quarta-sexta):\n");
        scanf("%49[^\n]", periodicidade);
        getchar();
        if (!validarPeriodicidade(periodicidade)){
            printf("ERRO: Periodicidade inválida!\n");
            printf("Use: 'diário' ou 'semanal-dia1-dia2...' (ex: semanal-segunda-quarta-sexta)\n");
        }
        else {
            periodicidade_valida = 1;
        }
    }while(!periodicidade_valida);

    do {
        printf("Informe a duração do programa (formato HH:MM, ex: 01:30):\n");
        scanf("%49[^\n]", duracao);
        getchar();
        
        if (!validarDuracao(duracao)) {
            printf("ERRO: Duração inválida! Use formato HH:MM (ex: 01:30, 02:00).\n");
            printf("Duração deve ser entre 00:01 e 24:00.\n");
        }
        else {
            duracao_valida = 1;
        }
    } while (!duracao_valida);

    do {
        printf("Informe o horário de início do programa (formato HH:MM, ex: 14:30):\n");
        scanf("%49[^\n]", inicio);
        getchar();
        
        if (!validarFormatoHorario(inicio)) {
            printf("ERRO: Horário inválido! Use formato HH:MM (ex: 09:00, 14:30).\n");
            printf("Horas: 00-23, Minutos: 00-59.\n");
        }
        else {
            inicio_valido = 1;
        }
    } while (!inicio_valido);

    do {
        printf("Informe o tipo do programa (ao vivo/sob demanda):\n");
        scanf("%49[^\n]", tipo);
        getchar();
        if (!validarTipoPrograma(tipo)) {
            printf("ERRO: Tipo de programa inválido! Use: ao vivo ou sob demanda\n");
        }
        else{
            tipo_valido = 1;
        }
    }while(!tipo_valido);

    printf("Informe o nome do apresentador:\n");
    scanf("%49[^\n]", apresentador); 
    getchar();
}

Programas* criarPrograma(const char* nome, const char* periodicidade, const char* duracao, const char* inicio, const char* tipo, Apresentadores* apresentador) {
    Programas* novo = malloc(sizeof(Programas));
    if(novo){
        novo->nomeprograma = strdup(nome);
        novo->periodicidade = strdup(periodicidade);
        novo->duracao = strdup(duracao);
        novo->inicio = strdup(inicio);
        novo->tipo = strdup(tipo);
        novo->apresentador = apresentador;
        novo->esquerda = novo->direita = NULL;
    }
    return novo;
}

void Cadastra_Programa(Programas** raiz, char* nome, Apresentadores* lista, Stream* stream, Categorias* categoria,int* flag,int* tem_prog) {
    char periodicidade[50], duracao[50], inicio[50], tipo[50], apresentadorNome[50];

    if((*raiz)){
        if(strcasecmp(nome, (*raiz)->nomeprograma) < 0){
            Cadastra_Programa(&(*raiz)->esquerda, nome, lista, stream, categoria,flag,tem_prog);
        } 
        else if(strcasecmp(nome, (*raiz)->nomeprograma) > 0){
            Cadastra_Programa(&(*raiz)->direita, nome, lista, stream, categoria,flag,tem_prog);
        } 
        else{
            *tem_prog = 0;
        }
    }
    else{
        lerDadosPrograma(periodicidade, duracao, inicio, tipo, apresentadorNome);
        Apresentadores* apresentador = validarApresentador(apresentadorNome, lista, stream, categoria);/*Verifica se a Stream e a Categoria do programa são as mesmas do apresentador*/
        if(apresentador){
            (*raiz) = criarPrograma(nome, periodicidade, duracao, inicio, tipo, apresentador);
            *flag = 1;
        } 
    }
}


Programas* busca_Programa(Programas* raiz, char* nome) {
    Programas* aux = NULL;
    if (raiz){
        int cmp = strcmp(nome, raiz->nomeprograma);
        if(cmp==0){
            aux  = raiz;
        }
        else if(cmp < 0){
            aux = busca_Programa(raiz->esquerda, nome);
        }
        else{
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

void copiarDadosPrograma(Programas* destino, Programas* origem) {
    if (destino && origem){
        free(destino->nomeprograma);
        free(destino->periodicidade);
        free(destino->duracao);
        free(destino->inicio);
        free(destino->tipo);

        //copia os dados do nó de origem para o destino
        destino->nomeprograma = strdup(origem->nomeprograma);
        destino->periodicidade = strdup(origem->periodicidade);
        destino->duracao = strdup(origem->duracao);
        destino->inicio = strdup(origem->inicio);
        destino->tipo = strdup(origem->tipo);
        destino->apresentador = origem->apresentador;
    }
}

Programas* maior_esquerda(Programas* Maior, Programas** Pai_Maior){
    while (Maior->direita != NULL) {
        *Pai_Maior = Maior;
        Maior = Maior->direita;         
    }
    return Maior;
}

int eh_folha(Programas* no){
    int cont = 0;
    if(no->direita==NULL && no->esquerda==NULL)
        cont = 1;
    return cont;
}

int SotemUm_Filho(Programas* no, Programas** filho){
    int aux = 0;
    if(no->direita==NULL && no->esquerda!=NULL){
        aux = 1;
        *filho = no->esquerda;
    }
    else if(no->direita!=NULL && no->esquerda==NULL){
        aux = 1;
        *filho = no->direita;
    }
    return aux;
}

void removePrograma(Programas** raiz, char* nomePrograma, int* achou){
    if(*raiz!=NULL){
        if(strcmp(nomePrograma, (*raiz)->nomeprograma)==0){
            Programas* aux, *No_maior,*Pai_Maior, *No_filho;
            *achou = 1;
            aux = *raiz;
            if(eh_folha(*raiz)){
                *raiz = NULL;
            }
            else{
                if(SotemUm_Filho(*raiz,&No_filho)){
                    *raiz = No_filho;
                }
                else{
                    Pai_Maior = NULL;
                    No_maior = maior_esquerda(*raiz,&Pai_Maior);
                    copiarDadosPrograma((*raiz),No_maior);
                    if (Pai_Maior == NULL){
                        (*raiz)->esquerda = No_maior->esquerda;
                    }
                    else{
                        Pai_Maior->direita = No_maior->esquerda;
                    }
                    aux = No_maior;
                }
            }
            liberardadosPrograma(aux);
        }
        else if(strcmp(nomePrograma, (*raiz)->nomeprograma)<0){
            removePrograma(&(*raiz)->esquerda,nomePrograma,achou);
        }
        else{
            removePrograma(&(*raiz)->direita,nomePrograma,achou);
        }
    }
}
 
void mostrarProgramasPorDiaSemana(Programas* raiz, const char* dia) {
    if(raiz) {
        mostrarProgramasPorDiaSemana(raiz->esquerda, dia);        
        if(programaAconteceNoDia(raiz, dia)) {
            printf("Programa: %s | Horário: %s | Periodicidade: %s\n", 
                   raiz->nomeprograma, raiz->inicio, raiz->periodicidade);
        }        
        mostrarProgramasPorDiaSemana(raiz->direita, dia);
    }
}

void mostrarDadosPrograma(Programas* programa) {
    if(programa) {
        printf("=== DADOS DO PROGRAMA ===\n");
        printf("Nome: %s\n", programa->nomeprograma);
        printf("Tipo: %s\n", programa->tipo);
        printf("Início: %s\n", programa->inicio);
        printf("Duração: %s\n", programa->duracao);
        printf("Periodicidade: %s\n", programa->periodicidade);
        printf("Apresentador: %s\n", programa->apresentador->nomeapresentador);
        printf("Stream: %s\n", programa->apresentador->streamatual->nomestream);
        printf("Categoria: %s\n", programa->apresentador->categoria->nomecategoria);
    }
}

void libera_Programa(Programas* raiz){
    if(raiz){  
        libera_Programa(raiz->direita);
        libera_Programa(raiz->esquerda);
        free(raiz->nomeprograma); 
        free(raiz->periodicidade);
        free(raiz->duracao);
        free(raiz->inicio);
        free(raiz->tipo);
        free(raiz);
    }
}

void liberardadosPrograma(Programas* prog){
    if(prog){
        free(prog->nomeprograma);
        free(prog->periodicidade);
        free(prog->duracao);
        free(prog->inicio);
        free(prog->tipo);
        free(prog);
    }
}