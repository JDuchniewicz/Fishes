//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#ifndef FISHES_ACTION_H
#define FISHES_ACTION_H
#include <stdbool.h>
#include <stdio.h>

bool check_coordinates(int x, int y);
int check_how_many_fishes(int x, int y);
bool check_penguin(int x, int y);
void place_penguin(int x, int y);
bool check_target_coordinates(int x, int y);
bool check_valid_move(int x, int y);
void movement();
void placement();

#endif //FISHES_ACTION_H
