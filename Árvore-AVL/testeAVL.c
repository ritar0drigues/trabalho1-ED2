#include "tadAVL.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_STREAMS 50000
#define NUM_PROGRAMAS 50000
#define NUM_APRESENTADORES 50000
#define NUM_CATEGORIAS 1

// Arquivos para salvar resultados
FILE *arquivo_streamsAVL;
FILE *arquivo_programasAVL;

void gerar_nome_aleatorio(char* buffer, int tamanho) {
    const char* prefixos[] = {"Alpha", "Beta", "Gamma", "Delta", "Epsilon", "Zeta", "Eta", "Theta", "Iota", "Kappa","Stream", "TV", "Live", "Channel", "Broadcast", "Media", "Net", "Cast", "Vision", "Hub","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    const char* sufixos[] = {"Stream", "TV", "Live", "Channel", "Broadcast", "Media", "Net", "Cast", "Vision", "Hub","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","Alpha", "Beta", "Gamma", "Delta", "Epsilon", "Zeta", "Eta", "Theta", "Iota", "Kappa"};
    
    int pre_idx = rand() % 10;
    int suf_idx = rand() % 10;
    int num = rand() % 1000000;
    
    snprintf(buffer, tamanho, "%s%s%d", prefixos[pre_idx], sufixos[suf_idx], num);
}

void gerar_url_aleatoria(char* buffer, int tamanho) {
    const char* dominios[] = {"example.com", "test.tv", "live.net", "stream.io", "broadcast.org", "media.com", "channel.tv"};
    
    int dom_idx = rand() % 7;
    int num = rand() % 1000;
    
    snprintf(buffer, tamanho, "https://www.%s/%d", dominios[dom_idx], num);
}

void gerar_periodicidade_aleatoria(char* buffer, int tamanho) {
    const char* dias[] = {"segunda", "terca", "quarta", "quinta", "sexta", "sabado", "domingo"};
    
    if (rand() % 4 == 0) {
        strncpy(buffer, "diário", tamanho);
    } else {
        int num_dias = 1 + rand() % 3;
        strncpy(buffer, "semanal-", tamanho);
        
        for (int i = 0; i < num_dias; i++) {
            int dia_idx = rand() % 7;
            strncat(buffer, dias[dia_idx], tamanho - strlen(buffer) - 1);
            if (i < num_dias - 1) {
                strncat(buffer, "-", tamanho - strlen(buffer) - 1);
            }
        }
    }
}

void gerar_duracao_aleatoria(char* buffer, int tamanho) {
    int horas = rand() % 3;
    int minutos = 15 * (1 + rand() % 4);
    
    if (minutos == 60) {
        horas++;
        minutos = 0;
    }
    
    snprintf(buffer, tamanho, "%02d:%02d", horas, minutos);
}

void gerar_horario_aleatorio(char* buffer, int tamanho) {
    int hora = 6 + rand() % 15;
    int minuto = 15 * (rand() % 4);
    
    snprintf(buffer, tamanho, "%02d:%02d", hora, minuto);
}

void gerar_tipo_programa(char* buffer, int tamanho) {
    const char* tipos[] = {"ao vivo", "sob demanda"};
    int tipo_idx = rand() % 2;
    
    strncpy(buffer, tipos[tipo_idx], tamanho);
}

void teste_insercao_streams(Stream** raiz, char** nomes_streams) {
    clock_t inicio, fim;
    double tempo_total;
    int op = 1;
    
    //printf("Informe se deseja inserir as streams em ordem: 1-crescente 2-decrescente, 3-Aleatoria.\n");
    //scanf("%d", &op);
    
    printf("=== TESTE DE INSERÇÃO DE STREAMS ===\n");
    inicio = clock();
    
    if(op==1){
        for (int i = 0; i < NUM_STREAMS; i++) {
            char nome[50], url[100];
            int flag = 0;
            
            snprintf(nome, sizeof(nome), "Stream%d", i);
            gerar_url_aleatoria(url, sizeof(url));
            nomes_streams[i] = strdup(nome);
            Cadastra_StreamAVL(raiz, nome, url, &flag);
            
            if (i % 25000 == 0) {
                printf("Inseridas %d streams...\n", i);
            }
        }
    }
    else if(op==2){
        for (int i = NUM_STREAMS-1; i >= 0; i--) {
            char nome[50], url[100];
            int flag = 0;
            snprintf(nome, sizeof(nome), "Stream%d", i);
            gerar_url_aleatoria(url, sizeof(url));
            nomes_streams[i] = strdup(nome);
            Cadastra_StreamAVL(raiz, nome, url, &flag);
            
            if (i % 25000 == 0) {
                printf("Inseridas %d streams...\n", i);
            }
        }
    }
    else if(op==3){
        for (int i = 0; i < NUM_STREAMS; i++) {
            char nome[50], url[100];
            int flag = 0;
            
            gerar_nome_aleatorio(nome, sizeof(nome));
            gerar_url_aleatoria(url, sizeof(url));
            nomes_streams[i] = strdup(nome);
            Cadastra_StreamAVL(raiz, nome, url, &flag);
            
            if (i % 25000 == 0) {
                printf("Inseridas %d streams...\n", i);
            }
        }
    }
    else{
        printf("Resposta invalida.\n");
        return;
    }
    
    fim = clock();
    tempo_total = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("Tempo total: %.8f segundos\n", tempo_total);
    printf("Média por inserção: %.8f segundos\n", tempo_total / NUM_STREAMS);
    printf("Streams inseridas: %d\n", NUM_STREAMS);
    
    // Salvar no arquivo
    fprintf(arquivo_streamsAVL, "Inserção - Tempo: %.8fs, Média: %.8fs, Ordem: %d", 
            tempo_total, tempo_total / NUM_STREAMS, op);
}

void teste_busca_streams(Stream* raiz, char** nomes_streams) {
    printf("=== TESTE DE BUSCA DE STREAMS ===\n");
    clock_t inicio = clock();
    
    int encontradas = 0;
    for (int i = 0; i < NUM_STREAMS; i++) {
        Stream* resultado = busca_Stream(raiz, nomes_streams[i]);
        if (resultado != NULL) {
            encontradas++;
        }
        
        if (i % 25000 == 0) {
            printf("Buscadas %d streams...\n", i);
        }
    }
    
    clock_t fim = clock();
    double tempo_total = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("Tempo total: %.8f segundos\n", tempo_total);
    printf("Média por busca: %.8f segundos\n", tempo_total / NUM_STREAMS);
    printf("Streams encontradas: %d/%d\n", encontradas, NUM_STREAMS);
    
    // Salvar no arquivo
    fprintf(arquivo_streamsAVL, "Busca - Tempo: %.8fs, Média: %.8fs, Encontradas: %d/%d\n\n", 
            tempo_total, tempo_total / NUM_STREAMS, encontradas, NUM_STREAMS);
}

void teste_insercao_programas(Stream* stream_raiz, char** nomes_programas, Apresentadores* Apresentador) {
    clock_t inicio, fim;
    printf("=== TESTE DE INSERÇÃO DE PROGRAMAS ===\n");
    int op =1 ;
    
    //printf("Informe se deseja inserir os programas em ordem: 1-crescente 2-decrescente, 3-Aleatoria.\n");
    //scanf("%d", &op);
    
    inicio = clock();
    
    if(op==1){
        for (int i = 0; i < NUM_PROGRAMAS; i++) {
            char nome_programa[50];
            char periodicidade[50], duracao[50], inicio_horario[50], tipo[50];
            char* nome_apresentador = NULL;
            
            snprintf(nome_programa, sizeof(nome_programa), "Programa%d", i);
            nomes_programas[i] = strdup(nome_programa);
            gerar_periodicidade_aleatoria(periodicidade, sizeof(periodicidade));
            gerar_duracao_aleatoria(duracao, sizeof(duracao));
            gerar_horario_aleatorio(inicio_horario, sizeof(inicio_horario));
            gerar_tipo_programa(tipo, sizeof(tipo));
            
            Apresentadores* ap_aleatorio = Apresentador;
            for (int j = 0; j < rand() % NUM_APRESENTADORES; j++) {
                if (ap_aleatorio->prox != NULL) {
                    ap_aleatorio = ap_aleatorio->prox;
                }
            }
            nome_apresentador = ap_aleatorio->nomeapresentador;
            int flag = 0, flagg = 0;
            
            Cadastra_Programa(&stream_raiz->categoria->programas, nome_programa, Apresentador, stream_raiz, stream_raiz->categoria, &flag, &flagg, periodicidade, duracao, inicio_horario, tipo, nome_apresentador);
            
            if (i % 25000 == 0) {
                printf("Inseridos %d programas...\n", i);
            }
        }
    }
    else if(op==2){
        for (int i = NUM_PROGRAMAS-1; i >= 0; i--) {
            char nome_programa[50];
            char periodicidade[50], duracao[50], inicio_horario[50], tipo[50];
            char* nome_apresentador = NULL;
            
            snprintf(nome_programa, sizeof(nome_programa), "Programa%d", i);
            nomes_programas[i] = strdup(nome_programa);
            gerar_periodicidade_aleatoria(periodicidade, sizeof(periodicidade));
            gerar_duracao_aleatoria(duracao, sizeof(duracao));
            gerar_horario_aleatorio(inicio_horario, sizeof(inicio_horario));
            gerar_tipo_programa(tipo, sizeof(tipo));
            
            Apresentadores* ap_aleatorio = Apresentador;
            for (int j = 0; j < rand() % NUM_APRESENTADORES; j++) {
                if (ap_aleatorio->prox != NULL) {
                    ap_aleatorio = ap_aleatorio->prox;
                }
            }
            nome_apresentador = ap_aleatorio->nomeapresentador;
            int flag = 0, flagg = 0;
            
            Cadastra_Programa(&stream_raiz->categoria->programas, nome_programa, Apresentador, stream_raiz, stream_raiz->categoria, &flag, &flagg, periodicidade, duracao, inicio_horario, tipo, nome_apresentador);
            
            if (i % 25000 == 0) {
                printf("Inseridos %d programas...\n", i);
            }
        }
    }
    else if(op==3){
        for (int i = 0; i < NUM_PROGRAMAS; i++) {
            char nome_programa[50];
            char periodicidade[50], duracao[50], inicio_horario[50], tipo[50];
            char* nome_apresentador = NULL;
            
            gerar_nome_aleatorio(nome_programa, sizeof(nome_programa));
            nomes_programas[i] = strdup(nome_programa);
            gerar_periodicidade_aleatoria(periodicidade, sizeof(periodicidade));
            gerar_duracao_aleatoria(duracao, sizeof(duracao));
            gerar_horario_aleatorio(inicio_horario, sizeof(inicio_horario));
            gerar_tipo_programa(tipo, sizeof(tipo));
            
            Apresentadores* ap_aleatorio = Apresentador;
            for (int j = 0; j < rand() % NUM_APRESENTADORES; j++) {
                if (ap_aleatorio->prox != NULL) {
                    ap_aleatorio = ap_aleatorio->prox;
                }
            }
            nome_apresentador = ap_aleatorio->nomeapresentador;
            int flag = 0, flagg = 0;
            
            Cadastra_Programa(&stream_raiz->categoria->programas, nome_programa, Apresentador, stream_raiz, stream_raiz->categoria, &flag, &flagg, periodicidade, duracao, inicio_horario, tipo, nome_apresentador);
            
            if (i % 25000 == 0) {
                printf("Inseridos %d programas...\n", i);
            }
        }
    }
    else{
        printf("Valor inválido.\n");
        return;
    }
    
    fim = clock();
    double tempo_total = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("Tempo total: %.8f segundos\n", tempo_total);
    printf("Média por inserção: %.8f segundos\n", tempo_total / NUM_PROGRAMAS);
    printf("Programas inseridos: %d\n", NUM_PROGRAMAS);
    
    // Salvar no arquivo
    fprintf(arquivo_programasAVL, "Inserção - Tempo: %.8fs, Média: %.8fs, Ordem: %d", 
            tempo_total, tempo_total / NUM_PROGRAMAS, op);
}

void teste_busca_programas(Programas* raiz, char** nomes_programas) {
    printf("\n=== TESTE DE BUSCA DE PROGRAMAS ===\n");
    int encontrados = 0;
    clock_t inicio = clock();
    
    for (int i = 0; i < NUM_PROGRAMAS; i++) {
        Programas* resultado = busca_Programa(raiz, nomes_programas[i]);
        if (resultado != NULL) {
            encontrados++;
        } 
        if (i % 25000 == 0) {
            printf("Buscados %d programas...\n", i);
        }
    }

    clock_t fim = clock();
    double tempo_total = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("Tempo total de busca: %.8f segundos\n", tempo_total);
    printf("Média por busca: %.8f segundos\n", tempo_total / NUM_PROGRAMAS);
    printf("Programas encontrados: %d/%d\n", encontrados, NUM_PROGRAMAS);
    printf("Taxa de sucesso: %.2f%%\n", (encontrados * 100.0) / NUM_PROGRAMAS);
    
    // Salvar no arquivo
    fprintf(arquivo_programasAVL, "Busca - Tempo: %.8fs, Média: %.8fs, Encontrados: %d/%d\n\n", 
            tempo_total, tempo_total / NUM_PROGRAMAS, encontrados, NUM_PROGRAMAS);
}

void teste_completo() {
    for(int g=0; g<30;g++){
        Stream* raiz_t = NULL;
        char** nomes_streams = malloc(NUM_STREAMS * sizeof(char*));
        char** nomes_programas = malloc(NUM_PROGRAMAS * sizeof(char*));

        // Abrir arquivos para escrita
        arquivo_streamsAVL = fopen("resultados_streamsAVL.txt", "a");
        arquivo_programasAVL = fopen("resultados_programasAVL.txt", "a");
        
        if (!arquivo_streamsAVL || !arquivo_programasAVL) {
            printf("Erro ao criar arquivos de resultados!\n");
            return;
        }
        
        fprintf(arquivo_streamsAVL, "=== RESULTADOS STREAMS ===\n\n");
        fprintf(arquivo_programasAVL, "=== RESULTADOS PROGRAMAS ===\n\n");

        printf("🎬 INICIANDO TESTES DE PERFORMANCE 🎬\n\n");
        
        srand(time(NULL));
        
        teste_insercao_streams(&raiz_t, nomes_streams);
        printf("\n");
        
        teste_busca_streams(raiz_t, nomes_streams);
        printf("\n");
        int cadastrou;
        Apresentadores* apresentadores = NULL;
        Cadastra_Categoria(&raiz_t->categoria,"Paralelepipedo", "esporte", &cadastrou);
        for (int i = NUM_APRESENTADORES; i >0; i--) {
            char nome[50];
            snprintf(nome, sizeof(nome), "Apresentador%d", i);
            cadastrar_Apresentador(&apresentadores, nome, (int[]){0});
            Apresentadores* ap = Busca_Apresentador(nome, apresentadores);
            if(ap){
                Associar_Stream(raiz_t, ap, raiz_t->categoria, (int[]){0});
            }
            if(i%25000==0){
                printf("%d apresentadores assciados e cadastrados.\n", i);
            }
        }

        teste_insercao_programas(raiz_t,nomes_programas,apresentadores);
        printf("\n");
        
        teste_busca_programas(raiz_t->categoria->programas,nomes_programas);
        printf("\n");
        for(int i=0;i<NUM_STREAMS;i++){
            free(nomes_streams[i]);
        }
        for(int i=0;i<NUM_PROGRAMAS;i++){
            free(nomes_programas[i]);
        }
        libera_Stream(raiz_t);

        printf("✅ TESTES CONCLUÍDOS ✅\n");
    }
}

int main() {
    teste_completo();
    return 0;
}