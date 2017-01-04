//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#ifndef FISHES_IO_H
#define FISHES_IO_H
#include <stdio.h>
#include "map.h"
FILE* openFile(char* name, char *mode);
void writeFile(FILE* file);
void readFile(FILE* file);
int getOneCharAsInt(FILE* file);
int getIntBySize(FILE *file);
int readOneFloe(FILE* file, struct floe* oneFloe, int status);
void jumpToNextLine(FILE* file);
void FirstLoadCycle();
void UpdateContentCycle();
#endif //FISHES_IO_H
