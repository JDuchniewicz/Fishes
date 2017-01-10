//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#ifndef FISHES_ACTION_H
#define FISHES_ACTION_H
#include <stdbool.h>
#include <stdio.h>

#include "map.h"
#include "io.h"

bool checkCoordinates(int x, int y);
void placePenguin(int x, int y);
bool checkTargetCoordinates(int x, int y);
bool checkValidMove(int x, int y);
bool checkPenguin(struct floe *Floe);
bool checkIfIsAFloe();
int checkHowManyFishes(struct floe *ourFloe);
void runMovement(char* fileName);
void runPlacement(char* fileName);


#endif //FISHES_ACTION_H
