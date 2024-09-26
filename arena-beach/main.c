#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "C:\Users\shamy\Desktop\estrutura de dados 2\EstruturaDeDadosII-Grupo\arena-beach\reservas\reservas.c"
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
    inicializa_tabela_hash(tabela);
    
    int opcao;
    do {
        menu();
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                exibe_horarios_disponiveis(tabela);
                break;
            case 2:
                tela_adicionar_reservas(tabela);
                break;
            case 3:
                tela_remove_reserva(tabela);
                break;
            case 4:
                tela_edita_reserva(tabela);
                break;
            case 5:
                tela_busca_reserva(tabela);
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

 