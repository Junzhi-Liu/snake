#include "time.h"
#include "snake_common.h"

void apple_update()
{
    time_t t;
    srand((unsigned) time(&t));

    POS_S pos = { 0 };
    pos.row = rand() % (HEIGHT - 1) + 1;
    pos.col = rand() % (WIDTH - 1) + 1;

    while (matrix_search(pos) != ' ') {
        pos.col += 1;
        if (pos.col >= WIDTH) {
            pos.col = 1;
            pos.row += 1;
            if (pos.row >= HEIGHT) {
                pos.row = 1;
            }
        }
    }

    matrix_update(pos, '%');
}
