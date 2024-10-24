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
    char id_str[100];
    do{
        printf("Digite o ID do horário que deseja reservar: ");
        scanf(" %99[^\n]", &id_str);
        pausa_programa();
    }while(!numero_inteiroc(id_str));
    id = atoi(id_str);

    if ((*tabela)[id-1] != NULL)
    {
        printf("Horário indisponível!\n");
        free(reserva);
        pausa_programa();
        return;
    }

    acha_id_disponivel(tabela, id, &reserva->quadra, &reserva->horario);
    printf("Reservando a Quadra %d às %d:00\n", reserva->quadra, reserva->horario);


    do {
        printf("\nDigite o nome do cliente (apenas letras): ");
        scanf(" %49[^\n]", reserva->nome);
        getchar();
    } while (!contem_apenas_letras(reserva->nome));

    formata_string(reserva->nome);
    
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
    char id_str[100];
    
    do{
        printf("Digite o ID do horário que deseja remover (apenas números): ");
        scanf(" %99[^\n]", &id_str);
        pausa_programa();
    }while(!numero_inteiroc(id_str));
    id = atoi(id_str);
    acha_id_indisponivel(tabela, id, &reserva->quadra, &reserva->horario);

    if ((*tabela)[id-1] == NULL)
    {
        printf("Nenhuma reserva encontrada!\n");
        free(reserva);
        pausa_programa();
        return;
    }
    
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
    char id_str[100];
    
    do{
        printf("Digite o ID do horário que deseja buscar: ");
        scanf(" %99[^\n]", &id_str);
        pausa_programa();
    }while(!numero_inteiroc(id_str));
    id = atoi(id_str);

    acha_id_indisponivel(tabela, id, &reserva->quadra, &reserva->horario);

    if ((*tabela)[id-1] == NULL)
    {
        printf("Nenhuma reserva encontrada!\n");
        free(reserva);
        pausa_programa();
        return;
    }
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
    char id_str[100];
    
    do{
        printf("Digite o ID do horário que deseja editar: \n");
        scanf(" %99[^\n]", &id_str);
        pausa_programa();
    }while(!numero_inteiroc(id_str));
    id = atoi(id_str);

    acha_id_indisponivel(tabela, id, &reserva_antiga->quadra, &reserva_antiga->horario);

    if ((*tabela)[id-1] == NULL)
    {
        printf("Nenhuma reserva encontrada!\n");
        free(reserva_antiga);
        free(reserva_nova);
        pausa_programa();
        return;
    }
    int pos = chaveia(reserva_antiga->quadra, reserva_antiga->horario);
    *reserva_antiga = *(*tabela)[pos];

    printf("A seguinte reserva será editada:\n");
    exibe_informacoes_reserva(reserva_antiga);

    int opcao;
    char op[100];

    printf("Você deseja editar o horário e/ou a quadra?  [1] Sim [2] Não\n");
    do{
        scanf(" %99[^\n]", &op);
        pausa_programa();
    }while(!numero_inteiroc(op));
    opcao = atoi(op);

    switch (opcao)
    {
        case(1):
            exibe_horarios_disponiveis(tabela);
            printf("Digite o novo ID do horário que deseja reservar: ");
            scanf("%d", &id);
            do{
                scanf(" %99[^\n]", &id_str);
                pausa_programa();
            }while(!numero_inteiroc(id_str));
            id = atoi(id_str);
            acha_id_disponivel(tabela, id, &reserva_nova->quadra, &reserva_nova->horario);
            if ((*tabela)[id-1] != NULL)
            {
                printf("Horário indisponível!\n");
                free(reserva_antiga);
                free(reserva_nova);
                pausa_programa();
                return;
            }
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

    do {
        printf("\nDigite o novo nome do cliente (apenas letras): ");
        scanf(" %49[^\n]", reserva_nova->nome);
        getchar();
    } while (!contem_apenas_letras(reserva_nova->nome));

    formata_string(reserva_nova->nome);



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



Node* cria_novo_no(Reserva* reserva) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->reserva = reserva;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->altura = 1;  
    return novo;
}


int altura(Node* no) {
    if (no == NULL) return 0;
    return no->altura;
}


int fator_balanceamento(Node* no) {
    if (no == NULL) return 0;
    return altura(no->esquerda) - altura(no->direita);
}


