#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct pokemon {
    char *nome;
    char *tipo;
    float hp;
    float atk;
    float def;

} TPokemon;

typedef struct jogador {
    int num_poks;
    int current_pok;
    TPokemon *poks;

} TJogador;

char nome_arquivo[36], fstring[300];


void cria_log() {
    time_t now = time(0);
    struct tm *t = localtime(&now);
    strftime(nome_arquivo, sizeof(nome_arquivo), "./logs/log_%d-%m-%Y_%H-%M-%S.txt", t);
}


int verifica_arquivo(char *nome_arq) {
    FILE *arq = fopen(nome_arq, "r");
    if (arq == NULL) return 0;
    fclose(arq);

    return 1;
}


int grava_arquivo(char *nome_arq, char *data) {
    char *modo = "w";
    if (verifica_arquivo(nome_arq)) modo = "a";

    FILE *arq = fopen(nome_arq, modo);
    if (arq == NULL) return 0;
    fprintf(arq, "%s\n", data);
    fclose(arq);

    return 1;
}

char * le_arquivo(char *nome_arq) {
    char *data = NULL;
    char *line = NULL;
    int pa, pb, num_poks, i;
    size_t str_size;
    float atk, def, hp;
    char nome[20], tipo[9];

    FILE *arq = fopen(nome_arq, "r");
    if (arq == NULL) return NULL;

    fscanf(arq, " %d %d ", &pa, &pb);
    num_poks = pa + pb;

    str_size = 2 * sizeof(int) + 1;
    data = realloc(data, str_size);
    if (data == NULL) exit(1);
    snprintf(data, str_size, "%d %d\n", pa, pb);

    for (i = 0; i < num_poks; i++) {
        fscanf(arq, " %s %f %f %f %s ", nome, &atk, &def, &hp, tipo);

        str_size = strlen(data) + strlen(nome) + (3 * sizeof(float)) + strlen(tipo) + 2;
        line = realloc(line, str_size);
        if (line == NULL) exit(1);
        snprintf(line, str_size, "%s %.1f %.1f %.1f %s\n", nome, atk, def, hp, tipo);
        data = realloc(data, strlen(data) + strlen(line) + 1);
        if (data == NULL) exit(100);
        strcat(data, line);
    }

    printf("%s\n", data);
    return data;
}


char ** divide_linha(char * line) {
    char ** palavras = (char **) malloc(sizeof(char*) * 100);
    if (palavras == NULL) exit(1);
    int indice = 0;
    char * inicio, *fim;

    inicio = line;
    while (*inicio != '\0') {
        while (*inicio == ' ') inicio++;
        fim = inicio;
        while (*fim != ' ' && *fim != '\0') fim++;

        palavras[indice] = (char *) malloc(fim - inicio + 1);
        if (palavras[indice] == NULL) exit(1);
        strncpy(palavras[indice], inicio, fim - inicio);
        palavras[indice][fim - inicio] = '\0';

        inicio = fim;
        indice++;
    }
    palavras[indice] = NULL;

    return palavras;
}


TJogador * cria_jogadores(char *data) {
    TJogador * jogadores = (TJogador *) malloc(sizeof(TJogador) * 2);
    char *token, *line;
    int i = 0, j = 0;

    token = strtok(data, "\n");
    while (token != NULL) {
        line = malloc(strlen(token) + 1);
        strcpy(line, token);
        line[strlen(token)] = '\0';

        if (i == 0) {
            while (j < 2) {
                if (line[i] != ' ') {
                    jogadores[j].num_poks = (int) line[i] - 48;
                    jogadores[j].current_pok = 0;
                    jogadores[j].poks = (TPokemon *) malloc(sizeof(TPokemon) * jogadores[j].num_poks);
                    j++;
                }
                i++;
            }
            i = 0;
            j = 0;
        }
        else {
            char ** palavras = divide_linha(line);
            int player = i <= jogadores[0].num_poks ? 0 : 1;
            j = j >= jogadores[player].num_poks ? 0 : j;

            jogadores[player].poks[j].nome = malloc(strlen(palavras[0]) + 1);
            jogadores[player].poks[j].tipo = malloc(strlen(palavras[4]) + 1);

            strcpy(jogadores[player].poks[j].nome, palavras[0]);
            jogadores[player].poks[j].atk = (float) atoi(palavras[1]);
            jogadores[player].poks[j].def = (float) atoi(palavras[2]);
            jogadores[player].poks[j].hp = (float) atoi(palavras[3]);
            strcpy(jogadores[player].poks[j].tipo, palavras[4]);
            j++;
        }

        token = strtok(NULL, "\n");
        i++;
    }

    return jogadores;
}


