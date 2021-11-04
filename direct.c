#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main(){
  DIR * d;
  d = opendir("./");
  struct dirent *entry;
  struct stat *info;
  int total = 0;

  entry = readdir(d);

  printf("Directories:\n");
  while (entry){
    if (entry->d_type == DT_DIR){
      // stat(entry->d_name, info);
      // total += info->st_size;
      printf("\t%s\n",entry->d_name);
    }
    entry = readdir(d);
  }
  closedir(d);

  d = opendir("./");
  printf("\nRegular Files:\n");
  entry = readdir(d);
  while (entry){
    if (entry->d_type == DT_REG){
      // stat(entry->d_name, info);
      // total += info->st_size;
      printf("\t%s\n",entry->d_name);
    }
    entry = readdir(d);
  }
  closedir(d);

  d = opendir("./");
  printf("\nOther files:\n");
  entry = readdir(d);
  while (entry){
    if (entry->d_type != DT_DIR && entry->d_type != DT_REG){
      // stat(entry->d_name, info);
      // total += info->st_size;
      printf("\t%s\n",entry->d_name);
    }
    entry = readdir(d);
  }
  closedir(d);
}
