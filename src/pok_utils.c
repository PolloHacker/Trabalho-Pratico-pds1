/**
 * @file pok_utils.c
 * 
 * @brief Este arquivo contém as implementações das funções definidas em `pok_utils.h`
 * 
 * Este arquivo contém as implementações das funcões definidas em `pok_utils.h`.
 * As funções implementadas são responsáveis por controlar os stats dos pokemons e fazer os cálculos de batalha.
 
 * Contém as funções:
 *  - cria_jogadores(): cria uma lista de jogadores a partir de uma cadeia de caracteres.
 *  - classifica_pokemon(): classifica um pokemon com base no seu tipo.
 *  - mais_forte(): determina se o tipo defensor é mais forte do que o tipo atacante.
 *  - mais_fraco(): determina se o tipo defensor é mais fraco do que o tipo atacante.
 *  - ataca(): realiza um ataque entre dois jogadores.
 *  - checa_sobreviventes(): checa os pokemons sobreviventes após o fim do jogo.
 *  - checa_derrotados(): verifica os pokemons derrotados após o fim do jogo.
 * 
 * @author Isaac Reyes (isaac.reyalves@gmail.com)
 * @version 1.1.3
 * @date 2024-05-10
 * @bug Nenhum bug encontrado.
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"
#include "file_utils.h"


/**
 * @brief Classifica um Pokémon com base no seu tipo.
 * 
 * @param tipo O tipo do Pokémon.
 * 
 * @return Um valor inteiro representando a classificação do Pokémon.
 *         - 0: Tipo Elétrico
 *         - 1: Tipo Água
 *         - 2: Tipo Fogo
 *         - 3: Tipo Gelo
 *         - 4: Tipo Pedra
 *         - 5: Tipo Desconhecido
 */
int classifica_pokemon(const char *tipo) {
    // Criamos um array imutável de strings contendo os tipos de pokémons.
    const char *tipos[] = {"eletrico", "agua", "fogo", "gelo", "pedra"};

    // Verificamos se o tipo especificado existe no array de tipos.
    for (int i = 0; i < 5; i++) {
        // Caso o tipo exista, retornamos o valor correspondente.
        if (strcmp(tipo, tipos[i]) == 0)
            return i;
    }
    // Caso o tipo não exista, retornamos o valor `UNKNOWN_TYPE`.
    return UNKNOWN_TYPE;
}


/**
 * @author Isaac Reyes
 * 
 * @brief Cria uma lista de jogadores a partir de uma cadeia de caracteres.
 *
 * Esta função quebra uma cadeia de caracteres para criar um array de estruturas TJogador.
 * A cadeia de caracteres deve conter informações sobre dois jogadores e seus Pokemons.
 * Cada linha da cadeia de caracteres representa um Pokemon e seus atributos.
 * A primeira linha da cadeia de caracteres deve conter o número de Pokemons de cada jogador.
 * 
 * @note Cada jogador é representado por uma estrutura TJogador.
 * @note Cada pokemon de cada jogador é representado por uma estrutura TPokemon.
 * 
 * @param data A string de dados contendo as informações dos jogadores e seus pokémons.
 * 
 * @return Um ponteiro para a lista de jogadores criada.
 * 
 */
