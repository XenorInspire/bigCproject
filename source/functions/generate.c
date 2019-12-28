#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../includes/struct.h"
#include "../includes/generate.h"
#include "../includes/verify.h"

#define NB_CONFIG_LINES 16
#define SIZE_CONFIG_LINES 350

//Génère le config.ini
int8_t generate_config_ini(CONFIG * config_ini, int8_t mode){

    int16_t easy_level_multi_mode;
    int16_t medium_level_multi_mode;
    int16_t hard_level_multi_mode;
    int16_t easy_level_solo_mode;
    int16_t medium_level_solo_mode;
    int16_t hard_level_solo_mode;
    int16_t volume;
    int16_t artist_score;
    int16_t title_score;
    char * songs_directory = malloc(256 * sizeof(char));
    char * fonts_directory = malloc(256 * sizeof(char));

    check_memory(songs_directory);
    check_memory(fonts_directory);

  if(mode == DEFAULT_GEN){

    easy_level_multi_mode = 10;
    medium_level_multi_mode = 15;
    hard_level_multi_mode = 20;
    easy_level_solo_mode = 10;
    medium_level_solo_mode = 15;
    hard_level_solo_mode = 20;
    volume = 1;
    artist_score = 1;
    title_score = 1;
    strcpy(songs_directory,"../music/");
    strcpy(fonts_directory, "../fonts/");

  }else{

    if(verify_values(config_ini) != 0)
      return -1;

    if(mode == GEN_SONGS)
      strcat(config_ini->songs_directory,"\\music");

    easy_level_multi_mode = config_ini->easy_level_multi_mode;
    medium_level_multi_mode = config_ini->medium_level_multi_mode;
    hard_level_multi_mode = config_ini->hard_level_multi_mode;
    easy_level_solo_mode = config_ini->easy_level_solo_mode;
    medium_level_solo_mode = config_ini->medium_level_solo_mode;
    hard_level_solo_mode = config_ini->hard_level_solo_mode;
    volume = config_ini->volume;
    artist_score = config_ini->artist_score;
    title_score = config_ini->title_score;
    strcpy(songs_directory,config_ini->songs_directory);
    strcpy(fonts_directory, config_ini->fonts_directory);

  }

  FILE * config = fopen("config.ini","wb");
  if(config == NULL)
    return -1;

  char * temp = malloc(SIZE_CONFIG_LINES * sizeof(char));
  check_memory(temp);

  char ** content = malloc(sizeof(char *) * NB_CONFIG_LINES);
  if(content == NULL)
    return -1;

  for(int8_t i = 0; i < NB_CONFIG_LINES; i++){

    content[i] = malloc(sizeof(char) * SIZE_CONFIG_LINES);
    check_memory(content[i]);

  }


  strcpy(content[0],"[Number of Questions : Multiplayer mode]");

  sprintf(temp,"Easy_level = %hd",easy_level_multi_mode);
  strcpy(content[1],temp);

  sprintf(temp,"Medium_level = %hd",medium_level_multi_mode);
  strcpy(content[2],temp);

  sprintf(temp,"Hard_level = %hd",hard_level_multi_mode);
  strcpy(content[3],temp);

  strcpy(content[4],"[Number of Questions : Solo mode]");
  sprintf(temp,"Easy_level = %hd",easy_level_solo_mode);
  strcpy(content[5],temp);

  sprintf(temp,"Medium_level = %hd",medium_level_solo_mode);
  strcpy(content[6],temp);

  sprintf(temp,"Hard_level = %hd",hard_level_solo_mode);
  strcpy(content[7],temp);

  strcpy(content[8],"[Music]");
  sprintf(temp, "Directory = '%s'", songs_directory);
  strcpy(content[9],temp);

  sprintf(temp,"Volume = %hd",volume);
  strcpy(content[10],temp);

  strcpy(content[11],"[Points]");
  sprintf(temp,"Artist = %hd",artist_score);
  strcpy(content[12],temp);

  sprintf(temp,"Title = %hd",title_score);
  strcpy(content[13],temp);

  strcpy(content[14],"[Fonts]");
  sprintf(temp, "Directory = '%s'", fonts_directory);
  strcpy(content[15],temp);

  for(int8_t j = 0; j < NB_CONFIG_LINES; j++)
    fprintf(config, "%s \n", content[j]);

  fclose(config);

  return 0;

}
