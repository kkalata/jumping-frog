#include <stdio.h>
#include <string.h>

#include <ncurses.h>

#include "messages.h"

#define MIN_WIDTH 80
#define MIN_HEIGHT 24

#define START_MESSAGE_HEIGHT 3

const char* GAME_TITLE[] = {
    "    #  #   #  #   #  #####  #  #   #  #####       #####  #####  #####  #####",
    "    #  #   #  ## ##  #   #  #  ##  #  #           #      #   #  #   #  #    ",
    "    #  #   #  # # #  #####  #  # # #  #  ##       ###    #####  #   #  #  ##",
    "#   #  #   #  #   #  #      #  #  ##  #   #       #      #  #   #   #  #   #",
    "#####  #####  #   #  #      #  #   #  #####       #      #   #  #####  #####"
};

void print_game_title(WINDOW* window)
{
    const int GAME_TITLE_HEIGHT = sizeof(GAME_TITLE) / sizeof(GAME_TITLE[0]);
    int col_begin = (COLS - strlen(GAME_TITLE[0])) / 2;
    int row_begin = (LINES - START_MESSAGE_HEIGHT - GAME_TITLE_HEIGHT) / 2;
    for (int row_i = 0; row_i < GAME_TITLE_HEIGHT; row_i++)
    {
        move(row_i + row_begin, col_begin);
        waddstr(window, GAME_TITLE[row_i]);
    }
}

void print_start_message(WINDOW* window)
{
    move(LINES - START_MESSAGE_HEIGHT + 1, (COLS - strlen(MESSAGE_PRESS_TO_START)) / 2);
    waddstr(window, MESSAGE_PRESS_TO_START);
}

void start_game(WINDOW* window)
{
    print_game_title(window);
    print_start_message(window);
    getch();
}

int window_too_small()
{
    return (COLS < MIN_WIDTH) || (LINES < MIN_HEIGHT);
}

int main()
{
    WINDOW* window = initscr();

    if (window_too_small())
    {
        endwin();
        printf(MESSAGE_WINDOW_TOO_SMALL);
        return 1;
    }

    start_game(window);

    endwin();
    return 0;
}
