#include "tadAVL.h"

void mostra_Stream(Stream* raiz){
    if(raiz){
        mostra_Stream(raiz->esquerda);
        printf("Nome: %s | Site: %s\n", raiz->nomestream, raiz->site);
        printf("Altura:%d\n", raiz->altura);
        mostra_Stream(raiz->direita);
    }
}

int fatorBalanceamentostream(Stream* NO){
    int fb;
    if((NO->direita==NULL) && (NO->esquerda!=NULL)){//Calcule o fb se o no da direita for NULL
        fb = NO->esquerda->altura - (-1) ;
    }
    else if(NO->esquerda==NULL && NO->direita!=NULL){//Calcule o fb se o no da esquerda for NULL
        fb = (-1) - NO->direita->altura ;
    }
    else if(NO->direita && NO->esquerda){//Calcula o fb se o nenhum dos filhos são NULL
        fb = NO->esquerda->altura - NO->direita->altura;
    }
    else{//Se os dois filhos forem NULL o fb é zero
        fb = 0;
    }
    return fb;
}

int So_um_filho(Stream* NO){
    int aux = 0;
    if((NO->esquerda==NULL && NO->direita!=NULL) || (NO->esquerda!=NULL && NO->direita==NULL)){
        aux = 1;
    }
    return aux;
}

void Atualiza_Alt_Stream(Stream** NO){
    if(!((*NO)->esquerda)&& !((*NO)->direita)){//Se  o no é folha a altura é zero
        (*NO)->altura = 0;
    }
    else if(So_um_filho((*NO))){
        if((*NO)->direita){//se o filho for o nó da direita
            (*NO)->altura = (*NO)->direita->altura+1;
        }    
        else{ //se o filho for o nó da esquerda
            (*NO)->altura = (*NO)->esquerda->altura+1;
        }
    }
    else{ //Se o nó tem dois filhos
        /*Verifica qual dos filhos é o mais alto e atribui a "alturadofilho+1" à altura do nó*/ 
        if((*NO)->esquerda->altura > (*NO)->direita->altura){
            (*NO)->altura = (*NO)->esquerda->altura+1;
        }
        else{
            (*NO)->altura = (*NO)->direita->altura+1;
        }
    }
}

void rotacionar_Dir_Stream(Stream** raiz){
    //Efetua a rotação
    Stream* aux;
    aux = (*raiz)->esquerda;
    (*raiz)->esquerda = aux ->direita;
    aux->direita = (*raiz);
    (*raiz) = aux;
    /*Atualiza a altura do nós rotacionados*/ 
    Atualiza_Alt_Stream(&((*raiz)->direita));
    Atualiza_Alt_Stream(raiz);
}

void rotacionar_Esq_Stream(Stream** raiz){
    //Efetua a rotação
    Stream* aux;
    aux = (*raiz)->direita;
    (*raiz)->direita = aux->esquerda;
    aux->esquerda = (*raiz);
    (*raiz) = aux;
    /*Atualiza a altura do nós rotacionados*/ 
    Atualiza_Alt_Stream(&((*raiz)->esquerda));
    Atualiza_Alt_Stream(raiz);
}

void BalanceamentoStream(Stream** NO){
    int fb;
    fb = fatorBalanceamentostream((*NO));
    if(fb==2){
        int fb_esq;
        fb_esq = fatorBalanceamentostream((*NO)->esquerda);
        if(fb_esq<0){
            rotacionar_Esq_Stream(&(*NO)->esquerda);
        }
        rotacionar_Dir_Stream(NO);
    }
    else if(fb==-2){
        int fb_dir;
        fb_dir = fatorBalanceamentostream((*NO)->direita);
        if(fb_dir>0){
            rotacionar_Dir_Stream(&(*NO)->direita);
        }
        rotacionar_Esq_Stream(NO);
    }
}

