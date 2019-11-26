// #include "../lib/fmod/fmod.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdint.h>
#include <string.h>

#define SIZE_LINE 50

int32_t indexOf(char * line, char * search){

  char * result;

  if((result = strstr(line,search)) == NULL){

    return -1;

  }else{

    return result - line;

  }

}

int8_t init(char * fonts_directory, char * songs_directory, int16_t ** data){

  FILE * config;
  config = fopen("config.ini", "r");
  if(config == NULL) return -1;

  int32_t index;
  char * buffer;
  buffer = malloc(SIZE_LINE * sizeof(char));

  while(fgets(buffer, SIZE_LINE, config) != NULL){

    if((index = indexOf(buffer,"Easy level")) != NULL){

      

    }

  }


}

int main(int argc, char const *argv[]) {

  int16_t easy_level_solo_mode;
  int16_t easy_level_multi_mode;
  int16_t medium_level_solo_mode;
  int16_t medium_level_multi_mode;
  int16_t hard_level_solo_mode;
  int16_t hard_level_multi_mode;
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

  if((init(songs_directory, fonts_directory, data) != 0)
    printf("Le fichier de configuration est introuvable, le programme ne peut donc d%cmarrer",130);

  free(songs_directory);
  free(fonts_directory);

  for(int8_t i = 0; i < 9; i++)
    free(data[i]);

  free(data);

  system("pause");
  return 0;

}
