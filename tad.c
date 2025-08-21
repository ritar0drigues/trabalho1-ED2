#include "tad.h"

void mostra_Stream(Stream* raiz){
    /*Recebe como parâmetro a raiz de uma árvore e percorre recursivamente a árvore binária garantindo a exibição em ordem alfabética 
    imprimindo o nome e o site de cada Stream*/
    if(raiz){
        mostra_Stream(raiz->esquerda);
        printf("Nome: %s | Site: %s\n", raiz->nomestream, raiz->site);
        mostra_Stream(raiz->direita);
    }
}

Stream* Cadastra_stream(Stream* raiz, char* nome, char* site){
    /*Recebe como parâmetro a raiz da árvore de streams o nome da nova stream e o site dela, a função declara uma variável aux  que recebe
     a raiz e depois percorre recursivamente a árvore comparando o nome da nova stream com o nome da stream do nó que foi passado como parametro
      na chamada da função para definir se a função vai ser chamada para a subarvore à esquerda da raiz atual ou à direita da raiz atual até chegar
       em um valor NULL que seria o fim daquele galho da àrvore cria o novo nó e e atribui ele a variável aux  no fim a função retorna aux o que garente que novo no
       seja alocado como filho da raiz da função*/
    Stream* aux = raiz;
    if(!raiz){
        Stream* novo = (Stream*) malloc(sizeof(Stream));
        if(novo){
            novo->nomestream = strdup(nome);
            novo->site = strdup(site);
            novo->categoria = NULL;
            novo->esquerda = NULL;
            novo->direita = NULL;
        }
        else{
            printf("Erro de alocacao.\n");
        }
        aux = novo;
    }

    if(strcmp(nome, raiz->nomestream) < 0){
        raiz->esquerda = Cadastra_stream(raiz->esquerda, nome, site);
    }
    else if(strcmp(nome, raiz->nomestream) > 0){
        raiz->direita = Cadastra_stream(raiz->direita, nome, site);
    }
    else{
        printf("Já existe uma Stream de nome '%s' cadastrada.\n", nome);
    }
    return aux;
}

Stream* busca_Stream(Stream* raiz, char* nome) {
    /*A função recebe a raiz da árvore de Streams e o nome da stream a ser procurada o ponteiro aux é iniciado com NULL para que a função retorne NULL caso ela chegue
     ao último filho do galho, onde ela procura pela stream, e mesmo assim não tenha encontrado a stream a variável cmp guarda o resultado da comparão do nome informado 
     com o nome da raiz atual se for zero significa que são iguais e a stream foi encontrada se for menor que zero significa que o nome informado vem antes do nome da 
     stream em ordem alfabética e por isso a função é chamada para a subárvore da esquerda  e se for maior significa que vem depois por isso a função é chamada para a 
     subárvore da direita*/
    Stream* aux = NULL;
    if (raiz){
        int cmp = strcmp(nome, raiz->nomestream);
        if(cmp==0){
            aux = raiz;
        }
        else if(cmp < 0){
            aux = busca_Stream(raiz->esquerda, nome);
        }
        else{
            aux = busca_Stream(raiz->direita, nome);
        }
    }
    return aux;
}

Categorias* Cadastra_Categoria(Categorias* raiz, char* nome, char* tipo){
    /*Recebe como parâmetro a raiz da árvore de categorias o nome da nova categoria e o tipo dela, a função  a função declara uma variável aux  que recebe a raiz e percorre recursivamente a árvore 
      comparando o nome da nova categoria com o nome da categoria do nó que foi passado como parametro na chamada da função para definir se a 
      função vai ser chamada para a subarvore à esquerda da raiz atual ou à direita da raiz atual até chegar em um valor NULL que seria
      o fim daquele galho da àrvore cria o novo nó e atribui ele a aux no fim a função retorna aux o que garente que novo no
       seja alocado como filho da raiz da função*/
    Categorias* aux = raiz;
    if(!raiz){
        Categorias* novo = (Categorias*) malloc(sizeof(Categorias));
        if(novo){
            novo->nomecategoria = strdup(nome);
            novo->tipo = strdup(tipo);
            novo->programas = NULL;
            novo->esquerda = NULL;
            novo->direita = NULL;
        }
        else{
            printf("Erro de alocacao.\n");
        }
        aux = novo;
    }

    if(strcmp(nome, raiz->nomecategoria) < 0){
        raiz->esquerda = Cadastra_Categoria(raiz->esquerda, nome, tipo);
    }
    else if(strcmp(nome, raiz->nomecategoria) > 0){
        raiz->direita = Cadastra_Categoria(raiz->direita, nome, tipo);
    }
    else{
        printf("Já existe uma categoria com o nome '%s' cadastrada.\n", nome);
    }
    return aux;
}