void Cadastra_StreamAVL(Stream** raiz, char* nome, char* site,int *flag){
        if(!(*raiz)){
            Stream* novo = (Stream*) malloc(sizeof(Stream));
            if(novo){
                novo->nomestream = strdup(nome);
                novo->site = strdup(site);
                novo->altura = 0;
                novo->categoria = NULL;
                novo->esquerda = NULL;
                novo->direita = NULL;
            }
            (*raiz) = novo;
        }
        else{
            if(strcasecmp(nome, (*raiz)->nomestream) < 0){
                Cadastra_StreamAVL(&(*raiz)->esquerda, nome, site,flag);
            }
            else if(strcasecmp(nome,(*raiz)->nomestream) > 0){
                Cadastra_StreamAVL(&(*raiz)->direita, nome, site,flag);
            }
            else{
                *flag = 0;
            }
            /*A função para atualizar altura e de balanceamento são chamadas como uma pendência garantindo que a altura e o balanceamento sejam calculados de baixo para cima*/
            BalanceamentoStream(raiz);
            Atualiza_Alt_Stream(raiz);
        }
}

Stream* busca_Stream(Stream* raiz, char* nome) {
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

void FiltraStreamsporCategoria(Stream* raiz, char* categoria,int* flag){
    if(raiz){
        FiltraStreamsporCategoria(raiz->esquerda, categoria, flag);
        Categorias* atual = raiz->categoria;
        if(atual){
            do{
                if(strcmp(atual->nomecategoria,categoria)==0){
                    printf("%s \n", raiz->nomestream);
                    *flag = 1;
                }
                atual = atual->prox;
            }while(atual!=raiz->categoria);
        }
        FiltraStreamsporCategoria(raiz->direita, categoria, flag);
    }
}

void FiltraStreamsporTipo(Stream* raiz, char* tipo,int* flag){
    if(raiz){
        FiltraStreamsporTipo(raiz->esquerda, tipo, flag);
        Categorias* atual = raiz->categoria;
        if(atual){
            int encontrou = 0;
            do{
                if(strcmp(atual->tipo,tipo)==0){
                    encontrou = 1;
                }
                atual = atual->prox;
            }while(atual!=raiz->categoria);
            if(encontrou){
                printf("%s\n", raiz->nomestream);
                *flag = 1;
            }
        }
        FiltraStreamsporTipo(raiz->direita,tipo, flag); 
    }
}

void ExibeApresentadoresDeUmaStream (Apresentadores*lista, char* nomeStream,int* flag){
    if(lista){
        Apresentadores* atual = lista;
        while(atual!=NULL){
            if(strcmp(atual->streamatual->nomestream,nomeStream)==0){
                printf("%s\n", atual->nomeapresentador);
                *flag = 1;
            }
            atual = atual->prox;
        }
    }
}

void percorrerProgramasDiaHorario(Programas* raiz, const char* dia, const char* horario, int* encontrou) {
    if (raiz) {
        percorrerProgramasDiaHorario(raiz->esquerda, dia, horario, encontrou);
        
        if (programaAconteceNoDia(raiz, dia) && validarFormatoHorario(horario) && strcmp(raiz->inicio, horario) == 0) {
            
            printf("• %s | Categoria: %s | Apresentador: %s\n",raiz->nomeprograma, raiz->apresentador->categoria->nomecategoria, raiz->apresentador->nomeapresentador);
            *encontrou = 1;
        }
        
        percorrerProgramasDiaHorario(raiz->direita, dia, horario, encontrou);
    }
}

void mostrarProgramasStreamDiaHorario(Stream* stream, const char* dia, const char* horario,int* encontrou) {
    if(stream && stream->categoria){
        Categorias* cat_atual = stream->categoria;
        do {
            if (cat_atual->programas) {
                // Função auxiliar para percorrer a árvore de programas
                percorrerProgramasDiaHorario(cat_atual->programas, dia, horario, encontrou);
            }
            cat_atual = cat_atual->prox;
        }while(cat_atual != stream->categoria);
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
