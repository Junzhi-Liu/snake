#include "snake_common.h"

uint g_snake_dir = RIGHT; 
uint g_snake_length = 0;

SNAKE_NODE_S *g_snake_ll_head = NULL;
SNAKE_NODE_S *g_snake_ll_tail = NULL;

uint* snake_get_dir()
{
    return &g_snake_dir;
}

void snake_ll_init()
{
    SNAKE_NODE_S *node = (SNAKE_NODE_S *)malloc(sizeof(SNAKE_NODE_S));
    g_snake_ll_head = node;
    node->prev = NULL;
    node->next = NULL;
    node->pos.row = HEIGHT / 2;
    node->pos.col = WIDTH / 2 + 1;

    node = (SNAKE_NODE_S *)malloc(sizeof(SNAKE_NODE_S));
    g_snake_ll_tail = node;
    node->prev = g_snake_ll_head;
    node->next = NULL;
    node->pos.row = HEIGHT / 2;
    node->pos.col = WIDTH / 2;

    g_snake_ll_head->next = g_snake_ll_tail;
    g_snake_length = 2;
    return;
}

void snake_ll_destroy()
{
    while (g_snake_ll_head != NULL) {
        SNAKE_NODE_S *head_next = g_snake_ll_head->next;
        free(g_snake_ll_head);
        g_snake_ll_head = head_next;
    }

    g_snake_ll_head = NULL;
    g_snake_ll_tail = NULL;
    return;
}

void snake_ll_insert_head(POS_S pos)
{
    SNAKE_NODE_S *node = (SNAKE_NODE_S *)malloc(sizeof(SNAKE_NODE_S));
    node->prev = NULL;
    node->next = g_snake_ll_head;
    node->pos.row = pos.row;
    node->pos.col = pos.col;

    g_snake_ll_head->prev = node;
    g_snake_ll_head = node;
}

void snake_ll_del_tail()
{
    SNAKE_NODE_S *node = g_snake_ll_tail->prev;
    free(g_snake_ll_tail);
    g_snake_ll_tail = node;
    g_snake_ll_tail->next = NULL;
    return;
}

POS_S snake_get_head_next()
{
    POS_S head_next = g_snake_ll_head->pos;
    switch (g_snake_dir) {
        case RIGHT:
            head_next.col += 1;
            break;
        case LEFT:
            head_next.col -= 1;
            break;
        case UP:
            head_next.row -= 1;
            break;
        case DOWN:
            head_next.row += 1;
            break;
        default:
            break;
    }
    return head_next;
}

uint check_run_state(POS_S pos)
{
    if ((matrix_search(pos) == ' ') || (matrix_search(pos) == '%')) {
        return OK;
    }

    matrix_update(g_snake_ll_head->pos, '@');
    return ERR;
}

uint snake_move()
{
    POS_S snake_head_next = snake_get_head_next();
    if (check_run_state(snake_head_next) == ERR) {
        return ERR;
    }
    if (matrix_search(snake_head_next) == ' ') {
        matrix_update(g_snake_ll_head->pos, '+');
        snake_ll_insert_head(snake_head_next);
        matrix_update(snake_head_next, 'O');
        matrix_update(g_snake_ll_tail->pos, ' ');
        snake_ll_del_tail();
        matrix_update(g_snake_ll_tail->pos, 'x');
    } else { // apple
        matrix_update(g_snake_ll_head->pos, '+');
        snake_ll_insert_head(snake_head_next);
        matrix_update(snake_head_next, 'O');
        if ((++g_snake_length) == (HEIGHT - 2) * (WIDTH - 2)) {
            return WIN;
        }
        apple_update();
    }
}
