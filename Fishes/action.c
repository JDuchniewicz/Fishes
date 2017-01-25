//
// Created by Jakub Duchniewicz on 22.12.2016.
//

#include "action.h"

//Don't know why but it must be defined inside C file (some, linking logic)
struct vector coords[6] = { {1, -1}, {2, 0}, {1, 1}, {-1, 1}, {-2, 0}, {-1, -1}};

//checks whether it is a floe
bool checkCoordinates(int x, int y){
    int i = 0;
    for(i = 0; i < (gameData.SizeX*gameData.SizeY); i++){
        if(x==floes[i].x){
            if(y==floes[i].y){
                if(floes[i].isFloe && floes[i].canBeEntered){
                    return true;
                }
            }
        }
    }
    return false;
}

//checks how many fishes are there on the field we want to move on
int checkHowManyFishes(struct floe *ourFloe){
    int fishes = ourFloe->fishes;
    return fishes;
}

//checks whether there is a penguin on the field
bool checkPenguin(struct floe *Floe){
    return Floe->penguins ? true : false; // we need to check whether nr of penguins on a floe is equal to 0
}

//translates coords to floe
struct floe* translateToFloe(int x, int y){
    struct floe* floetrans = malloc(sizeof(struct floe));
    int i =0;
    for(i = 0; i <(gameData.SizeX*gameData.SizeY); i++){
        if(x == floes[i].x && y == floes[i].y){
            return floetrans = &floes[i];
        } else{ //we give it arbitrary values to show that it is not viable to be a floe
            floetrans->x = -100;
            floetrans->y = -100;
            floetrans->fishes = 0;
            floetrans->penguins = 0;
            floetrans->canBeEntered = false;
            floetrans->isFloe = false;
        }
    }
    return floetrans;
}

//check if we can place a penguin
// if we can -> perform placement on the best field -> greedy algorithm
//decrement number of penguins available and append penguin's coordinates to prevent cheating
//else we exit and save file
void runPlacement(char* values[]){

    //open that file //we get the name of the file from the console!!!, input and output both
    int i = 0, floeBias = 0, highest = 0, j = 0;
    char inputFileName[12], outputFileName[12], penChar[12];
    struct floe  *pickedFloe, *bestFloe;

    struct floe* floePointer = floes;
    struct penguin* penguinPtr = playerOnePenguins, pickedPenguin;
    struct GameData* gdPointer = &gameData;

    strcpy(inputFileName,values[3]);
    strcpy(outputFileName,values[4]);
    strcpy(penChar, values[2]);
    for (i=0; i<9; i++) //we change every non-numerical character in "penguins=[x]" to 0,
        penChar[i]='0'; //so that atoi can convert it to int leaving only x value

    gameData.PenguinNum = atoi(penChar);
    FILE* inputFile = fopen(inputFileName, "r");
    FILE* outputFile = fopen(outputFileName, "w");

    readFile(inputFile,gdPointer,floePointer);

    if(gameData.Player1ID == 2137){
        penguinPtr = playerOnePenguins;
    } else if(gameData.Player2ID == 2137){
        penguinPtr = playerTwoPenguins;
    }

    //loop through all the penguins and pick each one that is free
    for(j = 0; j < gameData.PenguinNum; j++){
        if(penguinPtr[j].x==-1 && penguinPtr[j].y==-1){
            pickedPenguin = penguinPtr[j];
            break; //need to protect so it won't get additional penguins from space after the limit is done
        }
    }
    //protection against spawning additional penguins
    if(j>=gameData.PenguinNum){
        return;
    }
    //loop through all floes and for each of them assign them score bias depending on their / and their surrounding floes
    for(i = 0; i < (gameData.SizeY*gameData.SizeX); i++){
        pickedFloe = &floes[i]; //careful here
        if(!pickedFloe->isFloe || (pickedFloe->penguins != 0) || (pickedFloe->fishes != 1)){
            continue;
        }
    floeBias = addFloeBias(pickedFloe);
        if(floeBias>highest){
        highest = floeBias;
        bestFloe = pickedFloe;
        }
    }
    if(highest==0){
        writeFile(outputFile, gdPointer,floePointer);
        fclose(outputFile);
        fclose(inputFile);
        return;
    }
    pickedPenguin.x = bestFloe->x;
    pickedPenguin.y = bestFloe->y;
    bestFloe->penguins = 2137;
    penguinPtr[j].x = pickedPenguin.x;
    penguinPtr[j].y = pickedPenguin.y;

    writeFile(outputFile, gdPointer,floePointer);
    fclose(outputFile);
    fclose(inputFile);
}

