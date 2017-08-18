#include <stdio.h>

#define Y (10)
#define X (20)
#define DEAD (0)
#define ALIVE (1)

/*To start => enter your selection in the board.bamb file: 1 for alive and 0 for dead.*/

/*initial the 2D array with 0.*/
void init_arr(int arr[][X]);

/*Prints the 2D array as a grid.*/
void print_arr(int arr[][X]);

/*Writes the 2D array content as a grid to board.bamb*/
void write_arr(int arr [][X]);

/*Reads a 2D array from board.bamb*/
void read_arr(int arr[][X]);

/*Returns the number of neighbors of a given cell.*/
int check_neighbors(int arr[][X], int i, int j);

/*Return 1 if the cell is alive or 0 otherwise.*/
int dead_or_alive(int arr[][X], int i, int j, int neighbors);

/*Write the changes of one generation of "The Game Of Life"*/
void change_board(int old_board[][X], int new_board[][X]);

int main() {
    int arr[Y][X];
    int new_arr[Y][X];
    init_arr(new_arr);

    init_arr(arr);
    read_arr(arr);
    print_arr(arr);
    change_board(arr, new_arr);
    printf("\n");
    print_arr(new_arr);
    write_arr(new_arr);




    return 0;
}


void init_arr(int arr[][X]){
    int i = 0;
    int j = 0;
    for(i = 0; i < Y; i++){
        for(j = 0;j < X; j++){
            arr[i][j] = DEAD;
        }
    }
}

void print_arr(int arr[][X]){
    int i = 0;
    int j = 0;
    for(i = 0; i < Y; i++){
        for(j = 0;j < X; j++){
            if(arr[i][j] == 0)
                printf("0 ");
            else
                if(arr[i][j] == 1)
                    printf("X ");
        }
        printf("\n");
    }
}

void write_arr(int arr [][X]){
    FILE* f = fopen("board.bamb", "w+");

    int i = 0;
    int j = 0;
    for(i = 0; i < Y; i++){
        for(j = 0;j < X; j++){
            fprintf(f, "%d ", arr[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

void read_arr(int arr[][X]){
    FILE* f = fopen("board.bamb", "r");
    int i = 0;
    int j = 0;
    char c;
    for(i = 0; i < Y; i++){
        for(j = 0; j < X; j++){

            if((c=(char)fgetc(f)) == '1') {
                arr[i][j] = ALIVE;
            }
            else{
                if(c == '0'){
                    arr[i][j] = DEAD;
                }
            }
            /*Reads the space char.*/
            fgetc(f);
        }
        /*Reads the new-line char.*/
        fgetc(f);
    }
    fclose(f);
}

/*Returns the number of the neighbors of a given cell.*/
int check_neighbors(int arr[][X], int i, int j){
    int neighbors_counter = 0;

    /*Checks if the sides and the corners of the given cell are alive.*/
    if(arr[i-1][j] == ALIVE) neighbors_counter ++;
    if(arr[i+1][j] == ALIVE) neighbors_counter ++;
    if(arr[i][j+1] == ALIVE) neighbors_counter ++;
    if(arr[i][j-1] == ALIVE) neighbors_counter ++;
    if(arr[i-1][j+1] == ALIVE) neighbors_counter ++;
    if(arr[i-1][j-1] == ALIVE) neighbors_counter ++;
    if(arr[i+1][j+1] == ALIVE) neighbors_counter ++;
    if(arr[i+1][j-1] == ALIVE) neighbors_counter ++;

    return neighbors_counter;
}

int dead_or_alive(int arr[][X], int i, int j, int neighbors){
    if(arr[i][j] == ALIVE && neighbors <= 3 && neighbors >= 2) return ALIVE;
    if(arr[i][j] == DEAD && neighbors == 3) return ALIVE;

    return DEAD;
}

void change_board(int old_board[][X], int new_board[][X]){
    int i = 0, j;
    for (i ; i < Y; ++i) {
        for (j = 0; j < X; ++j) {
            new_board[i][j] = dead_or_alive(old_board, i, j, check_neighbors(old_board, i, j));
        }
    }
}
