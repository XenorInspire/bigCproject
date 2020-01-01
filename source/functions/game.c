#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "../includes/struct.h"

int8_t game_solo_mode(CONFIG * config_ini){

  char choice = 0;
  int16_t nb_max_songs;
  int16_t counter;

  printf("Veuillez %c pr%csent s%cl%cctionner le niveau de diffuclt%c \n",133,130,130,130,130);
  printf("1 : Facile : %hd questions\n2 : Moyen : %hd questions\n3 : Difficile : %hd questions\n",config_ini->easy_level_solo_mode,config_ini->medium_level_solo_mode,config_ini->hard_level_solo_mode);
  printf("0 : Quitter\n");

  fflush(stdin);
  scanf("%c",&choice);

  printf("La partie commence !\n");

  switch(choice){

    case 48 : return 0;
              break;

    case 49 : nb_max_songs = config_ini->easy_level_solo_mode;
              break;

    case 50 : nb_max_songs = config_ini->medium_level_solo_mode;
              break;

    case 51 : nb_max_songs = config_ini->hard_level_solo_mode;
              break;

  }


}
