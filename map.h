//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#ifndef FISHES_MAP_H
#define FISHES_MAP_H
#include <stdio.h>
#include <stdbool.h> //make sure we don't include it too many times

struct floe //struct from which we create our board, contains nr of fishes and penguins on it -> single tile, and coordinates
{
    int x;
    int y;
    int fishes;
    int penguins;
};

struct floe floes[256];

struct floeMap{
    int x;
    int y;
    bool isFloe;
};

struct floeMap floeMap[256];

//GameData struct is our Singleton, it cointains all the required info in just one instance
struct GameData{
    int PlayerNum;
    int PenguinNum;
    int Player1ID;
    int Player2ID;
    int SizeX;
    int SizeY;
    int score1;
    int score2;
};
void printFirstUpper(int count);
void printBarsAndFillNumbers(int count, struct floe floes[], int index);
void printMidBarriers(int count);
void printMap(struct floe floes[],int, int);


#endif //FISHES_MAP_H
