#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tad.h"


Apresentadores* menu_Programas(Programas** raiz, Apresentadores* lista, Stream* stream, Categorias* categoria) {
    int op;
    do {
        printf("\n-------- MENU PROGRAMAS --------\n");
        printf("1- Adicionar Programa.\n");
        printf("2- Listar Programas.\n");
        printf("3- Buscar Programa.\n");
        printf("4- Excluir Programa.\n");
        printf("5- Programas por Dia.\n");
        printf("6- Voltar.\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1: {
                char nome[50];
                printf("Informe o nome do programa: ");
                scanf("%49[^\n]", nome);
                getchar();

                if (busca_Programa((*raiz), nome) != NULL) {
                    printf("❌ ERRO: O programa '%s' já está cadastrado nesta categoria.\n", nome);
                } else {
                    (*raiz) = Cadastra_Programa((*raiz), nome, lista, stream, categoria);
                    printf("✅ Programa '%s' cadastrado com sucesso!\n", nome);
                }
                break;
            }

            case 2:
                if ((*raiz)) {
                    printf("\n📋 Lista de Programas:\n");
                    mostra_Programa((*raiz));
                } else {
                    printf("ℹ️ Nenhum programa cadastrado até o momento.\n");
                }
                break;

            case 3: {
                char nome[50];
                printf("Informe o nome do programa para buscar: ");
                scanf("%49[^\n]", nome);
                getchar();

                Programas* result = busca_Programa((*raiz), nome);
                if (result == NULL) {
                    printf("❌ Programa '%s' não encontrado.\n", nome);
                } else {
                    printf("✅ Programa encontrado:\n");
                    mostrarDadosPrograma(result);
                }
                break;
            }

            case 4: {
                char nomePrograma[50];
                printf("Informe o nome do programa a remover: ");
                scanf("%49[^\n]", nomePrograma);
                getchar();

                if (busca_Programa(categoria->programas, nomePrograma)) {
                    categoria->programas = removePrograma(categoria->programas, nomePrograma);
                    printf("✅ Programa '%s' removido com sucesso!\n", nomePrograma);
                } else {
                    printf("❌ ERRO: Programa '%s' não encontrado na categoria.\n", nomePrograma);
                }
                break;
            }

            case 5: {
                char dia[20];
                printf("Informe o dia da semana: ");
                scanf("%19[^\n]", dia);
                getchar();

                printf("\n📅 Programas no dia %s:\n", dia);
                mostrarProgramasPorDiaSemana((*raiz), dia);
                break;
            }

            case 6:
                printf("↩️ Voltando ao menu principal...\n");
                break;

            default:
                printf("⚠️ Opção inválida. Tente novamente.\n");
                break;
        }

    } while (op != 6);

    return lista;
}

