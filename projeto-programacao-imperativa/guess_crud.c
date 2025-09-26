/* guess_crud.c
   Jogo de adivinhação com CRUD de resultados em arquivo texto.
   Compilar: gcc -o guess_crud guess_crud.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATAFILE "results.txt"
#define LINE_MAX 256

/* Prototipos */
void menu();
void play_game();
void list_results();
void remove_result();
int next_id();
void trim_newline(char *s);

/* main */
int main() {
    srand((unsigned)time(NULL));
    menu();
    return 0;
}

/* Menu principal */
void menu() {
    int op = 0;
    while (1) {
        printf("\n=== Jogo de Adivinhação (C) ===\n");
        printf("1) Jogar\n");
        printf("2) Listar resultados\n");
        printf("3) Remover resultado por id\n");
        printf("4) Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &op) != 1) { 
            while (getchar() != '\n'); 
            printf("Entrada invalida.\n");
            continue;
        }
        while (getchar() != '\n');
        if (op == 1) play_game();
        else if (op == 2) list_results();
        else if (op == 3) remove_result();
        else if (op == 4) { printf("Tchau!\n"); break; }
        else printf("Opcao invalida.\n");
    }
}

/* Jogar */
void play_game() {
    char player[64];
    int minv, maxv;
    printf("Seu nome: ");
    if (!fgets(player, sizeof(player), stdin)) return;
    trim_newline(player);
    if (strlen(player) == 0) strcpy(player, "Anonimo");

    printf("Intervalo - minimo: ");
    if (scanf("%d", &minv) != 1) { while (getchar()!='\n'); printf("Entrada invalida.\n"); return; }
    printf("Intervalo - maximo: ");
    if (scanf("%d", &maxv) != 1) { while (getchar()!='\n'); printf("Entrada invalida.\n"); return; }
    while (getchar() != '\n');

    if (minv > maxv) {
        int t = minv; minv = maxv; maxv = t;
    }
    int target = minv + rand() % (maxv - minv + 1);
    int guess = 0;
    int attempts = 0;
    printf("Ok %s! Pensei num numero entre %d e %d. Tente adivinhar.\n", player, minv, maxv);
    while (1) {
        printf("Seu palpite: ");
        if (scanf("%d", &guess) != 1) { while (getchar()!='\n'); printf("Entrada invalida.\n"); continue; }
        attempts++;
        if (guess == target) {
            printf("Parabens! Voce acertou em %d tentativas.\n", attempts);
            break;
        } else if (guess < target) {
            printf("Maior!\n");
        } else {
            printf("Menor!\n");
        }
    }
    while (getchar() != '\n'); /* limpar buffer */

    /* Gravar resultado (create) */
    int id = next_id();
    FILE *f = fopen(DATAFILE, "a");
    if (!f) {
        perror("Erro ao abrir arquivo para gravar");
        return;
    }
    fprintf(f, "%d|%s|%d|%d|%d|%d|ACERTOU\n", id, player, minv, maxv, target, attempts);
    fclose(f);
    printf("Resultado salvo com id %d.\n", id);
}

/* Listar resultados (read) */
void list_results() {
    FILE *f = fopen(DATAFILE, "r");
    if (!f) {
        printf("Nenhum resultado ainda. (arquivo %s nao encontrado)\n", DATAFILE);
        return;
    }
    char line[LINE_MAX];
    printf("\n--- Resultados salvos ---\n");
    printf("ID | Jogador | Min | Max | Target | Tentativas | Status\n");
    while (fgets(line, sizeof(line), f)) {
        trim_newline(line);
        if (strlen(line) == 0) continue;
        /* exibir tal como esta, substituindo '|' por ' | ' para melhor leitura */
        char *p = line;
        while (*p) {
            if (*p == '|') putchar(' ');
            putchar(*p);
            p++;
        }
        printf("\n");
    }
    fclose(f);
}

/* Remover resultado por id (delete) */
void remove_result() {
    int id;
    printf("Digite o id a remover: ");
    if (scanf("%d", &id) != 1) { while (getchar()!='\n'); printf("Entrada invalida.\n"); return; }
    while (getchar() != '\n');
    FILE *f = fopen(DATAFILE, "r");
    if (!f) {
        printf("Arquivo de resultados nao existe.\n");
        return;
    }
    FILE *tmp = fopen("tmp_results.txt", "w");
    if (!tmp) { fclose(f); perror("Erro"); return; }

    char line[LINE_MAX];
    int found = 0;
    while (fgets(line, sizeof(line), f)) {
        int curid;
        char copy[LINE_MAX];
        strcpy(copy, line);
        char *tok = strtok(copy, "|");
        if (tok) curid = atoi(tok);
        else curid = -1;
        if (curid == id) {
            found = 1; /* pula esta linha (remove) */
        } else {
            fputs(line, tmp);
        }
    }
    fclose(f);
    fclose(tmp);
    if (!found) {
        remove("tmp_results.txt");
        printf("ID %d nao encontrado.\n", id);
    } else {
        remove(DATAFILE);
        rename("tmp_results.txt", DATAFILE);
        printf("Registro %d removido.\n", id);
    }
}

/* Proximo id: le arquivo e retorna max+1 */
int next_id() {
    FILE *f = fopen(DATAFILE, "r");
    if (!f) return 1;
    char line[LINE_MAX];
    int maxid = 0;
    while (fgets(line, sizeof(line), f)) {
        int curid = atoi(line);
        if (curid > maxid) maxid = curid;
    }
    fclose(f);
    return maxid + 1;
}

/* remove newline de string */
void trim_newline(char *s) {
    size_t L = strlen(s);
    if (L == 0) return;
    if (s[L-1] == '\n') s[L-1] = '\0';
}
