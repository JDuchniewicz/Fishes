//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#ifndef FISHES_IO_H
#define FISHES_IO_H
#include <stdio.h>
#include "map.h"
#include <stdbool.h>


FILE* openFile(char* name, char *mode);
void writeFile(FILE* file);
void readFile(FILE* file, struct GameData* data, struct floe* floeptr);
void MapFloes(struct GameData* gameDataForMap, struct floe* floeptr, int floeCount);
int getOneCharAsInt(FILE* file);
int getIntBySize(FILE *file);
int readOneFloe(FILE* file, struct floe* oneFloe, int status);
void jumpToNextLine(FILE* file);
void runInteractive();
void UpdateContentCycle();
#endif //FISHES_IO_H
