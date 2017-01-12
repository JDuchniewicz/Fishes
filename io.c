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

void writeFile(FILE* file, struct GameData* data, struct floe* floeptr){
    int status = 0, floeIndex = 0, i= 0;
    //WRITE FIRST LINE
    fprintf(file, "%d;%d;\n", data->PlayerNum, data->PenguinNum);
    //WRITE PLAYER ID'S SCORE'S AND PENGUIN'S LOCATIONS
    fprintf(file, "%d:%d", data->Player1ID, data->score1);
    for(i = 0; i < data->PenguinNum; i++){
        fprintf(file,":%d:%d", playerOnePenguins[i].x, playerOnePenguins[i].y);
    } fprintf(file, ";\n");
    fprintf(file, "%d:%d", data->Player2ID, data->score2);
    for(i = 0; i < data->PenguinNum; i++){
        fprintf(file,":%d:%d", playerTwoPenguins[i].x, playerTwoPenguins[i].y);
    } fprintf(file, ";\n");
    //WRITE MAP SIZE
    fprintf(file, "Map\n");
    fprintf(file,"%d:%d\n", data->SizeX, data->SizeY);
    //WRITE FLOES
    while (floeIndex != (data->SizeX * data->SizeY)) { // here we write floeMap
        floeptr = &floes[floeIndex];
        fprintf(file, "%d:%d:%d:%d\n", floeptr->x, floeptr->y, floeptr->fishes, floeptr->penguins);
        floeIndex++;
    }
    return;
}
void readFile(FILE* file, struct GameData* data, struct floe* floeptr)
{
    int status = 0, floeIndex = 0, i = 0;
    //READ FIRST LINE
    data->PlayerNum = getOneCharAsInt(file);
    data->PenguinNum = getOneCharAsInt(file);
    jumpToNextLine(file);
    //READ PLAYER ID'S SCORE'S AND PENGUIN'S LOCATIONS
    data->Player1ID = getIntBySize(file); //TODO: We need to reread array of penguin locations and save it into array, because in auto mode it needs the data every "frame"
    data->score1 = getIntBySize(file);
    for(i = 0; i < data->PenguinNum; i++){
        playerOnePenguins[i].x = getIntBySize(file);
        playerOnePenguins[i].y = getIntBySize(file);
        if(playerOnePenguins[i].x==-1 && playerOnePenguins[i].y==-1){
            data->player1RemainingPeng++;
        }
    }
    jumpToNextLine(file);
    data->Player2ID = getIntBySize(file);
    data->score2 = getIntBySize(file);
    for(i = 0; i < data->PenguinNum; i++){
        playerTwoPenguins[i].x = getIntBySize(file);
        playerTwoPenguins[i].y = getIntBySize(file);
        if(playerTwoPenguins[i].x==-1 && playerTwoPenguins[i].y==-1){
            data->player2RemainingPeng++;
        }
    }
    jumpToNextLine(file);
    jumpToNextLine(file);
    //READ MAP SIZE
    data->SizeX = getIntBySize(file);
    data->SizeY = getIntBySize(file);
    //READ FLOES AND FILL THEM
    while (floeIndex != (data->SizeX * data->SizeY)) {
        floeptr = &floes[floeIndex];
        status = readOneFloe(file, floeptr, status); //we monitor state of loading with returning status variable
        if (status == EOF) { //we return EOF to break all continuation of floe loading
            break;
        }
        floes[floeIndex] = *floeptr;
        floeIndex++;  //increase index only by 1 because we want them ordered
    }
    return;

     //MapFloes(data,floeptr,floeCount);

}

void peek(FILE *file)
{
    char c;
    c = getc(file);
    if(c=='\n'){
        return;
    }
    ungetc(c, file);
    return;
}

/*
//i am not sure if we even need such struct like floemap, because we can add a field exists on each floe and just check them, we don't care what's
//not loaded onto our map thus we don't need checking like this
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
 */

//Gets one char from input file and returns it
int getOneCharAsInt(FILE* file){
    int c = 0;
  do{
      c = getc(file);
      if(c==EOF){
          return EOF; //we return EOF to break all continuation
      }
  } while(c < 48 || c >= 57);
    return c - '0';
}

//Gets as many chars as it can until it meets ; : \n
int getIntBySize(FILE *file){
    int ret = 0 , i = 0;
    char content[5] = "";
    char c;
    while ((c = fgetc(file)) != EOF){
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
    peek(file);
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
    if(oneFloe->penguins || oneFloe->fishes){
        oneFloe->isFloe = true;
    } else{
        oneFloe->isFloe = false;
    }
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