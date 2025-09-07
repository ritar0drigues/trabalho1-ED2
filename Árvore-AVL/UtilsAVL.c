#include "tadAVL.h"

int validarAssociacao(Stream* stream, Apresentadores* apresentador){
    int aux = 1;
    if (!stream || !apresentador) {
        printf("Erro: Stream ou apresentador inválido.\n");
        aux = 0;
    }
    else{
        if (apresentadorTemProgramaNaStream(stream->categoria, apresentador)) {
            printf("Erro: Apresentador já possui programa nesta stream.\n");
            aux = 0;
        }
        else if(apresentadorTemProgramaNaStream(apresentador->categoria, apresentador)){
            printf("Erro: O apresentador apresenta um programa na stream %s categoria %s.\n",apresentador->streamatual->nomestream, apresentador->categoria->nomecategoria);
            aux = 0;
        }
    }
    return aux;
}

int validarTipoCategoria(const char* tipo){
    const char* tipos_validos[] = {"notícias", "esporte", "entretenimento"};
    int num_tipos = 3;
    int valido = 0;
    for (int i = 0; i < num_tipos; i++) {
        if (strcasecmp(tipo, tipos_validos[i]) == 0) {
            valido = 1;
        }
    }
    return valido;
}

int validarPeriodicidade(const char* periodicidade) {
    int valido = 0;

    if (periodicidade && strlen(periodicidade) > 0) {
        char copy[50];
        strncpy(copy, periodicidade, sizeof(copy) - 1);
        copy[sizeof(copy) - 1] = '\0';

        for (int i = 0; copy[i]; i++) {
            copy[i] = tolower(copy[i]);
        }


        if (strcmp(copy, "diário") == 0 || strcmp(copy, "diario") == 0) {
            valido = 1;
        }

        else if (strstr(copy, "semanal-") != NULL) {
            char *dias = copy + 8;
            if (strlen(dias) > 0) {
                int diasValidos = 1;
                char *token = strtok(dias, "-");
                while (token != NULL) {
                    if (!validarDiaSemana(token)) {
                        diasValidos = 0;
                        break;
                    }
                    token = strtok(NULL, "-");
                }
                if (diasValidos) {
                    valido = 1;
                }
            }
        }
    }

    return valido; 
}


int validarDiaSemana(const char* dia) {
    const char* dias_validos[] = {"segunda", "terca", "quarta", "quinta", "sexta", "sabado", "domingo"};
    int valido = 0;
    for(int i = 0; i < 7; i++) {
        if(strcmp(dia, dias_validos[i]) == 0){
            valido = 1;
        }
    }
    return valido;
}

int validarTipoPrograma(const char* tipo) {
    const char* tipos_validos[] = {"ao vivo", "sob demanda"};
    int num_tipos = 2;
    int valido = 0;
    for (int i = 0; i < num_tipos; i++) {
        if (strcasecmp(tipo, tipos_validos[i]) == 0) {
            valido = 1;
        }
    }
    return valido;
}

int validarURL(const char* url) {
    int valido = 1;
    if (!url || strlen(url) < 10){
        valido = 0; 
    }
    else{
        int is_http = (strncmp(url, "http://", 7) == 0);
        int is_https = (strncmp(url, "https://", 8) == 0);
        if(!is_http && !is_https){
            valido = 0;
        }
        else{
            const char* dominio = strstr(url, "://");
            if(!dominio){
                valido = 0;
            }
            else{
                dominio += 3;
                if(strlen(dominio) == 0){
                    valido = 0;
                }
                else if(strchr(url, ' ')){
                    valido = 0;
                }
            }
        }
    }
    return valido;
}

int validarFormatoHorario(const char* horario) {
    int valido = 1;
    if (horario == NULL || strlen(horario) != 5) {
        valido = 0;
    }
    else{
        if (horario[2] != ':') {
            valido = 0;
        }
        else{
            for (int i = 0; i < 5; i++) {
                if (i != 2) { 
                    if (horario[i] < '0' || horario[i] > '9') {
                        valido = 0;
                    }
                }
            }
            if(valido){
                int horas = (horario[0] - '0') * 10 + (horario[1] - '0');
                int minutos = (horario[3] - '0') * 10 + (horario[4] - '0');
                if (horas < 0 || horas > 23) {
                    valido = 0;
                }
                else if (minutos < 0 || minutos > 59) {
                    valido = 0;
                }
            }
        }
    }
    
    return valido;
}

