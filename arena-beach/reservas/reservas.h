#ifndef RESERVAS_H
#define RESERVAS_H

#define SIZE 21

typedef struct reserva{
    char nome[50];
    char data[10];
    int quadra;
    char horario[3];
} Reserva;

typedef Reserva *Hash[SIZE];

void inicializa_tabela_hash(Hash tabela);

void exibe_horarios_disponiveis(Hash tabela);

int chaveia (int quadra, int horario);

void insere_reserva(Hash tabela, Reserva reserva);

void remove_reserva(Hash tabela, Reserva reserva);

#endif 