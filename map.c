//
// Created by Jakub Duchniewicz on 22.12.2016.
//

//
//  main.c
//  mockPlansza
//
//  Created by Jakub Duchniewicz on 08.12.2016.
//  Copyright © 2016 Jakub Duchniewicz. All rights reserved.
//

#include "map.h"

struct floe{
    int xCo;
    int yCo;
    int fishNo;
    int playerNo;
};

void printMap(int data[],int rows, int columns){ //TODO: read the char of floe structs, create a library from floe struct
    //change char array into a ice floes array and read their corresponding Penguin and fish nr details
    int i=0;
    printFirstUpper(columns);
    for(i=0; i<rows; i++){
        if(i==0 || i%2==0){ //shift middle bars by two either inside this function or inside printMidBarriers
            printBarsAndFillNumbers(columns, data, i);

            printMidBarriers(columns);
            if(i!=rows-1){
                printf(" \\");
            }
            printf("\n");


        } else {
            printf("   "); //shift by half of the floe (floe is like 2 fields remember)
            printBarsAndFillNumbers(columns, data, i);
            printf(" / ");
            printMidBarriers(columns);
            printf("\n");

        }
    } //last lower is always printed therefore we don't need it

    return;
}

void printFirstUpper(int count){
    int i = 0;
    do{
        printf(" /  \\ "); //6character fields
        i++;
    } while(i!= count);
    printf("\n");
    return;
}

void printBarsAndFillNumbers(int count, int markings[], int index){
    int i = 0;
    for(i=0; i < count; i++){
        printf("| 11 |"); //here we need to print both player and fish nr or decide which format we want to choose
        //ind+=2;
    }
    printf("\n");
    return;
}

void printMidBarriers(int count){
    int i = 0;
    for(i = 0; i< count; i++){
        printf(" \\__/ ");
    }
    return;
}

