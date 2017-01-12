//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#include "action.h"

//Don't know why but it must be defined inside C file (some, linking logic)
struct vector coords[6] = { {1, -1}, {2, 0}, {1, 1}, {-1, 1}, {-2, 0}, {-1, -1}};

//checks whether it is a floe
bool checkCoordinates(int x, int y){
    int i = 0;
    //we need to check whether we even need to map the floes bcs maybe i am not loading anything else
    for(i = 0; i < (gameData.SizeX*gameData.SizeY); i++){
        if(x==floes[i].x){
            if(y==floes[i].y){
                if(floes[i].isFloe){
                    return true;
                }
            }
        }
    }
    return false;
}
//checks how many fishes are there on the field we want to move on
int checkHowManyFishes(struct floe *ourFloe){
    int fishes = ourFloe->fishes;
    return fishes;
}

//checks whether there is a penguin on the field
bool checkPenguin(struct floe *Floe){
    return Floe->penguins ? true : false; // we need to check whether nr of penguins on a floe is equal to 0
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

struct floe* translateToFloe(int x, int y){
    struct floe* floetrans;
    int i =0;
    for(i = 0; i <(gameData.SizeX*gameData.SizeY); i++){
        if(x == floes[i].x && y == floes[i].y){
            return floetrans = &floes[i];
        }
    }
    return floetrans;
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

void runPlacement(char* values[]){
    //open that file //we get the name of the file from the console!!!, input and output both
    int i = 0;
    char* inputFileName[12], outputFileName[12], penChar[12];
    strcpy(inputFileName,values[3]);
    strcpy(outputFileName,values[4]);
    strcpy(penChar, values[2]);
    for (i=0; i<9; i++) //we change every non-numerical character in "penguins=[x]" to 0,
        penChar[i]='0'; //so that atoi can convert it to int leaving only x value

    gameData.PenguinNum = atoi(penChar);
    FILE* inputFile = fopen(inputFile, "r");
    FILE* outputFile = fopen(outputFile, "w");

    //check if we can place a penguin
        // if we can -> perform placement on the best field -> greedy algorithm
        //decrement number of penguins available and append penguin's coordinates to prevent cheating
    //else we exit and save file



}

void runMovement(char* values[]){
    //open that file //we get the name of the file form the console!!!, input and output both
    char* inputFileName[12], outputFileName[12];
    strcpy(inputFileName,values[3]);
    strcpy(outputFileName,values[4]);

    FILE* inputFile = fopen(inputFile, "r");
    FILE* outputFile = fopen(outputFile, "w");


    //then we check whether we can perform any movement
        //we choose the best suited penguin for that job
        //if we can then we choose the best axis to move -> remember we can only specify axis to move
            //then we loop movement until we can move no more, the floes behind us disappear, and we collect all the fishes from the fields
            //we have been on
    //else we exit
    //save file

}

//TODO: Check this works
bool runInteractivePlacement(int x, int y){
    struct floe* floeptr;
    int nr = 0;
    if(!checkCoordinates(x,y)){ return false; }
    floeptr = translateToFloe(x,y);
    if((nr=checkHowManyFishes(floeptr))!=1){return false; }
    if(checkPenguin(floeptr)){ return false;}
    return true;
}

void runInteractive(){ //add file name to read
    //VARIABLES
    char* fileName = "fileFormatMock.txt"; //we fix it to a particular file or create two, one for reading and one for writing
    FILE* fp = openFile(fileName, "r+");

    int destX = 0, destY = 0, choice = 0, penPlacementCount = 0;

    bool isOver = false;

    struct floe* floePointer = floes;


    struct GameData* gdPointer = &gameData;

    //DISPLAY INTERACTIVE WELCOME SCREEN
    //give user choice exit or play
    //maybe difficulty choice later?
    //or human vs ai mode?

    //FIRST
    readFile(fp,gdPointer,floePointer);
    printMap(floes, gameData.SizeX, gameData.SizeY);

    //PLACEMENT
    //ask user for placement coords and perform logic
    while(gameData.player1RemainingPeng > 0){
        //READ FILE
        fp = freopen(fileName,"r",fp);
        //ask user for data
        printf("\nMovement mode: \n choose the coordinates of the floe you would like to place your penguin on.\n");
        printf("x: ");
        scanf("%d", &destX);
        printf("y: ");
        scanf("%d", &destY);
        //ensure we can place there
        if(runInteractivePlacement(destX,destY)){
            //place penguin
            playerOnePenguins[penPlacementCount].x = destX;
            playerOnePenguins[penPlacementCount].y = destY;
            floePointer->penguins = 1;
            gameData.player1RemainingPeng--;

        }
        //SAVE FILE
        fp = freopen(fileName,"w",fp);
        writeFile(fp,gdPointer,floePointer);

        //TODO: Debug closely to be 100 percent sure
    }
    /*
    //MOVEMENT
    while(!isOver){
        //READ FILE

        //ask user to tell us which penguin to move
        //display the list of penguins with their corresponding coordinates -> this list will later be used as a reference for saving it into
        //ask user for movement coords

        //ensure we can place there
        //if not then exit game

        //SAVE FILE
    }
*/
    fp = freopen(fileName,"w",fp);
    writeFile(fp, gdPointer,floePointer);
    fclose(fp);
    //GAME OVER SCREEN + STATS
    return;
}
