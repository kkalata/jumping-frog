#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <ncurses.h>

#include "constants.h"
#include "messages.h"

typedef struct
{
    WINDOW *window;
    int col_begin;
    int row_begin;
    int width;
    int height;
} SUBWINDOW;