//loop through surroundingFloes and add particular biases to them depending on their content
//0 if it has a penguin or is not existent and 1,2,3 for fishes content on them
int addFloeBias(struct floe *checkedFloe){ //TODO: Check why it adds really big biases
    struct floe* currFloe;
    int totalBias = 0, oneBias = 0, i = 0;
    if(checkedFloe->penguins!=0 || !checkedFloe->isFloe || !checkedFloe->canBeEntered){
        return  0;
    } else {
        totalBias+= checkedFloe->fishes;
    }
    for(i = 0; i < 6; i++){
        currFloe = translateToFloe(checkedFloe->x + coords[i].x,checkedFloe->y +  coords[i].y);
        if(!currFloe->canBeEntered || !currFloe->isFloe || currFloe->penguins != 0){
            oneBias+=0;
        } else {
            oneBias+=currFloe->fishes;
        }
        totalBias+=oneBias;
    }
    return totalBias;
}


void runMovement(char* values[]){
    //open that file //we get the name of the file form the console!!!, input and output both
    char inputFileName[12], outputFileName[12];
    int i = 0, j = 0, singleBias = 0, highestBias = 0, coordCounter = 0, k = 0;
    bool isMoveAvailable = true;
    strcpy(inputFileName,values[2]);
    strcpy(outputFileName,values[3]);

    FILE* inputFile = fopen(inputFileName, "r");
    FILE* outputFile = fopen(outputFileName, "w");

    struct floe *pickedFloe, *bestFloe, *currFloe;

    struct floe* floePointer = floes;
    struct penguin* penguinPtr = playerOnePenguins;
    struct GameData* gdPointer = &gameData;

    readFile(inputFile, gdPointer, floePointer);

    if(gameData.Player1ID == 2137){
        penguinPtr = playerOnePenguins;
    } else if(gameData.Player2ID == 2137){
        penguinPtr = playerTwoPenguins;
    }

    //loops the penguins array and checks their surroundings to flag whether the player can move any more or not
    for(i = 0; i < gdPointer->PenguinNum; i++){
        pickedFloe = translateToFloe(penguinPtr[i].x, penguinPtr[i].y);
        if(!checkSurroundings(pickedFloe)){ //we check if there is at least one floe in surrounding
            isMoveAvailable = false;
        } else{ //returns the first penguin that can still move
            k = i; //not sure if it's right
            isMoveAvailable = true;
            break;
        }
    }
    //perform movement
    while(isMoveAvailable){
        //the condition to add biases and choose the best suited floe
        singleBias = 0;
        highestBias = 0;
        for(i = 0; i < 6; i++){
            currFloe = translateToFloe(pickedFloe->x + coords[i].x,pickedFloe->y +  coords[i].y);
            singleBias += addFloeBias(currFloe);
            if(singleBias > highestBias){
                highestBias = singleBias;
                bestFloe = currFloe;
                coordCounter = i;
            }
        }
        do{
            if(gameData.Player1ID == 2137){
                gameData.score1+=pickedFloe->fishes;
            } else if(gameData.Player2ID == 2137){
                gameData.score2+=pickedFloe->fishes;
            }
            pickedFloe->fishes = 0;
            pickedFloe->penguins = 0;
            pickedFloe->canBeEntered = false;
            bestFloe = translateToFloe(pickedFloe->x+coords[coordCounter].x, pickedFloe->y+coords[coordCounter].y);
            bestFloe->penguins = 2137; //HARDCODED ID
            penguinPtr[k].x = bestFloe->x;
            penguinPtr[k].y = bestFloe->y;
            pickedFloe = bestFloe;
        }while(checkIfFree(bestFloe,coordCounter));
        break; //so we know that penguin moved all way on its axis until end
        //now move until cannot anymore
        //add floe biases and choose best suited one/ probably depth 2 recursion
            //perform movement on the axis we chose until cannot move
        //then we loop movement until we can move no more, the floes behind us disappear, and we collect all the fishes from the fields
        //we have been on
    }
    writeFile(outputFile, gdPointer,floePointer);
    fclose(outputFile);
    fclose(inputFile);
    return;
}

