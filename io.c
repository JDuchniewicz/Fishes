//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#include "io.h"

FILE* openFile(char* name, char mode){
    FILE* fp;
    if(!fp = fopen(name, mode)){
        printf("Cannot open file\n");
        return -1;
    };
    return fp;
}

void writeFile(FILE* file){



}
void readFile(FILE* file){


}

//Gets one char from input file and returns it
int getOneCharAsInt(FILE* file){
    int c = 0;
  do{
      c = getc(file);
  } while(c <= 48 || c >= 57);
    return c;
}

//Gets as many chars as it can until it meets ; : \n
int getIntBySize(FILE *file){
    int ret , i = 0;
    char content[4];
    char c;
    while ((c = fgetc(file)) != ':' || (c = fgetc(file)) != ';' || (c = fgetc(file))  != '\n' ){
        content[i] = c;
        i++;
    }
    sscanf(content, "%d", &ret);
    return ret;
}

void readOneFloe(FILE* file, struct floe* oneFloe){
    int x = 0, y = 0, fishes = 0, penguins = 0;
    x = getIntBySize(file);
    y = getIntBySize(file);
    fishes = getOneCharAsInt(file);
    penguins = getOneCharAsInt(file);
    oneFloe->x = x;
    oneFloe->y = y;
    oneFloe->fishes = fishes;
    oneFloe->penguins = penguins;
    return;
}

//jumps to next line in current file
void jumpToNextLine(FILE* file){
    int c;
    do {
        c = fgetc(file);
    } while (c != '\n');
    return;
}

void FirstLoadCycle();


//Will update all floes + scores + localization of penguins/ called whenever we move/place penguin and before closing the file
void UpdateContentCycle();
