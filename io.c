//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#include "io.h"

FILE* openFile(char* name, char *mode){
    FILE* fp = fopen(name, mode);
    if(!fp){
        printf("Cannot open file\n");
    };
    return fp;
}

void writeFile(FILE* file){



}
void readFile(FILE* file, struct GameData* data, struct floe* floeptr) {
    int status = 0, floeIndex = 0, floeCount = 0;
    data->PlayerNum = getOneCharAsInt(file);
    data->PenguinNum = getOneCharAsInt(file);
    //TODO we need to ask whether the num of penguins after num of players is penguin per player or total penguin nr
    // printf("%d", NumberOfPlayers);  //TODO check why it's not printing out
    // TODO: check why it's not working, endless loop
    data->Player1ID = getIntBySize(file);
    jumpToNextLine(file);
    data->Player1ID = getIntBySize(file);
    jumpToNextLine(file);
    jumpToNextLine(file);
    data->SizeX = getIntBySize(file);
    data->SizeY = getIntBySize(file);
    jumpToNextLine(file);
    while (floeIndex != (data->SizeX * data->SizeY)) { // here we fill the floemap with values 1 by 1
        floeptr = &floes[floeIndex];
        status = readOneFloe(file, floeptr, status); //we monitor state of loading with returning status variable
        if (status == EOF) { //we return EOF to break all continuation of floe loading
            break;
        }
        floes[floeIndex] = *floeptr;
        floeCount++;
        floeIndex++;  //increase index only by 1 because we want them ordered
    }
    //TODO:we need to check whether it will compute the good amount of times
//This function loops through global floeMap and returns whether a particular (x,y) is a floe and saves it
     MapFloes(data,floeptr,floeCount);

}

void MapFloes(struct GameData* gameDataForMap, struct floe* floeptr, int floeCount){
    int iterY = 0, iterX = 0, x = 0, y = 0, i = 0;
    while (iterY != gameDataForMap->SizeY) {
        iterX = 0;
        while (iterX != gameDataForMap->SizeX) {
            floeMap[gameDataForMap->SizeX * iterY + iterX].x = iterX;
            floeMap[gameDataForMap->SizeX * iterY + iterX].y = iterY;
            for (i = 0; i < floeCount; i++) {
                floeptr = &floes[i];
                x = floeptr->x;
                y = floeptr->y;
                if (x == iterX && y == iterY) {
                    floeMap[gameDataForMap->SizeX * iterY + iterX].isFloe = true;
                }
            }
            iterX++;
        }
        iterY++;

    }
}
//Gets one char from input file and returns it
int getOneCharAsInt(FILE* file){
    int c = 0;
  do{
      c = getc(file);
      if(c==EOF){
          return EOF; //we return EOF to break all continuation
      }
  } while(c <= 48 || c >= 57);
    return c - '0';
}

//Gets as many chars as it can until it meets ; : \n
int getIntBySize(FILE *file){
    int ret = 0 , i = 0;
    char content[5] = "";
    char c;
    while ((c = fgetc(file) != EOF)){
        if(c == ':' || c == ';' || c == '\n' ){
            sscanf(content, "%d", &ret);
            return ret;
        } else {
            content[i] = c;
            i++;
        }
    }
    return EOF; //we return EOF to break all continuation
}

int readOneFloe(FILE* file, struct floe* oneFloe, int status){
    int x = 0, y = 0, fishes = 0, penguins = 0;
    x = getIntBySize(file);
    y = getIntBySize(file);
    fishes = getOneCharAsInt(file);
    penguins = getOneCharAsInt(file);
    if( x == EOF || y == EOF || fishes == EOF || penguins == EOF){
        status = EOF; //we return EOF status to break all continuation
        return status;
    }
    oneFloe->x = x;
    oneFloe->y = y;
    oneFloe->fishes = fishes;
    oneFloe->penguins = penguins;
    return 1;
}

//jumps to next line in current file
void jumpToNextLine(FILE* file){
    int c;
    do {
        c = fgetc(file);
    } while (c != '\n');
    return;
}

void runInteractive(){
    //VARIABLES
    char* fileName = "fileFormatMock.txt";
    FILE* fp = openFile(fileName, "r+");

    bool isOver = false;

    struct floe* floePointer = floes;

    struct GameData gameData;
    struct GameData* gdPointer = &gameData;

    //FIRST READ
    readFile(fp,gdPointer,floePointer);

    //PLACEMENT
        //ask user for placement coords and perform logic
    while(gameData.PenguinNum != 0){
        //READ FILE
        readFile(fp,gdPointer,floePointer);

        //ask user for data
        //ensure we can place there
            //if yes -> change the floe's data and append penguin's coordinates to an array holding penguins locations



        //SAVE FILE
    }
    //MOVEMENT
    //ask user to tell us which penguin to move
        //display the list of penguins with their corresponding coordinates -> this list will later be used as a reference for saving it into
        //ask user for movement coords

    while(!isOver){
        //READ FILE

        //ask user for data
        //ensure we can place there
        //if not then exit game

        //SAVE FILE
    }


}


//Will update all floes + scores + localization of penguins/ called whenever we move/place penguin and before closing the file
void UpdateContentCycle();
