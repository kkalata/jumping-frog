#include <stdio.h>
#include <ncurses.h>

#define MIN_WIDTH 80
#define MIN_HEIGHT 24

#define WINDOW_TOO_SMALL_MESSAGE "Your window is too small."

int window_too_small()
{
    return (COLS < MIN_WIDTH) || (LINES < MIN_HEIGHT);
}

int main()
{
    initscr();

    if (window_too_small())
    {
        endwin();
        printf(WINDOW_TOO_SMALL_MESSAGE);
        return 1;
    }

    endwin();
    return 0;
}
