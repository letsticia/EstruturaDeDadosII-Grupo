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
void inicializa_tabela_hash(Hash* tabela);

/**
 * Exibe os horários disponíveis.
 * @param tabela A tabela hash contendo as reservas.
 */
void exibe_horarios_disponiveis(Hash* tabela);

/**
 * Encontra a quadra e o horário correspondentes a um ID de reserva disponível.
 * @param tabela A tabela hash contendo as reservas.
 * @param id_reserva O ID da reserva.
 * @param quadra_ O endereço de uma variável para armazenar a quadra encontrada.
 * @param horario_ O endereço de uma variável para armazenar o horário encontrado.
 */
void acha_id_disponivel(Hash *tabela, int id_reserva, int *quadra_, int *horario_);

/**
 * Encontra a quadra e o horário correspondentes a um ID de reserva indisponível.
 * @param tabela A tabela hash contendo as reservas.
 * @param id O ID da reserva.
 * @param quadra O endereço de uma variável para armazenar a quadra encontrada.
 * @param horario O endereço de uma variável para armazenar o horário encontrado.
 */
void acha_id_indisponivel(Hash *tabela, int id, int *quadra, int *horario);

/**
 * Calcula a chave hash para uma quadra e horário.
 * @param quadra A quadra.
 * @param horario O horário.
 * @return A chave hash.
 */
int chaveia(int quadra, int horario);

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
 * @return 1 se a reserva foi removida com sucesso, 0 caso contrário.
 */
int remove_reserva(Hash *tabela, Reserva reserva);

/**
 * Busca uma reserva na tabela hash.
 * @param tabela A tabela hash.
 * @param reserva A reserva a ser buscada.
 * @param resultado O endereço de uma variável para armazenar o resultado da busca.
 * @return A reserva encontrada.
 */
Reserva busca_reserva(Hash *tabela, Reserva reserva, int *resultado);

/**
 * Edita uma reserva na tabela hash.
 * @param tabela A tabela hash.
 * @param reserva_antiga A reserva antiga a ser substituída.
 * @param reserva_nova A nova reserva a ser inserida.
 * @return 1 se a reserva foi editada com sucesso, 0 caso contrário.
 */
int edita_reserva(Hash *tabela, Reserva reserva_antiga, Reserva reserva_nova);

/**
 * Exibe as informações de uma reserva.
 * @param reserva A reserva.
 */
void exibe_informacoes_reserva(Reserva *reserva);

/**
 * Exibe a tela de adição de reserva.
 * @param tabela A tabela hash contendo as reservas.
 */
void tela_adiciona_reserva(Hash *tabela);

/**
 * Exibe a tela de remoção de reserva.
 * @param tabela A tabela hash contendo as reservas.
 */
void tela_remove_reserva(Hash *tabela);

#endif // RESERVAS_H