Apresentadores* menu_Categorias(Categorias** raiz, Apresentadores* lista, Stream* stream) {
    int op = 1;
    do {
        printf("\n-------- MENU CATEGORIAS --------\n");
        printf("1- Adicionar Categoria.\n");
        printf("2- Listar Categorias.\n");
        printf("3- Buscar Categoria.\n");
        printf("4- Acessar Categoria.\n");
        printf("5- Excluir Categoria.\n");
        printf("6- Voltar.\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1: {
                char nome[50], tipo[50];
                printf("Informe o nome da categoria: ");
                scanf("%49[^\n]", nome);
                getchar();

                printf("Informe o tipo da categoria (notícias / esporte / entretenimento): ");
                scanf("%49[^\n]", tipo);
                getchar();

                // verifica se já existe categoria com esse nome
                if (busca_Categorias((*raiz), nome) != NULL) {
                    printf("❌ ERRO: A categoria '%s' já está cadastrada.\n", nome);
                } 
                // validação do tipo
                else if (
                    strcmp(tipo, "notícias") != 0 &&
                    strcmp(tipo, "esporte") != 0 &&
                    strcmp(tipo, "entretenimento") != 0
                ) {
                    printf("❌ ERRO: Tipo inválido! Digite exatamente 'notícias', 'esporte' ou 'entretenimento'.\n");
                }
                // só cadastra se passou em todas as verificações
                else {
                    (*raiz) = Cadastra_Categoria((*raiz), nome, tipo);
                    printf("✅ Categoria '%s' cadastrada com sucesso!\n", nome);
                }
                break;
            }


            case 2:
                if ((*raiz) == NULL) {
                    printf("ℹ️ Nenhuma categoria cadastrada no momento.\n");
                } else {
                    printf("\n📋 Lista de Categorias:\n");
                    mostra_Categoria((*raiz));
                }
                break;

            case 3: {
                char nome[50];
                printf("Informe o nome da categoria para buscar: ");
                scanf("%49[^\n]", nome);
                getchar();

                Categorias* result = busca_Categorias((*raiz), nome);
                if (result == NULL) {
                    printf("❌ Categoria '%s' não encontrada.\n", nome);
                } else {
                    printf("✅ Categoria encontrada:\n");
                    printf("   Nome: %s\n", result->nomecategoria);
                    printf("   Tipo: %s\n", result->tipo);
                }
                break;
            }

            case 4: {
                char nome[50];
                printf("Informe o nome da categoria para acessar: ");
                scanf("%49[^\n]", nome);
                getchar();

                Categorias* result = busca_Categorias((*raiz), nome);
                if (result == NULL) {
                    printf("❌ Categoria '%s' não encontrada.\n", nome);
                } else {
                    printf("✅ Acessando categoria '%s'...\n", nome);
                    lista = menu_Programas(&(result->programas), lista, stream, result);
                }
                break;
            }

            case 5: {
                char nome[50];
                printf("Informe o nome da categoria a remover: ");
                scanf("%49[^\n]", nome);
                getchar();

                if (busca_Categorias((*raiz), nome) == NULL) {
                    printf("❌ ERRO: Categoria '%s' não encontrada.\n", nome);
                } else {
                    (*raiz) = removeCategoria(*raiz, nome);
                    printf("✅ Categoria '%s' removida com sucesso!\n", nome);
                }
                break;
            }

            case 6:
                printf("↩️ Voltando ao menu principal...\n");
                break;

            default:
                printf("⚠️ Opção inválida. Tente novamente.\n");
                break;
        }

    } while (op != 6);

    return lista;
}

