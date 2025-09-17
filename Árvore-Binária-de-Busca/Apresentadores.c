#include "tad.h"

Apresentadores* criar_Apresentador(const char* nome){
    Apresentadores* novo = malloc(sizeof(Apresentadores));
    if(novo) {
        //Cria cópia independente do nome para poder modificar se necessário
        novo->nomeapresentador = strdup(nome);
        novo->ant = novo->prox = NULL;
        novo->streamatual = NULL;
        novo->categoria = NULL;
        //Inicia as informações do vetor
        novo->inicio_historico = 0;
        novo->fim_historico = 0;
        novo->tamanho_historico = 0;
        for(int i = 0; i < 2000; i++) {
            novo->historico[i].nomestream = NULL;
            novo->historico[i].data_inicio = NULL;
            novo->historico[i].data_fim = NULL;
        }

    }
    return novo; 
}

void cadastrar_Apresentador(Apresentadores** lista,char* nome,int* flag){
    Apresentadores* novo = criar_Apresentador(nome);
    Apresentadores* atual = *lista;
    Apresentadores* anterior = NULL;
    int existe = 0;
    //percorre até achar posição que o no será cadastrado ou duplicado/
    while(atual != NULL && existe == 0 && strcasecmp(nome, atual->nomeapresentador) > 0){
        anterior = atual;
        atual = atual->prox;
    }
    //verifica se parou em alguém com o mesmo nome que estão tentando cadastrar/
    if(atual != NULL && strcasecmp(nome, atual->nomeapresentador) == 0){
        existe = 1;
    }
    if(existe == 0){
        if (anterior == NULL) {
            /* insere no início da lista*/
            novo->prox = *lista;
            if(*lista != NULL){
                (*lista)->ant = novo;
            }
            *lista = novo;
        }else{
            /* insere no meio ou no fim da lista*/
            novo->prox = atual;
            if (atual != NULL) {
                atual->ant = novo;
            }
            anterior->prox = novo;
            novo->ant = anterior;
        }
        *flag = 1; 
    }
}
void Mostra_Apresentador(Apresentadores* lista){
    Apresentadores* atual = lista;
    if(atual){
        while(atual!=NULL){
            printf("%s\n", atual->nomeapresentador);
            atual = atual->prox;
        }
    }
}

Apresentadores* Busca_Apresentador( const char* nome, Apresentadores* lista){
    Apresentadores* atual = lista;
    while(atual!=NULL && strcmp(nome,atual->nomeapresentador)!=0){
        atual = atual->prox;
    }
    return atual;
}

void Cria_Historico(Apresentadores* apresentador, const char* nomestream){
    time_t tempo_atual;
    struct tm *info_tempo;
    char data_inicio[20];
    time(&tempo_atual);
    info_tempo = localtime(&tempo_atual);
    strftime(data_inicio, 20, "%d/%m/%Y", info_tempo);
            
    //Aloca e preenche o primeiro registro do histórico
    apresentador->historico[apresentador->fim_historico].nomestream = strdup(nomestream);
    apresentador->historico[apresentador->fim_historico].data_inicio = strdup(data_inicio);
    apresentador->historico[apresentador->fim_historico].data_fim = strdup("Presente");
    apresentador->fim_historico = (apresentador->fim_historico + 1) % 2000;
    apresentador->tamanho_historico++;
}

void atualizarFimHistorico(Apresentadores* apresentador){
   /*Atualiza a informação do campo "data_fim" no último registro do histórico de "Presente" para a data em que o apresentador saiu da stream*/ 
    if(apresentador && apresentador->tamanho_historico > 0){
        time_t tempo_atual;
        struct tm *info_tempo;
        char data[20];
        time(&tempo_atual);
        info_tempo = localtime(&tempo_atual);
        strftime(data, 20, "%d/%m/%Y", info_tempo);

        int ultimo_indice = (apresentador->fim_historico - 1 + 2000) % 2000;
        free(apresentador->historico[ultimo_indice].data_fim);
        apresentador->historico[ultimo_indice].data_fim = strdup(data);
    }
} 

void adicionarHistorico(Apresentadores* apresentador, const char* nomestream) {
    if(apresentador){
        time_t tempo_atual;
        struct tm *info_tempo;
        char data[20];
        time(&tempo_atual);
        info_tempo = localtime(&tempo_atual);
        strftime(data, 20, "%d/%m/%Y", info_tempo);
        if(apresentador->tamanho_historico == 2000){
            // Histórico cheio - sobrescrever o mais antigo
            int indice_antigo = apresentador->inicio_historico;
            free(apresentador->historico[indice_antigo].nomestream);
            free(apresentador->historico[indice_antigo].data_inicio);
            free(apresentador->historico[indice_antigo].data_fim);
            apresentador->historico[indice_antigo].nomestream = strdup(nomestream);
            apresentador->historico[indice_antigo].data_inicio = strdup(data);
            apresentador->historico[indice_antigo].data_fim = strdup("Presente");
            apresentador->inicio_historico = (apresentador->inicio_historico + 1) % 2000;
        }
        else{
            /*Entra nesse else até encher as 2000 posições*/
            int novo_indice = apresentador->fim_historico;
            apresentador->historico[novo_indice].nomestream = strdup(nomestream);
            apresentador->historico[novo_indice].data_inicio = strdup(data);
            apresentador->historico[novo_indice].data_fim = strdup("Presente");
            apresentador->fim_historico = (apresentador->fim_historico + 1) % 2000;
            apresentador->tamanho_historico++;
        }
    }
}

void Associar_Stream(Stream* stream, Apresentadores* apresentador, Categorias* novaCategoria,int* flag){
    int aux=1;
    if (validarAssociacao(stream, apresentador)){
        if(apresentador->categoria != novaCategoria){
            if(apresentador->streamatual!= stream){
                if (apresentador->tamanho_historico > 0) {
                    atualizarFimHistorico(apresentador);
                }
                else{
                    Cria_Historico(apresentador,stream->nomestream);
                    aux = 0;
                }
                if(aux)
                    adicionarHistorico(apresentador, stream->nomestream);
            }
        }
        apresentador->streamatual = stream;
        apresentador->categoria = novaCategoria;
        *flag = 1;
    }
}

void ExibeApresentadoresPorCategoria(Apresentadores* lista, char* categoria,int *encontrou) {
    Apresentadores* atual = lista;
    while (atual != NULL) {
        if (atual->categoria!= NULL && strcmp(atual->categoria->nomecategoria, categoria) == 0) {
            printf("Apresentador: %s | Stream: %s\n",atual->nomeapresentador, atual->streamatual->nomestream);
            *encontrou = 1;
        }
        atual = atual->prox;
    }
}

void Exibe_Historico(Apresentadores* apresentador){
    for(int i = 0; i < apresentador->tamanho_historico; i++) {
        int indice = (apresentador->inicio_historico + i) % 2000;
        printf("Stream: %s\n", apresentador->historico[indice].nomestream);
        printf("Período: %s à %s\n", 
        apresentador->historico[indice].data_inicio,
        apresentador->historico[indice].data_fim);
        printf("-----------------------------\n");
    }
}

void libera_apresentadores(Apresentadores* lista){
    while(lista != NULL){
        Apresentadores* temp = lista;
        lista = lista->prox;
        for(int i = temp->inicio_historico; i != temp->fim_historico; i++){
            if(i>=2000){
                i = 0;
            }
            free(temp->historico[i].nomestream);
            free(temp->historico[i].data_inicio);
            free(temp->historico[i].data_fim);
        }
        free(temp->nomeapresentador);
        free(temp);
    }
}
