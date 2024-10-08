#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "reservas.h"
#define SIZE 21

void limpa_tela()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausa_programa()
{
    #ifdef _WIN32
        system("pause");
    #else
        printf("Pressione ENTER para continuar...");
        getchar();
    #endif
}

void inicializa_tabela_hash(Hash* tabela)
{
    for (int count = 0; count < SIZE; count++)
    {
        (*tabela)[count] = NULL;
    }
}

void exibe_horarios_disponiveis(Hash* tabela)
{

    int contagem[21] = {0};
    printf("-----------------------------------------------\n");
    printf("Quadra 1\tQuadra 2\tQuadra 3\n");
    printf("-----------------------------------------------\n\n");
    int count = 0;
    for (int Horario = 16; Horario <= 22; Horario++)
    {
        count = count + 1;
        for (int quadra = 0; quadra <= 2; quadra++)
        {
            int id = count + 7 * quadra;
            int pos = chaveia(quadra + 1, Horario);
            if ((*tabela)[pos] == NULL)
            {
                printf("[%d] %d:00\t", id, Horario);
            }
            else
            {
                printf("---------\t");
            }
        }

        printf("\n");
    }
    printf("-----------------------------------------------\n\n");
}

void exibe_horarios_indisponiveis(Hash* tabela)
{
    printf("-----------------------------------------------\n");
    printf("Quadra 1\tQuadra 2\tQuadra 3\n");
    printf("-----------------------------------------------\n\n");
    int count = 0;
    for (int Horario = 16; Horario <= 22; Horario++)
    {
        count = count + 1;
        for (int quadra = 0; quadra <= 2; quadra++)
        {
            int id = count + 7 * quadra;
            int pos = chaveia(quadra + 1, Horario);
            if ((*tabela)[pos] != NULL)
            {
                printf("[%d] %d:00\t", id, Horario);
            }
            else
            {
                printf("---------\t");
            }
        }

        printf("\n");
    }
    printf("-----------------------------------------------\n\n");
}

void acha_id_disponivel(Hash *tabela, int id_reserva, int *quadra_, int *horario_)
{
    int count = 0;
    
    for (int Horario = 16; Horario <= 22; Horario++)
    {
        count = count + 1;
        for (int quadra = 0; quadra <= 2; quadra++)
        {

            int pos = chaveia(quadra + 1, Horario);

            if ((*tabela)[pos] == NULL)
            {
                int id = count + 7 * quadra;
                if (id == id_reserva)
                {
                    *quadra_ = quadra + 1;
                    *horario_ = Horario;
                    break;
                }
            }
        }
    }
}

void acha_id_indisponivel(Hash *tabela, int id, int *quadra, int *horario)
{
    int count = 0;
    
    for (int Horario = 16; Horario <= 22; Horario++)
    {
        count = count + 1;
        for (int quadra_ = 0; quadra_ <= 2; quadra_++)
        {
            int pos = chaveia(quadra_ + 1, Horario);
            if ((*tabela)[pos] != NULL)
            {
                int id_ = count + 7 * quadra_;
                if (id_ == id)
                {
                    *quadra = quadra_ + 1;
                    *horario = Horario;
                    break;
                }
            }
        }
    }
}

int chaveia(int quadra, int horario)
{
    return (horario - 16) + 7 * (quadra - 1);
}

int insere_reserva(Hash *tabela, Reserva *reserva)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(reserva->data, "%d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    int quadra = reserva->quadra;
    int horario = reserva->horario;
    int pos = chaveia(quadra, horario);
    if ((*tabela)[pos] == NULL)
    {
        (*tabela)[pos] = reserva;
        return 1;
    }
    return 0;
}

int remove_reserva(Hash *tabela, Reserva reserva)
{
    int quadra = reserva.quadra;
    int horario = reserva.horario;
    int pos = chaveia(quadra, horario);
    if ((*tabela)[pos] != NULL)
    {
        (*tabela)[pos] = NULL;
        return 1;
    }
    return 0;
}


Reserva busca_reserva(Hash *tabela, Reserva reserva, int *resultado)
{
    int quadra = reserva.quadra;
    int horario = reserva.horario;
    int pos = chaveia(quadra, horario);
    if ((*tabela)[pos] != NULL)
    {
        *resultado = 1;
        return *(*tabela)[pos];
    }
    *resultado = 0;
}

int edita_reserva(Hash *tabela, Reserva *reserva_antiga, Reserva *reserva_nova)
{
    remove_reserva(tabela, *reserva_antiga);

    return insere_reserva(tabela, reserva_nova);
}

void exibe_informacoes_reserva(Reserva *reserva)
{
    printf("===============================================\n");
    printf("               Informações da Reserva\n");
    printf("===============================================\n\n");
    printf("Nome do cliente: %s\n", reserva->nome);
    printf("Data da reserva: %s\n", reserva->data);
    printf("Quadra:          %d\n", reserva->quadra);
    printf("Horário:         %d:00\n", reserva->horario);
    printf("===============================================\n\n");
}

