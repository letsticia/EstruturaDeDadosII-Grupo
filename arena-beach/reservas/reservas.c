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
    printf("-----------------------------------------------\n\n");
}

void acha_id(Hash tabela, int id_reserva, int* quadra_, int* horario_){
    int count = 0;
    int quadra_horario[2];
    for (int Horario = 16; Horario <= 22; Horario++){
        count = count + 1;
        for (int quadra = 0; quadra <= 2; quadra++){

            int pos = chaveia(quadra + 1, Horario);

            if (tabela[pos] == NULL){
                int id = count + 7 * quadra;
                if (id == id_reserva){
                    *quadra_ = quadra + 1;
                    *horario_ = Horario;
                    break;
                }
            }
        }
    }
}

int chaveia(int quadra, int horario){
    char str_quadra[10];
    char str_horario[10];

    sprintf(str_quadra, "%d", quadra);
    sprintf(str_horario, "%d", horario);

    char str_concatenado[20];
    strcpy(str_concatenado, str_quadra);
    strcat(str_concatenado, str_horario);

    int chave = atoi(str_concatenado); 

    return chave % SIZE;
}

void exibe_informacoes_reserva(Reserva reserva){
    printf("Nome:   \t%s\n", reserva.nome);
    printf("Data:   \t%s\n", reserva.data);
    printf("Quadra: \t%d\n", reserva.quadra);
    printf("Horário:\t%s\n", reserva.horario);
}

void insere_reserva(Hash tabela, Reserva reserva){

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char data[11];
    sprintf(data, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    strcpy(reserva.data, data);
    
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

void remove_reserva(Hash tabela, Reserva reserva){
    int pos = chaveia(reserva.quadra, atoi(reserva.horario));

    if (tabela[pos] != NULL){
        free(tabela[pos]);
        tabela[pos] = NULL;
    }
    else{
        printf("Este horário não está reservado. %d\n", pos);
    }
}

Reserva busca_reserva(Hash tabela, Reserva reserva, int * resultado){

    int pos = chaveia(reserva.quadra, atoi(reserva.horario));

    if (tabela[pos] != NULL){
        *resultado = 1;
        return *tabela[pos];
    }
    else{
        *resultado = 0;
        printf("Este horário não está reservado.\n");
    }
}

void exibe_reservas(Hash tabela){
    for (int count = 0; count < SIZE; count++){
        if (tabela[count] != NULL){
            exibe_informacoes_reserva(*tabela[count]);
            printf("\n");
        }
    }
}

void tela_adicionar_reservas(Hash tabela){
    Reserva reserva;
    printf("=============================================\n");
    printf("=           Adicionar Reserva               =\n");
    printf("=============================================\n\n");

    exibe_horarios_disponiveis(tabela);

    printf("Digite o ID do horário desejado: ");
    int id;
    scanf("%d", &id);

    int horario_int = atoi(reserva.horario);
    acha_id(tabela, id, &reserva.quadra, &horario_int);

    printf("Digite o nome do cliente: ");
    scanf("%s", reserva.nome);

    insere_reserva(tabela, reserva);

    printf("Reserva adicionada com sucesso! Informações:\n");
    exibe_informacoes_reserva(reserva);

}

void tela_busca_reserva(Hash tabela){
    Reserva reserva;
    printf("=============================================\n");
    printf("=           Buscar Reserva                  =\n");
    printf("=============================================\n\n");

    printf("Digite a quadra: ");
    scanf("%d", &reserva.quadra);

    printf("Digite o horário: ");
    scanf("%s", reserva.horario);
    int resultado = 0;
    Reserva busca = busca_reserva(tabela, reserva, &resultado);
    if (resultado == 1){
        printf("\n-------------Reserva Encontrada--------------\n");
        exibe_informacoes_reserva(busca);
        printf("----------------------------------------------\n");
        printf("\n");
    }

}

void tela_remove_reserva(Hash tabela){
    Reserva reserva;
    printf("=============================================\n");
    printf("=           Remover Reserva                  =\n");
    printf("=============================================\n\n");

    printf("Digite a quadra: ");
    scanf("%d", &reserva.quadra);

    printf("Digite o horário: ");
    scanf("%s", reserva.horario);
    int resultado = 0;
    Reserva reserva_busca = busca_reserva(tabela, reserva, &resultado);
    
    if (resultado == 1){
        
        printf("A seguinte reserva será removida:\n");
        exibe_informacoes_reserva(reserva_busca);

        remove_reserva(tabela, reserva_busca);
        printf("Reserva removida com sucesso!\n");
    }

}

void tela_edita_reserva(Hash tabela){
    Reserva reserva;
    printf("=============================================\n");
    printf("=           Editar Reserva                   =\n");
    printf("=============================================\n\n");

    printf("Digite a quadra da reserva a ser editada: ");
    scanf("%d", &reserva.quadra);

    printf("Digite o horário da reserva a ser editada: ");
    scanf("%s", reserva.horario);
    int resultado = 0;

    Reserva reserva_busca = busca_reserva(tabela, reserva, &resultado);
    
    if (resultado == 1){
        
        printf("A seguinte reserva será editada:\n");
        exibe_informacoes_reserva(reserva_busca);
        remove_reserva(tabela, reserva_busca);

        printf("Digite o nome do cliente: ");
        scanf("%s", reserva.nome);

        printf("Digite a nova quadra: ");
        scanf("%d", &reserva.quadra);

        printf("Digite o novo horário: ");
        scanf("%s", reserva.horario);

        insere_reserva(tabela, reserva);
    }

}

int main(void){
    Hash tabela;
    system("chcp 65001");
    inicializa_tabela_hash(tabela);
 
    // linhas de teste
    Reserva reserva = {"João", "", 1, "16"};
 
    insere_reserva(tabela, reserva);

    Reserva reserva2 = {"Leticia", "", 3 , "20"};
    insere_reserva(tabela, reserva2);
   
    
    // exibe_horarios_disponiveis(tabela);
    // acha_id(tabela, 15);
    // tela_edita_reserva(tabela);
    // exibe_reservas(tabela);
    // tela_busca_reserva(tabela);
    // tela_adicionar_reservas(tabela);
    exibe_horarios_disponiveis(tabela);

    return 0;
}