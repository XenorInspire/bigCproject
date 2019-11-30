#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
/*
Copie d'un fichier
source_path: chemin du fichier
dest_path : seulement le nom du repertoire de destination
Retourne 0 si la copie s'est bien effectuée
Retourne 1 si le fichier est introuvable
*/
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
  FILE * source_file = NULL;
  source_file = fopen(source_path,"rb");
  if (source_file == NULL) {
    //printf("Le fichier est introuvable\n");
    return 1;
  }

  //Creation du dossier si inexistant
  char path[ARRAY_LENGHT];
  sprintf(path,"%s\\%s",dest_path,file_name);

  FILE * dest_file = NULL;
  dest_file = fopen(path,"wb");
  if (dest_file == NULL) {
    // printf("Le dossier 'musics' n'existe pas\n");
    sprintf(command,"mkdir %s",dest_path);
    system(command);
  }

  //Copie du fichier
  sprintf(command,"cp %s %s > nul 2>&1",source_path,path);
  system(command);

  fclose(dest_file);
  fclose(source_file);

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
