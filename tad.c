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
        raiz = novo;
    }
    else{
        if(strcmp(nome, raiz->nomestream) < 0){
            raiz->esquerda = Cadastra_stream(raiz->esquerda, nome, site);
        }
        else if(strcmp(nome, raiz->nomestream) > 0){
            raiz->direita = Cadastra_stream(raiz->direita, nome, site);
        }
        else{
            printf("Já existe uma Stream de nome '%s' cadastrada.\n", nome);
        }
    }
    return raiz;
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

Categorias* Cadastra_Categoria(Categorias* lista, char* nome, char* tipo) {
    /*A fução recebe a lista de categorias de uma stream o nome da nova categoria e o tipo dela cria um novo no do tipo categoria e o preenche e o coloca na lista
     de categorias em ordem alfabetica retornando o inicio da lista já atualizada*/
    Categorias* novo = (Categorias*) malloc(sizeof(Categorias));
    novo->nomecategoria = strdup(nome);
    novo->tipo = strdup(tipo);
    novo->programas = NULL;
    if (lista) {// Se a lista não é vazia
        Categorias* atual = lista;
        if (strcmp(nome, lista->nomecategoria) < 0){//Se o nome da nova categoria vem antes do nome do primeiro no da lista na ordem alfabética o novo no é colocado no inicio da lista atualizado os ponteiros.
            while (atual->prox != lista) {
                atual = atual->prox;
            }
            atual->prox = novo;
            novo->prox = lista;
            lista = novo;
        }
        else {// se a nova categoria não entrar no começo da lista
            while (atual->prox != lista && strcmp(atual->prox->nomecategoria, nome) < 0) {//Percorre a lista até encontrar um programa que vem depois do novo na ordem alfabética ou até chgar ao último nóda lista
                atual = atual->prox;
            }
            if (strcmp(atual->prox->nomecategoria, nome) == 0) {//Verifica se já existe uma categoria com o mesmo nome
                printf("Já existe uma categoria com o nome %s cadastrada.\n", nome);
                free(novo->nomecategoria);
                free(novo->tipo);
                free(novo);
            }
            else {//se não existe categoria com o mesmo nome os ponteiros são  atualizados encaixando o novo no na lista de forma ordenada
                novo->prox = atual->prox;
                atual->prox = novo;
            }
        }
    } 
    else {//Se a lista estiver vazia o novo no aponta para si mesmo e lista tera apenas o novo no
        novo->prox = novo;
        lista = novo;
    }
    return lista;
}


Categorias* busca_Categorias(Categorias* lista, char* nome){
    /*A função  recebe uma lista de  Categorias de uma determinada Stream e o nome da categoria a ser buscada percorre a lista procurando pelacategoria
     se encontrar retorna a posição de memória da categoria buscada se não encontrar retorna NULL*/
    Categorias* resultado = NULL; 
    Categorias* atual = lista;
    if(lista){// Verifia se a lista não é vazia
        do {
            if(strcmp(atual->nomecategoria, nome) == 0){//Verifica se é a categoria buscada
                resultado = atual;// atualisa o resultado com a posição de memória da categoria buscada.
            }
            else{//se não é a categoria buscada vai para a próxima categoria
                atual = atual->prox;
            }
        } while(atual != lista && !resultado);//Percorre a lista até encontrar a categoria ou até voltar para o início
    }
    return resultado;
}

void mostra_Categoria(Categorias* lista){
    /*A função recebe um lista de categorias de uma determinada Stream e a percorre através de uma estrutura de repetição printando o nome e o tipo de cada categoria*/
    if (lista) {
        Categorias* atual = lista;
        do {
            printf("Nome: %s\n", atual->nomecategoria);
            printf("Tipo: %s\n", atual->tipo);
            atual = atual->prox;
        } while (atual != lista);
    }
}


