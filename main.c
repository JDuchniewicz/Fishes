//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#include <string.h>
#include "io.h"
#include "action.h"
#include "map.h"

/* THIS IS OUR MAIN FILE
 * Here we perform initial setup and the game Loop Operations
 * and finally evaluate who has won
 * */

//TODO distinguish between interactive and automatic game modes with preprocessor directives
//TODO also add reading from command line phase, penguinsNr, inputname, outputname


int main(int argc, char* argv[]){
    //Declare and define required game loop variables
    int NumberOfPlayers = 0;
    int Player1ID = 2137;
    int Player2ID = 5555;
    int Player1Score = 0;
    int Player2Score = 0;
    int PenguinCount = 0;
    FILE* loadFileName;
    FILE* saveFileName;
    bool isGameWon = false;
    bool isPhaseMovement = false;
    bool isFirstLoad = true;

    int a, sizeX = 0, sizeY = 0;
    FILE* currentOpenedFile = NULL;
    int ap[10];

    char fileFormatMock[15] = "fileFormatMock";
    struct floe floes[sizeX*sizeY];
    struct floe* floePointer;
    int floeIndex = 0;



    //PERFORM FIRST LOAD
    currentOpenedFile = openFile(fileFormatMock, 'r');
    readFile(currentOpenedFile);
    //TODO: read all other values and load them into our project
    fclose(currentOpenedFile);

    //THEN WE GO ON WITH OUR GAME LOOP
    printMap(ap, 10, 10);
    /*
    printf("Enter game mode choice: 0 for placement, 1 for movement");
    scanf("%d", &a);
    if(a == 1){
        isPhaseMovement = true;
     else if(a == 0){
        isPhaseMovement = false;
    }
    //readFile();
    if (!isPhaseMovement){
        placement();
    } else {
        movement();
    }

     //TODO:HERE WE WRITE AUTOMATIC MODE


     */ //interactive mode here
    //writeFile();
///This is our main game loop
    while(!isGameWon){
        if(isFirstLoad){
            floeIndex = 0; //TODO we need to ask whether the num of penguins after num of players is penguin per player or total penguin nr
            NumberOfPlayers = getOneCharAsInt(currentOpenedFile);
            PenguinCount = getOneCharAsInt(currentOpenedFile);
            Player1ID = getIntBySize(currentOpenedFile);
            jumpToNextLine(currentOpenedFile);
            jumpToNextLine(currentOpenedFile);
            Player2ID = getIntBySize(currentOpenedFile);
            jumpToNextLine(currentOpenedFile);
            jumpToNextLine(currentOpenedFile);
            jumpToNextLine(currentOpenedFile);
            jumpToNextLine(currentOpenedFile);
            sizeX = getIntBySize(currentOpenedFile);
            sizeY = getIntBySize(currentOpenedFile);
            jumpToNextLine(currentOpenedFile);
            jumpToNextLine(currentOpenedFile);
            while(floeIndex != (sizeX*sizeY)){
                floePointer = &floes[floeIndex];
                readOneFloe(currentOpenedFile, floePointer);
                floes[floeIndex] = *floePointer;
                floeIndex +=2;
            }








            //perform al loading operations - read everything from the first paragraph of input file
            isFirstLoad = false;
        }
        //here we perform our all operations on the second part of input file, and we keep on updating the score of each player in the first part


        //perform placement and movement actions until end of player's penguins/ then change player


        //if sth then the game is won and we exit game and present brief statistics of the game
        isGameWon = true;
    }
    //PRINTF GAME STATS
    return 0;

}
