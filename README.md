# EstruturaDeDadosII-Grupo

Esse repositório refere-se ao trabalho da disciplina de Estrutura de Dados II, ministrada pelo professor Dr. Kennedy Lopes, no curso de Tecnologia da Informação da Universidade Federal Rural do Semi-Árido (UFERSA). Para este projeto, foi decidido que o grupo irá desenvolver um sistema de gerenciamento de uma arena de esportes de praia, que será chamado de Arena Beach (nome fictício). Dessa forma, este sistema terá como objetivo principal o agendamento de horários para uso das quadras, de modo que possa ser feito o controle de disponibilidade e reserva das mesmas.

## 1. Funcionalidades

O sistema Arena Beach terá as seguintes funcionalidades:

| Funcionalidade           | Características                                                                                              |
|--------------------------|-------------------------------------------------------------------------------------------------------------|
| Histórico de reservas   | Armazena o histórico de reservas realizadas, contendo informações como data, horário, quadra, cliente e status. |
| Controle de disponibilidade | Permite o controle de disponibilidade das quadras, evitando reservas duplicadas no mesmo horário e quadra. |
| Adicionar reserva       | Exibe uma tabela com horários disponíveis para reserva, permite ao usuário selecionar um horário e quadra, solicita informações do cliente para confirmar a reserva. |
| Remover reserva         | Permite que o usuário remova uma reserva existente, informando o horário e a quadra da reserva. |
| Editar reserva          | Permite que o usuário edite uma reserva existente, informando o horário e a quadra da reserva. |
| Exibir reserva disponíveis         | Permite que o usuário busque por horários disponíveis|
| Buscar reserva         | Permite que o usuário busque por uma reserva específica, informando o horário e a quadra da reserva. |

## 2. Como o sistema funciona?

O usuário terá acesso a uma interface (no terminal) onde poderá visualizar as funcionalidades disponíveis e interagir com o sistema. Para isso, o usuário poderá utilizar o teclado para navegar entre as opções e realizar as ações desejadas. 

### 2.1 Estrutura de pastas


```
📁ESTRUTURADEDADOSII-GRUPO
    │
    ├── arena_beach
    │   ├── reservas
    │   │   ├── historico.txt
    │   │   ├── reservas.c
    │   │   └── reservas.h
    │   └──  main.c
    └── ...   

```

- **reservas.c**: arquivo que contém a implementação das funções relacionadas às reservas.
- **reservas.h**: arquivo que contém a declaração das funções relacionadas às reservas.
- **historico.txt**: arquivo que armazena o histórico de reservas realizadas.
- **main.c**: arquivo que contém a função principal do sistema.

### 2.2 Estrutura de dados


#### • Hash

O sistema Arena Beach utiliza, no momento, a Tabela Hash para armazenar as reservas realizadas para o dia atual. A tabela hash é uma estrutura de dados que permite o armazenamento de dados de forma eficiente, permitindo a busca, inserção e remoção de elementos em tempo constante (no caso médio). Dessa forma, a quadra e o horário da reserva são utilizados como chave para a tabela hash, utilizando o método de divisão para calcular o índice da tabela. 

### 3. Participantes

<table align="center">
  <tr>    
    <td align="center">
      <a href="https://github.com/letsticia">
        <img src="https://avatars.githubusercontent.com/u/126128839?v=4" 
        width="120px;" alt="Foto de Letícia Gonçalves no GitHub"/><br>
        <sub>
          <br>Letícia Gonçalves</br>
          <b>Git Hub</b>
         </sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/hillaryds">
        <img src="https://avatars.githubusercontent.com/u/143619299?v=4" 
        width="120px;" alt="Foto de Hillary Diniz no GitHub"/><br>
        <sub>
          <br>Hillary Diniz</br>
          <b>Testadora</b>
         </sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/claraleal12">
        <img src="https://avatars.githubusercontent.com/u/147611128?v=4" 
        width="120px;" alt="Foto de Clara Leal no GitHub"/><br>
        <sub>
          <br>Clara Leal</br>
          <b>Redatora</b>
         </sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/shamyracarvalhoo">
        <img src="https://avatars.githubusercontent.com/u/147446284?v=4" 
        width="120px;" alt="Foto de Shamyra Carvalho no GitHub"/><br>
        <sub>
          <br>Shamyra Carvalho</br>
          <b>Codificadora</b>
         </sub>
      </a>
    </td>
    
    
  </tr>
</table>

