#include "jumping_frog.h"

CARS create_cars(SUBWINDOW *board, const char board_layout[])
{
    int road_lanes = 0;
    for (int i = 0; board_layout[i] != '\0'; i++)
    {
        road_lanes += board_layout[i] == '=';
    }

    CARS cars;

    cars.cars = malloc(road_lanes * sizeof(CAR));

    for (int row_i = 0, car_i = 0; board_layout[row_i] != '\0' && car_i < road_lanes; row_i++)
    {
        if (board_layout[row_i] == '=')
        {
            cars.cars[car_i].row = strlen(board_layout) - row_i - 1;
            cars.cars[car_i].front_col = car_i;
            cars.cars[car_i].direction = CAR_DIRECTION_RIGHT;
            cars.cars[car_i].type = CAR_TYPE_CAR;
            cars.cars[car_i].length = CAR_LENGTH_CAR;
            car_i++;
        }
    }

    cars.count = road_lanes;

    return cars;
}

CARS place_car(SUBWINDOW *board, CARS cars, int col_i, int row_i)
{
    for (int car_i = 0; car_i < cars.count; car_i++)
    {
        CAR car = cars.cars[car_i];
        if (car.row == row_i)
        {
            // check if car is at (row_i, col_i)
            if ((car.direction == CAR_DIRECTION_RIGHT && col_i > car.front_col - car.length && col_i <= car.front_col) || (car.direction == CAR_DIRECTION_LEFT && col_i >= car.front_col && col_i < car.front_col + car.length))
            {
                mvwaddch(board->window, row_i, col_i, '#');
            }
        }
    }
}

void move_cars(CARS *cars)
{
    for (int car_i = 0; car_i < cars->count; car_i++)
    {
        CAR *car = &cars->cars[car_i];
        switch (car->direction)
        {
        case CAR_DIRECTION_LEFT:
            car->front_col--;
            break;
        case CAR_DIRECTION_RIGHT:
            car->front_col++;
            break;
        }
    }
}
