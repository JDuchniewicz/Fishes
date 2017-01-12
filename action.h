//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#ifndef FISHES_ACTION_H
#define FISHES_ACTION_H
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "io.h"

struct vector{
    int x;
    int y;
};



bool checkCoordinates(int x, int y);
void placePenguin(int x, int y);
bool checkTargetCoordinates(int x, int y);
bool checkValidMove(int x, int y);
bool checkPenguin(struct floe *Floe);
bool checkIfIsAFloe();
int checkHowManyFishes(struct floe *ourFloe);

struct floe* translateToFloe(int x, int y);

void runMovement(char* values[]);
void runPlacement(char* values[]);

bool runInteractivePlacement(int x, int y);
//void runInteractiveMovement(//vector variable?);
//function to run interactive mode
void runInteractive();

#endif //FISHES_ACTION_H