//this is more specified version of check surrounding, checks only next floe in particular axis
bool checkIfFree(struct floe *ourFloe, int axisIndex){
    struct floe* currFloe;
        currFloe = translateToFloe(ourFloe->x + coords[axisIndex].x,ourFloe->y +  coords[axisIndex].y);
        if(!currFloe->canBeEntered || !currFloe->isFloe || currFloe->penguins != 0){
            return false;
        }
    return true;
}

//checks surrounding floes whether they are viable to move onto them
bool checkSurroundings(struct floe *ourFloe){
    struct floe* currFloe;
    int  i = 0, floesNotReachableCount = 0;
    for(i = 0; i < 6; i++){
        currFloe = translateToFloe(ourFloe->x + coords[i].x,ourFloe->y +  coords[i].y);
        if(!currFloe->canBeEntered || !currFloe->isFloe || currFloe->penguins != 0){
           floesNotReachableCount+=1;
        }
    }
    if(floesNotReachableCount==6){
        return  false;
    }
    return true;
}

bool runInteractivePlacement(int x, int y){
    struct floe* floeptr;
    int nr = 0;
    if(!checkCoordinates(x,y)){ return false; }
    floeptr = translateToFloe(x,y);
    if((nr=checkHowManyFishes(floeptr))!=1){return false; }
    if(checkPenguin(floeptr)){ return false;}
    return true;
}

bool runInteractiveMovement(int x ,int y){
    struct floe* floeptr;
    if(!checkCoordinates(x,y)){ return false; }
    floeptr = translateToFloe(x,y);
    if(checkPenguin(floeptr)){ return false;}
    return true;
}

