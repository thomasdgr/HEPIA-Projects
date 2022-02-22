#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


int main(){
    typedef enum piece{SAFE, VULN, QUEEN}piece;
    int size = 16;
    piece board[size][size];

    for (int i =0; i <size; i++){
        for (int j = 0; j < size; j++){
            board[i][j] = SAFE;
        }
    }
    
    int pos_x = 8;
    int pos_y = 2; 


    //Approche très naïve
    for (int i =0; i <size; i++){
        for (int j = 0; j <size; j++){
            if (j == pos_y)
                board[i][j] = VULN;
            if (i == pos_x)
                board[i][j] = VULN;
            if (pos_x + i < size && pos_y + i < size)
                board[pos_x + i][pos_y + i] = VULN;
            if (pos_x - i >= 0 && pos_y + i < size)
                board[pos_x -i][pos_y + i] = VULN;
            if (pos_x - 1 >=0 && pos_y - i >=0)
                board[pos_x -i][pos_y -i] = VULN;
            if (pos_x + i < size && pos_y - i >=0)
                board[pos_x +i][pos_y -i] = VULN;
        }
    }

    board[pos_x][pos_y] = QUEEN;

    for (int i = 0; i < size; i ++){
        for(int j = 0; j < size; j++){
            if (board[i][j] == VULN)
                printf(" X");
            else if (board[i][j] == SAFE)
                printf(" O");
            else if (board[i][j] == QUEEN)
                printf(" R");
        }
        printf("\n");
    }




}


