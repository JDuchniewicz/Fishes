//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#include "action.h"


bool check_coordinates(int x, int y){
    //if they are not valid then return false
    return true;
}
//checks how many fishes are there on the field we want to move on
int check_how_many_fishes(int x, int y){
    int fishes;
    return fishes;
}

//checks whether there is a penguin on the field ...
bool check_penguin(int x, int y){
    return true;
}

//places penguin
void place_penguin(int x, int y){
    return;
}

//checks whetehr they are vakud
bool check_target_coordinates(int x, int y){
    return true;
}

bool check_valid_move(int x, int y){
    return true;
}

void movement(){
    //we collect fishes at the beggining of this function
    int x1, x2, y1, y2;
    scanf("%i %i %i %i", &x1, &y1, &x2, &y2);  //x1,y1 are coordinates of a penguin user wants to move, x2,y2 are target coordinates

    //check_coordinates(x1, y1); not useful
    check_penguin(x2, y2); //here we check next field for penguin presence
    check_target_coordinates(x2, y2);
    check_valid_move(x2, y2);

}

void placement(){
    int x, y;
    scanf("%i %i", &x, &y);
    if (check_coordinates(x,y) && check_how_many_fishes(x,y) == 1 && !check_penguin(x,y)){
        place_penguin(x,y);
    }
}