void runInteractive(){ //add file name to read
    //VARIABLES
    char* fileName = "fileFormatMock.txt"; //we fix it to a particular file or create two, one for reading and one for writing
    FILE* fp = openFile(fileName, "r+");

    int destX = 0, destY = 0, pengX = 0, pengY = 0, choice = 0, penPlacementCount = 0, penMovementCount = 0, i = 0, j = 0, vectX = 0, vectY = 0, k = 0;

    bool isOver = false, noMoves = false;

    struct floe* floePointer = floes, *oldFloePtr;

    struct penguin* penguinsptr;


    struct GameData* gdPointer = &gameData;

    //DISPLAY INTERACTIVE WELCOME SCREEN
    //give user choice exit or play
    //maybe difficulty choice later?
    //or human vs ai mode?

    //FIRST
    readFile(fp,gdPointer,floePointer);
    printMap(floes, gameData.SizeX, gameData.SizeY);

    //PLACEMENT
    //ask user for placement coords and perform logic
    while(gameData.player1RemainingPeng > 0) {
        //READ FILE
        fp = freopen(fileName, "r", fp);
        printMap(floes, gameData.SizeX, gameData.SizeY);
        //ask user for data
        printf("\nPlacement mode: \n choose the coordinates of the floe you would like to place your penguin on.\n");
        printf("x: ");
        scanf("%d", &destX);
        printf("y: ");
        scanf("%d", &destY);
        //ensure we can place there
        if (runInteractivePlacement(destX, destY)) {
            playerOnePenguins[penPlacementCount].x = destX;
            playerOnePenguins[penPlacementCount].y = destY;
            floePointer = translateToFloe(destX, destY);
            floePointer->penguins = gameData.Player1ID;
            gameData.player1RemainingPeng--;
            penPlacementCount++;

        }
        //SAVE FILE
        fp = freopen(fileName, "w", fp);
        writeFile(fp, gdPointer, floePointer);
    }
    printMap(floes, gameData.SizeX, gameData.SizeY);
    //MOVEMENT
    while(!isOver){
        //READ FILE
        fp = freopen(fileName,"r",fp);
        readFile(fp,gdPointer,floePointer);
        printf("\nMovement mode:\n choose a penguin from the list of available penguins\n");
        for(i = 0; i < gameData.PenguinNum; i++){
            penguinsptr = &playerOnePenguins[i];
            pengX = penguinsptr->x;
            pengY = penguinsptr->y;
            if(pengX!=-1 && pengY!=-1){
                printf("Penguin nr: %d, Coordinates: x:%d y:%d\n", i, pengX, pengY);
            }
        }
        printf("Enter the number of penguin you want to move\n");
        scanf("%d", &choice);
        for(j = 0; j < i; j++){
            if(j==choice){
                penguinsptr=&playerOnePenguins[j];
                pengX = penguinsptr->x;
                pengY = penguinsptr->y;
                k = j;
            }
        }
        printf("Now choose the vector in which you would like to move your penguin\n");
        printf("1: North-East\n2: East \n3: South-East\n4: South-West\n5:West\n6:North-West\n");
        scanf("%d", &choice);
        vectX = coords[choice-1].x;
        vectY =  coords[choice-1].y;
        while(runInteractiveMovement(pengX+vectX, pengY+vectY)) {
            fp = freopen(fileName,"r",fp);
            readFile(fp, gdPointer, floePointer);
            //can move so can perform all the cleanup operations
            //remove penguin from the floe it was on, collect fishes and update score, remove floe
            //add penguin to the floe it is currently on
            floePointer = translateToFloe(pengX+vectX,pengY+vectY);
            oldFloePtr = translateToFloe(pengX, pengY);
            gameData.score1 += oldFloePtr->fishes;
            oldFloePtr->fishes = 0;
            oldFloePtr->penguins = 0;
            oldFloePtr->canBeEntered = false;
            floePointer->penguins = gameData.Player1ID;
            pengX+=vectX;
            pengY+=vectY;
            penguinsptr = &playerOnePenguins[k];
            penguinsptr->x = pengX;
            penguinsptr->y = pengY;
            fp = freopen(fileName,"w",fp);
            writeFile(fp, gdPointer,floePointer);
        }
        printMap(floes, gameData.SizeX, gameData.SizeY);
      for(i = 0; i < gameData.PenguinNum; i++){
          noMoves = false;
          if(!checkSurroundings(translateToFloe(playerOnePenguins[i].x, playerOnePenguins[i].y))){
              noMoves = true;
          }
      }
        if(noMoves){
            isOver = true;
        }

        //SAVE FILE
        fp = freopen(fileName,"w",fp);
        writeFile(fp,gdPointer,floePointer);
    }
    fclose(fp);
    //GAME OVER SCREEN + STATS
    printf("\n\nGAME OVER!!!\n");
    printf("score: %d", gameData.score1);
    return;
}