Node* rotacao_direita(Node* y) {
    Node* x = y->esquerda;
    Node* T2 = x->direita;
    
    x->direita = y;
    y->esquerda = T2;
    
    y->altura = 1 + (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita));
    x->altura = 1 + (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita));
    
    return x;
}


Node* rotacao_esquerda(Node* x) {
    Node* y = x->direita;
    Node* T2 = y->esquerda;
    
    y->esquerda = x;
    x->direita = T2;
    
    x->altura = 1 + (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita));
    y->altura = 1 + (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita));
    
    return y;
}


Node* insere_no(Node* node, Reserva* reserva) {
    if (node == NULL)
        return cria_novo_no(reserva);

 
    if (reserva->horario < node->reserva->horario) {
        node->esquerda = insere_no(node->esquerda, reserva);
    } else if (reserva->horario > node->reserva->horario) {
        node->direita = insere_no(node->direita, reserva);
    } else {
       
        if (reserva->quadra < node->reserva->quadra) {
            node->esquerda = insere_no(node->esquerda, reserva);
        } else if (reserva->quadra > node->reserva->quadra) {
            node->direita = insere_no(node->direita, reserva);
        } else {
            
            return node;  
        }
    }


    node->altura = 1 + (altura(node->esquerda) > altura(node->direita) ? altura(node->esquerda) : altura(node->direita));

 
    int balance = fator_balanceamento(node);


    if (balance > 1 && reserva->horario < node->esquerda->reserva->horario) {
        return rotacao_direita(node);
    }

    if (balance < -1 && reserva->horario > node->direita->reserva->horario) {
        return rotacao_esquerda(node);
    }

    if (balance > 1 && reserva->horario > node->esquerda->reserva->horario) {
        node->esquerda = rotacao_esquerda(node->esquerda);
        return rotacao_direita(node);
    }

    if (balance < -1 && reserva->horario < node->direita->reserva->horario) {
        node->direita = rotacao_direita(node->direita);
        return rotacao_esquerda(node);
    }

    return node;
}


Node* carrega_avl_dia_atual(Node* raiz_avl, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return NULL;
    }

    char linha[256];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char data_atual[11]; 
    sprintf(data_atual, "%d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    while (fgets(linha, sizeof(linha), arquivo)) {
        Reserva* reserva = (Reserva*)malloc(sizeof(Reserva));
      
        sscanf(linha, "Cliente: %[^,], Data: %[^,], Quadra: %d, Horário: %d",
               reserva->nome, reserva->data, &reserva->quadra, &reserva->horario);

     
        if (strcmp(reserva->data, data_atual) == 0) {
           
            raiz_avl = insere_no(raiz_avl, reserva);
        } else {
            free(reserva);  
        }
    }

    fclose(arquivo);
    return raiz_avl;
}

void transfere_avl_para_hash(Node* raiz_avl, Hash* tabela) {
    if (raiz_avl != NULL) {
        transfere_avl_para_hash(raiz_avl->esquerda, tabela);
        

        insere_reserva(tabela, raiz_avl->reserva);  

        transfere_avl_para_hash(raiz_avl->direita, tabela);
    }
}

void salva_historico(Node* raiz_avl, FILE* arquivo) {
    if (raiz_avl != NULL) {
        salva_historico(raiz_avl->esquerda, arquivo);

        fprintf(arquivo, "Cliente: %s, Data: %s, Quadra: %d, Horário: %d\n",
                raiz_avl->reserva->nome, raiz_avl->reserva->data, raiz_avl->reserva->quadra, raiz_avl->reserva->horario);

        salva_historico(raiz_avl->direita, arquivo);
    }
}

void salva_historico_atualizado(Node* raiz_avl, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }

    char** linhas_anteriores = NULL;
    int total_linhas = 0;
    char linha[256];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char data_atual[11];  
    sprintf(data_atual, "%d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

  
    while (fgets(linha, sizeof(linha), arquivo)) {
        char data_reserva[11];
        sscanf(linha, "%*[^,], Data: %[^,], %*s", data_reserva);
        if (strcmp(data_reserva, data_atual) != 0) {
            linhas_anteriores = realloc(linhas_anteriores, (total_linhas + 1) * sizeof(char*));
            linhas_anteriores[total_linhas] = strdup(linha);
            total_linhas++;
        }
    }
    fclose(arquivo);

    arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }

    for (int i = 0; i < total_linhas; i++) {
        fputs(linhas_anteriores[i], arquivo);
        free(linhas_anteriores[i]);
    }
    free(linhas_anteriores);

    salva_historico(raiz_avl, arquivo);

    fclose(arquivo);
}


