//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#include <string.h>
#include <stdlib.h>
#include "io.h"
#include "action.h"
#include "map.h"

/* THIS IS OUR MAIN FILE
 * Here we only asses which course of action to take
 * */

//TODO distinguish between interactive and automatic game modes with preprocessor directives
//TODO also add reading from command line phase, penguinsNr, inputname, outputname

//#define interactive //comment to run in automatic


int main(int argc, char* argv[]){

    char* placementOp = "phase=placement";
    char* movementOp = "phase=movement";

    //THIS IS THE INTERCATIVE MODE
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
