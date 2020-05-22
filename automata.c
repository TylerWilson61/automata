#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  //declare generations, row, cols
  int gen = atoi(argv[1]);
  int cells[5][5] = {0};
  int count = 0;
  int r = 0;
  int c = 0;
  FILE *input;
  input = fopen(argv[2], "r");
  if (input){
    //read text file
    while (!feof(input)){
      //get each char, compare to 1 or 0
      char cell_status = fgetc(input);
      int alive = strncmp(&cell_status, "1", 1);
      int dead = strncmp(&cell_status, "0", 1);
      //if not whitespace or crlf pair, add to our matrix
      if (alive == 0 || dead == 0){
        if (alive == 0){
          cells[r][c] = 1;
          if (c < 4){
            c++;
          }
          else{
            c = 0;
            r++;
          };
        }
        else {
          cells[r][c] = 0;
          if (c < 4){
            c++;
          }
          else{
            c = 0;
            r++;
          };
        };
      };
    };
};
fclose(input);

  //iterate through generations
  for (int i = 0; i < gen; i ++){
    int shell[5][5] = {0}; //need extra memory to hold changes to cells
    //iterate through each cell
    for (int row = 0; row < 5; row ++){
      for (int col = 0; col < 5; col ++){
        int status = cells[row][col]; //get alive or dead status
        int neighbors[8] = {0};
        int x = -1;
        int y = -1;
        //create list of 8 neighbors (excludes current cell) from 2D array by iterating through cells
        for (int v=0; v < 9; v ++){
          //if both 0, this is our current cell so ignore it
          if (x == 0 && y == 0){
            y++;
            neighbors[v] = 0;
            continue;
          };
          if (y < 2){
            //check we are trying to acces row or column outisde in the matrix, else automatically a dead neighbor
            if (row+x < 0 || row+x > 4 || col + y < 0 || col + y > 4){
              neighbors[v] = 0;
              y++;
              continue;
            };
            //add new neighbor to array
            neighbors[v] = cells[row + x][col + y];
            y++;
          }
          //goes to next row
          else {
            y = -1;
            x++;
            if (row+x < 0 || row+x > 4 || col + y < 0 || col + y > 4){
              neighbors[v] = 0;
              y++;
              continue;
            };
            neighbors[v] = cells[row + x][col + y];
            y++;
          };
        };
        int n_alive = 0;
        //get number of neighbors that are alive by iterating through neighbors array
        for (int v=0; v < 9; v ++){
          if (neighbors[v] == 1){
            n_alive ++;
          };
        };
        if (status == 0){ //cell is currently dead
          if (n_alive == 3){
            shell[row][col] = 1;
          };
        }
        else{ //cell is currently alive
          if (n_alive < 2 || n_alive > 3) {
            shell[row][col] = 0;
          }
          else{
            shell[row][col] = 1;
          };
        };
      };
    };
    //push temporary shell values into cells
    for (int row = 0; row < 5; row ++){
      for (int col = 0; col < 5; col ++){
        cells[row][col] = shell[row][col];
      };
    };
  };
  //write our out file
  FILE *output;
  //create name of file
  char name[100];
  strcpy(name,argv[2]);
  strcat(name, ".out");
  //create contents of file
  output = fopen(name, "w");
  for (int q = 0; q < 5; q++){
    fprintf(output, "%d %d %d %d %d\n", cells[q][0], cells[q][1], cells[q][2], cells[q][3], cells[q][4]);
  };
  fclose(output);
}
