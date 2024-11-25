#ifndef JUMPING_FROG_H
#define JUMPING_FROG_H

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

typedef struct {
    int row;
    int front_col;
    int direction;
    int type;
    int length;
} CAR;

typedef struct {
    CAR *cars;
    int count;
} CARS;

SUBWINDOW *create_subwindow(
    WINDOW *main_window,
    const int col_offset,
    const int row_offset,
    const int width,
    const int height);
void clear_window(WINDOW *window);

FROG *create_frog(const SUBWINDOW *board);
void move_frog(FROG *frog, const SUBWINDOW *board, const int key);

CARS create_cars(SUBWINDOW *board, const char board_layout[]);
CARS place_car(SUBWINDOW *board, CARS cars, int col_i, int row_i);
void move_cars(CARS *cars);

#endif