Apresentadores* criar_Apresentador(const char* nome, Stream* streamAtual, Categorias* categoria){
    /*A função recebe como parametro o nome do apresentado o ponteiro para a stream em que ele será cadastrado e um para a categoria
     em que ele será cadastrado e retorna o ponteiro do novo apresentador ou NULL em caso de erro de alocação*/
    Apresentadores* novo = malloc(sizeof(Apresentadores));
    if(!novo) {
        printf("Erro de alocacao.\n");
        return NULL;
    }
    //Cria cópia independente do nome para poder modificar se necessário
    novo->nomeapresentador = strdup(nome);
    novo->ant = novo->prox = NULL;
    novo->streamatual = streamAtual;
    novo->categoria = categoria;

    //Cria o histórico
    time_t tempo_atual;
    struct tm *info_tempo;
    char data_inicio[20];
    time(&tempo_atual);
    info_tempo = localtime(&tempo_atual);
    strftime(data_inicio, 20, "%d/%m/%Y", info_tempo);
    
    //Aloca e preenche o primeiro registro do histórico
    Historico* historic = malloc(sizeof(Historico));
    historic->nomestream = strdup(streamAtual->nomestream);
    historic->data_inicio = strdup(data_inicio);
    historic->data_fim = strdup("Presente");
    historic->prox = NULL;
    novo->lista = historic;
    return novo;
}

Apresentadores* inserir_Apresentador(Apresentadores* lista, Apresentadores* novo) {
    /*A função  recebe como parâmetro um ponteiro para o inicio da lista de apresentadores e um ponteiro para o apresentador que será adicionado  a lista e retorna o inicio
     da lista já atualizada*/
    if (lista){
        //Verifica se o nome do novo apresentador vem antes do nome do primeiro apresentador da lista em ordem alfabética se sim insere o novo apresentador no começo da lista.
        if (strcmp(novo->nomeapresentador, lista->nomeapresentador) < 0) {
            novo->prox = lista;
            lista->ant = novo;
            lista = novo;
        }
        else{
            Apresentadores* atual = lista;
            /*Caso o apresentador não entre no começo da lista o while percorrera a lista até encontrar uma apresentador que vem depois do novo na ordem alfabética
             ou  até chegar ao final da lista*/
            while (atual->prox != NULL && strcmp(novo->nomeapresentador, atual->prox->nomeapresentador) > 0){
                atual = atual->prox;
            }
            novo->prox = atual->prox;
            if(atual->prox){ // se o while parou antes do último nó  esse condição garante que o ponteiro pro anterior do nó que vem após o atual seja atualizado corretamente
                atual->prox->ant = novo;
            }
            atual->prox = novo;
            novo->ant = atual;
        }
    }
    else{  //Se a lista estiver vazia ela recebe o novo nó que será o primeiro nó da lista
        lista = novo;
    }
    return lista;
}


