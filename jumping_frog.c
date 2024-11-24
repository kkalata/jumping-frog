#include "jumping_frog.h"

const char *GAME_TITLE[] = {
    "    #  #   #  #   #  #####  #  #   #  #####       #####  #####  #####  #####",
    "    #  #   #  ## ##  #   #  #  ##  #  #           #      #   #  #   #  #    ",
    "    #  #   #  # # #  #####  #  # # #  #  ##       ###    #####  #   #  #  ##",
    "#   #  #   #  #   #  #      #  #  ##  #   #       #      #  #   #   #  #   #",
    "#####  #####  #   #  #      #  #   #  #####       #      #   #  #####  #####"};

SUBWINDOW *create_subwindow(
    WINDOW *main_window,
    int col_begin,
    int row_begin,
    int width,
    int height)
{
    SUBWINDOW *subwindow = (SUBWINDOW *)malloc(sizeof(SUBWINDOW));
    subwindow->window = subwin(
        main_window,
        height,
        width,
        row_begin,
        col_begin);

    subwindow->col_begin = col_begin;
    subwindow->row_begin = row_begin;
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

void print_game_title(WINDOW *window)
{
    const int GAME_TITLE_HEIGHT = sizeof(GAME_TITLE) / sizeof(GAME_TITLE[0]);

    SUBWINDOW *game_title_section = create_subwindow(
        window,
        (COLS - strlen(GAME_TITLE[0])) / 2,
        (LINES - START_MESSAGE_HEIGHT - GAME_TITLE_HEIGHT) / 2,
        strlen(GAME_TITLE[0]),
        GAME_TITLE_HEIGHT);

    for (int row_i = 0; row_i < game_title_section->height; row_i++)
    {
        for (int col_i = 0; col_i < game_title_section->width; col_i++)
        {
            if (GAME_TITLE[row_i][col_i] == '#')
            {
                wattron(game_title_section->window, COLOR_PAIR(GAME_TITLE_COLOR_REVERSED));
            }
            else
            {
                wattron(game_title_section->window, COLOR_PAIR(GAME_TITLE_COLOR));
            }
            move(row_i, col_i);
            waddch(game_title_section->window, ' ');
        }
    }

    delwin(game_title_section->window);
    free(game_title_section);
}

void print_start_message(WINDOW *window)
{
    move(LINES - START_MESSAGE_HEIGHT + 1,
         (COLS - strlen(MESSAGE_PRESS_TO_START)) / 2);
    waddstr(window, MESSAGE_PRESS_TO_START);
}

void init_level(SUBWINDOW *board)
{
    const char objects[] = "###===##=#===###==#==###";
    for (int row_i = board->height - 1; row_i >= 0; row_i--)
    {
        for (int col_i = 0; col_i < board->width; col_i++)
        {
            switch (objects[row_i])
            {
            case '#':
                wattron(board->window, COLOR_PAIR(SAND_COLOR));
                break;
            case '=':
                wattron(board->window, COLOR_PAIR(ROAD_COLOR));
                break;
            }
            move(row_i, col_i);
            waddch(board->window, ' ');
        }
    }
}

void start_game(WINDOW *window)
{
    print_game_title(window);
    print_start_message(window);
    getch();
    clear_window(window);

    SUBWINDOW *stat_section = create_subwindow(
        window,
        (COLS - MIN_WIDTH) / 2,
        (LINES - MIN_HEIGHT) / 2,
        STAT_SECTION_WIDTH,
        MIN_HEIGHT);
    box(stat_section->window, 0, 0);
    wrefresh(stat_section->window);

    SUBWINDOW *board_section = create_subwindow(
        window,
        (COLS - STAT_SECTION_WIDTH) / 2,
        (LINES - MIN_HEIGHT) / 2,
        36, MIN_HEIGHT);
    init_level(board_section);
    wrefresh(board_section->window);
    getch();

    delwin(stat_section->window);
    delwin(board_section->window);
    free(stat_section);
    free(board_section);
}

int window_too_small()
{
    return (COLS < MIN_WIDTH) || (LINES < MIN_HEIGHT);
}

int main()
{
    WINDOW *window = initscr();
    curs_set(0);
    start_color();
    init_pair(GAME_TITLE_COLOR, COLOR_GREEN, COLOR_BLACK);
    init_pair(GAME_TITLE_COLOR_REVERSED, COLOR_BLACK, COLOR_GREEN);
    init_pair(SAND_COLOR, COLOR_BLACK, COLOR_YELLOW);
    init_pair(ROAD_COLOR, COLOR_WHITE, COLOR_BLACK);

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
