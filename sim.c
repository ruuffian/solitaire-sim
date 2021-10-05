#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define COLOUMNS 4

typedef struct tag_Coloumn {
  int ray[8];
  int depth;
  int tag;
} Coloumn;

typedef struct tag_Board {
  Coloumn coloumns[4];
} Board;

void print_col(Coloumn col);
void print_board(Board board);
void check_col(int *buf, Coloumn col, int val);
void check_stack(int *buf, Coloumn col, int val);

int main(int arg, char **argv){
  Board board;

  for(int i = 0; i < COLOUMNS; i++){
    board.coloumns[i].tag = i+1;
    board.coloumns[i].depth = EMPTY;
  }

  print_board(board);
  return 0;
}

void check_col(int *buf, Coloumn col, int val){
  if(col.ray[col.depth] == val)
    check_stack(buf, col, val);
  if(col.ray[col.depth] > val){
    buf[0] = 0;
    buf[1] = val;
  }
  buf[0] = -1;
  buf[1] = val;
}

void check_stack(int *buf, Coloumn col, int val){
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
  for(int i = 0; i < COLOUMNS; i++){
    print_col(board.coloumns[i]);
  }
}

void print_col(Coloumn col){
  printf("%s%d%s", "Coloumn ", col.tag, ":: [");
  for(int i = 0; i < 7; i++){
    printf("%d%s", col.ray[i], ", ");
  }
  printf("%d%s", col.ray[7], "]\n");
}
