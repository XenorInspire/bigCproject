#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <io.h>

#define MAX_VOLUME 30
#define MAX_MUSICS 100
#define MAX_PTS_ARTIST 1000
#define MAX_PTS_TITLE 1000

// Vérifie si un fichier existe à partir de son chemin d'accès
int8_t is_file_exists(const char * path, FILE * file_pointer){

  file_pointer = fopen(path, "r");

  if (file_pointer == NULL)
    return -1;

  fclose(file_pointer);

  return 0;

}

// Vérifie si un dossier existe à partir de son chemin d'accès
int8_t is_folder_exists(const char * path){

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


  if(is_folder_exists(songs_directory) != 0)
    return -1;

  if(is_folder_exists(fonts_directory) != 0)
    return -1;


  return 0;

}