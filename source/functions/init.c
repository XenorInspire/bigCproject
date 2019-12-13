#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../includes/struct.h"
#include "../includes/init.h"
#include "../includes/verify.h"

#define SIZE_LINE 80

// Renvoie la valeur numérique de la ligne de config.ini
int16_t find_value(char * line_config){

  int16_t value;
  char * trash = malloc(sizeof(char) * 20);
  check_memory(trash);
  sscanf(line_config,"%s = %hd",trash,&value);

  free(trash);
  return value;

}

// Renvoie le répertoire de la ligne de config.ini
char * find_directory(char * line_config){

  char * directory = malloc(sizeof(char) * 256);
  char * trash = malloc(sizeof(char) * 20);

  check_memory(trash);
  check_memory(directory);

  sscanf(line_config,"%s = '%s'",trash,directory);
  //on écrase le ' en fin de chaine
  directory[strlen(directory) - 1] = '\0';

  free(trash);
  return directory;

}

int8_t init(char * fonts_directory, char * songs_directory, CONFIG * config_ini){

  FILE * config;
  config = fopen("config.ini", "r");
  if(config == NULL) return -1;

  int32_t index;
  char * buffer;
  buffer = malloc(SIZE_LINE * sizeof(char));
  check_memory(buffer);

  while(fgets(buffer, SIZE_LINE, config) != NULL){

    if((strstr(buffer, "Multiplayer mode")) != NULL){

      // for(int8_t i = 0; i < 3; i++){
      //
      //   fgets(buffer, SIZE_LINE, config);
      //   *data[i] = find_value(buffer);
      //
      // }

      fgets(buffer, SIZE_LINE, config);
      config_ini->easy_level_multi_mode = find_value(buffer);
      fgets(buffer, SIZE_LINE, config);
      config_ini->medium_level_multi_mode = find_value(buffer);
      fgets(buffer, SIZE_LINE, config);
      config_ini->hard_level_multi_mode = find_value(buffer);

    }else if((strstr(buffer, "Solo mode")) != NULL){

      // for(int8_t i = 3; i < 6; i++){
      //
      //   fgets(buffer, SIZE_LINE, config);
      //   *data[i] = find_value(buffer);
      //
      // }

      fgets(buffer, SIZE_LINE, config);
      config_ini->easy_level_solo_mode = find_value(buffer);
      fgets(buffer, SIZE_LINE, config);
      config_ini->medium_level_solo_mode = find_value(buffer);
      fgets(buffer, SIZE_LINE, config);
      config_ini->hard_level_solo_mode = find_value(buffer);

    }else if((strstr(buffer, "[Music]")) != NULL){

      fgets(buffer, SIZE_LINE, config);
      strcpy(songs_directory,find_directory(buffer));
      // fgets(buffer, SIZE_LINE, config);
      // *data[6] = find_value(buffer);

      fgets(buffer, SIZE_LINE, config);
      config_ini->volume = find_value(buffer);


    }else if((strstr(buffer, "[Points]")) != NULL){

      fgets(buffer, SIZE_LINE, config);
      // *data[7] = find_value(buffer);
      config_ini->artist_score = find_value(buffer);
      fgets(buffer, SIZE_LINE, config);
      // *data[8] = find_value(buffer);
      config_ini->title_score = find_value(buffer);

    }else if((strstr(buffer, "[Fonts]")) != NULL){

      fgets(buffer, SIZE_LINE, config);
      strcpy(fonts_directory,find_directory(buffer));

    }

  }

  if((verify_values(fonts_directory,songs_directory,config_ini)) != 0)
    return -1;

  fclose(config);
  return 0;

}
