#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../includes/struct.h"
#include "../includes/settings.h"
#include "../includes/verify.h"
#include "../includes/generate.h"

#define SIZE_LINE 80

//Menu principal des paramètres du jeu
void main_settings(CONFIG * config_ini){

  int8_t choice = 0;

  while(choice != '0'){

    printf("1 : Modifier le nombre de questions \n");
    printf("2 : Changer le r%cpertoire de la biblioth%cque\n",130,138);
    printf("3 : Modifier le volume\n");
    printf("0 : Quitter\n");

    fflush(stdin);
    scanf("%c",&choice);

    switch(choice){

      case 49 : m_nb_questions(config_ini);
                break;

      case 50 : m_directory_songs(config_ini);
                break;

      case 51 : m_volume(config_ini);
                break;

    }

  }

}

void m_nb_questions(CONFIG * config_ini){

  printf("Mode Multijoueur :\n\nEasy : %hd\nMedium : %hd\nHard : %hd\n\n",config_ini->easy_level_multi_mode,config_ini->medium_level_multi_mode,config_ini->hard_level_multi_mode);
  printf("Mode Solo :\n\nEasy : %hd\nMedium : %hd\nHard : %hd\n\n",config_ini->easy_level_solo_mode,config_ini->medium_level_solo_mode,config_ini->hard_level_solo_mode);

  int8_t choice = '0';
  int8_t second_choice = '0';
  int16_t value;
  int16_t temp;

  printf("1 : Mode Multijoueur\n");
  printf("2 : Mode Solo \n");
  printf("0 : Quitter\n");

  fflush(stdin);
  scanf("%c",&choice);

  if(choice != '0'){

    printf("1 : Easy Mode\n");
    printf("2 : Medium Mode \n");
    printf("3 : Hard Mode \n");

    fflush(stdin);
    scanf("%c",&second_choice);

    if(choice == '1'){

      printf("Mode Mutlijoueur : \nSaisissez la nouvelle valeur \n");
      fflush(stdin);
      scanf("%hd",&value);


      if(second_choice == '1'){

        temp = config_ini->easy_level_multi_mode;
        config_ini->easy_level_multi_mode = value;

        if((generate_config_ini(config_ini, GEN_EMM)) != 0){

          printf("Impossible de modifier la valeur, celle-ci n'est pas correcte \n");
          config_ini->easy_level_multi_mode = temp;

        }

      }else if(second_choice == '2'){

        temp = config_ini->medium_level_multi_mode;
        config_ini->medium_level_multi_mode = value;

        if((generate_config_ini(config_ini, GEN_MMM)) != 0){

          printf("Impossible de modifier la valeur, celle-ci n'est pas correcte \n");
          config_ini->medium_level_multi_mode = temp;

        }

      }else if(second_choice == '3'){

        temp = config_ini->hard_level_multi_mode;
        config_ini->hard_level_multi_mode = value;

        if((generate_config_ini(config_ini, GEN_HMM)) != 0){

          printf("Impossible de modifier la valeur, celle-ci n'est pas correcte \n");
          config_ini->hard_level_multi_mode = temp;

        }

      }

    }

      if(choice == '2'){

        printf("Mode Solo : \nSaisissez la nouvelle valeur \n");
        fflush(stdin);
        scanf("%hd",&value);

        if(second_choice == '1'){

          temp = config_ini->easy_level_solo_mode;
          config_ini->easy_level_solo_mode = value;

          if((generate_config_ini(config_ini, GEN_ESM)) != 0){

            printf("Impossible de modifier la valeur, celle-ci n'est pas correcte \n");
            config_ini->easy_level_solo_mode = temp;

          }

        }else if(second_choice == '2'){

          temp = config_ini->medium_level_solo_mode;
          config_ini->medium_level_solo_mode = value;

          if((generate_config_ini(config_ini, GEN_MSM)) != 0){

            printf("Impossible de modifier la valeur, celle-ci n'est pas correcte \n");
            config_ini->medium_level_solo_mode = temp;

          }

        }else if(second_choice == '3'){

          temp = config_ini->hard_level_solo_mode;
          config_ini->hard_level_solo_mode = value;

          if((generate_config_ini(config_ini, GEN_HSM)) != 0){

            printf("Impossible de modifier la valeur, celle-ci n'est pas correcte \n");
            config_ini->hard_level_solo_mode = temp;

          }

        }

    }

  }

}

//Fonction qui permet de changer le répertoire des musiques du jeu
void m_directory_songs(CONFIG * config_ini){

  char * new_songs_directory = malloc(256 * sizeof(char));
  char * temp = malloc(256 * sizeof(char));
  check_memory(new_songs_directory);
  check_memory(temp);

  printf("Veuillez saisir le nouveau r%cpertoire des musiques\n",130);
  fflush(stdin);
  fgets(new_songs_directory, 256, stdin);

  if(new_songs_directory[strlen(new_songs_directory) - 1] == '\n')
    new_songs_directory[strlen(new_songs_directory) - 1] = '\0';

  strcpy(temp,config_ini->songs_directory);
  strcpy(config_ini->songs_directory, new_songs_directory);

  if((generate_config_ini(config_ini, GEN_SONGS)) != 0){

    printf("Impossible de modifier la valeur, celle-ci n'est pas correcte \n");
    strcpy(config_ini->songs_directory,temp);

  }

  free(temp);
  free(new_songs_directory);

}

//Fonction qui permet de changer le volume de la musique du jeu
void m_volume(CONFIG * config_ini){

  int16_t new_volume;
  int16_t temp;

  printf("Veuillez entrer le nouveau volume \n");
  scanf("%hd",&new_volume);

  temp = config_ini->volume;
  config_ini->volume = new_volume;

  if((generate_config_ini(config_ini, GEN_VOL)) != 0){

    printf("Impossible de modifier la valeur, celle-ci n'est pas correcte \n");
    config_ini->volume = temp;

  }

}