int classifica_pokemon(const char *tipo) {
    const char *tipos[] = {"fogo", "pedra", "eletrico", "agua"}; // TODO: add type 'gelo'

    for (int i = 0; i < 4; i++) {
        if (strcmp(tipo, tipos[i]) == 0)
            return i;
    }
    return 4;
}

int mais_forte(char *tipo_atk, char * tipo_def) {
    
    int atk = classifica_pokemon(tipo_atk);
    int def = classifica_pokemon(tipo_def);

    return (atk + 1 == def || (atk == 4 && def == 0));
}

int mais_fraco(char *tipo_atk, char * tipo_def) {

    int atk = classifica_pokemon(tipo_atk);
    int def = classifica_pokemon(tipo_def);

    return (def + 1 == atk || (def == 4 && atk == 0));
}

void ataca(TJogador *jogadores, int atacante) {
    int defensor = atacante == 0 ? 1 : 0;
    float atk, def, hp;
    char *forca = "";
    int current_atk = jogadores[atacante].current_pok, current_def= jogadores[defensor].current_pok;

    if (mais_forte(jogadores[atacante].poks[current_atk].tipo, jogadores[defensor].poks[current_def].tipo)) {
        atk = (float) (jogadores[atacante].poks[current_atk].atk * 1.2);
        forca = "forte";
    }  
    else if (mais_fraco(jogadores[atacante].poks[current_atk].tipo, jogadores[defensor].poks[current_def].tipo)) {
        atk = (float) (jogadores[atacante].poks[current_atk].atk * 0.8);
        forca = "fraco";
    }
    else {
        atk = jogadores[atacante].poks[current_atk].atk;
        forca = "normal";
    }

    def = jogadores[defensor].poks[current_def].def;
    hp = jogadores[defensor].poks[current_def].hp;

    snprintf(fstring, sizeof(fstring), "[+] Pokemon %s do jogador %d atacou pokemon %s do jogador %d com efeito de Atk %.1f/ Def %.1f. (%s)", jogadores[atacante].poks[current_atk].nome, atacante + 1, jogadores[defensor].poks[current_def].nome, defensor + 1, atk, def, forca);
    grava_arquivo(nome_arquivo, fstring);

    hp -= atk > def ? atk - def : 1;
    snprintf(fstring, sizeof(fstring), "Pokemon %s agora tem %.1f de HP.\tInicial: %.1f\n", jogadores[defensor].poks[current_def].nome, hp, jogadores[defensor].poks[current_def].hp);
    grava_arquivo(nome_arquivo, fstring);

    jogadores[defensor].poks[current_def].hp = hp;

    if (hp <= 0) {
        jogadores[defensor].current_pok++;

        snprintf(fstring, sizeof(fstring), "[!] Pokemon %s do jogador %d perdeu.\n\n[+]----------Fim de round----------[+]\n", jogadores[defensor].poks[current_def].nome, defensor + 1);
        grava_arquivo(nome_arquivo, fstring);
        printf("%s venceu %s\n", jogadores[atacante].poks[current_atk].nome, jogadores[defensor].poks[current_def].nome);
    }
}

