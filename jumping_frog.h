#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <ncurses.h>

#include "constants.h"
#include "messages.h"

typedef struct
{
    WINDOW *window;
    int col_offset;
    int row_offset;
    int width;
    int height;
} SUBWINDOW;

typedef struct {
    int col;
    int row;
    char symbol;
    struct {
        int alive;
        int dead;
    } color;
} FROG;
