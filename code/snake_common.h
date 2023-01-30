#include "stdio.h"
#include "stdlib.h"

#define OK 0
#define WIN 1
#define ERR 2

#define RIGHT 45
#define LEFT 43
#define UP 40
#define DOWN 48

#define WIDTH 6
#define HEIGHT 6

typedef unsigned int uint;

typedef struct {
    uint row;
    uint col;
} POS_S;

typedef struct SNAKE_NODE {
    struct SNAKE_NODE *prev;
    struct SNAKE_NODE *next;
    POS_S pos;
} SNAKE_NODE_S;

void matrix_init();
uint matrix_update(POS_S pos, char symbol);
char matrix_search(POS_S pos);
void matrix_display();

uint* snake_get_dir();
void snake_ll_init();
void snake_ll_destroy();
uint snake_move();

void apple_update();
