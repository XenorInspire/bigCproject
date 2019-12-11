#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../includes/verify.h"

//Copie d'un fichier vers le nom du dossier
int8_t copy_file(const char * source_path, const char * dest_path){

  uint16_t ARRAY_LENGHT = 1000;
  char command[1000];

  //Suppression du chemin du fichier source
  char file_name[ARRAY_LENGHT];
  const char back_slash = '\\';
  char * res = NULL;
  res = strrchr(source_path,back_slash);

  if (res != NULL) {
    strcpy(file_name,res+1);
  }else{
    strcpy(file_name,source_path);
  }

  //Verification de la presence du fichier source
  if (does_file_exist(source_path)){
      return -1;
    }

  //Creation du dossier si inexistant
  if (does_file_exist(dest_path)) {
    sprintf(command,"mkdir %s",dest_path);
    system(command);
  }

  //Copie du fichier
  char path[ARRAY_LENGHT];
  sprintf(path,"%s\\%s",dest_path,file_name);
  sprintf(command,"cp %s %s > nul 2>&1",source_path,path);
  system(command);

  return 0;
}

//Suppression d'un fichier
int8_t delete_file(const char * source_file){

  if (remove(source_file) == 0) {
    return 0;
  }else{
    return 1;
  }

}
