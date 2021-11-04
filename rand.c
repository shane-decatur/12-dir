#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int random_num(){
  int i = open("/dev/random",O_RDONLY);
  int ret = 0;
  read(i,&ret,sizeof(int));
  return ret;
}

void print_arr(int *array, int size){
  int i;
  for (i = 0; i < size; i++){
    printf("random %d: %d\n",i,array[i]);
  }
}

int main(){
  int arr[10];
  int i;

  printf("Generating:\n");
  for(i = 0; i < 10;i++){
    arr[i] = random_num();
  }
  for(i = 0; i < 10; i++){
    printf("random %d: %d\n",i,arr[i]);
  }

  printf("Writing...\n");
  int file = open("file.dat", O_RDWR | O_CREAT, 0644);
  write(file, arr, 10 * sizeof(int));

  printf("Reading:\n");
  int reading_arr[10];
  int reading_file = open("file.dat",O_RDONLY);
  int reader = read(reading_file, reading_arr, 10*sizeof(int));
  for (i = 0; i < 10; i++){
    printf("random %d: %d\n",i,reading_arr[i]);
  }
}
