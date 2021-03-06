/*
 * author: ruuffian
 * description: simulate and solve the 2048 solitaire game
 * date started: 10/4/2021
 * date complete: 
 */

#include <stdio.h>
#include <stdlib.h>

#define INIT -1
#define EMPTY 7
#define COLUMNS 4
#define POSITIONS 8

typedef struct tag_Column {
    int ray[8];
    int depth;
    int tag;
} Column;

typedef struct tag_Board {
    Column columns[COLUMNS];
} Board;

void print_col(Column col);

void print_board(Board board);

void check_col(int *buf, Column col, int val);

void check_stack(int *buf, Column col, int val);

Column add_val(int val, Column col);

int main(int arg, char **argv) {
    Board p;
    Board *board = &p;

    for (int i = 0; i < COLUMNS; i++) {
        (*board).columns[i].tag = i;
        (*board).columns[i].depth = INIT;
        for (int j = 0; j < POSITIONS; j++) {
            (*board).columns[i].ray[j] = 0;
        }
    }

    print_board(*board);
    Column new = add_val(2, (*board).columns[0]);
    (*board).columns[0] = new;
    print_board(*board);
    Column new2 = add_val(2, (*board).columns[0]);
    (*board).columns[0] = new2;
    print_board(*board);
    return 0;
}

Column add_val(int val, Column col) {
    int arr[2];
    int *check;
    check = arr;
    if (col.ray[col.depth] == val) {
        check_stack(check, col, val);
        col.ray[*check] = *(check + 1);
        for (int i = *check; i < POSITIONS; i++) {
            col.ray[i] = 0;
        }
        col.depth = *(check + 1);
    }
    col.ray[col.depth + 1] = val;
    col.depth = col.depth + 1;
    return col;
}

void check_col(int *buf, Column col, int val) {
    if (col.ray[col.depth] == val)
        check_stack(buf, col, val);
    if (col.ray[col.depth] > val) {
        buf[0] = 0;
        buf[1] = val;
    }
    buf[0] = -1;
    buf[1] = val;
}

void check_stack(int *check, Column col, int val) {
    int i = col.depth;
    while (col.ray[i] == val && i > 0) {
        val *= 2;
        i--;
    }
    if (col.ray[0] == val)
        val *= 2;
    *check = i;
    *(check + 1) = val;
}

void print_board(Board board) {
    for (int i = 0; i < COLUMNS; i++) {
        print_col(board.columns[i]);
    }
    printf("\n\n");
}

void print_col(Column col) {
    printf("%s%d%s", "Column ", col.tag + 1, ":: [");
    for (int i = 0; i < POSITIONS - 1; i++) {
        printf("%d%s", col.ray[i], ", ");
    }
    printf("%d%s", col.ray[POSITIONS - 1], "]\n");
}
