#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int playNum = 0, penguinNum = 0, player1ID = 0, player2ID = 0;
    int sizeX = 0, sizeY = 0, i = 0, j = 0, fishesOnFloe = 0, w = 0;
    FILE* map = fopen("board.txt", "w");
    printf("PlayerNum: ");
    scanf("%d", &playNum);
    printf("PenguinNum: ");
    scanf("%d", &penguinNum);
    printf("Player1ID: ");
    scanf("%d", &player1ID);
    printf("Player2ID: ");
    scanf("%d", &player2ID);
    printf("SizeX: ");
    scanf("%d", &sizeX);
    printf("SizeY: ");
    scanf("%d", &sizeY);

    srand(time(NULL));
    fprintf(map, "%d:%d;\n", playNum, penguinNum);
    fprintf(map, "%d:0", player1ID); //ad play id
        for(i = 0; i < penguinNum; i++){
            fprintf(map, ":-1:-1");
        } fprintf(map, ";\n");
    fprintf(map, "%d:0", player2ID); //ad play id
    for(i = 0; i < penguinNum; i++){
        fprintf(map, ":-1:-1");
    } fprintf(map, ";\n");

    fprintf(map,"Map\n");
    fprintf(map, "%d:%d\n", sizeX, sizeY);
    for(i = 0; i < sizeY; i++){
        for(j = 0; j < sizeX; j++, fishesOnFloe = 0){
            if(i%2) {
                if (j%2 != 0) {
                    fishesOnFloe = rand() % (4-1)+1;
                }
            } else {
                if(j%2==0){
                    fishesOnFloe = rand() % (4-1)+1;
                }

            }
            fprintf(map,"%d:%d:%d:0\n", j, i, fishesOnFloe);
        }
    }


};