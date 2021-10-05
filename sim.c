#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define COLUMNS 4

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
void check_col(int *buf, Colomn col, int val);
void check_stack(int *buf, Colomn col, int val);

int main(int arg, char **argv){
  Board board;

  for(int i = 0; i < COLUMNS; i++){
    board.columns[i].tag = i+1;
    board.columns[i].depth = EMPTY;
  }

  print_board(board);
  return 0;
}

void check_col(int *buf, Column col, int val){
  if(col.ray[col.depth] == val)
    check_stack(buf, col, val);
  if(col.ray[col.depth] > val){
    buf[0] = 0;
    buf[1] = val;
  }
  buf[0] = -1;
  buf[1] = val;
}

void check_stack(int *buf, Column col, int val){
  int i = col.depth;
  while(col.ray[i] == val && i > 0){
    val *= 2;
    i--;
  }
  if(col.ray[0] == val)
    val *= 2;
  buf[0] = i;
  buf[1] = val;
}

void print_board(Board board){
  for(int i = 0; i < COLUMNS; i++){
    print_col(board.columns[i]);
  }
}

void print_col(Column col){
  printf("%s%d%s", "Column ", col.tag, ":: [");
  for(int i = 0; i < 7; i++){
    printf("%d%s", col.ray[i], ", ");
  }
  printf("%d%s", col.ray[7], "]\n");
}