Categorias* busca_Categorias(Categorias* raiz, char* nome){
    /*A função recebe a raiz de uma árvore de categorias e o nome da categoria a ser procurada o ponteiro aux é iniciado com NULL para que a função retorne NULL caso ela chegue
     ao último filho do galho, onde ela procura pela categoria, e mesmo assim não tenha encontrado a categoria. A variável cmp guarda o resultado da comparão do nome informado 
     com o nome da raiz atual se for zero significa que são iguais e a Categoria foi encontrada se for menor que zero significa que o nome informado vem antes do nome da 
     Categoria em ordem alfabética e por isso a função é chamada para a subárvore da esquerda  e se for maior significa que vem depois por isso a função é chamada para a 
     subárvore da direita*/
    Categorias* aux = NULL;
    if (raiz){
        int cmp = strcmp(nome, raiz->nomecategoria);
        if(cmp==0){
            aux = raiz;
        }
        else if(cmp < 0){
            aux = busca_Categorias(raiz->esquerda, nome);
        }
        else{
            aux = busca_Categorias(raiz->direita, nome);
        }
    }
    return aux;
}

void mostra_Categoria(Categorias* raiz){
    /*Recebe como parâmetro a raiz de uma árvore e percorre recursivamente a árvore binária garantindo a exibição em ordem alfabética 
    imprimindo o nome e o tipo de cada categoria da stream*/
    if(raiz){
        mostra_Categoria(raiz->esquerda);
        printf("Nome: %s | Tipo: %s\n", raiz->nomecategoria, raiz->tipo);
        mostra_Categoria(raiz->direita);
    }
}

Apresentadores* cadastrar_Apresentador(Apresentadores* lista, Stream* raizStreams) {
    char nome[50], nomeStream[50], nomeCategoria[50];
    Apresentadores* aux = lista;
    printf("Nome do apresentador: ");
    scanf("%49[^\n]", nome);
    getchar();
    Apresentadores* novo = malloc(sizeof(Apresentadores));
    if(novo==NULL){
        printf("Erro de alocao.\n");
    }
    else{
        novo->nomeapresentador = strdup(nome);
        novo->ant = novo->prox = NULL;
        printf("Stream atual: ");
        scanf("%49[^\n]", nomeStream);
        getchar();
        Stream* streamAtual = busca_Stream(raizStreams, nomeStream);
        if (streamAtual) {
            novo->streamatual = streamAtual;
            time_t tempo_atual;
            struct tm *info_tempo;
            char data_inicio[20];
            time(&tempo_atual);
            info_tempo = localtime(&tempo_atual);
            strftime(data_inicio, 20, "%d/%m/%Y", info_tempo);
            Historico* historic = (Historico*)malloc(sizeof(Historico));
            historic->nomestream = strdup(streamAtual->nomestream);
            historic->data_inicio = strdup(data_inicio);
            historic->data_fim = strdup("Presente");
            novo->lista = historic;
            printf("Categoria que ele trabalha: ");
            scanf("%49[^\n]", nomeCategoria);
            getchar();
            Categorias* catAtual = busca_Categorias(streamAtual->categoria, nomeCategoria);
            if (catAtual) {
                novo->categoria = catAtual;
                if (lista == NULL || strcmp(novo->nomeapresentador, lista->nomeapresentador) < 0) {
                    novo->prox = lista;
                    if (lista)
                        lista->ant = novo;
                    aux = novo;
                }
                Apresentadores* atual = lista;
                while (atual->prox && strcmp(novo->nomeapresentador, atual->prox->nomeapresentador) > 0) {
                    atual = atual->prox;
                }
                novo->prox = atual->prox;
                if (atual->prox) {
                    atual->prox->ant = novo;
                }
                atual->prox = novo;
                novo->ant = atual;
            }
            else{
                printf("Categoria não encontrada nessa stream. Cadastro cancelado.\n");
                free(novo);
            }
        }
        else{
            printf("Stream não encontrada. Cadastro cancelado.\n");
            free(novo);
        }
    }
    return aux;
}