TJogador * cria_jogadores(char *data) {
    // Alocamos dinamicamente um array de jogadores para armazenar os jogadores.
    TJogador * jogadores = (TJogador *) malloc(sizeof(TJogador) * 2);
    // Caso ocorra um erro ao alocar memória, informamos o usuário e encerramos o programa.
    if (jogadores == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(MEM_ERR);
    }
    // Criamos ponteiros para as linhas da cadeia de caracteres.
    char *token, *line;
    // Inicializamos os contadores e o jogador que está sendo criado.
    int i = 0, j = 0, player = 0;

    // Ao usarmos a funcão `strtok`, dividimos a cadeia de caracteres em linhas e colocamos o endereço da primeira linha em `token`.
    token = strtok(data, "\n");
    // Enquanto o endereço apontar para uma palavra válida, continuamos a processar dados.
    while (token != NULL) {
        // Alocamos dinamicamente uma string para cada linha.
        line = malloc(strlen(token) + 1);
        // Caso ocorra um erro ao alocar memória, informamos o usuário e encerramos o programa.
        if (line == NULL) {
            printf("Erro ao alocar memória.\n");
            exit(MEM_ERR);
        }

        // Copiamos a linha lida para a string.
        strcpy(line, token);
        // Adicionamos um caractere nulo ao final da string.
        line[strlen(token)] = '\0';

        // Verificamos se é a primeira linha da cadeia de caracteres.
        if (i == 0) {
            // Ao usarmos a funcção `sscanf`, lemos o número de pokemons de cada jogador da primeira linha e armazenamos os valores.
            sscanf(line, "%d %d", &jogadores[0].num_poks, &jogadores[1].num_poks);
            printf("Num pokemons 1: %d\nNum pokemons 2: %d\n", jogadores[0].num_poks, jogadores[1].num_poks);
            // Alocamos dinamicamente um array de pokémons para cada jogador.
            for (j = 0; j < 2; j++) {
                jogadores[j].current_pok = 0;
                jogadores[j].poks = (TPokemon *) malloc(sizeof(TPokemon) * jogadores[j].num_poks);
                // Caso ocorra um erro ao alocar memória, informamos o usuário e encerramos o programa.
                if (jogadores[j].poks == NULL) {
                    printf("Erro ao alocar memória.\n");
                    exit(MEM_ERR);
                }
            }
            // Reiniciamos o contador `j`.
            j = 0;
        }
        else {
            // Recebemos um array de strings contendo os atributos do pokemon.
            char ** palavras = divide_linha(line);
            // Definimos o número do pokemon que estamos criando.
            j = j >= jogadores[player].num_poks ? 0 : j;
            // Definimos o jogador que estamos criando.
            player = i <= jogadores[0].num_poks ? 0 : 1;       

            // Colocamos os atributos do pokemon no array do jogador correspondente.
            jogadores[player].poks[j].nome = malloc(strlen(palavras[0]) + 1);
            jogadores[player].poks[j].tipo = malloc(strlen(palavras[4]) + 1);
            jogadores[player].poks[j].tipo_int = classifica_pokemon(jogadores[player].poks[j].tipo);

            strcpy(jogadores[player].poks[j].nome, palavras[0]);
            // Fazemos as convesões de string para float.
            jogadores[player].poks[j].atk = atof(palavras[1]);
            jogadores[player].poks[j].def = atof(palavras[2]);
            jogadores[player].poks[j].hp = atof(palavras[3]);
            strcpy(jogadores[player].poks[j].tipo, palavras[4]);

            // Liberamos a memória alocada dinamicamente.
            free(palavras);
            // Avançamos o contador `j`.
            j++;
        }

        // Recebemos o endereço da próxima linha da cadeia de caracteres.
        token = strtok(NULL, "\n");
        // Avançamos o contador `i`.
        i++;
    }
    // Retornamos a lista de jogadores.
    return jogadores;
}


/**
 * @brief Determina se um tipo atacante dado é mais forte do que um tipo defensor dado.
 *
 * @param forca_atk O tipo atacante.
 * @param forca_def O tipo defensor.
 * 
 * @return 1 se o tipo atacante for mais forte do que o tipo defensor, 0 caso contrário.
 */
int mais_forte(int forca_atk, int forca_def) {
    /*
    * Calculamos a força do atacante e do defensor.
    * A fórmula provém do fato das relações serem circulares, ou seja, o próximo tipo é mais forte que o anterior.
    * Se o atacante for mais forte do que o defensor, retornamos 1. Caso contrário, retornamos 0.
    */
    return (forca_atk + 1 == forca_def || (forca_atk == 4 && forca_def == 0));
}


/**
 * @brief Determina se o tipo defensor é mais fraco do que o tipo atacante.
 *
 * @param forca_atk O tipo atacante.
 * @param forca_def O tipo defensor.
 * 
 * @return 1 se o tipo defensor for mais fraco do que o tipo atacante, 0 caso contrário.
 */
int mais_fraco(int forca_atk, int forca_def) {
    /*
    * Calculamos a força do atacante e do defensor.
    * A fórmula provém do fato das relações serem circulares, ou seja, o próximo tipo é mais forte que o anterior.
    * Se o atacante for mais forte do que o defensor, retornamos 1. Caso contrário, retornamos 0.
    */
    return (forca_def + 1 == forca_atk || (forca_def == 4 && forca_atk == 0));
}


/**
 * @brief Realiza um ataque entre dois jogadores.
 * 
 * Para realizar o ataque, a função verifica qual a relação de tipo entre os pokemons envolvidos.
 * Se o atacante for mais forte do que o defensor, o ataque é de 1.2x. Se o atacante for mais fraco do que o defensor, o ataque é de 0.8x.
 * Ao final, verifica se o defensor foi derrotado e registra o resultado nos logs.
 * 
 * @param jogadores Array contendo os jogadores.
 * @param atacante Índice do jogador atacante.
 */
