//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#ifndef FISHES_IO_H
#define FISHES_IO_H
#include <stdio.h>
#include "map.h"
#include <stdbool.h>

//file format files
FILE* openFile(char* name, char *mode);
void writeFile(FILE* file, struct GameData* data, struct floe* floeptr);
void readFile(FILE* file, struct GameData* data, struct floe* floeptr);
//This function loops through global floeMap and returns whether a particular (x,y) is a floe and saves it
//void MapFloes(struct GameData* gameDataForMap, struct floe* floeptr, int floeCount);

//char input functions
int getOneCharAsInt(FILE* file);
int getIntBySize(FILE *file);
void peek(FILE *file);
int readOneFloe(FILE* file, struct floe* oneFloe, int status);
void jumpToNextLine(FILE* file);

#endif //FISHES_IO_H
