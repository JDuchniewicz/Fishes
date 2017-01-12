//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#ifndef FISHES_MAP_H
#define FISHES_MAP_H
#include <stdio.h>
#include <stdbool.h> //make sure we don't include it too many times

/*
 * This file is responsible fo printing out the map for the user and filling it with all required data,
 * The map displays only borders of the floe and: nr of fish on the floe, nr of player whose penguin is on the floe
 * the empty floe i.e. '00' means that it is not existent, thus cannot be moved on.
 */

struct floe //struct from which we create our board, contains nr of fishes and penguins on it -> single tile, and coordinates
{
    int x;
    int y;
    int fishes;
    int penguins;
    bool isFloe;
};

struct floe floes[256];

//Denotes where the penguin currently is, value of (-1,-1) denotes it is not yet placed
struct penguin{
    int x;
    int y;
};

struct penguin playerOnePenguins[100];
struct penguin playerTwoPenguins[100];

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
    int player1RemainingPeng;
    int player2RemainingPeng;
};

struct GameData gameData; //ensuring it only once instantiated



void printFirstUpper(int count);
void printBarsAndFillNumbers(int count, struct floe floes[], int index);
void printMidBarriers(int count);
void printMap(struct floe floes[],int, int);

#endif //FISHES_MAP_H
