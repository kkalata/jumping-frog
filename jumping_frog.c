#include "jumping_frog.h"

const char *GAME_TITLE[] = {
    "    #  #   #  #   #  #####  #  #   #  #####       #####  #####  #####  #####",
    "    #  #   #  ## ##  #   #  #  ##  #  #           #      #   #  #   #  #    ",
    "    #  #   #  # # #  #####  #  # # #  #  ##       ###    #####  #   #  #  ##",
    "#   #  #   #  #   #  #      #  #  ##  #   #       #      #  #   #   #  #   #",
    "#####  #####  #   #  #      #  #   #  #####       #      #   #  #####  #####"};

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

void init_level(SUBWINDOW *board, const FROG *frog)
{
    const char objects[] = "###===##=#===###==#==###";
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
                switch (objects[board->height - row_i - 1])
                {
                case '#':
                    wattron(board->window, COLOR_PAIR(SAND_COLOR));
                    break;
                case '=':
                    wattron(board->window, COLOR_PAIR(ROAD_COLOR));
                    break;
                }
                mvwaddch(board->window, row_i, col_i, ' ');
            }
        }
    }
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
        BOARD_WIDTH,
        MIN_HEIGHT);

    FROG *frog = create_frog(board_section);
    nodelay(window, 1);
    while (1)
    {
        init_level(board_section, frog);
        wrefresh(board_section->window);
        int key = getch();
        move_frog(frog, board_section, key);
    }

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