void checa_sobreviventes(TJogador *jogadores, int vencedor) {
    int i;
    grava_arquivo(nome_arquivo, "\n\n[!]----------Fim de jogo----------[!]\nChecando sobreviventes...\n");
    printf("Pokemon sobreviventes:\n");
    for (i = jogadores[vencedor].current_pok; i < jogadores[vencedor].num_poks; i++) {
        snprintf(fstring, sizeof(fstring), "[+] Pokemon %s do jogador %d sobreviveu.\n", jogadores[vencedor].poks[i].nome, vencedor + 1);
        grava_arquivo(nome_arquivo, fstring);
        printf("%s\n", jogadores[vencedor].poks[i].nome);
    }
}

void checa_derrotados(TJogador *jogadores) {
    int i;
    grava_arquivo(nome_arquivo, "\nChecando derrotados...\n");
    printf("Pokemon derrotados:\n");
    for (i = 0; i < jogadores[0].current_pok; i++) {
        snprintf(fstring, sizeof(fstring), "[+] Pokemon %s do jogador 1 foi derrotado.\n", jogadores[0].poks[i].nome);
        grava_arquivo(nome_arquivo, fstring);
        printf("%s ", jogadores[0].poks[i].nome);
    }
    for (i = 0; i < jogadores[1].current_pok; i++) {
        snprintf(fstring, sizeof(fstring), "[+] Pokemon %s do jogador 2 foi derrotado.\n", jogadores[1].poks[i].nome);
        grava_arquivo(nome_arquivo, fstring);
        printf("%s ", jogadores[1].poks[i].nome);
    }
    printf("\n");
}


void inicia_jogo(TJogador *jogadores) {
    grava_arquivo(nome_arquivo, "Jogo iniciado.");
    int atacante = 0;
    
    while((jogadores[0].current_pok < jogadores[0].num_poks) && (jogadores[1].current_pok < jogadores[1].num_poks)) {
        ataca(jogadores, atacante);
        atacante = atacante == 0 ? 1 : 0;
    }
    if (jogadores[0].current_pok >= jogadores[0].num_poks) {
        grava_arquivo(nome_arquivo, "Jogador 2 venceu.");
        printf("Jogador 2 venceu.\n");
    }
    else {
        grava_arquivo(nome_arquivo, "Jogador 1 venceu.");
        printf("Jogador 1 venceu.\n");
    }

    checa_sobreviventes(jogadores, jogadores[0].current_pok < jogadores[0].num_poks ? 0 : 1);
    checa_derrotados(jogadores);

    system("pause");
}


int main(int argc, char *argv[]) {
    TJogador *jogadores;
    char *data;
    
    cria_log();

    if (argc == 2) {
        printf("Usando arquivo %s\n", argv[1]);
        data = le_arquivo(argv[1]);
    } else {
        grava_arquivo(nome_arquivo, "[+]-----------------------------[+]\nNenhum arquivo informado.\nUsando o arquivo 'input.txt'.\nUso: main.exe <arquivo>.txt\n[+]-----------------------------[+]\n");
        data = le_arquivo("input.txt");
    }
    if (data == NULL) {
        grava_arquivo(nome_arquivo, "[!] Erro ao ler arquivo.");
        exit(1);
    }

    printf("%s\n", data);
    jogadores = cria_jogadores(data);

    for (int i = 0; i < 2; i++) {
        snprintf(fstring, sizeof(fstring), "Jogador %d:", i + 1);
        grava_arquivo(nome_arquivo, fstring);
        for (int j = 0; j < jogadores[i].num_poks; j++) {
            snprintf(fstring, sizeof(fstring), "- %s: Atk: %.1f\tDef: %.1f\tHp: %.1f\tTipo: %s\n", jogadores[i].poks[j].nome, jogadores[i].poks[j].atk, jogadores[i].poks[j].def, jogadores[i].poks[j].hp, jogadores[i].poks[j].tipo);
            grava_arquivo(nome_arquivo, fstring);
        }
    }

    inicia_jogo(jogadores);
    free(data);
    free(jogadores);
    
    return (0);
}