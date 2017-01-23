//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#include "map.h"

void printMap(struct floe floes[],int rows, int columns){
    int i=0, index = 0;
    printf("\n\n");
    columns/=2;
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
    struct floe* localptr;
    int i = 0, playReplNum = 0;
    int colNr = count*2;
    for(i=0; i < colNr; i++){
        localptr = &floes[index*colNr+i];
        if(localptr->isFloe && localptr->canBeEntered){
            if(localptr->penguins==gameData.Player1ID){
                playReplNum = 1;
            } else if (localptr->penguins==gameData.Player2ID){
                playReplNum = 2;
            } else{
                playReplNum = 0;
            }
            printf("| %d%d |",localptr->fishes, playReplNum); //first displayed is fish then penguin
        } else if(localptr->isFloe && !localptr->canBeEntered){
            printf("|    |");
        }
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



