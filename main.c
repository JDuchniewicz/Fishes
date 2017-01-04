//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#include <string.h>
#include <stdlib.h>
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

    int choice = 0, x= 0, y =0, i = 0, j = 0, status = 0;

    //the variables we need to track player scores etc
    int NumberOfPlayers = 0;
    int Player1ID = 2137;
    int Player2ID = 5555;
    int Player1Score = 0;
    int Player2Score = 0;
    int PenguinCount = 0;

    //file reading variables
    FILE* loadFileName;
    FILE* saveFileName;
    FILE* currentOpenedFile = NULL;

    //bools of state
    bool isGameWon = false;
    bool isPhaseMovement = false;
    bool isFirstLoad = true;

    //map size variables
    int a, sizeX = 0, sizeY = 0, iterX = 0, iterY = 0;

    char fileFormatMock[20] = "fileFormatMock.txt";

    //floe variables
    struct floe floes[256]; //TODO:Check whether we need such a big array
    struct floe* floePointer;
    int floeIndex = 0, floeCount = 0;
    struct floeMap floeMap[256];


    //PERFORM FIRST LOAD

    //readFile(currentOpenedFile);
    //TODO: read all other values and load them into our project
   // fclose(currentOpenedFile);

    //THEN WE GO ON WITH OUR GAME LOOP
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


     */
    //interactive mode here
    //writeFile();
///This is our main game loop
    while(!isGameWon){
        //perform al loading operations - read everything from the first paragraph of input file
        if(isFirstLoad){
            currentOpenedFile = openFile(fileFormatMock, "r"); //TODO: Remove the fileformatmock name
            floeIndex = 0; //TODO we need to ask whether the num of penguins after num of players is penguin per player or total penguin nr
            NumberOfPlayers = getOneCharAsInt(currentOpenedFile);
            printf("%d", NumberOfPlayers);  //TODO check why it's not printing out
            PenguinCount = getOneCharAsInt(currentOpenedFile); //TODO: check why it's not working, endless loop
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
            while(floeIndex != (sizeX*sizeY)){ // here we fill the floemap with values 1 by 1
                floePointer = &floes[floeIndex];
                status = readOneFloe(currentOpenedFile, floePointer, status); //we monitor state of loading with returning status variable
                if(status == EOF){ //we return EOF to break all continuation of floe loading
                    break;
                }
                floes[floeIndex] = *floePointer;
                floeCount++;
                floeIndex++;  //increase index only by 1 because we want them ordered
            }
            //TODO:we need to check whether it will compute the good amount of times

            while(iterY!= sizeY){
                iterX = 0;
                while(iterX != sizeX){
                    floeMap[sizeX*iterY + iterX].x = iterX;
                    floeMap[sizeX*iterY + iterX].y = iterY;
                    for(i = 0; i < floeCount; i++){
                        floePointer = &floes[i];
                        x = floePointer->x;
                        y = floePointer->y;
                        if(x==iterX && y == iterY){
                            floeMap[sizeX*iterY + iterX].isFloe = true;
                        }
                    }
                    iterX++;
                }
                iterY++;
            }
            isFirstLoad = false;
        }
        printf("Welcome to Our Fishes Game Wanderer!\n");
        printf("Please press 1 to start, press 2 to exit the game\n");
        scanf("%d", &choice);
        if(choice == 1){
            //print map
                //give choices for placement
            printf("Please enter coordinates for placement of the penguin\n");
            printf("x: ");
            scanf("%d", &x);
            printf("y: ");
            scanf("%d", &y);
            //check the coordinates
            //beforehand translate them into a particular floe
            //we simply multiply the y*sizeY+x and check whether the flag for isFloe is true -> this is our isFloe validation mechanism
        } else {
            exit(1);
        }
        //here we perform our all operations on the second part of input file, and we keep on updating the score of each player in the first part


        //perform placement and movement actions until end of player's penguins/ then change player


        //if sth then the game is won and we exit game and present brief statistics of the game
        isGameWon = true;
    }
    //PRINTF GAME STATS
    return 0;

}
