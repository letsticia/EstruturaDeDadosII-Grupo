#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    
    printf("============================================================================================\n");
    printf("=                            Bem vindo(a) ao Arena Beach                                   =\n");
    printf("============================================================================================\n\n");

    printf("                                                                              %02d/%02d/%04d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    printf("                             1 - Histórico de Reservas\n");
    printf("                             2 - Adicionar Reserva\n");
    printf("                             3 - Remover Reserva\n");
    printf("                             4 - Editar Reserva\n");
    printf("                             5 - Buscar Reserva\n");
    printf("                             6 - Sair\n\n");

    printf("============================================================================================\n");
    printf("--->  Digite a opção desejada: ");
    
}

int main(){
    system("chcp 65001"); // Define o charset para UTF-8 (permite a exibição de caracteres especiais)
    menu();
    return 0;
}
