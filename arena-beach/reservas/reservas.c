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

void acha_id(Hash *tabela, int id_reserva, int *quadra_, int *horario_)
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
        printf("na função é %s\n", (*tabela)[pos]->nome);
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

int edita_reserva(Hash *tabela, Reserva reserva_antiga, Reserva reserva_nova)
{
    int quadra = reserva_antiga.quadra;
    int horario = reserva_antiga.horario;
    int pos = chaveia(quadra, horario);
    if ((*tabela)[pos] != NULL)
    {
        (*tabela)[pos] = &reserva_nova;
        return 1;
    }
    return 0;
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
    acha_id(tabela, id, &reserva->quadra, &reserva->horario);
    printf("Reservando a Quadra %d às %d:00\n", reserva->quadra, reserva->horario);

    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", reserva->nome);
    
    if (insere_reserva(tabela, reserva))
    {
        printf("Reserva realizada com sucesso!\n");
        pausa_programa();
        limpa_tela();
        exibe_informacoes_reserva(reserva);
    }
    else
    {
        printf("Erro ao realizar reserva!\n");
        free(reserva); // Se a reserva não pôde ser inserida, libere a memória
        pausa_programa();
    }
}



// int main(void){

//     system("chcp 65001");
//     Hash tabela;

//     inicializa_tabela_hash(&tabela);

//     tela_adiciona_reserva(&tabela);

//     exibe_horarios_disponiveis(&tabela);
//     int pos = chaveia(1, 16);
//     printf("Reserva na posição %d:\n", pos);
    
//     exibe_informacoes_reserva(tabela[pos]);

// }