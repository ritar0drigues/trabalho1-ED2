#include "tad.h"

void mostra_Stream(Stream* raiz){
    if(raiz){
        mostra_Stream(raiz->esquerda);
        printf("Nome: %s | Site: %s\n", raiz->nomestream, raiz->site);
        mostra_Stream(raiz->direita);
    }
}

void Cadastra_stream(Stream** raiz, char* nome, char* site,int *flag){
        if(!(*raiz)){
            Stream* novo = (Stream*) malloc(sizeof(Stream));
            if(novo){
                novo->nomestream = strdup(nome);
                novo->site = strdup(site);
                novo->categoria = NULL;
                novo->esquerda = NULL;
                novo->direita = NULL;
            }
            (*raiz) = novo;
        }
        else{
            if(strcasecmp(nome, (*raiz)->nomestream) < 0){
                Cadastra_stream(&(*raiz)->esquerda, nome, site,flag);
            }
            else if(strcasecmp(nome,(*raiz)->nomestream) > 0){
                Cadastra_stream(&(*raiz)->direita, nome, site,flag);
            }
            else{
                *flag = 0;
            }
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