void Mostra_Apresentador(Apresentadores* lista){
    /* percorre a lista duplamente encadeada de apresentadores através de uma estrutura de repetição mostrando o nome de cada apresentador
     na lista até que o ponteiro atual receba um valor NULL*/
    Apresentadores* atual = lista;
    if(atual){
        while(atual!=NULL){
            printf("%s\n", atual->nomeapresentador);
            atual = atual->prox;
        }
    }
    else{
        printf("Nenhum apresentador Cadastrado.\n");
    }
}

Apresentadores* Busca_Apresentador(char* nome, Apresentadores* lista){
    /* A função recebe uma lista de apresentadores e o nome do apresentador a ser buscado, ela percorre a lista duplamente encadeada de apresentadores
     através de uma estrutura de repetição até que o ponteiro atual receba um valor NULL ou até que o nome do apresentador atual seja igual ao nome informado
     pelo usuario garantindo que o return atual retorne NULL caso o apresentador não seja encontrado ou o endereço de memória para o nó do apresentador caso ele seja encontrado*/
    Apresentadores* atual = lista;
    while(atual!=NULL && strcmp(nome,atual->nomeapresentador)!=0){
        atual = atual->prox;
    }
    return atual;
}

Programas* Cadastra_Programa(Programas* raiz,char* nome,Apresentadores* lista, Stream* stream, Categorias* categoria) {
    Programas* aux = raiz;
    if(!raiz){
        char periodicidade[50], duracao[50],inicio[50],tipo[50],apresentador[50];
        Programas* novo = (Programas*) malloc(sizeof(Programas));
        if(novo==NULL){
            printf("Erro de alocacao.\n");
            aux = NULL;
        }
        else{
            novo->nomeprograma = strdup(nome);
            printf("Informe a periodicidade do prgrama:\n");
            scanf("%49[^\n]", periodicidade);
            getchar();
            novo->periodicidade = strdup(periodicidade);
            printf("Informe a duração do prgrama:\n");
            scanf("%49[^\n]", duracao);
            getchar();
            novo->duracao = strdup(duracao);
            printf("Informe o  horário de inicio do prgrama:\n");
            scanf("%49[^\n]", inicio);
            getchar();
            novo->inicio = strdup(inicio);
            printf("Informe o tipo do prgrama:\n");
            scanf("%49[^\n]", tipo);
            getchar();
            novo->tipo = strdup(tipo);
            printf("Informe o nome do apresentador:\n");
            scanf("%49[^\n]", apresentador);
            getchar();
            Apresentadores* aux = Busca_Apresentador(apresentador,lista);
            if(aux==NULL){
                printf("ERRO!! Apresentador não cadastrado.\n");
                aux = NULL;
            }
            else{
                if (strcmp(aux->categoria->nomecategoria, categoria->nomecategoria) != 0 ||strcmp(aux->streamatual->nomestream, stream->nomestream) != 0) {
                    printf("ERRO!! Apresentador não corresponde à categoria ou stream.\n");
                    aux = NULL;
                }
                else{
                    novo->apresentador = aux;
                    novo->esquerda = NULL;
                    novo->direita = NULL;
                    aux = novo;
                }
            }
        }
    }
    if(strcmp(nome, raiz->nomeprograma) < 0){
        raiz->esquerda = Cadastra_Programa(raiz->esquerda, nome,lista,stream,categoria);
    }
    else if(strcmp(nome, raiz->nomeprograma) > 0){
        raiz->direita = Cadastra_Programa(raiz->direita, nome,lista,stream,categoria);
    }
    else{
        printf("Já existe um Programa com o nome '%s' cadastrada.\n", nome);
    }
    return aux;
}

Programas* busca_Programa(Programas* raiz, char* nome) {
    /*A função recebe a raiz para uma árvore de Programas e o nome do programa a ser procurado o ponteiro aux é iniciado com NULL para que a função retorne NULL caso ela chegue
     ao último filho do galho, onde ela procura pelo programa, e mesmo assim não tenha encontrado o programa. A variável cmp guarda o resultado da comparação do nome informado 
     pelo usuário com o nome da raiz atual se for zero significa que são iguais e o programa foi encontrado, se for menor que zero significa que o nome informado vem antes do nome do 
     programa atual em ordem alfabética e por isso a função é chamada para a subárvore da esquerda  e se for maior significa que vem depois por isso a função é chamada para a 
     subárvore da direita*/
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
    /*Recebe como parâmetro a raiz de uma árvore e percorre recursivamente a árvore binária garantindo a exibição em ordem alfabética 
    imprimindo o nome e o tipo de cada programa da categoria*/
    if(raiz){
        mostra_Programa(raiz->esquerda);
        printf("Nome: %s | Tipo: %s\n", raiz->nomeprograma, raiz->tipo);
        mostra_Programa(raiz->direita);
    }
}

