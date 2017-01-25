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
bool checkSurroundings(struct floe *ourFloe);
bool checkIfFree(struct floe *ourFloe, int axisIndex);
int checkHowManyFishes(struct floe *ourFloe);

struct floe* translateToFloe(int x, int y);

void runMovement(char* values[]);
void runPlacement(char* values[]);
int addFloeBias(struct floe *checkedFloe);

bool runInteractivePlacement(int x, int y);
bool runInteractiveMovement(int x ,int y);
//function to run interactive mode
void runInteractive();

void runTournament();

#endif //FISHES_ACTION_H
