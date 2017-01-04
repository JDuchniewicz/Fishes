//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#include "map.h"

void printMap(struct floe floes[],int rows, int columns){ //TODO: create a library from floe struct
    //change char array into a ice floes array and read their corresponding Penguin and fish nr details
    int i=0, index = 0;
    printFirstUpper(columns);
    for(i=0; i<rows; i++){
        if(i==0 || i%2==0){ //shift middle bars by two either inside this function or inside printMidBarriers
            printBarsAndFillNumbers(columns, floes, index);
            index++;
            printMidBarriers(columns);
            if(i!=rows-1){
                printf(" \\");
            }
            printf("\n");


        } else {
            printf("   "); //shift by half of the floe (floe is like 2 fields remember)
            printBarsAndFillNumbers(columns, floes, index);
            index++;
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

void printBarsAndFillNumbers(int count, struct floe floes[], int index){
    int i = 0;
    for(i=0; i < count; i++){
        printf("| %d%d |",floes[index].penguins,floes[index].fishes); //first displayed is penguin and next fishg
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



