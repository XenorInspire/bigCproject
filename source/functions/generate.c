#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../includes/struct.h"
#include "../includes/generate.h"
#include "../includes/verify.h"

#define NB_CONFIG_LINES 16
#define SIZE_CONFIG_LINES 50

int8_t generate_config_ini(){

  FILE * config = fopen("config.ini","wb");
  if(config == NULL)
    return -1;

  char ** content = malloc(sizeof(char *) * NB_CONFIG_LINES); //16 étant le nombre de lignes du fichier config.ini
  if(content == NULL)
    return -1;

  for(int8_t i = 0; i < NB_CONFIG_LINES; i++){

    content[i] = malloc(sizeof(char) * SIZE_CONFIG_LINES);
    check_memory(content[i]);

  }


  strcpy(content[0],"[Number of Questions : Multiplayer mode]");
  strcpy(content[1],"Easy_level = 10");
  strcpy(content[2],"Medium_level = 15");
  strcpy(content[3],"Hard_level = 20");
  strcpy(content[4],"[Number of Questions : Solo mode]");
  strcpy(content[5],content[1]);
  strcpy(content[6],content[2]);
  strcpy(content[7],content[3]);
  strcpy(content[8],"[Music]");
  strcpy(content[9],"Directory = '../music/'");
  strcpy(content[10],"Volume = 1");
  strcpy(content[11],"[Points]");
  strcpy(content[12],"Artist = 1");
  strcpy(content[13],"Title = 1");
  strcpy(content[14],"[Fonts]");
  strcpy(content[15],"Directory = '../fonts/'");

  for(int8_t j = 0; j < NB_CONFIG_LINES; j++)
    fprintf(config, "%s \n", content[j]);

  fclose(config);

  return 0;

}
