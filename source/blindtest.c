#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

// #include "../lib/fmod/fmod.h"
#include "includes/struct.h"
#include "includes/init.h"
#include "includes/generate.h"
#include "includes/verify.h"
#include "includes/manage_song.h"

int main(int argc, char const *argv[]) {

  int8_t choice = 1;
  int8_t choice_config = 1;
  CONFIG config_ini;

  char * songs_directory;
  songs_directory = malloc(256 * sizeof(char));

  char * fonts_directory;
  fonts_directory = malloc(256 * sizeof(char));

  check_memory(songs_directory);
  check_memory(fonts_directory);

  while((init(&songs_directory, &fonts_directory, &config_ini)) != 0){

    printf("Le fichier de configuration est introuvable ou les valeurs renseign%ces ne sont pas coh%crentes, le programme ne peut donc d%cmarrer\n",130,130,130);
    printf("Pour plus d'informations, consultez le fichier readme.md \n");
    printf("Voulez-vous restaurer le fichier de configuration par d%cfaut ?\n",130);
    printf("Tapez 'o' pour oui \n");
    fflush(stdin);
    scanf("%c",&choice_config);

    if(choice_config != 'o'){

      printf("Le programme va donc s'arr%cter \n",136);
      sleep(2000);
      exit(0);

    }

    if(generate_config_ini(&config_ini, DEFAULT_GEN) != 0){

      printf("Impossible de recr%cer le fichier config.ini, le programme va donc s'arr%cter \n",130,136);
      sleep(2000);
      exit(0);

    }

  }

  // main_settings(&config_ini, &songs_directory);

  //test config.ini
  printf("Mode Multijoueur :\n\nEasy : %hd\nMedium : %hd\nHard : %hd\n\n",config_ini.easy_level_multi_mode,config_ini.medium_level_multi_mode,config_ini.hard_level_multi_mode);
  printf("Mode Solo :\n\nEasy : %hd\nMedium : %hd\nHard : %hd\n\n",config_ini.easy_level_solo_mode,config_ini.medium_level_solo_mode,config_ini.hard_level_solo_mode);
  printf("Volume : %hd\n\n",config_ini.volume);
  printf("Score : \n\nArtist : %hd\nTitle : %hd\n\n",config_ini.artist_score,config_ini.title_score);

  printf("Fonts : %s\n\nMusics : %s\n\n",fonts_directory,songs_directory);


  free(songs_directory);
  free(fonts_directory);


  //test copy
  // if((copy_file("..\\music\\Lil_Nas_X.mp3","..\\musics")) !=0)
  //   printf("Erreur de copie \n");

  system("pause");
  return 0;

}
