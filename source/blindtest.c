#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdint.h>
#include <string.h>

// #include "../lib/fmod/fmod.h"
#include "includes/init.h"
#include "includes/generate.h"
#include "includes/verify.h"
#include "includes/manage_song.h"

int main(int argc, char const *argv[]) {

  int8_t choice = 1;
  int8_t choice_config = 1;
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

  while((init(songs_directory, fonts_directory, data)) != 0){

    printf("Le fichier de configuration est introuvable ou les valeurs renseign%ces ne sont pas coh%crentes, le programme ne peut donc d%cmarrer\n",130,130,130);
    printf("Pour plus d'informations, consultez le fichier readme.md \n");
    printf("Voulez-vous restaurer le fichier de configuration par d%cfaut ?\n",130);
    printf("Tapez 'o' pour oui \n");
    fflush(stdin);
    scanf("%c",&choice_config);

    if(choice_config != 'o'){

      printf("Le programme va donc s'arr%cter \n",136);
      Sleep(2000);
      exit(0);

    }

    if(generate_config_ini() != 0){

      printf("Impossible de recr%cer le fichier config.ini, le programme va donc s'arr%cter \n",130,136);
      Sleep(2000);
      exit(0);

    }

  }

  free(songs_directory);
  free(fonts_directory);

  for(int8_t i = 0; i < 9; i++)
    free(data[i]);

  free(data);

  //test copy
  // if((copy_file("..\\music\\Lil_Nas_X.mp3","..\\musics")) !=0)
  //   printf("Erreur de copie \n");

  system("pause");
  return 0;

}
