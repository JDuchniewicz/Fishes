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
void readFile(FILE* file){


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

void FirstLoadCycle();


//Will update all floes + scores + localization of penguins/ called whenever we move/place penguin and before closing the file
void UpdateContentCycle();
