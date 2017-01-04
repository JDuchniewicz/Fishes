//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#ifndef FISHES_IO_H
#define FISHES_IO_H
#include <stdio.h>
#include "map.h"
FILE* openFile(char* name, char mode);
void writeFile(FILE* file);
void readFile(FILE* file);
int getOneCharAsInt(FILE* file);
int getIntBySize(FILE *file);
void readOneFloe(FILE* file, struct floe* oneFloe);
void jumpToNextLine(FILE* file);
#endif //FISHES_IO_H