Apresentadores* cadastrar_Apresentador(Apresentadores* lista, Stream* raizStreams){
    /*A função recebe como parametro o inicio da lista de apresentadores e raiz da arvore de Streams ela pede o nome do apresentador e da stream verifica
     se a stream existe, depois pede o nome da categoria e verifica se a categoria existe então cria um novo apresentador e adiciona ele a lista de apresentadores
      e retorna a lista de apresentadores já atualizada*/
    char nome[50], nomeStream[50], nomeCategoria[50];
    printf("Informe o nome do apresentador.\n");
    scanf("%49[^\n]", nome);
    getchar();
    printf("Informe a Stream em que deseja cadastra-lo:\n");
    scanf("%49[^\n]", nomeStream);
    getchar();
    Stream* streamAtual = busca_Stream(raizStreams, nomeStream);
    if(!streamAtual){//verifica se a stream informada existe
        printf("Stream não encontrada. Cadastro cancelado.\n");
    }
    else{// se ela existe pede o nome da categoria
        printf("Informe a Categoria em que deseja cadastra-lo:\n");
        scanf("%49[^\n]", nomeCategoria);
        Categorias* catAtual = busca_Categorias(streamAtual->categoria, nomeCategoria);
        if(!catAtual) {// verifica se a categoria informada existe na stream informada
            printf("Categoria não encontrada nessa stream. Cadastro cancelado.\n");
        }
        else{
            Apresentadores* novo = criar_Apresentador(nome, streamAtual, catAtual); //retorna um novo no de apresentador já com todas as informações devidamente inicializadas
            if(novo){//verifica se o apresentador foi criado corretamente
                lista = inserir_Apresentador(lista, novo); //insere o apresentador na lista em ordem alfabética
            }
        }
    }
    return lista;
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

Apresentadores* Busca_Apresentador( const char* nome, Apresentadores* lista){
    /* A função recebe uma lista de apresentadores e o nome do apresentador a ser buscado, ela percorre a lista duplamente encadeada de apresentadores
     através de uma estrutura de repetição até que o ponteiro atual receba um valor NULL ou até que o nome do apresentador atual seja igual ao nome informado
     pelo usuario garantindo que o return atual retorne NULL caso o apresentador não seja encontrado ou o endereço de memória para o nó do apresentador caso ele seja encontrado*/
    Apresentadores* atual = lista;
    while(atual!=NULL && strcmp(nome,atual->nomeapresentador)!=0){
        atual = atual->prox;
    }
    return atual;
}

void lerDadosPrograma(char* periodicidade, char* duracao, char* inicio, char* tipo, char* apresentador) {
   /*recebe como parâmetro os ponteiros para onde serão armazenados temporariamente os dados do programa e lê cada um dos dados informados pelo usuário*/ 
    printf("Informe a periodicidade do programa:\n");
    scanf("%49[^\n]", periodicidade);
    getchar();

    printf("Informe a duração do programa:\n");
    scanf("%49[^\n]", duracao);
    getchar();

    printf("Informe o horário de início do programa:\n");
    scanf("%49[^\n]", inicio);
    getchar();

    printf("Informe o tipo do programa:\n");
    scanf("%49[^\n]", tipo);
    getchar();

    printf("Informe o nome do apresentador:\n");
    scanf("%49[^\n]", apresentador); 
    getchar();
}

Programas* criarPrograma(const char* nome, const char* periodicidade, const char* duracao, const char* inicio, const char* tipo, Apresentadores* apresentador) {
    /*A função recebe como parâmetro os dados do programa que será criado e o poteiro para o apresentador do programa e retorna a posição de memória do novo programa ou NULL no caso de erro de alocação*/
    Programas* novo = malloc(sizeof(Programas));
    if(!novo) {
        printf("Erro de alocacao.\n");
        return NULL;
    }
    //copia os dados do programa alocando o espaço necessário para as strings e  inicializa os ponteiros corretamente
    novo->nomeprograma = strdup(nome);
    novo->periodicidade = strdup(periodicidade);
    novo->duracao = strdup(duracao);
    novo->inicio = strdup(inicio);
    novo->tipo = strdup(tipo);
    novo->apresentador = apresentador;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

Apresentadores* validarApresentador(const char* nome, Apresentadores* lista, Stream* stream, Categorias* categoria) {
    /*A função recebe como parâmetro o nome do apresentador informado pelo usuário o inicio da lista de apresentadores a stream e a categria onde o programa será cadastrado
     verifica se o nome do apresentador informado existe na lista e se a Stream e Categorias do programas são as mesmas que as do apresentador se sim retorna
     a posição de memória do apresentador  e se não retorna NULL*/

    Apresentadores* pont = Busca_Apresentador(nome, lista);
    if(!pont) { //Verifica se o apresentador inforado realmente existe.
        printf("ERRO!! Apresentador não cadastrado.\n");
    }
    //verifica se o apresentador informado pertence a mesma Stream e Categoria do programa
    else if(strcmp(pont->categoria->nomecategoria, categoria->nomecategoria) != 0 || strcmp(pont->streamatual->nomestream, stream->nomestream) != 0) {
        printf("ERRO!! Apresentador não corresponde à categoria ou stream.\n");
        pont = NULL;
    }
    return pont;
}

Programas* Cadastra_Programa(Programas* raiz, char* nome, Apresentadores* lista, Stream* stream, Categorias* categoria) {
    /*A função recebe como parâmetro a raiz para a arvore de programas da categoria um ponterio para a stream e um para a categoria onde o programa será cadastrado além do 
     nome do novo programa ela percorre recursivamente a árvore até chegar ao local onde o novo programa deve ser criado cria ele e o seta na árvore corretamente*/
    char periodicidade[50], duracao[50], inicio[50], tipo[50], apresentadorNome[50];
    if(!raiz){//Verifica se a raiz é NULL
        lerDadosPrograma(periodicidade, duracao, inicio, tipo, apresentadorNome);// lê as informações do programa
        Apresentadores* apresentador = validarApresentador(apresentadorNome, lista, stream, categoria);//verifica se o apresentador existe e se ele está na mesma categoria e stream do programa
        if(!apresentador){
            raiz = NULL; // se o apresentador não pode ser validado o programa não é criado então a raiz recebe NULL
        } 
        else{
            raiz = criarPrograma(nome, periodicidade, duracao, inicio, tipo, apresentador); //se o apresentador foi validado um novo prgrama é criado e atribuído a raíz
        }
    }
    // percorre recursivamente a árvore de programas até chegar onde a nova folha da árvore deve ser criada
    else{
        if(strcmp(nome, raiz->nomeprograma) < 0){ // verifica se o nome do programa informado vem antes do nome do programa atual na ordem alfabetica se sim chama a função para a subarvore a esquerda
            raiz->esquerda = Cadastra_Programa(raiz->esquerda, nome, lista, stream, categoria);
        } 
        else if(strcmp(nome, raiz->nomeprograma) > 0){// verifica se o nome do novo programa informado vem depois do nome do programa atual na ordem alfabetica se sim chama a função para a subarvore a direita
            raiz->direita = Cadastra_Programa(raiz->direita, nome, lista, stream, categoria);
        } 
        else{//se não entrar em nenhuma das outras duas condições significa que o nome informado já existe na árvore de programas logo não podera ser cadastrado
            printf("Já existe um Programa com o nome '%s' cadastrada.\n", nome);
        }
    }
    return raiz;
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

void atualizarFimHistorico(Historico* historico) {
    /* a função recebe como parametro a lista do histórico de algum apresentador pega a data atual e copia ela para o campo "data_fim" do histórico informando a data
     em que o apresentador saiu da stream*/
    if(historico){
        time_t tempo_atual;
        struct tm *info_tempo;
        char data[20];
        time(&tempo_atual);
        info_tempo = localtime(&tempo_atual);
        strftime(data, 20, "%d/%m/%Y", info_tempo);
        Historico* atual = historico;
        while (atual->prox != NULL) { 
            atual = atual->prox;
        }
        free(atual->data_fim);
        atual->data_fim = strdup(data);
    }
}

void liberarPrograma(Programas* prog){
    //A função recebe o ponteiro para um programa e libera todos os seus capos corretamente
    if(prog){
        free(prog->nomeprograma);
        free(prog->periodicidade);
        free(prog->duracao);
        free(prog->inicio);
        free(prog->tipo);
        free(prog);
    }
}

void copiarDadosPrograma(Programas* destino, Programas* origem) {
    /*A função recebe como parametro um ponteiro "destino" para o nó que será apagado da árvore de programa e um para o nó "origem" de onde os dados serão
     copiados para manter a organização da árvore.*/
    if (destino && origem){
        //libera os dados atuais do programa
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

Programas* removePrograma(Programas* raiz, char* nomePrograma) {
    /* A função recebe como parâmetro a raiz da árvore de programas e o nome do programa que será removido ela percorre a ávore recursivamente até encontra-lo 
     ou atéencontrar um valo NULL se encontrar o programa o remove e se não a arvore permanece inalterada*/
    if (!raiz) {//Verifica se é o fim do galho e o programa não foi encontrado
        printf("Programa não encontrado.\n");
        return NULL;
    }
    int cmp = strcmp(nomePrograma, raiz->nomeprograma);
    if (cmp < 0) { // verifica se o nome do programa a ser apagado vem antes do nome da raiz atual se sim chama a função para a subarvore da esquerda
        raiz->esquerda = removePrograma(raiz->esquerda, nomePrograma);
    } 
    else if (cmp > 0) { // verifica se o nome do programa a ser apagado vem depois do nome da raiz atual se sim  chama a função para a subarvore de direita
        raiz->direita = removePrograma(raiz->direita, nomePrograma);
    } 
    else {//Programa encontrado
        // Atualiza histórico do apresentador
        if (raiz->apresentador && raiz->apresentador->lista) {
            atualizarFimHistorico(raiz->apresentador->lista);
        }
        // Caso 1 ou 2: nó tem zero ou um filho
        if (!raiz->esquerda) {
            Programas* filho = raiz->direita;
            liberarPrograma(raiz);
            return filho;
        } 
        else if (!raiz->direita) {
            Programas* filho = raiz->esquerda;
            liberarPrograma(raiz);
            return filho;
        }
        // Caso 3: nó tem dois filhos
        Programas* Menor_direita = raiz->direita;
        while (Menor_direita->esquerda != NULL) {
            Menor_direita = Menor_direita->esquerda;
        }
        // Copia dados do menor valor da direita
        copiarDadosPrograma(raiz, Menor_direita);
        // Libera recursivamente o menor elemento da direita da sua posição  antiga sobrando apenas o que foi copiado
        raiz->direita = removePrograma(raiz->direita, Menor_direita->nomeprograma);
    }
    return raiz;
}



void Exibe_Historico(Apresentadores* apresentador){
    // recebe o apresentador e exibe todo o seu histórico
    if(apresentador->lista==NULL){//verifica se o histórico do apresentador não é NULL
        printf("O histórico está vazio.\n");
    }
    else{
        Historico* atual = apresentador->lista;
        while(atual!=NULL){// percorre e printa o histórico completo
            printf("Stream: %s\n", atual->nomestream);
            printf("Periodo: %s à %s\n", atual->data_inicio,atual->data_fim);
            atual = atual->prox;
        }
    }
}

Categorias* removeNoListaCircular(Categorias* lista, Categorias* anterior, Categorias* remover){
    /*A função recebe a lista de categorias de uma stream um ponteiro para a categoria que sera removida e o ponteiro para a categoria anterior a que será removida
     o remoe e retorna a lista atualizada*/
    if (lista->prox == lista) {
        lista = NULL;
    }
    else if(remover == lista) {
        // remover é o primeiro da lista
        Categorias* ultimo = lista;
        while (ultimo->prox != lista){ 
            ultimo = ultimo->prox;
        }
        lista = remover->prox; // novo início
        ultimo->prox = lista;  // mantém circularidade
    }
    else{
         anterior->prox = remover->prox; // remove o nó do meio/final
    }
    //libera os espaços alocados
    free(remover->nomecategoria);
    free(remover->tipo);
    free(remover);
    printf("Categoria removida com sucesso.\n");
    return lista;
}

void buscaCategoriaEAnterior(Categorias* lista, char* nome, Categorias** anterior, Categorias** remover){
    /*A função recebe a lista de categorias o nome da categoria a ser buscada e o ponteiro para guardar o anterior ao que será removido e um para guradar o que será 
     removido ambos por referência e percorre a lista até encontrar o no que sera removido e o seu antecessor caso não enncontre, o  ponteiro que gurdaria a posição do no
      a ser removido recebe NULL*/
    *anterior = lista;
    *remover = lista;
    if(lista){
        do{
            *anterior = *remover;
            *remover = (*remover)->prox;
        }while(*remover != lista && strcmp((*remover)->nomecategoria, nome) != 0);

        if(strcmp((*remover)->nomecategoria, nome) != 0){
            *remover = NULL; // não encontrado
        }
    }
}

Categorias* removeCategoria(Categorias* lista, char* nomeCategoria){
    /*A função recebe a lista de categorias e o nome da categoria que será removida chama a função buscaCategoriaEAnterior para atualizar os ponteiros atual e anterior
     corretamente, depois verifica se o no que sera removido tem ou não programas e se não tiver a função removeNoListaCircular é chamada e remove o no e então retorna a lista atualizada*/
    if (lista){
        Categorias* anterior = NULL;
        Categorias* remover = NULL;
        buscaCategoriaEAnterior(lista, nomeCategoria, &anterior, &remover);//Preenche o ponteiros atual e anterior com o no a ser removido e o no antecessor a ele respectivamente
        if (!remover){
            printf("Categoria não encontrada.\n");
        }
        else{
            if (remover->programas){//verifica se a categoria possui programas
                printf("A categoria possui programas cadastrados.\n");
            }
            else{// SE Não possui programas a categoria é removida
                lista = removeNoListaCircular(lista, anterior, remover);
            }
        }
    }
    return lista; // único return no final
}


int apresentadorTemProgramaNosProgramas(Programas* prog, Apresentadores* apresentador){
    /*A função recebe como parâmetro a raiz da arvore de programas e um ponteiro para um apresentador e percorre a arvore recursuvamente comparando o apresentador 
     de cada programa com o apresentador que foi  passado como parâmetro se o apresentador já apresenta algum programa a função retorna 1 (verdadeiro) de não retorna 0 (falso)*/
    int aux = 0;
    if(prog){
        if(prog->apresentador == apresentador){// verifica se o apresentador do programa eu mesmo que foi passado compo parâmetro
            aux = 1;
        }
        else if (apresentadorTemProgramaNosProgramas(prog->esquerda, apresentador) || apresentadorTemProgramaNosProgramas(prog->direita, apresentador)){//Se não é o mesmo a função é chamada novamente para a subarvore da direita e para a da esquerda
            aux = 1;
        }
    }
    return aux;
}

int apresentadorTemProgramaNaStream(Categorias* lista, Apresentadores* apresentador) {
    /*A função recebe a lista de categorias de uma Stream e o ponteiro para um apresentador ela percorre todas as categorias verificando se o apresentador
     já apresenta algum programa em alguma categoria se sim retorna 1 (verdadeiro) se não retorna 0 (false)*/
    int aux = 0;
    if(lista){
        Categorias* atual = lista;
        do{
            if(atual->programas && apresentadorTemProgramaNosProgramas(atual->programas, apresentador)){//verifica se algum programa da categoria atual já é apresentado pelo apresentador passado como parâmetro
                aux = 1;
            }
            atual = atual->prox;
        }while(atual!=lista);
    }
    return aux;
}

int validarAssociacao(Stream* stream, Apresentadores* apresentador){
    /*A função recebe um ponteiro para a stream onde o apresentador será associado e um ponteiro para o apresentador e verifica se a stream e o apresentador 
     são validos depois verifica se o apresentador já apresenta algum programa nessa stream se entrar em alguma das condições retorna 0 (false) se não retorna 1 (verdadeiro)*/
    int aux = 1;
    if (!stream || !apresentador) {
        printf("Erro: Stream ou apresentador inválido.\n");
        aux = 0;
    }
    else{
        //verifica se o apresentador já tem programa na nova stream
        if (apresentadorTemProgramaNaStream(stream->categoria, apresentador)) {
            printf("Erro: Apresentador já possui programa nesta stream.\n");
            aux = 0;
        }
    }
    return aux;
}


void adicionarHistorico(Apresentadores* apresentador, const char* nomestream) {
    /*A função recebe um ponteiro para um apresentador e o nome da stream em que o apresentador está sendo associaado ela pega o tempo atual e guarda em "data_inicio"
     e coloca a "data_fim" como "presente" para especificar que o apresentador está nesta stream atualmente depois ela adiciona o novo no do historico na lista de histórico do aprentador*/
    if(apresentador){// verifica se o apresentador é válido
        time_t tempo_atual;
        struct tm *info_tempo;
        char data[20];
        time(&tempo_atual);
        info_tempo = localtime(&tempo_atual);
        strftime(data, 20, "%d/%m/%Y", info_tempo);
        Historico* novo = malloc(sizeof(Historico));
        novo->nomestream = strdup(nomestream);
        novo->data_inicio = strdup(data);
        novo->data_fim = strdup("Presente");
        novo->prox = NULL;
        if (apresentador->lista == NULL){// verifica se a lista de historico é NULL e se sim o novo no se torna o primeiro no da lista
            apresentador->lista = novo;
        }
        else { // se a lista não é vazia o  novo no é adicionado no final  do histórico
            Historico* atual = apresentador->lista;
            while (atual->prox != NULL){//percorre a lista e para no último elemento
                atual = atual->prox;
            }
            atual->prox = novo;//faz o ultimo elemento apontar para o novo que agr será o último
        }
    }
}

void Associar_Stream(Stream* stream, Apresentadores* apresentador, Categorias* novaCategoria){
    /*A função recebe um ponteiro para a Stream e para a categoria onde o apresentador será associado alèm do ponteiro para o próprio apresentador verifica se
     ele pode ser associado atualiza seu histórico e o associa a nova Stream*/
    if (validarAssociacao(stream, apresentador)){ //Verifica se o apresentador já tem programa cadastrado na strean
        if (apresentador->lista != NULL) {
            atualizarFimHistorico(apresentador->lista);//Encerra o periodo em que o apresentador esteve associado a sua antiga stream.
        } 
        adicionarHistorico(apresentador, stream->nomestream);//Inicia o periodo em que o apresentador está associado a nova stream
        
        // Atualizar stream e categoria
        apresentador->streamatual = stream;
        apresentador->categoria = novaCategoria;
        
        printf("Stream associada/alterada com sucesso!\n");
    }
}


void libera_Programa(Programas* raiz){
    /*recebe a raiz para uma arvore de categorias e a percorre recursivamente liberando ca espaço alocado*/
    if(raiz){  
        libera_Programa(raiz->direita);//chama para liberar a subarvore da direita
        libera_Programa(raiz->esquerda);//chama para liberar a subarvore da esquerda
        free(raiz->nomeprograma); 
        free(raiz->periodicidade);
        free(raiz->duracao);
        free(raiz->inicio);
        free(raiz->tipo);
        free(raiz);
    }
}

void libera_Categoria(Categorias* lista){
    /*A função recebe uma lista de categorias e a percorre liberando todos os seus espaços alocados*/
    if (lista) {//Verifica se a lista é vazia
        Categorias* atual = lista->prox;
        while (atual != lista) {// Percoore a lista do segundo nó até o ultimo.
            Categorias* temp = atual;
            atual = atual->prox;
            free(temp->tipo);
            free(temp->nomecategoria);
            libera_Programa(temp->programas);
            free(temp);
        }
        // libera o nó inicial por último
        free(lista->tipo);
        free(lista->nomecategoria);
        libera_Programa(lista->programas);
        free(lista);
    }
}


void libera_Stream(Stream* raiz){
    /*recebe a raiz da arvore de Stream e a percorre recursivamete por completo liberando cada espaço alocado dentro dela*/
    if(raiz){
        libera_Categoria(raiz->categoria);//libera a arvore de categorias
        libera_Stream(raiz->direita); //chama para liberar a subarvore da direita
        libera_Stream(raiz->esquerda);//chama para liberar a subarvore da esquerda
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