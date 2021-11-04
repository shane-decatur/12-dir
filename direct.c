#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]){
  DIR * d;
  struct dirent *entry;
  struct stat *info;
  int total = 0;

  char dir[100];
  if (argc > 1){
    if (!opendir(dir)){
        printf("please enter a proper directory\n");
        printf("error %d: %s\n",errno,strerror(errno));
        return 0;
    }
    strcpy(dir,argv[1]);
  }
  else{
    printf("please enter a directory\n");
    return 0;
  }

  d = opendir(dir);
  entry = readdir(d);

  printf("Directories:\n");
  while (entry){
    if (entry->d_type == DT_DIR){
      info = malloc(sizeof(struct stat));
      stat(entry->d_name, info);
      total += info->st_size;
      printf("\t%s\n",entry->d_name);
    }
    entry = readdir(d);
  }
  closedir(d);

  d = opendir(dir);
  printf("\nRegular Files:\n");
  entry = readdir(d);
  while (entry){
    if (entry->d_type == DT_REG){
      info = malloc(sizeof(struct stat));
      stat(entry->d_name, info);
      total += info->st_size;
      printf("\t%s\n",entry->d_name);
    }
    entry = readdir(d);
  }
  closedir(d);

  d = opendir(dir);
  printf("\nOther files:\n");
  entry = readdir(d);
  while (entry){
    if (entry->d_type != DT_DIR && entry->d_type != DT_REG){
      info = malloc(sizeof(struct stat));
      stat(entry->d_name, info);
      total += info->st_size;
      printf("\t%s\n",entry->d_name);
    }
    entry = readdir(d);
  }
  closedir(d);

  printf("Total Directory Size: %d bytes\n",total);
}