//the tournament mode, slightly modified interactive mode
//player1 is player and player2 is AI with ID:9999
void runTournament(){ //add file name to read
    //VARIABLES
    char* fileName = "fileFormatMock.txt"; //we fix it to a particular file or create two, one for reading and one for writing
    FILE* fp = openFile(fileName, "r+");

    int destX = 0, destY = 0, pengX = 0, pengY = 0, choice = 0, penPlacementCount = 0, penMovementCount = 0, i = 0, j = 0, vectX = 0, vectY = 0, k = 0;
    int floeBias = 0, highest = 0,singleBias = 0, highestBias = 0, coordCounter = 0;
    int player1RemainingPeng  = 0, player2RemainingPeng = 0;
    bool isOver = false, noMoves = false, AICanMove = true;

    struct floe* floePointer = floes, *oldFloePtr;
    struct floe  *pickedFloe, *bestFloe;
    struct floe *currFloe;

    struct penguin* penguinsptr, pickedPenguin;

    struct GameData* gdPointer = &gameData;

    //DISPLAY INTERACTIVE WELCOME SCREEN
    //give user choice exit or play
    //maybe difficulty choice later?
    //or human vs ai mode?

    //FIRST
    readFile(fp,gdPointer,floePointer);
    player1RemainingPeng = gameData.player1RemainingPeng;
    player2RemainingPeng = gameData.player2RemainingPeng;
    printMap(floes, gameData.SizeX, gameData.SizeY);

    while(player1RemainingPeng > 0 && player2RemainingPeng) {
        if(player1RemainingPeng > 0){
            //READ FILE
            fp = freopen(fileName, "r", fp);
            readFile(fp,gdPointer,floePointer);
            printMap(floes, gameData.SizeX, gameData.SizeY);
            //ask user for data
            printf("\nPlacement mode: \n choose the coordinates of the floe you would like to place your penguin on.\n");
            printf("x: ");
            scanf("%d", &destX);
            printf("y: ");
            scanf("%d", &destY);
            //ensure we can place there
            if (runInteractivePlacement(destX, destY)) {
                playerOnePenguins[penPlacementCount].x = destX;
                playerOnePenguins[penPlacementCount].y = destY;
                floePointer = translateToFloe(destX, destY);
                floePointer->penguins = gameData.Player1ID;
                player1RemainingPeng;
                penPlacementCount++;

            }
            //SAVE FILE
            fp = freopen(fileName, "w", fp);
            writeFile(fp, gdPointer, floePointer);
        }
        if(player2RemainingPeng >0){
            //perform comp placement
            //READ FILE
            highest = 0;
            fp = freopen(fileName, "r", fp);
            readFile(fp,gdPointer,floePointer);
            for(j = 0; j < gameData.PenguinNum; j++){
                if(playerTwoPenguins[j].x==-1 && playerTwoPenguins[j].y==-1){
                    pickedPenguin = playerTwoPenguins[j];
                    break; //need to protect so it won't get additional penguins from space after the limit is done
                }
            }
            //protection against spawning additional penguins
            if(j>=gameData.PenguinNum){
                return;
            }
            //loop through all floes and for each of them assign them score bias depending on their / and their surrounding floes
            for(i = 0; i < (gameData.SizeY*gameData.SizeX); i++){
                pickedFloe = &floes[i]; //careful here
                if(!pickedFloe->isFloe || (pickedFloe->penguins != 0) || (pickedFloe->fishes != 1)){
                    continue;
                }
                floeBias = addFloeBias(pickedFloe);
                if(floeBias>highest){
                    highest = floeBias;
                    bestFloe = pickedFloe;
                }
            }
            if(highest==0){
                writeFile(fp, gdPointer,floePointer);
                return;
            }
            pickedPenguin.x = bestFloe->x;
            pickedPenguin.y = bestFloe->y;
            bestFloe->penguins = 9999;
            playerTwoPenguins[j].x = pickedPenguin.x;
            playerTwoPenguins[j].y = pickedPenguin.y;
            player2RemainingPeng--;

            fp = freopen(fileName, "w", fp);
            writeFile(fp, gdPointer, floePointer);
        }
        printMap(floes, gameData.SizeX, gameData.SizeY);
    }
    //MOVEMENT
    while(!isOver){
        //READ FILE
        fp = freopen(fileName,"r",fp);
        readFile(fp,gdPointer,floePointer);
        printMap(floes, gameData.SizeX, gameData.SizeY);
        printf("\nMovement mode:\n choose a penguin from the list of available penguins\n");
        for(i = 0; i < gameData.PenguinNum; i++){
            penguinsptr = &playerOnePenguins[i];
            pengX = penguinsptr->x;
            pengY = penguinsptr->y;
            if(pengX!=-1 && pengY!=-1){
                printf("Penguin nr: %d, Coordinates: x:%d y:%d\n", i, pengX, pengY);
            }
        }
        printf("Enter the number of penguin you want to move\n");
        scanf("%d", &choice);
        for(j = 0; j < i; j++){
            if(j==choice){
                penguinsptr=&playerOnePenguins[j];
                pengX = penguinsptr->x;
                pengY = penguinsptr->y;
                k = j;
            }
        }
        printf("Now choose the vector in which you would like to move your penguin\n");
        printf("1: North-East\n2: East \n3: South-East\n4: South-West\n5:West\n6:North-West\n");
        scanf("%d", &choice);
        vectX = coords[choice-1].x;
        vectY =  coords[choice-1].y;
        while(runInteractiveMovement(pengX+vectX, pengY+vectY)) {
            fp = freopen(fileName,"r",fp);
            readFile(fp, gdPointer, floePointer);
            //can move so can perform all the cleanup operations
            //remove penguin from the floe it was on, collect fishes and update score, remove floe
            //add penguin to the floe it is currently on
            floePointer = translateToFloe(pengX+vectX,pengY+vectY);
            oldFloePtr = translateToFloe(pengX, pengY);
            gameData.score1 += oldFloePtr->fishes;
            oldFloePtr->fishes = 0;
            oldFloePtr->penguins = 0;
            oldFloePtr->canBeEntered = false;
            floePointer->penguins = gameData.Player1ID;
            pengX+=vectX;
            pengY+=vectY;
            penguinsptr = &playerOnePenguins[k];
            penguinsptr->x = pengX;
            penguinsptr->y = pengY;
            fp = freopen(fileName,"w",fp);
            writeFile(fp, gdPointer,floePointer);
        }
        printMap(floes, gameData.SizeX, gameData.SizeY);
        for(i = 0; i < gameData.PenguinNum; i++){
            noMoves = false;
            if(!checkSurroundings(translateToFloe(playerOnePenguins[i].x, playerOnePenguins[i].y))){
                noMoves = true;
            }
        }
        if(noMoves){
            isOver = true;
        }

        //SAVE FILE
        fp = freopen(fileName,"w",fp);
        writeFile(fp,gdPointer,floePointer);

        //AI
        if(isOver){
            break;
        }
        fp = freopen(fileName,"r",fp);
        readFile(fp,gdPointer,floePointer);
        //loops the penguins array and checks their surroundings to flag whether the player can move any more or not
        for(i = 0; i < gdPointer->PenguinNum; i++){
            pickedFloe = translateToFloe(playerTwoPenguins[i].x, playerTwoPenguins[i].y);
            if(!checkSurroundings(pickedFloe)){ //we check if there is at least one floe in surrounding
                AICanMove = false;
                isOver = true;
            } else{ //returns the first penguin that can still move
                k = i; //not sure if it's right
                AICanMove = true;
                isOver = false;
                break;
            }
        }
        //perform movement
        while(AICanMove){
            //the condition to add biases and choose the best suited floe
            singleBias = 0;
            highestBias = 0;
            for(i = 0; i < 6; i++){
                currFloe = translateToFloe(pickedFloe->x + coords[i].x,pickedFloe->y +  coords[i].y);
                singleBias += addFloeBias(currFloe);
                if(singleBias > highestBias){
                    highestBias = singleBias;
                    bestFloe = currFloe;
                    coordCounter = i;
                }
            }
            do{
                gameData.score2+=pickedFloe->fishes;
                pickedFloe->fishes = 0;
                pickedFloe->penguins = 0;
                pickedFloe->canBeEntered = false;
                bestFloe = translateToFloe(pickedFloe->x+coords[coordCounter].x, pickedFloe->y+coords[coordCounter].y);
                bestFloe->penguins = 9999; //HARDCODED ID
                playerTwoPenguins[k].x = bestFloe->x;
                playerTwoPenguins[k].y = bestFloe->y;
                pickedFloe = bestFloe;
            }while(checkIfFree(bestFloe,coordCounter)); //TODO: add open/reopen eachtime?
            fp = freopen(fileName,"w",fp);
            writeFile(fp,gdPointer,floePointer);
            break;
        }
    }
    fclose(fp);
    //GAME OVER SCREEN + STATS
    printf("\n\nGAME OVER!!!\n");
    printf("Player 1 score: %d", gameData.score1);
    printf("AI score: %d", gameData.score2);
    if(gameData.score1>gameData.score2){
        printf("Congratz, you have beaten AI, you're the guy!\n");
    } else {
        printf("Maybe next time!\n");
    }
    return;
}