void ataca(TJogador *jogadores, int atacante) {
    // Definimos o índice do defensor.
    int defensor = atacante == 0 ? 1 : 0;
    float atk, def, hp;
    // Criamos uma string para armazenar a força do ataque.
    char *forca = "";
    // Definimos o pokémon atacante e o defensor.
    int current_atk = jogadores[atacante].current_pok, current_def= jogadores[defensor].current_pok;

    /*
    * Determinamos a força do ataque por meio de uma função auxiliar e armazenamos em `forca`.
    * Se o atacante for mais forte do que o defensor, o ataque é de 1.2x. 
    * Se o atacante for mais fraco do que o defensor, o ataque é de 0.8x.
    * Caso contrário, o ataque é normal.
    */
    if (mais_forte(jogadores[atacante].poks[current_atk].tipo_int, jogadores[defensor].poks[current_def].tipo_int)) {
        atk = (float) (jogadores[atacante].poks[current_atk].atk * 1.2);
        forca = "forte";
    }  
    else if (mais_fraco(jogadores[atacante].poks[current_atk].tipo_int, jogadores[defensor].poks[current_def].tipo_int)) {
        atk = (float) (jogadores[atacante].poks[current_atk].atk * 0.8);
        forca = "fraco";
    }
    else {
        atk = jogadores[atacante].poks[current_atk].atk;
        forca = "normal";
    }

    // Armazenamos os valores de defesa e vida do defensor.
    def = jogadores[defensor].poks[current_def].def;
    hp = jogadores[defensor].poks[current_def].hp;

    // Gravamos as informações do ataque nos logs.
    snprintf(form_string, sizeof(form_string), "[+] Pokemon %s do jogador %d atacou pokemon %s do jogador %d com efeito de Atk %.1f/ Def %.1f. (%s)", jogadores[atacante].poks[current_atk].nome, atacante + 1, jogadores[defensor].poks[current_def].nome, defensor + 1, atk, def, forca);
    grava_arquivo(nome_arq_log, form_string);

    /*
    * Calculamos a dedução total de vida do defensor.
    * Caso a força do ataque seja maior do que a defesa do defensor, a dedução é a diferença entre esses valores. 
    * Caso contrário, a dedução é de 1.
    */
    hp -= atk > def ? atk - def : 1;
    // Gravamos o resultado do ataque nos logs.
    snprintf(form_string, sizeof(form_string), "Pokemon %s agora tem %.1f de HP.\tInicial: %.1f\n", jogadores[defensor].poks[current_def].nome, hp, jogadores[defensor].poks[current_def].hp);
    grava_arquivo(nome_arq_log, form_string);

    // Atualizamos a vida do defensor.
    jogadores[defensor].poks[current_def].hp = hp;

    // Caso sua vida caia para 0 ou menor, o pokemon foi derrotado.
    if (hp <= 0) {
        // Avançamos o contator do pokemon atual.
        jogadores[defensor].current_pok++;

        // Gravamos a derrota do pokemon nos logs.
        snprintf(form_string, sizeof(form_string), "[!] Pokemon %s do jogador %d perdeu.\n\n[+]----------Fim de round----------[+]\n", jogadores[defensor].poks[current_def].nome, defensor + 1);
        grava_arquivo(nome_arq_log, form_string);
        // Informamos o usuário que o pokemon foi derrotado.
        printf("%s venceu %s\n", jogadores[atacante].poks[current_atk].nome, jogadores[defensor].poks[current_def].nome);
    }
}


/**
 * @brief Checa os pokémons sobreviventes após o fim do jogo.
 * 
 * @param jogadores O array de jogadores.
 * @param vencedor O índice do jogador vencedor.
 */
void checa_sobreviventes(TJogador *jogadores, int vencedor) {
    // Inicializamos o contador.
    int i;

    // Gravamos o fim de jogo nos logs.
    grava_arquivo(nome_arq_log, "\n\n[!]----------Fim de jogo----------[!]\nChecando sobreviventes...\n");
    printf("Pokemon sobreviventes:\n");

    /*
    * Para cada pokemon sobrevivente, informamos o usuário e gravamos no arquivo de logs.
    * A detecção é feita por meio do contador de pokemon atual do jogador.
    * Caso o índice do pokemon seja maior, ele sobreviveu.
    * Caso contrário, ele foi derrotado.
    */
    for (i = jogadores[vencedor].current_pok; i < jogadores[vencedor].num_poks; i++) {
        snprintf(form_string, sizeof(form_string), "[+] Pokemon %s do jogador %d sobreviveu.\n", jogadores[vencedor].poks[i].nome, vencedor + 1);
        grava_arquivo(nome_arq_log, form_string);
        printf("%s\n", jogadores[vencedor].poks[i].nome);
    }
}

/**
 * @brief Verifica os pokémons derrotados após o fim do jogo.
 * 
 * @param jogadores Um array de estruturas do tipo TJogador contendo os jogadores e seus pokémons.
 */
void checa_derrotados(TJogador *jogadores) {
    // Inicializamos o contador.
    int i;
    grava_arquivo(nome_arq_log, "\nChecando derrotados...\n");
    printf("Pokemon derrotados:\n");

    /*
    * Para cada pokemon sobrevivente, informamos o usuário e gravamos no arquivo de logs.
    * A detecção é feita por meio do contador de pokemon atual do jogador.
    * Caso o índice do pokemon seja menor, ele foi derrotado.
    * Caso contrário, ele sobreviveu.
    */
    for (i = 0; i < jogadores[0].current_pok; i++) {
        snprintf(form_string, sizeof(form_string), "[+] Pokemon %s do jogador 1 foi derrotado.\n", jogadores[0].poks[i].nome);
        grava_arquivo(nome_arq_log, form_string);
        printf("%s\n", jogadores[0].poks[i].nome);
    }
    for (i = 0; i < jogadores[1].current_pok; i++) {
        snprintf(form_string, sizeof(form_string), "[+] Pokemon %s do jogador 2 foi derrotado.\n", jogadores[1].poks[i].nome);
        grava_arquivo(nome_arq_log, form_string);
        printf("%s\n", jogadores[1].poks[i].nome);
    }
}