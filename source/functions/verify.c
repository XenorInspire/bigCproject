#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <io.h>
#include <unistd.h>

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

    // Check for file existence
    if (access(path, F_OK) == -1)
        return -1;

    return 0;
}

// Vérifie la conformité des valeurs du fichier config.ini
int8_t verify_values(char * fonts_directory,char * songs_directory,int16_t ** data){

  for(int8_t i = 0; i <= 5; i++)
    if(*data[i] < 1 || *data[i] > MAX_MUSICS)
      return -1;

  if(*data[6] < 0 || *data[6] > MAX_VOLUME)
    return -1;

  if(*data[7] < 0 || *data[7] > MAX_PTS_ARTIST)
    return -1;

  if(*data[8] < 0 || *data[8] > MAX_PTS_TITLE)
    return -1;


  if(does_folder_exist(songs_directory) != 0)
    return -1;

  if(does_folder_exist(fonts_directory) != 0)
    return -1;

  return 0;

}

void check_memory(void * ptr){

  if(ptr == NULL){

    printf("Vous ne disposez pas d'assez de m%cmoire disponible, le programme va donc s'%cteindre \n",130,130);
    sleep(3000);
    exit(0);

  }

}
