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
    inicializa_tabela_hash(&tabela);
    
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
    
    return 0;
}

 
