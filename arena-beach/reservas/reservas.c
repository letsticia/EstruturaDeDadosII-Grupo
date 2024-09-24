#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "reservas.h"
#define SIZE 21

void inicializa_tabela_hash(Hash tabela){
    for (int count = 0; count < SIZE; count++){
        tabela[count] = NULL;
    }
}

void exibe_horarios_disponiveis(Hash tabela)
{

    printf("-----------------------------------------------\n");
    printf("Quadra 1\tQuadra 2\tQuadra 3\n");
    printf("-----------------------------------------------\n\n");
    int count = 0;
    for (int Horario = 16; Horario <= 22; Horario++){
        count = count + 1;
        for (int quadra = 0; quadra <= 2; quadra++){
            int pos = chaveia(quadra + 1, Horario);
            

            if (tabela[pos] == NULL){
                int id = count + 7 * quadra;
                printf("[%d] ", id);
                printf("%d:00\t", Horario);
            }
            else
            {
                printf("-----   \t");
            }

        }

        printf("\n");
    }
}

void acha_id(Hash tabela, int id_reserva){
    int count = 0;
    for (int Horario = 16; Horario <= 22; Horario++){
        count = count + 1;
        for (int quadra = 0; quadra <= 2; quadra++){

            int pos = chaveia(quadra + 1, Horario);
            printf("%d\n", pos);

            if (tabela[pos] == NULL){
                int id = count + 7 * quadra;
                if (id == id_reserva){
                    printf("Quadra %d - Horário %d:00\n", quadra + 1, Horario);
                }
            }
        }
    }
}

int chaveia(int quadra, int horario){
    int chave = quadra * 24 + horario;
    
    return chave % SIZE;
}

void insere_reserva(Hash tabela, Reserva reserva){
    
    int pos = chaveia(reserva.quadra, atoi(reserva.horario));

    if (tabela[pos] == NULL){
        tabela[pos] = (Reserva *)malloc(sizeof(Reserva));
        *tabela[pos] = reserva;
    }
    else
    {
        printf("Este horário não está disponível. %d\n", pos);
    }
}

void remove_reserva(Hash tabela, Reserva reserva)
{
    int pos = chaveia(reserva.quadra, atoi(reserva.horario));

    if (tabela[pos] != NULL){
        free(tabela[pos]);
        tabela[pos] = NULL;
        printf("Removido com sucesso. %d\n", pos);
    }
    else{
        printf("Este horário não está reservado. %d\n", pos);
    }
}

void edita_reserva(Hash tabela, Reserva reserva)
{

    int pos = chaveia(reserva.quadra, atoi(reserva.horario));

    if (tabela[pos] != NULL){
        *tabela[pos] = reserva;
        printf("Editado com sucesso. %d\n", pos);
    }
    else{
        printf("Este horário não está reservado. %d\n", pos);
    }
}

Reserva busca_reserva(Hash tabela, Reserva reserva){

    int pos = chaveia(reserva.quadra, atoi(reserva.horario));

    if (tabela[pos] != NULL){
        return *tabela[pos];
    }
    else{
        printf("Este horário não está reservado. %d\n", pos);
    }
}

int main(void){
    Hash tabela;
    inicializa_tabela_hash(tabela);
    // linhas de teste
    Reserva reserva = {"João", "10/10/2021", 1, "16"};
    insere_reserva(tabela, reserva);
    Reserva reserva2 = {"Leticia", "10/21/2021", 3 , "20"};
    insere_reserva(tabela, reserva2);
    exibe_horarios_disponiveis(tabela);
    acha_id(tabela, 15);


    return 0;
}