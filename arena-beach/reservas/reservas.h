#ifndef RESERVAS_H
#define RESERVAS_H

#define SIZE 21

typedef struct reserva{
    char nome[50];
    char data[11];
    int quadra;
    int horario;
} Reserva;

typedef Reserva *Hash[SIZE];

/**
 * Inicializa a tabela hash.
 * @param tabela A tabela hash a ser inicializada.
 */
void inicializa_tabela_hash(Hash *tabela);

/**
 * Exibe os horários disponíveis.
 * @param tabela A tabela hash contendo as reservas.
 */
void exibe_horarios_disponiveis(Hash * tabela);

/**
 * Encontra a quadra e o horário correspondentes a um ID de reserva.
 * @param tabela A tabela hash contendo as reservas.
 * @param id_reserva O ID da reserva.
 * @param quadra_ O endereço de uma variável para armazenar a quadra encontrada.
 * @param horario_ O endereço de uma variável para armazenar o horário encontrado.
 */
void acha_id(Hash *tabela, int id_reserva, int* quadra_, int* horario_);

/**
 * Calcula a chave hash para uma quadra e horário.
 * @param quadra A quadra.
 * @param horario O horário.
 * @return A chave hash.
 */
int chaveia(int quadra, int horario);

/**
 * Exibe as informações de uma reserva.
 * @param reserva A reserva.
 */
void exibe_informacoes_reserva(Reserva reserva);

/**
 * Insere uma reserva na tabela hash.
 * @param tabela A tabela hash.
 * @param reserva A reserva a ser inserida.
 * @return 1 se a reserva foi inserida com sucesso, 0 caso contrário.
 */
int insere_reserva(Hash *tabela, Reserva *reserva);

/**
 * Remove uma reserva da tabela hash.
 * @param tabela A tabela hash.
 * @param reserva A reserva a ser removida.
 */
void remove_reserva(Hash tabela, Reserva reserva);

/**
 * Busca uma reserva na tabela hash.
 * @param tabela A tabela hash.
 * @param reserva A reserva a ser buscada.
 * @param resultado O endereço de uma variável para armazenar o resultado da busca.
 * @return A reserva encontrada.
 */
Reserva busca_reserva(Hash tabela, Reserva reserva, int * resultado);

/**
 * Exibe todas as reservas na tabela hash.
 * @param tabela A tabela hash.
 */
void exibe_reservas(Hash tabela);

#endif // RESERVAS_H