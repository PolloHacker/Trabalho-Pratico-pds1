# Testes e erros

## Sumário

- [Testes e erros](#testes-e-erros)
  - [Sumário](#sumário)
  - [Testes](#testes)
    - [Main.c](#mainc)
      - [main](#main)
      - [inicia\_Jogo](#inicia_jogo)
    - [File\_utils.c](#file_utilsc)
      - [cria\_log](#cria_log)
      - [verifica\_arquivo](#verifica_arquivo)
      - [grava\_arquivo](#grava_arquivo)
      - [le\_arquivo](#le_arquivo)
      - [divide\_linha](#divide_linha)
    - [Pok\_utils.c](#pok_utilsc)
      - [classifica\_pokemon](#classifica_pokemon)
      - [cria\_jogadores](#cria_jogadores)
      - [mais\_forte](#mais_forte)
      - [mais\_fraco](#mais_fraco)
      - [ataca](#ataca)
      - [checa\_sobreviventes](#checa_sobreviventes)
      - [checa\_derrotados](#checa_derrotados)
  - [Erros encontrados](#erros-encontrados)
    - [Segmentation fault](#segmentation-fault)
    - [Erro de tipagem de pokemons](#erro-de-tipagem-de-pokemons)
  - [Código de erros](#código-de-erros)
    - [Erros de arquivos](#erros-de-arquivos)
      - [Erro 1.1: Abertura de um arquivo inexistente](#erro-11-abertura-de-um-arquivo-inexistente)
      - [Erro 1.2: Abertura inválida de um arquivo para gravação](#erro-12-abertura-inválida-de-um-arquivo-para-gravação)
      - [Erro 1.3: Nome de arquivo inválido](#erro-13-nome-de-arquivo-inválido)
      - [Erro 1.4: Arquivo vazio](#erro-14-arquivo-vazio)
      - [Erro 1.5: Erro de escrita](#erro-15-erro-de-escrita)
    - [Erros de ponteiro e memória](#erros-de-ponteiro-e-memória)
      - [Erro 2.1: Erro de alocação de memória](#erro-21-erro-de-alocação-de-memória)
      - [Erro 2.2: Passagem de array de jogadores nulo](#erro-22-passagem-de-array-de-jogadores-nulo)
      - [Erro 2.3: Passagem de array de jogadores vazio](#erro-23-passagem-de-array-de-jogadores-vazio)
    - [Erros de dados](#erros-de-dados)
      - [Erro 3.1: Número de pokemons negativo ou nulo](#erro-31-número-de-pokemons-negativo-ou-nulo)
      - [Erro 3.2: Número de pokemon atual maior do que o total](#erro-32-número-de-pokemon-atual-maior-do-que-o-total)
      - [Erro 3.3: Atributos de pokemon inválidos](#erro-33-atributos-de-pokemon-inválidos)
      - [Erro 3.4: Índice de atacante inválido](#erro-34-índice-de-atacante-inválido)

## Testes

A testagem do programa foi feita usando os casos de teste fornecidos junto ao enunciado. Os mesmos se encontram na pasta `src/input`.

Além desses testes, todas as funções foram testadas individualmente, de modo a garantir uma execução plena.

### Main.c

#### main

- Testar se a função funciona sem argumentos da linha de comando ✅
- Testar se a função funciona com argumentos inválidos ✅
- Testar se a função funciona com argumentos da linha de comando ✅

#### inicia_Jogo

- Testar se a função funciona com um ponteiro nulo ✅
- Testar se a função funciona com um array vazio ✅
- Testar se a função funciona com um array preenchido ✅

### File_utils.c

#### cria_log

- Testar se a função consegue criar o arquivo de log ✅

#### verifica_arquivo

- Testar se a função funciona com um arquivo inexistente ✅
- Testar se a função funciona com um nome de arquivo vazio ou nulo ✅
- Testar se a função funciona com um arquivo existente ✅

#### grava_arquivo

- Testar se a função funciona com dados vazios ou nulos ✅
- Testar se a função funciona com nome de arquivo inválido ✅
- Testar se a função consegue contornar possíveis erros de escrita ✅

#### le_arquivo

- Testar se a função lê corretamente um arquivo ✅
- Testar se a função funciona com um arquivo vazio ou inexistente ✅
- Testar se a função funciona com um nome de arquivo nulo ou vazio ✅

#### divide_linha

- Testar se a função divide corretamente uma linha com múltiplas palavras ✅
- Testar se a função divide corretamente uma linha com apenas uma palavra ✅
- Testar se a função funciona com uma linha vazia ou nula ✅

### Pok_utils.c

#### classifica_pokemon

- Testar a função com um tipo nulo ou vazio ✅
- Testar a função com um tipo inválido ✅
- Testar a função com um tipo válido ✅

#### cria_jogadores

- Testar a função com dados vazios ou nulos ✅
- Testar a função com dados inválidos ✅
- Testar a função com dados válidos ✅

#### mais_forte

- Testar a função quando o atacante é mais forte ✅
- Testar a função quando o defensor é mais forte ✅
- Testar a função quando ambos possuem a mesma força ✅
  
#### mais_fraco

- Testar a função quando o atacante é mais forte ✅
- Testar a função quando o defensor é mais forte ✅
- Testar a função quando ambos possuem a mesma força ✅

#### ataca

- Testar a função com array nulo ✅
- Testar a função com um índice de atacante inválido ✅
- Testar a função com dados válidos ✅
  
#### checa_sobreviventes

- Testar a função com array nulo ✅
- Testar a função com um índice de vencedor inválido ✅
- Testar a função com dados válidos ✅

#### checa_derrotados

- Testar a função com array nulo ✅
- Testar a função com dados válidos ✅

## Erros encontrados

### Segmentation fault

**Descrição:** É um erro **muito** comum quando se trabalha com alocação dinâmica e ponteiros. Ocorre quando o programa:

- Tenta alocar memória indisponível
- Tenta acessar um endereço inválido

**Correção:** Verificar as operações de alocação, liberação e manipulação de memória.

```C
    char * s1;
    int tam;
    scanf("%d", &tam);
    s1 = (char *) malloc(tam * sizeof(char));
    // verificação
    if (s1 == NULL) {
        printf("Erro ao alocar memória\n");
        return;
    }
    // alguma operação

    // liberar memória
    free(s1);
```

### Erro de tipagem de pokemons

**Descrição:** Foi um erro oriundo da ordem em que as operações foram realizadas ao criar e definir os parâmetros de cada pokemon.

```C
char ** palavras = divide_linha(line);
// Definimos o número do pokemon que estamos criando.
j = j >= jogadores[player].num_poks ? 0 : j;
// Definimos o jogador que estamos criando.
player = i <= jogadores[0].num_poks ? 0 : 1;       

jogadores[player].poks[j].nome = malloc(strlen(palavras[0]) + 1);
jogadores[player].poks[j].tipo = malloc(strlen(palavras[4]) + 1);

/*
* Em vez de usar "palavras[4]", que seria o campo com o tipo, 
* usei o campo tipo da struct pokemon, que ainda não havia sido inicializada.
*
* jogadores[player].poks[j].tipo_int = classifica_pokemon(jogadores[player].poks[j].tipo);
*/

jogadores[player].poks[j].tipo_int = classifica_pokemon(palavras[4]);

strcpy(jogadores[player].poks[j].nome, palavras[0]);

jogadores[player].poks[j].atk = atof(palavras[1]);
jogadores[player].poks[j].def = atof(palavras[2]);
jogadores[player].poks[j].hp = atof(palavras[3]);

strcpy(jogadores[player].poks[j].tipo, palavras[4]);
```

**Correção:** Bastou substituir `jogadores[player].poks[j].tipo` por `palavras[4]`.

## Código de erros

### Erros de arquivos

#### Erro 1.1: Abertura de um arquivo inexistente

- **Descrição:** Este erro ocorre quando o programa tenta abrir um arquivo que não existe.

- **Motivo:** Pode ocorrer, por exemplo, quando o usuário especifica um arquivo que não existe, ou quando o programa tenta abrir um arquivo que não pode acessar.

- **Saída:** Arquivo `nome_arq` inexistente.

- **Código de retorno:** 11

#### Erro 1.2: Abertura inválida de um arquivo para gravação

- **Descrição:** Este erro ocorre quando o programa tenta abrir um arquivo que não pode ser aberto.

- **Motivo:** Pode ocorrer, por exemplo, quando o usuário especifica um arquivo que não pode ser aberto, ou qválida ou insuficiente

- **Saída:** Erro ao abrir arquivo `nome_arq`.

- **Código de retorno:** 12

#### Erro 1.3: Nome de arquivo inválido

- **Descrição:** Este erro ocorre quando o programa tenta abrir um arquivo que não pode ser aberto.

- **Motivo:** Pode ocorrer, por exemplo, quando o usuário especifica um arquivo que não pode ser aberto, ou qválida ou insuficiente

- **Saída:** Nome de arquivo inválido (vazio ou nulo).

- **Código de retorno:** 13

#### Erro 1.4: Arquivo vazio

- **Descrição:** Este erro ocorre quando o programa tenta abrir um arquivo que não pode ser aberto.

- **Motivo:** Pode ocorrer, por exemplo, quando o usuário especifica um arquivo que não pode ser aberto, ou qválida ou insuficiente

- **Saída:** O arquivo está vazio.

- **Código de retorno:** 14

#### Erro 1.5: Erro de escrita

- **Descrição:** Este erro ocorre quando o programa tenta abrir um arquivo que não pode ser aberto.

- **Motivo:** Pode ocorrer, por exemplo, quando o usuário especifica um arquivo que não pode ser aberto, ou qválida ou insuficiente

- **Saída:** Erro ao gravar dados no arquivo `nome_arq`.

- **Código de retorno:** 15

---

### Erros de ponteiro e memória

#### Erro 2.1: Erro de alocação de memória

- **Descrição:** Este erro ocorre quando o programa fica sem memória disponível para alocar ou tenta alocar em memória inacessível.

- **Motivo:** Pode ocorrer, por exemplo, quando o programa tenta alocar grandes quantidades de memória, quando tenta sobreescrever memória que não foi disponibilizada ou quando falta memória na máquina.

- **Saída:** Erro ao alocar memória.

- **Código de retorno:** 21

#### Erro 2.2: Passagem de array de jogadores nulo

- **Descrição:** Este erro ocorre quando o programa tenta trabalhar sobre um array de jogadores nulo.

- **Saída:** Erro: jogadores é um ponteiro nulo.

- **Código de retorno:** 22

#### Erro 2.3: Passagem de array de jogadores vazio

- **Descrição:** Este erro ocorre quando o programa tenta trabalhar sobre um array de jogadores vazio.

- **Saída:** Erro: um dos jogadores não possui pokémons.

- **Código de retorno:** 23

---

### Erros de dados

#### Erro 3.1: Número de pokemons negativo ou nulo

- **Descrição:** Este erro ocorre quando o programa tenta criar os pokemons com base em um arquivo informado com dados negativos ou inválidos.

- **Saída:** Erro: número de pokémons inválido.

- **Código de retorno:** 31

#### Erro 3.2: Número de pokemon atual maior do que o total

- **Descrição:** Este erro ocorre quando o índice do pokemon atual é maior do que o total de pokemons do jogador.

- **Saída:** Erro: número de pokémons insuficiente.

- **Código de retorno:** 32

#### Erro 3.3: Atributos de pokemon inválidos

- **Descrição:** Este erro ocorre quando algum atributo de um pokemon é negativo ou nulo.

- **Saída:** Erro: atributos de pokémon inválidos.

- **Código de retorno:** 33

#### Erro 3.4: Índice de atacante inválido

- **Descrição:** Este erro ocorre quando o índice do jogador atacente é diferente de `0` ou `1`

- **Saída:** Erro: índice de jogador inválido.

- **Código de retorno:** 34
