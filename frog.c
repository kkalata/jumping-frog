#include "jumping_frog.h"

FROG *create_frog(const SUBWINDOW *board)
{
    FROG *frog = (FROG *)malloc(sizeof(FROG));

    frog->col = board->width / 2 - 1;
    frog->row = board->height - 1;
    frog->symbol = '"';
    frog->color.alive = ALIVE_FROG_COLOR;
    frog->color.dead = DEAD_FROG_COLOR;

    return frog;
}

void move_frog(FROG *frog, const SUBWINDOW *board, const int key)
{
    switch (key)
    {
    case KEY_UP:
        if (frog->row - 1 >= 0)
        {
            frog->row -= 1;
        }
        break;
    case KEY_DOWN:
        if (frog->row + 1 < board->height)
        {
            frog->row += 1;
        }
        break;
    case KEY_LEFT:
        if (frog->col - 1 >= 0)
        {
            frog->col -= 1;
        }
        break;
    case KEY_RIGHT:
        if (frog->col + 1 < board->width)
        {
            frog->col += 1;
        }
        break;
    }
}
