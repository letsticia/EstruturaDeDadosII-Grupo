#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "reservas.h"
#define SIZE 21


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

void exibe_informacoes_reserva(Reserva reserva)
{
    printf("Nome:   \t%s\n", reserva.nome);
    printf("Data:   \t%s\n", reserva.data);
    printf("Quadra: \t%d\n", reserva.quadra);
    printf("Horário:\t%d\n", reserva.horario);
}



// int main(void){

//     system("chcp 65001");
//     Hash tabela;

//     inicializa_tabela_hash(&tabela);

//     insere_reserva(&tabela, &(Reserva){"João", "10/10/2021", 1, 16});

//     exibe_horarios_disponiveis(&tabela);

//     int pos = chaveia(1, 16);
//     printf("Reserva na posição %d:\n", pos);
//     exibe_informacoes_reserva(*tabela[pos]);

// }