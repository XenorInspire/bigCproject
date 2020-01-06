#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../includes/struct.h"
#include "../includes/init.h"
#include "../includes/verify.h"

#define SIZE_LINE 100

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

int8_t init(CONFIG * config_ini){

  FILE * config;
  config = fopen("config.ini", "r");
  if(config == NULL) return -1;

  char * buffer;
  buffer = malloc(SIZE_LINE * sizeof(char));
  check_memory(buffer);

  while(fgets(buffer, SIZE_LINE - 1, config) != NULL){

    if((strstr(buffer, "Multiplayer mode")) != NULL){

      fgets(buffer, SIZE_LINE - 1, config);
      config_ini->easy_level_multi_mode = find_value(buffer);
      fgets(buffer, SIZE_LINE - 1, config);
      config_ini->medium_level_multi_mode = find_value(buffer);
      fgets(buffer, SIZE_LINE - 1, config);
      config_ini->hard_level_multi_mode = find_value(buffer);

    }else if((strstr(buffer, "Solo mode")) != NULL){

      fgets(buffer, SIZE_LINE - 1, config);
      config_ini->easy_level_solo_mode = find_value(buffer);
      fgets(buffer, SIZE_LINE - 1, config);
      config_ini->medium_level_solo_mode = find_value(buffer);
      fgets(buffer, SIZE_LINE - 1, config);
      config_ini->hard_level_solo_mode = find_value(buffer);

    }else if((strstr(buffer, "[Music]")) != NULL){

      fgets(buffer, SIZE_LINE - 1, config);
      strcpy(config_ini->songs_directory,find_directory(buffer));

      fgets(buffer, SIZE_LINE - 1, config);
      config_ini->volume = find_value(buffer);


    }else if((strstr(buffer, "[Points]")) != NULL){

      fgets(buffer, SIZE_LINE - 1, config);
      config_ini->artist_score = find_value(buffer);

      fgets(buffer, SIZE_LINE - 1, config);
      config_ini->title_score = find_value(buffer);

    }else if((strstr(buffer, "[Fonts]")) != NULL){

      fgets(buffer, SIZE_LINE - 1, config);
      strcpy(config_ini->fonts_directory,find_directory(buffer));

    }

  }

  fclose(config);

  if((verify_values(config_ini)) != 0)
    return -1;

  return 0;

}