Programas* removePrograma(Programas* raiz, char* nomePrograma) {
    if(raiz == NULL){
        printf("Programa não encontrado.\n");
        return NULL;
    }

    int cmp = strcmp(nomePrograma, raiz->nomeprograma);
    
    if (cmp < 0) {
        raiz->esquerda = removePrograma(raiz->esquerda, nomePrograma);
    }
    else if (cmp > 0) {
        raiz->direita = removePrograma(raiz->direita, nomePrograma);
    }
    else {
        if (raiz->esquerda == NULL || raiz->direita == NULL) {
            time_t tempo_atual;
            struct tm *info_tempo;
            char data_fim[20];
            time(&tempo_atual);
            info_tempo = localtime(&tempo_atual);
            strftime(data_fim, 20, "%d/%m/%Y", info_tempo);
            Historico* historico = raiz->apresentador->lista;
            while (historico != NULL && historico->prox != NULL) {
                historico = historico->prox;
            }
            
            if (historico != NULL && strcmp(historico->data_fim, "Presente") == 0) {
                free(historico->data_fim);
                historico->data_fim = strdup(data_fim);
            }
        }
        if(raiz->esquerda == NULL) {
            Programas* temp = raiz->direita;
            free(raiz->nomeprograma);
            free(raiz->periodicidade);
            free(raiz->duracao);
            free(raiz->inicio);
            free(raiz->tipo);
            free(raiz);
            return temp;
        }
        else if (raiz->direita == NULL) {
            Programas* temp = raiz->esquerda;
            free(raiz->nomeprograma);
            free(raiz->periodicidade);
            free(raiz->duracao);
            free(raiz->inicio);
            free(raiz->tipo);
            free(raiz);
            return temp;
        }
        else {
            Programas* temp = raiz->direita;
            while (temp->esquerda != NULL) {
                temp = temp->esquerda;
            }
            free(raiz->nomeprograma);
            free(raiz->periodicidade);
            free(raiz->duracao);
            free(raiz->inicio);
            free(raiz->tipo);
            raiz->nomeprograma = strdup(temp->nomeprograma);
            raiz->periodicidade = strdup(temp->periodicidade);
            raiz->duracao = strdup(temp->duracao);
            raiz->inicio = strdup(temp->inicio);
            raiz->tipo = strdup(temp->tipo);
            raiz->apresentador = temp->apresentador;
            
            raiz->direita = removePrograma(raiz->direita, temp->nomeprograma);
        }
    }
    return raiz;
}

void Exibe_Historico(Apresentadores* apresentador){
    Historico* atual = apresentador->lista;
    char c;
    if(atual==NULL){
        printf("O histórico está vazio.\n");
    }
    else{
        while(atual!=NULL){
            printf("Stream: %s\n", atual->nomestream);
            printf("Periodo: %s à %s\n", atual->data_inicio,atual->data_fim);
            atual = atual->prox;
        }
    }
    while ((c = getchar()) != '\n' && c != EOF);
}

Categorias* removeCategoria(Categorias* raiz, char* nomeCategoria) {
    if (raiz == NULL) {
        printf("Categoria não encontrada.\n");
        return NULL;
    }

    int cmp = strcmp(nomeCategoria, raiz->nomecategoria);
    
    if (cmp < 0) {
        raiz->esquerda = removeCategoria(raiz->esquerda, nomeCategoria);
    } else if (cmp > 0) {
        raiz->direita = removeCategoria(raiz->direita, nomeCategoria);
    } else {
        if (raiz->programas) {
            printf("Não é possível remover: a categoria contém programas.\n");
            return raiz;
        }

        if (raiz->esquerda == NULL) {
            Categorias* temp = raiz->direita;
            free(raiz->nomecategoria);
            free(raiz->tipo);
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            Categorias* temp = raiz->esquerda;
            free(raiz->nomecategoria);
            free(raiz->tipo);
            free(raiz);
            return temp;
        } else {
            Categorias* temp = raiz->direita;
            while (temp->esquerda != NULL) {
                temp = temp->esquerda;
            }
            
            free(raiz->nomecategoria);
            free(raiz->tipo);
            
            raiz->nomecategoria = strdup(temp->nomecategoria);
            raiz->tipo = strdup(temp->tipo);
            
            raiz->direita = removeCategoria(raiz->direita, temp->nomecategoria);
        }
    }
    return raiz;
}

