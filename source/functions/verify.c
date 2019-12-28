#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <io.h>
#include <unistd.h>

#include "../includes/struct.h"
#include "../includes/verify.h"

#define MAX_VOLUME 30
#define MAX_MUSICS 100
#define MAX_PTS_ARTIST 1000
#define MAX_PTS_TITLE 1000

// Vérifie si un fichier existe à partir de son chemin d'accès
int8_t does_file_exist(const char * path){

  FILE * file_pointer = NULL;
  file_pointer = fopen(path, "r");

  if (file_pointer == NULL)
    return -1;

  fclose(file_pointer);

  return 0;
}

// Vérifie si un dossier existe à partir de son chemin d'accès
int8_t does_folder_exist(const char * path){

    if (access(path, F_OK) == -1)
        return -1;

    return 0;
}

// Vérifie la conformité des valeurs du fichier config.ini
int8_t verify_values(CONFIG * config_ini){

  if(config_ini->easy_level_solo_mode < 1 || config_ini->easy_level_solo_mode > MAX_MUSICS)
    return -1;

  if(config_ini->medium_level_solo_mode < 1 || config_ini->medium_level_solo_mode > MAX_MUSICS)
    return -1;

  if(config_ini->hard_level_solo_mode < 1 || config_ini->hard_level_solo_mode > MAX_MUSICS)
    return -1;


  if(config_ini->easy_level_multi_mode < 1 || config_ini->easy_level_multi_mode > MAX_MUSICS)
    return -1;

  if(config_ini->medium_level_multi_mode < 1 || config_ini->medium_level_multi_mode > MAX_MUSICS)
    return -1;

  if(config_ini->hard_level_multi_mode < 1 || config_ini->hard_level_multi_mode > MAX_MUSICS)
    return -1;


  if(config_ini->volume < 0 || config_ini->volume > MAX_VOLUME)
    return -1;

  if(config_ini->artist_score < 0 || config_ini->artist_score > MAX_PTS_ARTIST)
    return -1;

  if(config_ini->title_score < 0 || config_ini->title_score > MAX_PTS_TITLE)
    return -1;


  if(does_folder_exist(config_ini->songs_directory) != 0)
    return -1;

  if(does_folder_exist(config_ini->fonts_directory) != 0)
    return -1;

  return 0;

}

//Vérifie si un pointeur a bien été correctement alloué, sinon le programme s'arrête
void check_memory(void * ptr){

  if(ptr == NULL){

    printf("Vous ne disposez pas d'assez de m%cmoire disponible, le programme va donc s'%cteindre \n",130,130);
    sleep(3000);
    exit(0);

  }

}