int validarDuracao(const char* duracao) {
    int valido = 0;
    if (validarFormatoHorario(duracao)) {
        int horas = (duracao[0] - '0') * 10 + (duracao[1] - '0');
        int minutos = (duracao[3] - '0') * 10 + (duracao[4] - '0');
        if (horas >= 0 && horas <= 99 && minutos >= 0 && minutos <= 59) {
            valido = 1;
        }
    }
    return valido;
}

int programaAconteceNoDia(Programas* prog, const char* dia) {
    int result = 0;
    if(prog && prog->periodicidade && dia){
        char periodicidade_copy[100];
        char dia_lower[50];
        strncpy(periodicidade_copy, prog->periodicidade, sizeof(periodicidade_copy)-1);
        periodicidade_copy[sizeof(periodicidade_copy)-1] = '\0';
        strncpy(dia_lower, dia, sizeof(dia_lower)-1);
        dia_lower[sizeof(dia_lower)-1] = '\0';

        for(int i = 0; periodicidade_copy[i]; i++) {
            periodicidade_copy[i] = tolower(periodicidade_copy[i]);
        }
        for(int i = 0; dia_lower[i]; i++) {
            dia_lower[i] = tolower(dia_lower[i]);
        }
        
        if(strcmp(periodicidade_copy, "diário") == 0 || strcmp(periodicidade_copy, "diario") == 0) {
            result = 1;
        }        
        else if(strstr(periodicidade_copy, "semanal-") != NULL) {
            char *dias_semana = periodicidade_copy + 8;
            char padrao[60];
            snprintf(padrao, sizeof(padrao), "-%s-", dia_lower);
            if (strstr(dias_semana, padrao) != NULL) {
                result = 1;
            }
            else if (strncmp(dias_semana, dia_lower, strlen(dia_lower)) == 0 && 
                    (dias_semana[strlen(dia_lower)] == '-' || dias_semana[strlen(dia_lower)] == '\0')) {
                result = 1;
            }
            else if (strstr(dias_semana, "-") != NULL) {
                char *ultimo_dia = strrchr(dias_semana, '-') + 1;
                if (strcmp(ultimo_dia, dia_lower) == 0) {
                    result = 1;
                }
            }
            else if (strcmp(dias_semana, dia_lower) == 0) {
                result = 1;
            }
        }
    }
    return result;
}

Apresentadores* validarApresentador(const char* nome, Apresentadores* lista, Stream* stream, Categorias* categoria) {
    Apresentadores* pont = Busca_Apresentador(nome, lista);
    if(pont) {
        if (!pont->categoria || !pont->streamatual) {
            pont = NULL;
        } 
        else if(strcmp(pont->categoria->nomecategoria, categoria->nomecategoria) != 0 || strcmp(pont->streamatual->nomestream, stream->nomestream) != 0) {
            pont = NULL;
        }
    }
    return pont;
}


int apresentadorTemProgramaNosProgramas(Programas* prog, Apresentadores* apresentador){
    int aux = 0;
    if(prog){
        if(prog->apresentador == apresentador){
            aux = 1;
        }
        else if (apresentadorTemProgramaNosProgramas(prog->esquerda, apresentador) || apresentadorTemProgramaNosProgramas(prog->direita, apresentador)){//Se não é o mesmo a função é chamada novamente para a subarvore da direita e para a da esquerda
            aux = 1;
        }
    }
    return aux;
}

int apresentadorTemProgramaNaStream(Categorias* lista, Apresentadores* apresentador) {
    int aux = 0;
    if(lista){
        Categorias* atual = lista;
        do{
            if(atual->programas && apresentadorTemProgramaNosProgramas(atual->programas, apresentador)){
                aux = 1;
            }
            atual = atual->prox;
        }while(atual!=lista);
    }
    return aux;
}