int apresentadorTemProgramaNosProgramas(Programas* prog, Apresentadores* apresentador){
    int aux = 0;
    if(prog){
        if(prog->apresentador == apresentador || apresentadorTemProgramaNosProgramas(prog->esquerda, apresentador) || apresentadorTemProgramaNosProgramas(prog->direita, apresentador)){
            aux = 1;
        }
    }
    return aux;
}

int apresentadorTemProgramaNaStream(Categorias* cat, Apresentadores* apresentador) {
    int aux = 0;
    if (cat){
        aux = apresentadorTemProgramaNaStream(cat->esquerda, apresentador) ||(cat->programas && apresentadorTemProgramaNosProgramas(cat->programas, apresentador)) ||
           apresentadorTemProgramaNaStream(cat->direita, apresentador);
    }
    return aux;
}

void Associar_Stream(Stream* stream, Apresentadores* apresentador){
    if (!stream || !apresentador) {
        printf("Erro: Stream ou apresentador inválido.\n");
        return;
    }
    else if (apresentadorTemProgramaNaStream(stream->categoria, apresentador)) {
        printf("Erro: Apresentador já possui programa nesta stream.\n");
    }
    else{
        time_t tempo_atual;
        struct tm *info_tempo;
        char data_inicio[20];

        time(&tempo_atual);
        info_tempo = localtime(&tempo_atual);
        strftime(data_inicio, 20, "%d/%m/%Y", info_tempo);
        Historico* atual = apresentador->lista;
        while(atual->prox != NULL){
            atual = atual->prox;
        }
        free(atual->data_fim);
        atual->data_fim = strdup(data_inicio);
        Historico* novo = (Historico*) malloc(sizeof(Historico));
        novo->nomestream = strdup(stream->nomestream);
        novo->data_inicio = strdup(data_inicio);
        novo->data_fim = strdup("Presente");
        novo->prox = NULL;
        if(apresentador->lista == NULL){
            apresentador->lista = novo;
        }
        else{
            Historico* atual = apresentador->lista;
            while(atual->prox != NULL){
                atual = atual->prox;
            }
            atual->prox = novo;
        }
        apresentador->streamatual = stream;
        printf("Stream associada/alterada com sucesso!\n");
    }
}

void libera_Programa(Programas* raiz){
    /*Recebe a raiz para uma árvore de programas e a percorre recursivamente começando da subárvore mais a direita ela percorre até o fim de um galho e volta*/
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

void libera_Categoria(Categorias* raiz){
    if(raiz){
        libera_Programa(raiz->programas);
        libera_Categoria(raiz->direita);
        libera_Categoria(raiz->esquerda);
        free(raiz->tipo); 
        free(raiz->nomecategoria);
        free(raiz);
    }
}

void libera_Stream(Stream* raiz){
    if(raiz){
        libera_Categoria(raiz->categoria);
        libera_Stream(raiz->direita);
        libera_Stream(raiz->esquerda);
        free(raiz->nomestream);
        free(raiz->site);
        free(raiz);
    }
}

void libera_Historico(Historico* lista){
    /*recebe a lista de histórico de um apresentado e a percorre usando um laço de repetição
     enquanto libera todas as strings alocadas com a função strdup e em seguida o próprio nó da lista*/
    while(lista!=NULL){
        Historico* temp = lista;
        lista = lista->prox;
        free(temp->nomestream);
        free(temp->data_fim);
        free(temp->data_inicio);
        free(temp);
    }
}

void libera_apresentadores(Apresentadores* lista){
    /*Recebe a lista de apresentadores e a percorre chamando a função libera_historico para cada apresentador depois liberando o nome e o próprio nó do apresentador*/
    while(lista!=NULL){
        Apresentadores* temp = lista;
        lista = lista->prox;
        libera_Historico(temp->lista);
        free(temp->nomeapresentador);
        free(temp);
    }
}