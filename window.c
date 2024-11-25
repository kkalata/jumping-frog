#include "jumping_frog.h"

SUBWINDOW *create_subwindow(
    WINDOW *main_window,
    const int col_offset,
    const int row_offset,
    const int width,
    const int height)
{
    SUBWINDOW *subwindow = (SUBWINDOW *)malloc(sizeof(SUBWINDOW));
    subwindow->window = subwin(
        main_window,
        height,
        width,
        row_offset,
        col_offset);

    subwindow->col_offset = col_offset;
    subwindow->row_offset = row_offset;
    subwindow->width = width;
    subwindow->height = height;

    return subwindow;
}

void clear_window(WINDOW *window)
{
    for (int row_i = 0; row_i < LINES; row_i++)
    {
        for (int col_i = 0; col_i < COLS; col_i++)
        {
            mvwprintw(window, row_i, col_i, " ");
        }
    }
}
