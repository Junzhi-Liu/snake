#include "string.h"
#include "conio.h"
#include <windows.h>
#include "snake_common.h"

void input_response()
{
    if (kbhit()) {
        char cmd0 = getch(); //distinguish between getch() and getchar()
        char cmd1 = getch();
        char cmd = cmd0 + cmd1;
        if (((cmd == RIGHT) && (*(snake_get_dir()) == LEFT)) ||
            ((cmd == LEFT) && (*(snake_get_dir()) == RIGHT)) ||
            ((cmd == UP) && (*(snake_get_dir()) == DOWN)) ||
            ((cmd == DOWN) && (*(snake_get_dir()) == UP))) {
            //invalid
        } else {
            *(snake_get_dir()) = cmd;
        }
    }
    return;
}

void run_snake()
{
    matrix_init();
    snake_ll_init();
    apple_update();

    uint run_state = OK;
    while (run_state == OK) {
        matrix_display();
        Sleep(600); //ms
        input_response();
        run_state = snake_move();
    }
    matrix_display();
    if (run_state == WIN) {
        printf("\r\nYOU WIN!\r\n");
    } else {
        printf("\r\nGAME OVER!\r\n");
    }
    printf("press R to restart...\r\n");

    snake_ll_destroy();
    return;
}

int main()
{
    run_snake();
    char input = getch();
    while ((input == 'R') || (input == 'r')) {
        run_snake();
        input = getch();
    }

    return OK;
}
