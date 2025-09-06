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

void inserir_Apresentador(Apresentadores** lista, Apresentadores* novo) {
    if (*lista){
        /*Verifica se o nome do novo apresentador vem antes do nome do primeiro na ordem alfbética, se sim insere o novo apresentador   no início*/
        if(strcasecmp(novo->nomeapresentador, (*lista)->nomeapresentador) < 0){ 
            novo->prox = *lista;
            (*lista)->ant = novo;
            *lista = novo;
        }
        else{
            Apresentadores* atual = *lista;
            /*Percorre a lista até chegar no primeiro apresentdor que vem depois do novo na ordem alfabética*/
            while (atual->prox != NULL && strcmp(novo->nomeapresentador, atual->prox->nomeapresentador) > 0){
                atual = atual->prox;
            }
            novo->prox = atual->prox;
            if(atual->prox){//Verifica se o atual->prox não é NULL antes de acessá-lo pois o no atual pode ser o último nó da lista.
                atual->prox->ant = novo;
            }
            atual->prox = novo;
            novo->ant = atual;
        }
    }
    else{
        *lista = novo;
    }
}

void cadastrar_Apresentador(Apresentadores** lista,int* flag){
    char nome[50];
    printf("Informe o nome do apresentador.\n");
    scanf("%49[^\n]", nome);
    getchar();
    Apresentadores* novo = criar_Apresentador(nome);
    if(novo){
        *flag = 1;
        inserir_Apresentador(lista, novo);
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
    if(apresentador && apresentador->historico){
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
        if (apresentador->tamanho_historico > 0) {
            atualizarFimHistorico(apresentador);
        }
        else{
            Cria_Historico(apresentador,stream->nomestream);
            aux = 0;
        }
        if(aux)
            adicionarHistorico(apresentador, stream->nomestream);
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