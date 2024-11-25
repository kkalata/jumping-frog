#include "jumping_frog.h"

const char *GAME_TITLE[] = {
    "    #  #   #  #   #  #####  #  #   #  #####       #####  #####  #####  #####",
    "    #  #   #  ## ##  #   #  #  ##  #  #           #      #   #  #   #  #    ",
    "    #  #   #  # # #  #####  #  # # #  #  ##       ###    #####  #   #  #  ##",
    "#   #  #   #  #   #  #      #  #  ##  #   #       #      #  #   #   #  #   #",
    "#####  #####  #   #  #      #  #   #  #####       #      #   #  #####  #####"};

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

void print_stats(SUBWINDOW *stat_section, const FROG *frog)
{
    clear_window(stat_section->window);
    mvwprintw(stat_section->window, 1, 1, "Pos: (%d, %d)", frog->row, frog->col);
    if (frog->row == 0)
    {
        mvwprintw(stat_section->window, 2, 1, "You won!");
    }
}

void print_board(SUBWINDOW *board, const char board_layout[], const FROG *frog, const CARS cars)
{
    for (int row_i = board->height - 1; row_i >= 0; row_i--)
    {
        for (int col_i = 0; col_i < board->width; col_i++)
        {
            if (row_i == frog->row && col_i == frog->col)
            {
                wattron(board->window, COLOR_PAIR(frog->color.alive));
                mvwaddch(board->window, row_i, col_i, frog->symbol);
            }
            else
            {
                switch (board_layout[board->height - row_i - 1])
                {
                case '#':
                    wattron(board->window, COLOR_PAIR(SAND_COLOR));
                    break;
                case '=':
                    wattron(board->window, COLOR_PAIR(ROAD_COLOR));
                    break;
                }
                mvwaddch(board->window, row_i, col_i, ' ');
                place_car(board, cars, col_i, row_i);
            }
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

    SUBWINDOW *board_section = create_subwindow(
        window,
        (COLS - STAT_SECTION_WIDTH) / 2,
        (LINES - MIN_HEIGHT) / 2,
        BOARD_WIDTH,
        MIN_HEIGHT);

    const char board_layout[] = "###===##=#===###==#==###";

    FROG *frog = create_frog(board_section);
    CARS cars = create_cars(board_section, board_layout);

    int win = 0;
    halfdelay(2);
    while (!win)
    {
        if (frog->row == 0)
        {
            win = 1;
            cbreak();
        }
        
        print_stats(stat_section, frog);
        box(stat_section->window, 0, 0);
        wrefresh(stat_section->window);

        print_board(board_section, board_layout, frog, cars);
        wrefresh(board_section->window);

        int key = getch();
        move_frog(frog, board_section, key);

        move_cars(&cars);        
    }
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
    noecho();
    curs_set(0);
    start_color();
    init_pair(GAME_TITLE_COLOR, COLOR_GREEN, COLOR_BLACK);
    init_pair(GAME_TITLE_COLOR_REVERSED, COLOR_BLACK, COLOR_GREEN);
    init_pair(SAND_COLOR, COLOR_BLACK, COLOR_YELLOW);
    init_pair(ROAD_COLOR, COLOR_WHITE, COLOR_BLACK);
    init_pair(ALIVE_FROG_COLOR, COLOR_BLACK, COLOR_GREEN);
    init_pair(DEAD_FROG_COLOR, COLOR_GREEN, COLOR_RED);
    keypad(window, 1);

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