Node* transfere_para_avl(Hash* tabela, Node* raiz) {
    for (int i = 0; i < SIZE; i++) {
        if ((*tabela)[i] != NULL) {
            raiz = insere_no(raiz, (*tabela)[i]);
        }
    }
    return raiz;
}


void libera_avl(Node* raiz) {
    if (raiz != NULL) {
        libera_avl(raiz->esquerda);
        libera_avl(raiz->direita);
        free(raiz);
    }
}


NoBinario* insere_no_binario(NoBinario* raiz, Reserva* reserva) {
    if (raiz == NULL) {
        NoBinario* novo_no = (NoBinario*)malloc(sizeof(NoBinario));
        novo_no->reserva = reserva;
        novo_no->esquerda = NULL;
        novo_no->direita = NULL;
        return novo_no;
    }

    if (reserva->horario < raiz->reserva->horario) {
        raiz->esquerda = insere_no_binario(raiz->esquerda, reserva);
    } else if (reserva->horario > raiz->reserva->horario) {
        raiz->direita = insere_no_binario(raiz->direita, reserva);
    } else {
        if (reserva->quadra < raiz->reserva->quadra) {
            raiz->esquerda = insere_no_binario(raiz->esquerda, reserva);
        } else {
            raiz->direita = insere_no_binario(raiz->direita, reserva);
        }
    }

    return raiz;
}

NoBinario* carrega_reservas_anteriores_binario(NoBinario* raiz, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return raiz;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        Reserva* reserva = (Reserva*)malloc(sizeof(Reserva));
        

        int campos_lidos = sscanf(linha, "Cliente: %49[^,], Data: %10[^,], Quadra: %d, Horário: %d",
                                  reserva->nome, reserva->data, &reserva->quadra, &reserva->horario);
        
        
        if (campos_lidos == 4) {
            
            raiz = insere_no_binario(raiz, reserva);
            printf("Reserva carregada: Nome: %s, Data: %s, Quadra: %d, Horário: %d\n",
                   reserva->nome, reserva->data, reserva->quadra, reserva->horario);
        } else {
            printf("Erro ao ler linha: %s\n", linha);
            free(reserva); 
        }
    }

    fclose(arquivo);
    return raiz;
}


void busca_por_horario(NoBinario* raiz, int horario) {
    if (raiz == NULL) {
        return;
    }

    busca_por_horario(raiz->esquerda, horario);

    if (raiz->reserva->horario == horario) {
        printf("Reserva carregada: Nome: %s, Data: %s, Quadra: %d, Horário: %d\n",
               raiz->reserva->nome, raiz->reserva->data, raiz->reserva->quadra, raiz->reserva->horario);
    }

    busca_por_horario(raiz->direita, horario);
}



void tela_busca_por_horario(NoBinario* raiz){
    limpa_tela();
    printf("===============================================\n");
    printf("          Busca Historico de Reservas\n");
    printf("===============================================\n\n");

    int id = 0;
    char id_str[100];
    
    do{
        printf("Digite o horário que deseja pesquisar (apenas números): ");
        scanf(" %99[^\n]", &id_str);
        pausa_programa();
    }while(!numero_inteiroc(id_str));
    id = atoi(id_str);

    printf("Buscando reservas para o horário %d:\n", id);

    busca_por_horario(raiz, id);

}


int numero_inteiroc(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

int contem_apenas_letras(char *str) {
    for (int index = 0; str[index] != '\0'; index++) {
        if (!isalpha(str[index]) && str[index] != ' ') {
            printf("\nEsse campo deve conter apenas letras. Por favor, digite um nome válido\n");
            return 0;
        }
    }
    return 1;
}

void formata_string(char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (i==0){
            str[0] = toupper(str[0]);
        }
        else{
            if (str[i - 1] == ' ') {
                str[i] = toupper(str[i]);
            } 
            else {
                str[i] = tolower(str[i]);
            }
        }
    }
}