void tela_adiciona_reserva(Hash *tabela)
{
    limpa_tela();
    printf("===============================================\n");
    printf("               Adicionar Reserva\n");
    printf("===============================================\n\n");

    Reserva *reserva = (Reserva *)malloc(sizeof(Reserva));
    exibe_horarios_disponiveis(tabela);

    int id = 0;
    printf("Digite o ID do horário que deseja reservar: ");
    scanf("%d", &id);
    acha_id_disponivel(tabela, id, &reserva->quadra, &reserva->horario);
    printf("Reservando a Quadra %d às %d:00\n", reserva->quadra, reserva->horario);

    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", reserva->nome);
    
    if (insere_reserva(tabela, reserva))
    {
        printf("Reserva realizada com sucesso!\n");
        pausa_programa();
        limpa_tela();
        exibe_informacoes_reserva(reserva);
        printf("A reserva acima foi cadastrada com sucesso!\n");
        pausa_programa();
    }
    else
    {
        printf("Erro ao realizar reserva!\n");
        free(reserva); 
        pausa_programa();
    }
}

void tela_remove_reserva(Hash *tabela)
{
    limpa_tela(); 
    printf("===============================================\n");
    printf("               Remover Reserva\n");
    printf("===============================================\n\n");

    Reserva *reserva = (Reserva *)malloc(sizeof(Reserva));
    exibe_horarios_indisponiveis(tabela);

    int id = 0;
    printf("Digite o ID do horário que deseja remover: ");
    scanf("%d", &id);
    acha_id_indisponivel(tabela, id, &reserva->quadra, &reserva->horario);
    
    int pos = chaveia(reserva->quadra, reserva->horario);
    reserva = (*tabela)[pos];

    printf("A seguinte reserva será removida:\n");
    exibe_informacoes_reserva(reserva);

    if (remove_reserva(tabela, *reserva))
    {
        printf("Reserva removida com sucesso!\n");
        free(reserva);
        pausa_programa();
        limpa_tela();
    }
    else
    {
        printf("Erro ao remover reserva!\n");
        free(reserva);
        pausa_programa();
    }
}

void tela_busca_reserva(Hash *tabela)
{
    limpa_tela();
    printf("===============================================\n");
    printf("               Buscar Reserva\n");
    printf("===============================================\n\n");

    Reserva *reserva = (Reserva *)malloc(sizeof(Reserva));
    exibe_horarios_indisponiveis(tabela);

    int id = 0;
    printf("Digite o ID do horário que deseja buscar: ");
    scanf("%d", &id);
    acha_id_indisponivel(tabela, id, &reserva->quadra, &reserva->horario);
    int resultado;
    *reserva = busca_reserva(tabela, *reserva, &resultado);

    if (resultado)
    {
        printf("Reserva encontrada!\n");
        exibe_informacoes_reserva(reserva);
        pausa_programa();
        limpa_tela();
    }
    else
    {
        printf("Reserva não encontrada!\n");
        pausa_programa();
    }

}

void tela_edita_reserva(Hash *tabela)
{
    limpa_tela();
    printf("===============================================\n");
    printf("               Editar Reserva\n");
    printf("===============================================\n\n");

    Reserva *reserva_antiga = (Reserva *)malloc(sizeof(Reserva));
    Reserva *reserva_nova = (Reserva *)malloc(sizeof(Reserva));
    exibe_horarios_indisponiveis(tabela);
    
    int id = 0;
    printf("Digite o ID do horário que deseja editar: ");
    scanf("%d", &id);
    acha_id_indisponivel(tabela, id, &reserva_antiga->quadra, &reserva_antiga->horario);
    int pos = chaveia(reserva_antiga->quadra, reserva_antiga->horario);
    *reserva_antiga = *(*tabela)[pos];

    printf("A seguinte reserva será editada:\n");
    exibe_informacoes_reserva(reserva_antiga);

    int opcao;

    printf("Você deseja editar o horário e/ou a quadra?  [1] Sim [2] Não\n");
    scanf("%d", &opcao);

    switch (opcao)
    {
        case(1):
            exibe_horarios_disponiveis(tabela);
            printf("Digite o novo ID do horário que deseja reservar: ");
            scanf("%d", &id);
            acha_id_disponivel(tabela, id, &reserva_nova->quadra, &reserva_nova->horario);
            printf("Reservando a Quadra %d às %d:00\n", reserva_nova->quadra, reserva_nova->horario);
            break;
        case(2):
            reserva_nova->quadra = reserva_antiga->quadra;
            reserva_nova->horario = reserva_antiga->horario;
            break;
        default:
            printf("Opção inválida!\n");
            break;
            exit(1);
    }

    printf("Digite o novo nome do cliente: ");
    scanf(" %[^\n]", reserva_nova->nome);


    if (edita_reserva(tabela, reserva_antiga, reserva_nova))
    {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        sprintf(reserva_nova->data, "%d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
        printf("Reserva editada com sucesso!\n");
        pausa_programa();
        limpa_tela();
        exibe_informacoes_reserva(reserva_nova);
        printf("A reserva acima foi editada com sucesso!\n");
        pausa_programa();
        free(reserva_antiga);
    }
    else
    {
        printf("Erro ao editar reserva!\n");
        free(reserva_antiga);
        free(reserva_nova);
        pausa_programa();
    }

}