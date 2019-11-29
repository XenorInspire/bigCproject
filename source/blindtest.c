// #include "../lib/fmod/fmod.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdint.h>
#include <string.h>

#define SIZE_LINE 80

// Renvoie la valeur numérique de la ligne de config.ini
int16_t find_value(char * line_config){

  int16_t value;
  char * trash = malloc(sizeof(char) * 20);
  sscanf(line_config,"%s = %hd",trash,&value);

  free(trash);
  return value;

}

// Renvoie le répertoire de la ligne de config.ini
char * find_directory(char * line_config){

  char * temp = malloc(sizeof(char) * 256);
  char * directory = malloc(sizeof(char) * 256);
  char * trash = malloc(sizeof(char) * 20);

  sscanf(line_config,"%s = '%s'",trash,directory);
  //on supprime le ' en fin de chaine
  directory[strlen(directory) - 1] = '\0';

  free(trash);
  return directory;

}

int8_t init(char * fonts_directory, char * songs_directory, int16_t ** data){

  FILE * config;
  config = fopen("config.ini", "r");
  if(config == NULL) return -1;

  int32_t index;
  char * buffer;
  buffer = malloc(SIZE_LINE * sizeof(char));

  while(fgets(buffer, SIZE_LINE, config) != NULL){

    if((strstr(buffer, "Multiplayer mode")) != NULL){

      for(int8_t i = 0; i < 3; i++){

        fgets(buffer, SIZE_LINE, config);
        *data[i] = find_value(buffer);

      }

    }else if((strstr(buffer, "Solo mode")) != NULL){

      for(int8_t i = 3; i < 6; i++){

        fgets(buffer, SIZE_LINE, config);
        *data[i] = find_value(buffer);

      }

    }else if((strstr(buffer, "[Music]")) != NULL){

      fgets(buffer, SIZE_LINE, config);
      strcpy(songs_directory,find_directory(buffer));
      fgets(buffer, SIZE_LINE, config);
      *data[6] = find_value(buffer);

    }else if((strstr(buffer, "[Points]")) != NULL){

      fgets(buffer, SIZE_LINE, config);
      *data[7] = find_value(buffer);
      fgets(buffer, SIZE_LINE, config);
      *data[8] = find_value(buffer);

    }else if((strstr(buffer, "[Fonts]")) != NULL){

      fgets(buffer, SIZE_LINE, config);
      strcpy(fonts_directory,find_directory(buffer));

    }

  }

  fclose(config);

}

/*
Copie d'un fichier
sourcePath: chemin du fichier
destPath : seulement le nom du repertoire de destination
Retourne 0 si la copie s'est bien effectue
Retourne 1 si le fichier est introuvable
*/
int8_t copyFile(const char * sourcePath, const char * destPath){

  uint16_t  ARRAY_LENGHT = 1000;
  char command[1000];

  //Suppression du chemin du fichier source
  char fileName[ARRAY_LENGHT];
  const char backSlash = '\\';
  char * res = NULL;
  res = strrchr(sourcePath,backSlash);

  if (res != NULL) {
    strcpy(fileName,res+1);
  }else{
    strcpy(fileName,sourcePath);
  }

  //Verification de la presence du fichier source
  FILE * sourceFile = NULL;
  sourceFile = fopen(sourcePath,"rb");
  if (sourceFile == NULL) {
    //printf("Le fichier est introuvable\n");
    return 1;
  }

  //Creation du dossier si inexistant
  char path[ARRAY_LENGHT];
  sprintf(path,"%s\\%s",destPath,fileName);

  FILE * destFile = NULL;
  destFile = fopen(path,"wb");
  if (destFile == NULL) {
    // printf("Le dossier 'musics' n'existe pas\n");
    sprintf(command,"mkdir %s",destPath);
    system(command);
  }

  // copy sous windows et cp sous Linux
  sprintf(command,"copy %s %s > nul 2>&1",sourcePath,path);
  system(command);

  fclose(destFile);
  fclose(sourceFile);

  return 0;
}

int main(int argc, char const *argv[]) {

  int16_t easy_level_multi_mode;
  int16_t medium_level_multi_mode;
  int16_t hard_level_multi_mode;
  int16_t easy_level_solo_mode;
  int16_t medium_level_solo_mode;
  int16_t hard_level_solo_mode;
  int16_t volume;
  int16_t artist_score;
  int16_t title_score;

  char * songs_directory;
  songs_directory = malloc(256 * sizeof(char));

  char * fonts_directory;
  fonts_directory = malloc(256 * sizeof(char));

  int16_t ** data;
  data = malloc(9 * sizeof(int16_t*));
  data[0] = &easy_level_solo_mode;
  data[1] = &easy_level_multi_mode;
  data[2] = &medium_level_solo_mode;
  data[3] = &medium_level_multi_mode;
  data[4] = &hard_level_solo_mode;
  data[5] = &hard_level_multi_mode;
  data[6] = &volume;
  data[7] = &artist_score;
  data[8] = &title_score;

  if((init(songs_directory, fonts_directory, data)) != 0){

    printf("Le fichier de configuration est introuvable, le programme ne peut donc d%cmarrer",130);
    exit(0);

  }

  printf("Multijoueur :\nEasy level : %hd\nMedium level : %hd\nHard level : %hd\n\n",easy_level_multi_mode,medium_level_multi_mode,hard_level_multi_mode);
  printf("Solo :\nEasy level : %hd\nMedium level : %hd\nHard level : %hd\n\n",easy_level_solo_mode,medium_level_solo_mode,hard_level_solo_mode);
  printf("Music\nDirectory : %s\nVolume : %hd\n\n",songs_directory,volume);
  printf("Points\nArtist : %hd\nTitle : %hd\n\n",artist_score,title_score);
  printf("Fonts\nDirectory : %s\n\n",fonts_directory);

  free(songs_directory);
  free(fonts_directory);

  for(int8_t i = 0; i < 9; i++)
    free(data[i]);

  free(data);

  //test copy 
  //copyFile("..\\music\\Lil_Nas_X.mp3","..\\musics");

  system("pause");
  return 0;

}
