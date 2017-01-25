//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#include <string.h>
#include <stdlib.h>
#include "action.h"

/* THIS IS OUR MAIN FILE
 * Here we only asses which course of action to take
 * */

//#define interactive //uncomment to run in interactive
#define tournament //uncomment to run in tournament

int main(int argc, char* argv[]){

    char* placementOp = "phase=placement";
    char* movementOp = "phase=movement";

    #ifdef tournament
    runTournament();
    return 0;
    #endif
    //THIS IS THE INTERACTIVE MODE
    #ifdef interactive
    runInteractive();
    #else
    if(argc == 5 && strcmp(placementOp,argv[1]) == 0){
        runPlacement(argv);
    } else if(argc == 4 && strcmp(movementOp, argv[1]) == 0){
        runMovement(argv);
    } else {
        printf("Incorrect number of parameters, please try again\n");
    }
    #endif
    return 0;
}
