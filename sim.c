/*
 * author: ruuffian
 * description: simulate and solve the 2048 solitaire game
 * date started: 10/4/2021
 * date complete: 
 */

#include <stdio.h>
#include <stdlib.h>

#define EMPTY 7
#define COLUMNS 4
#define POSITIONS 8

typedef struct tag_Ranking
{
  int columns[4][2];
} Ranking;

typedef struct tag_Column 
{
  int ray[8];
  int depth;
  int tag;
} Column;

typedef struct tag_Board 
{
  Column columns[COLUMNS];
} Board;

void print_col(Column col);
void print_board(Board board);
void check_col(int *buf, Column col, int val);
void check_stack(int *buf, Column col, int val);
int get_best(Board board, Ranking *rank);
void check_best(Board board, Ranking *rank, int val);
void add_val(int val, Column col);

int main(int arg, char **argv)
{
  Board board;
  Ranking *rank = malloc(sizeof(Ranking));

  for(int i = 0; i < COLUMNS; i++){
    board.columns[i].tag = i;
    board.columns[i].depth = EMPTY;
    for(int j = 0; j < POSITIONS; j++){
      board.columns[i].ray[j] = 0;
    }
  }
  print_board(board);
  add_val(2, board.columns[0]);
  print_board(board);
  free(rank);
  return 0;
  }

void add_val(int val, Column col){
  int check[2];
  check_stack(check, col, val);
  col.ray[check[0]] = check[1];
  int blanked = col.depth - check[0];
  for(int i = POSITIONS - 1; i > blanked; i--){
    col.ray[i] = 0;
  }
  col.depth = check[1];
}

int get_best(Board board, Ranking *rank)
{
  int best = 0;
  int tag = 0;
  for(int i = 0; i < COLUMNS; i++){
    if(*(*(rank -> columns + i) + 0) > best)
      best = *(*(rank -> columns + i) + 0);
      tag = i;
  }
  if(tag = 0){
    best = 8;
    for(int i = 0; i < COLUMNS; i++){
      if(board.columns[i].depth < best && *(*(rank -> columns + i) + 0) == 0){
        best = board.columns[i].depth;
	tag = i;
      }
    }
  }
  return tag;
}

void check_best(Board board, Ranking *rank, int val)
{
  for(int i = 0; i < COLUMNS; i++){
    check_col(*(rank -> columns + i), board.columns[i+1], val);
  }
}

void check_col(int *buf, Column col, int val)
{
  if(col.ray[col.depth] == val)
    check_stack(buf, col, val);
  if(col.ray[col.depth] > val){
    buf[0] = 0;
    buf[1] = val;
  }
  buf[0] = -1;
  buf[1] = val;
}

void check_stack(int *buf, Column col, int val)
{
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

void print_board(Board board)
{
  for(int i = 0; i < COLUMNS; i++){
    print_col(board.columns[i]);
  }
}

void print_col(Column col)
{
  printf("%s%d%s", "Column ", col.tag + 1, ":: [");
  for(int i = 0; i < POSITIONS - 1; i++){
    printf("%d%s", col.ray[i], ", ");
  }
  printf("%d%s", col.ray[POSITIONS - 1], "]\n");
}
