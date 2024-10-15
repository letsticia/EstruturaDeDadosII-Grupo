#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "reservas\reservas.c"
#define SIZE 21

void menu() {
    printf("============================================================================================\n");
    printf("=                            Bem vindo(a) ao Arena Beach                                   =\n");
    printf("============================================================================================\n");
    printf("                             1 - Exibir Horários Disponíveis\n");
    printf("                             2 - Adicionar Reserva\n");
    printf("                             3 - Remover Reserva\n");
    printf("                             4 - Editar Reserva\n");
    printf("                             5 - Buscar Reserva\n");
    printf("                             6 - Sair\n");
    printf("============================================================================================\n");
    printf("--->  Digite a opção desejada: ");
}

int main(void) {
    Hash tabela;
    system("chcp 65001");

    Node * raiz_avl = NULL;
    inicializa_tabela_hash(&tabela);
    raiz_avl = carrega_avl_dia_atual(raiz_avl, "historico_agendamentos.txt");
    transfere_avl_para_hash(raiz_avl, &tabela);
    
    int opcao;
    do {
        limpa_tela();
        menu();
        scanf("%d", &opcao);
        pausa_programa();
        limpa_tela();
        
        switch (opcao) {
            case 1:
                exibe_horarios_disponiveis(&tabela);
                pausa_programa();
                break;
            case 2:
                tela_adiciona_reserva(&tabela);
                break;
            case 3:
                tela_remove_reserva(&tabela);
                break;
            case 4:
                tela_edita_reserva(&tabela);
                break;
            case 5:
                tela_busca_reserva(&tabela);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
        printf("\n");
    } while (opcao != 6);
    

    FILE* arquivo_historico = fopen("historico_agendamentos.txt", "a");

    if (arquivo_historico == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    raiz_avl = transfere_para_avl(&tabela, raiz_avl);
    
    salva_historico_atualizado(raiz_avl, "historico_agendamentos.txt");

    fclose(arquivo_historico);
    libera_avl(raiz_avl);
    printf("Histórico de agendamentos salvo com sucesso!\n");

    return 0;
}


 
