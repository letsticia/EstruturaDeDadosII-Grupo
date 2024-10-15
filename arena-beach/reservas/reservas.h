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
int edita_reserva(Hash *tabela, Reserva *reserva_antiga, Reserva *reserva_nova);

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

/**
 * Exibe a tela de busca de reserva.
 * @param tabela A tabela hash contendo as reservas.
 */
void tela_busca_reserva(Hash *tabela);

/**
 * Exibe a tela de edição de reserva.
 * @param tabela A tabela hash contendo as reservas.
 */
void tela_edita_reserva(Hash *tabela);


typedef struct Node {
    Reserva* reserva;
    struct Node* esquerda;
    struct Node* direita;
    int altura;
} Node;


// Estrutura da tabela hash
typedef Reserva* Hash[SIZE];

// Funções relacionadas à árvore AVL
Node* cria_novo_no(Reserva* reserva);
int altura(Node* no);
int fator_balanceamento(Node* no);
Node* rotacao_direita(Node* y);
Node* rotacao_esquerda(Node* x);
Node* insere_no(Node* node, Reserva* reserva);
Node* carrega_avl_dia_atual(Node* raiz_avl, const char* nome_arquivo);
void transfere_avl_para_hash(Node* raiz_avl, Hash* tabela);
void salva_historico(Node* raiz_avl, FILE* arquivo);
void salva_historico_atualizado(Node* raiz_avl, const char* nome_arquivo);
Node* transfere_para_avl(Hash* tabela, Node* raiz);
void libera_avl(Node* raiz);




typedef struct NoBinario {
    Reserva* reserva;
    struct NoBinario* esquerda;
    struct NoBinario* direita;
} NoBinario;

// Função para inserir uma nova reserva na árvore binária
NoBinario* insere_no_binario(NoBinario* raiz, Reserva* reserva);

// Função para carregar reservas de um arquivo de texto para a árvore binária
NoBinario* carrega_reservas_anteriores_binario(NoBinario* raiz, const char* nome_arquivo);

// Função para buscar e exibir reservas para um determinado horário
void busca_por_horario(NoBinario* raiz, int horario);

// Função para exibir uma tela de busca por horário e realizar a pesquisa
void tela_busca_por_horario(NoBinario* raiz);



#endif // RESERVAS_H