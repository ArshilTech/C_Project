#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char board[9];

void reset_board() {
    for (int i = 0; i < 9; ++i) board[i] = '1' + i;
}

void print_board() {
    printf("\n %c | %c | %c\n", board[0], board[1], board[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[3], board[4], board[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n\n", board[6], board[7], board[8]);
}

int is_winner(char p) {
    int w[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for (int i = 0; i < 8; ++i)
        if (board[w[i][0]] == p && board[w[i][1]] == p && board[w[i][2]] == p)
            return 1;
    return 0;
}

int board_full() {
    for (int i = 0; i < 9; ++i)
        if (board[i] != 'X' && board[i] != 'O')
            return 0;
    return 1;
}

int read_int_from_line(const char *line, int *out) {
    int val;
    char extra;
    if (sscanf(line, " %d %c", &val, &extra) == 1) {
        *out = val;
        return 1;
    }
    return 0;
}

int main() {
    char line[200];
    reset_board();
    char player = 'X';
    printf("Tic-Tac-Toe (2 players). Enter cell number 1-9.\n");
    while (1) {
        print_board();
        printf("Player %c, enter cell (1-9): ", player);
        if (!fgets(line, sizeof line, stdin)) {
            printf("\nInput closed. Exiting.\n");
            return 0;
        }
        int cell;
        if (!read_int_from_line(line, &cell)) {
            printf("Invalid input. Please enter a number from 1 to 9.\n");
            continue;
        }
        if (cell < 1 || cell > 9) {
            printf("Out of range. Choose 1 through 9.\n");
            continue;
        }
        int idx = cell - 1;
        if (board[idx] == 'X' || board[idx] == 'O') {
            printf("Cell already occupied. Pick another cell.\n");
            continue;
        }
        board[idx] = player;
        if (is_winner(player)) {
            print_board();
            printf("Player %c wins!\n", player);
            printf("Play again? (y/n): ");
            if (!fgets(line, sizeof line, stdin)) { printf("\nInput closed. Exiting.\n"); return 0; }
            if (line[0] == 'y' || line[0] == 'Y') {
                reset_board();
                player = 'X';
                continue;
            } else {
                printf("Goodbye.\n");
                break;
            }
        }
        if (board_full()) {
            print_board();
            printf("It's a draw!\n");
            printf("Play again? (y/n): ");
            if (!fgets(line, sizeof line, stdin)) { printf("\nInput closed. Exiting.\n"); return 0; }
            if (line[0] == 'y' || line[0] == 'Y') {
                reset_board();
                player = 'X';
                continue;
            } else {
                printf("Goodbye.\n");
                break;
            }
        }
        player = (player == 'X') ? 'O' : 'X';
    }
    return 0;
}
