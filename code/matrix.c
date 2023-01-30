#include <windows.h>
#include "snake_common.h"

char g_matrix[HEIGHT][WIDTH] = {};

void matrix_init()
{
    memset(&(g_matrix[0][0]), ' ', HEIGHT * WIDTH);

    for (uint i = 0; i < WIDTH; i++) {
        g_matrix[0][i] = '#';
        g_matrix[HEIGHT - 1][i] = '#';
    }

    for (uint i = 1; i < HEIGHT - 1; i++) {
        g_matrix[i][0] = '#';
        g_matrix[i][WIDTH - 1] = '#';
    }

    g_matrix[HEIGHT / 2][WIDTH / 2] = 'x';
    g_matrix[HEIGHT / 2][WIDTH / 2 + 1] = 'O';
}

uint matrix_update(POS_S pos, char symbol)
{
    if ((pos.col >= WIDTH) || (pos.row >= HEIGHT)) {
        return ERR;
    }
    g_matrix[pos.row][pos.col] = symbol;
    return OK;
}

char matrix_search(POS_S pos)
{
    return g_matrix[pos.row][pos.col];
}

void hideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void matrix_display()
{
    hideCursor();
    gotoxy(0, 0);

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", g_matrix[i][j]);
            if (j != (WIDTH - 1)) {
                printf("%c", ' ');
            }
        }
        printf("\r\n");
    }

    return;
}
