//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#ifndef FISHES_ACTION_H
#define FISHES_ACTION_H
#include <stdbool.h>
#include <stdio.h>

#include "map.h"

bool checkCoordinates(int x, int y);
void placePenguin(int x, int y);
bool checkTargetCoordinates(int x, int y);
bool checkValidMove(int x, int y);
bool checkPenguin(struct floe *Floe);
int checkHowManyFishes(struct floe *ourFloe);
void movement(struct floe *nextFloe);
void placement(struct floe *ourFloe);

#endif //FISHES_ACTION_H