Apresentadores* menu_Stream(Stream** raiz, Apresentadores* lista) {
    int op;

    do {
        printf("\n-------- MENU STREAMS --------\n");
        printf("1- Cadastrar Stream\n");
        printf("2- Buscar Stream\n");
        printf("3- Listar Streams\n");
        printf("4- Editar Categorias\n");
        printf("5- Filtrar Streams por Categoria\n");
        printf("6- Filtrar Streams por Tipo\n");
        printf("7- Exibir Apresentadores da Stream\n");
        printf("8- Programas por Dia e Horário em Stream\n");
        printf("9- Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1: {
                char nome[50];
                char site[50];
                printf("Informe o nome da stream: ");
                scanf("%49[^\n]", nome);
                getchar();

                printf("Informe o site da stream (ex: https://www.exemplo.com): ");
                scanf("%49[^\n]", site);
                getchar();

                if (busca_Stream((*raiz), nome) != NULL) {
                    printf("❌ ERRO: A stream '%s' já está cadastrada.\n", nome);
                } else {
                    Stream* nova = Cadastra_stream((*raiz), nome, site); // assume que retorna NULL se inválida
                    if (nova == NULL) {
                        printf("❌ ERRO: Stream não cadastrada. URL inválida ou dados incorretos.\n");
                    } else {
                        (*raiz) = nova;
                        printf("✅ Stream '%s' cadastrada com sucesso!\n", nome);
                    }
                }
                break;
            }


            case 2: {
                char nome[50];
                printf("Informe o nome da stream para buscar: ");
                scanf("%49[^\n]", nome);
                getchar();

                Stream* result = busca_Stream((*raiz), nome);
                if (result == NULL) {
                    printf("❌ Stream '%s' não encontrada.\n", nome);
                } else {
                    printf("✅ Stream encontrada:\n");
                    printf("   Nome: %s\n", result->nomestream);
                    printf("   Site: %s\n", result->site);
                }
                break;
            }

            case 3:
                if ((*raiz) == NULL) {
                    printf("ℹ️ Nenhuma stream cadastrada.\n");
                } else {
                    printf("\n📋 Lista de Streams:\n");
                    mostra_Stream((*raiz));
                }
                break;

            case 4: {
                char nome[50];
                printf("Informe o nome da Stream para editar categorias: ");
                scanf("%49[^\n]", nome);
                getchar();

                Stream* result = busca_Stream((*raiz), nome);
                if (result == NULL) {
                    printf("❌ Stream '%s' não encontrada.\n", nome);
                } else {
                    printf("✅ Acessando categorias da Stream '%s'...\n", nome);
                    lista = menu_Categorias(&(result->categoria), lista, (*raiz));
                }
                break;
            }

            case 5: {
                char categoria[50];
                int flag = 0;
                printf("Informe o nome da categoria: ");
                scanf("%49[^\n]", categoria);
                getchar();

                printf("\n📌 Streams que possuem a categoria '%s':\n", categoria);
                FiltraStreamsporCategoria((*raiz), categoria, &flag);

                if (!flag) {
                    printf("❌ Nenhuma stream encontrada com a categoria '%s'.\n", categoria);
                }
                break;
            }

            case 6: {
                char tipo[50];
                int flag = 0;
                printf("Informe o tipo da categoria: ");
                scanf("%49[^\n]", tipo);
                getchar();

                printf("\n📌 Streams que possuem categorias do tipo '%s':\n", tipo);
                FiltraStreamsporTipo((*raiz), tipo, &flag);

                if (!flag) {
                    printf("❌ Nenhuma stream encontrada com categorias do tipo '%s'.\n", tipo);
                }
                break;
            }

            case 7: {
                int flag = 0;
                char streamNome[50];
                printf("Informe o nome da Stream: ");
                scanf("%49[^\n]", streamNome);
                getchar();

                ExibeApresentadoresDeUmaStream(lista, streamNome, &flag);
                if (!flag) {
                    printf("❌ A stream '%s' não possui apresentadores cadastrados.\n", streamNome);
                }
                break;
            }

            case 8: {
                char nomeStream[50], dia[20], horario[10];
                printf("Informe o nome da Stream: ");
                scanf("%49[^\n]", nomeStream);
                getchar();

                printf("Informe o dia da semana: ");
                scanf("%19[^\n]", dia);
                getchar();

                printf("Informe o horário (HH:MM): ");
                scanf("%9[^\n]", horario);
                getchar();

                Stream* streamBusca = busca_Stream(*raiz, nomeStream);
                if (streamBusca) {
                    printf("\n📌 Programas da Stream '%s' no dia %s às %s:\n", nomeStream, dia, horario);
                    mostrarProgramasStreamDiaHorario(streamBusca, dia, horario);
                } else {
                    printf("❌ Stream '%s' não encontrada.\n", nomeStream);
                }
                break;
            }

            case 9:
                printf("↩️ Voltando ao menu principal...\n");
                break;

            default:
                printf("⚠️ Opção inválida. Tente novamente.\n");
                break;
        }

    } while (op != 9);

    return lista;
}
Apresentadores* menu_Apresentador(Apresentadores* lista, Stream* raiz) {
    int op;
    do {
        printf("\n-------- MENU APRESENTADORES --------\n");
        printf("1- Cadastrar Apresentador\n");
        printf("2- Listar Apresentadores\n");
        printf("3- Associar Apresentador a uma Stream\n");
        printf("4- Histórico do Apresentador\n");
        printf("5- Filtrar Apresentadores por Categoria\n");
        printf("6- Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1:
                lista = cadastrar_Apresentador(lista, raiz);
                printf("✅ Apresentador cadastrado com sucesso!\n");
                break;

            case 2:
                if (lista == NULL) {
                    printf("ℹ️ Nenhum apresentador cadastrado.\n");
                } else {
                    printf("\n📋 Lista de Apresentadores:\n");
                    Mostra_Apresentador(lista);
                }
                break;

            case 3: {
                char buscarAp[50], buscarSt[50], novaCategoria[50];
                printf("Informe o nome do apresentador: ");
                scanf("%49[^\n]", buscarAp);
                getchar();

                printf("Informe o nome da stream: ");
                scanf("%49[^\n]", buscarSt);
                getchar();

                printf("Informe a nova categoria na stream '%s': ", buscarSt);
                scanf("%49[^\n]", novaCategoria);
                getchar();

                Apresentadores* apresentador = Busca_Apresentador(buscarAp, lista);
                Stream* stream = busca_Stream(raiz, buscarSt);

                if (apresentador == NULL) {
                    printf("❌ Apresentador '%s' não encontrado.\n", buscarAp);
                } else if (stream == NULL) {
                    printf("❌ Stream '%s' não encontrada.\n", buscarSt);
                } else {
                    Categorias* categoria = busca_Categorias(stream->categoria, novaCategoria);
                    if (categoria == NULL) {
                        printf("❌ ERRO: Categoria '%s' não encontrada na stream '%s'.\n", 
                               novaCategoria, buscarSt);
                    } else {
                        Associar_Stream(stream, apresentador, categoria);
                        printf("✅ Apresentador '%s' associado à categoria '%s' da stream '%s' com sucesso!\n",
                               buscarAp, novaCategoria, buscarSt);
                    }
                }
                break;
            }

            case 4: {
                char buscar[50];
                printf("Informe o nome do apresentador: ");
                scanf("%49[^\n]", buscar);
                getchar();

                Apresentadores* apresentador = Busca_Apresentador(buscar, lista);
                if (apresentador == NULL) {
                    printf("❌ Apresentador '%s' não encontrado.\n", buscar);
                } else {
                    printf("📌 Histórico do Apresentador '%s':\n", buscar);
                    Exibe_Historico(apresentador);
                }
                break;
            }

            case 5: {
                char categoria[50];
                printf("Informe o nome da categoria: ");
                scanf("%49[^\n]", categoria);
                getchar();

                printf("\n📋 Apresentadores que possuem a categoria '%s':\n", categoria);
                ExibeApresentadoresPorCategoria(lista, categoria);
                break;
            }

            case 6:
                printf("↩️ Voltando ao menu principal...\n");
                break;

            default:
                printf("⚠️ Opção inválida. Tente novamente.\n");
                break;
        }

    } while (op != 6);

    return lista;
}
int main() {
    Stream* raiz = NULL;
    Apresentadores* lista = NULL;
    int op;

    do {
        printf("\n====================================\n");
        printf("          🎬 SISTEMA DE STREAMS 🎬\n");
        printf("====================================\n");
        printf("| 1 - Streams                     |\n");
        printf("| 2 - Apresentadores               |\n");
        printf("| 3 - Sair                         |\n");
        printf("====================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1:
                lista = menu_Stream(&raiz, lista);
                break;

            case 2:
                lista = menu_Apresentador(lista, raiz);
                break;

            case 3:
                printf("\n🔒 Encerrando o sistema...\n");
                libera_Stream(raiz);
                libera_apresentadores(lista);
                break;

            default:
                printf("⚠️ Opção inválida. Digite uma opção entre 1 e 3.\n");
                break;
        }

    } while (op != 3);

    printf("✅ Sistema finalizado. Até logo!\n");
    return 0;
}
