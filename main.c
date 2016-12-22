//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#include <string.h>
#include "io.h"
#include "action.h"
#include "map.h"

bool isPhaseMovement = false;
int fileCounter = 0;

/* TODO */


struct field //struct from which we create our board, contans nr of fishes and penguins on it -> single tile, and coordinates
{
    int x;
    int y;
    int fishes;
    int penguins;
};

int main(){
    /* declare structures and some variables */
    int a;
    int ap[10];
    printMap(ap, 10, 10);
    printf("Enter game mode choice: 0 for placement, 1 for movement");
    scanf("%d", &a);
    if(a == 1){
        isPhaseMovement = true;
    } else if(a == 0){
        isPhaseMovement = false;
    }
    //readFile();
    if (!isPhaseMovement){
        placement();
    } else {
        movement();
    }
    //writeFile();
    return 0;

}
