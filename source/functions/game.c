#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "../includes/struct.h"
#include "../includes/game.h"
#include "../includes/xml.h"
#include "../includes/manage_song.h"
#include "../includes/verify.h"
#include "../../lib/fmod/fmod.h"

// Fonction permettant de choisir le niveau de difficulté avant de démarrer la partie
int8_t game_solo_init(CONFIG * config_ini){

  char choice = '1';
  int16_t nb_max_songs;
  int16_t counter;

  while(choice > '0'){

    printf("Veuillez %c pr%csent s%cl%cctionner le niveau de difficult%c \n",133,130,130,130,130);
    printf("1 : Facile : %hd questions\n2 : Moyen : %hd questions\n3 : Difficile : %hd questions\n",config_ini->easy_level_solo_mode,config_ini->medium_level_solo_mode,config_ini->hard_level_solo_mode);
    printf("0 : Quitter\n");

    fflush(stdin);
    scanf("%c",&choice);

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

    printf("La partie commence !\n");
    play_solo_mode(nb_max_songs,config_ini,1);

  }

  return 0;

}

// Fonction pour le mode de jeu solo
void play_solo_mode(int16_t nb_max_songs, CONFIG * config_ini, int16_t nb_players){

  srand(time(NULL));
  int16_t score = 0;
  int id_music;
  int16_t index;
  SONG current_song;
  FMOD_SONG system_song;

  FILE * xml_file = NULL;
  xml_file = fopen("library.xml","rb");
  struct xml_document * document = xml_open_document(xml_file);
  unsigned int * list_id = id_list(document);

  struct xml_node * root = xml_document_root(document);
  unsigned int nb_elements =  xml_node_children(root);

  while(nb_max_songs > 0){

    do{

      index = rand() % nb_elements + 1;
      id_music = list_id[index];
      find_song(&current_song,document,id_music);
      // printf("ID : %hd\nTitle : %s\nArtist : %s\nFile Path : %s\n\n",current_song.id,current_song.title,current_song.artist,current_song.file_path);

    }
    while(play_fmod_music(&current_song,config_ini,&system_song) != 0);

    Sleep(5000);
    stop_music(&system_song);

    nb_max_songs--;

  }

  fclose(xml_file);

}

// Fonction qui permet de faire jouer la musique
int8_t play_fmod_music(SONG * current_song, CONFIG * config_ini, FMOD_SONG * system_song){

  char * song_path = malloc((strlen(current_song->file_path) + strlen(config_ini->songs_directory)) * sizeof(char));
  check_memory(song_path);

  FMOD_SYSTEM * sys;
  FMOD_SOUND * sound;
  FMOD_RESULT resultat;

  FMOD_System_Create(&sys);
  FMOD_System_Init(sys, 1, FMOD_INIT_NORMAL, NULL);

  strcpy(song_path,config_ini->songs_directory);
  strcat(song_path,current_song->file_path);

  /* On ouvre la musique */
  resultat = FMOD_System_CreateSound(sys, song_path, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &sound);

   /* On vérifie si elle a bien été ouverte (IMPORTANT) */
  if (resultat != FMOD_OK) return -1;

  /* On joue la musique */
  FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound, 0, NULL);

  system_song->sys = sys;
  system_song->sound = sound;

  return 0;

}

// Fonction qui permet de stopper la musique en cours
void stop_music(FMOD_SONG * system_song){

  FMOD_Sound_Release(system_song->sound);
  FMOD_System_Close(system_song->sys);

}
