#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include "../lib/fmod/fmod.h"
#include "includes/struct.h"
#include "includes/game.h"
#include "includes/init.h"
#include "includes/generate.h"
#include "includes/verify.h"
#include "includes/xml.h"
#include "includes/manage_song.h"
#include "includes/settings.h"

#ifdef _WIN32
  #include <windows.h>
  #define SLEEP(x) Sleep(x)
#else
  #include <unistd.h>
  #define SLEEP(x) sleep(x * 0.001)
#endif

int main(int argc, char const *argv[]) {

  int8_t choice = 1;
  int8_t choice_config = 1;
  CONFIG config_ini;

  config_ini.songs_directory = malloc(256 * sizeof(char));
  config_ini.fonts_directory = malloc(256 * sizeof(char));

  check_memory(config_ini.songs_directory);
  check_memory(config_ini.fonts_directory);

  while((init(&config_ini)) != 0){

    printf("Le fichier de configuration est introuvable ou les valeurs renseign%ces ne sont pas coh%crentes, le programme ne peut donc d%cmarrer\n",130,130,130);
    printf("Pour plus d'informations, consultez le fichier readme.md \n");
    printf("Voulez-vous restaurer le fichier de configuration par d%cfaut ?\n",130);
    printf("Tapez 'o' pour oui \n");
    fflush(stdin);
    scanf("%c",&choice_config);

    if(choice_config != 'o'){

      printf("Le programme va donc s'arr%cter \n",136);
      SLEEP(2000);
      exit(0);

    }

    if(generate_config_ini(&config_ini, DEFAULT_GEN) != 0){

      printf("Impossible de recr%cer le fichier config.ini, le programme va donc s'arr%cter \n",130,136);
      SLEEP(2000);
      exit(0);

    }

  }

  verify_xml("library.xml");
  while (choice != '0') {

    printf("1 : Lancer le mode solo\n2 : Lancer le mode multijoueur\n3 : Param%ctres du jeu\n4 : Afficher les scores (mode solo)\n0 : Quitter\n",138);
    fflush(stdin);
    scanf("%c",&choice);

    switch (choice) {
      case '1' : game_solo_init(&config_ini);// Mode solo
                 break;

      case '2' : game_multi_init(&config_ini); // Mode multijoueur
                 break;

      case '3' : main_settings(&config_ini); // Paramètres du jeu
                 break;

      case '4' : if(display_score() != 0) // Affichages des scores du mode multijoueur
                  printf("La liste des scores est vide \n");
                 break;
    }

  }

  printf("A tr%cs vite pour une nouvelle partie !\n",138);
  SLEEP(2000);
  free(config_ini.songs_directory);
  free(config_ini.fonts_directory);

  return 0;

}
