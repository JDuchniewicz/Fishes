//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#include "action.h"

bool checkCoordinates(int x, int y){
    //if they are not valid then return false
    return true;
}
//checks how many fishes are there on the field we want to move on
int checkHowManyFishes(struct floe *ourFloe){
    int fishes = ourFloe->fishes;
    return fishes;
}

//checks whether there is a penguin on the field ...
bool checkPenguin(struct floe *Floe){
    return Floe->penguins ? true : false; // wee need to check whether nr of penguins on a floe is equal to 0
}

//places penguin
void placePenguin(int x, int y){
    return;
}

//checks whether they are valid
bool checkTargetCoordinates(int x, int y){
    return true;
}

bool checkValidMove(int x, int y){
    return true;
}

/*
void movement(struct floe *nextFloe){
    int nextX = nextFloe->x;
    int nextY = nextFloe->y;
    if(!checkPenguin(nextFloe)){//here we check next field for penguin presence
        printf("Cannot move penguin to coordinates %d , %d -> One already there", nextX, nextY);
        return;
    } else if(!checkTargetCoordinates(nextX, nextY)){
        printf("Cannot move penguin to coordinates %d , %d -> They are not valid", nextX, nextY);
        return;
    }  else if(!checkValidMove(nextX, nextY)){
        printf("Cannot move penguin to coordinates %d , %d -> Not valid move", nextX, nextY);
        return;
    }

    //here we move the penguin onto the desired field


}
*/
/*
void placement(struct floe *ourFloe){
    int x, y;
    scanf("%i %i", &x, &y);
    if (checkCoordinates(x, y) && checkHowManyFishes(ourFloe) == 1 && !checkPenguin(ourFloe)){
        placePenguin(x, y);
        ourFloe->penguins = 1; // we need to check which player's penguin we want to place here
    }
}
*/

void runPlacement(char* values){
    //open that file
        //dissasemble the char values - parameters of the program
        /*char pengArg[12];
        int pengMax, currPeng, i;

        strcpy(pengArg, argv[2]);

        for (i=0; i<9; i++) //we change every non-numerical character in "penguins=[x]" to 0,
            pengArg[i]='0'; //so that atoi can convert it to int leaving only x value

        pengMax = atoi(pengArg);
        readBrd(argv[3]); //reads the board from file
*/
    //check if we can place a penguin
        // if we can -> perform placement on the best field -> greedy algorithm
        //decrement number of penguins available and append penguin's coordinates to prevent cheating
    //else we exit and



}

void runMovement(char* values){
    //open that file
    //then we check whether we can perform any movement
        //we choose the best suited penguin for that job
        //if we can then we choose the best axis to move -> remember we can only specify axis to move
            //then we loop movement until we can move no more, the floes behind us disappear, and we collect all the fishes from the fields
            //we have been on
    //else we exit

}
