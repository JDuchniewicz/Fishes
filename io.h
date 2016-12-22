//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#ifndef FISHES_IO_H
#define FISHES_IO_H
#include <stdio.h>
FILE* openFile(char* name, char mode);
void writeFile(FILE* file);
void readFile(FILE* file);
#endif //FISHES_IO_H
