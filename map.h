//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#ifndef FISHES_MAP_H
#define FISHES_MAP_H
#include <stdio.h> //make sure we don't include it too many times

struct floe //struct from which we create our board, contains nr of fishes and penguins on it -> single tile, and coordinates
{
    int x;
    int y;
    int fishes;
    int penguins;
};

void printFirstUpper(int count);
void printBarsAndFillNumbers(int count, struct floe floes[], int index);
void printMidBarriers(int count);
void printMap(struct floe floes[],int, int);


#endif //FISHES_MAP_H
