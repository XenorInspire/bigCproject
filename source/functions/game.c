#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../includes/struct.h"
#include "../includes/game.h"
#include "../includes/xml.h"
#include "../includes/manage_song.h"
#include "../includes/verify.h"
#include "../../lib/fmod/fmod.h"

#define MAX_STR_USER 200
#define LINE_SCORE 300

// Fonction permettant de choisir le niveau de difficulté avant de démarrer la partie en multi
int8_t game_multi_init(CONFIG * config_ini){

  char choice = '1';
  int16_t nb_max_songs;
  int16_t counter;
  int16_t nb_players;
  int16_t * score_players;
  PLAYER * list_players;

  while(choice > '0'){

    printf("Veuillez s%cl%cctionner le nombre de joueurs\n2 joueurs minimum\n5 Joueurs maximum\n",130,130);
    scanf("%hd",&nb_players);

    while(nb_players < 2 || nb_players > 5){

      printf("Erreur, veuillez entrer un nombre de joueur entre 2 et 5 maximum\n");
      scanf("%hd",&nb_players);

    }

    list_players = malloc(nb_players * sizeof(PLAYER));
    check_memory(list_players);

    printf("A pr%csent, s%cl%cctionnez les pseudos de chacun des joueurs \n",130,130,130);

    for(counter = 0; counter < nb_players; counter++){

      list_players[counter].pseudo = malloc(MAX_STR_USER * sizeof(char));
      check_memory(list_players[counter].pseudo);

      printf("Joueur %hd\n",counter + 1);
      fflush(stdin);
      fgets(list_players[counter].pseudo,MAX_STR_USER - 1,stdin);

      if(list_players[counter].pseudo[strlen(list_players[counter].pseudo) - 1] == '\n')
        list_players[counter].pseudo[strlen(list_players[counter].pseudo) - 1] = '\0';

    }

    printf("Enfin, veuillez s%cl%cctionner le niveau de difficult%c \n",130,130,130);
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
    play_multi_mode(nb_max_songs * nb_players,config_ini,nb_players,list_players);
    display_multi_score(nb_players, list_players);

    printf("Voulez-vous recommencer une nouvelle partie ?\n1 : Oui\n0 : Non\n");
    fflush(stdin);
    scanf("%c", &choice);

    for(counter = 0; counter<nb_players; counter++)
      free(list_players[counter].pseudo);

    free(list_players);

  }

  return 0;

}


// Fonction permettant de choisir le niveau de difficulté avant de démarrer la partie en solo
int8_t game_solo_init(CONFIG * config_ini){

  char choice = '1';
  char choice_score;
  int16_t nb_max_songs;
  PLAYER solo_player;

  while(choice > '0'){

    solo_player.pseudo = malloc(MAX_STR_USER * sizeof(char));
    check_memory(solo_player.pseudo);

    printf("Veuillez saisir votre pseudo\n");
    fflush(stdin);
    fgets(solo_player.pseudo,MAX_STR_USER - 1,stdin);

    if(solo_player.pseudo[strlen(solo_player.pseudo) - 1] == '\n')
      solo_player.pseudo[strlen(solo_player.pseudo) - 1] = '\0';

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

    printf("%s, la partie commence !\n",solo_player.pseudo);
    play_solo_mode(nb_max_songs,config_ini,&solo_player);
    printf("Partie termin%ce !\nVotre score est de %hd !\nVoulez-vous l'enregistrer ? \n",130,solo_player.score);
    printf("o\\n\n");
    fflush(stdin);
    scanf("%c", &choice_score);

    if(choice_score == 'o' || choice_score == 'O')
      if(save_score(&solo_player) != 0)
        printf("Impossible d'enregistrer votre score \n");

    printf("Voulez-vous recommencer une nouvelle partie ?\n1 : Oui\n0 : Non\n");
    fflush(stdin);
    scanf("%c", &choice);
    free(solo_player.pseudo);

  }

  return 0;

}

// Fonction pour le mode de jeu solo
void play_solo_mode(int16_t nb_max_songs, CONFIG * config_ini, PLAYER * solo_player){

  srand(time(NULL));
  int32_t id_music;
  int16_t index;
  int16_t temp = 0;
  int16_t questions = 1;
  int16_t counter = 0;
  SONG current_song;
  FMOD_SONG system_song;
  solo_player->score = 0;

  char * title_input = malloc(MAX_STR_USER * sizeof(char));
  char * artist_input = malloc(MAX_STR_USER * sizeof(char));

  check_memory(title_input);
  check_memory(artist_input);

  FILE * xml_file = NULL;
  xml_file = fopen("library.xml","rb");
  struct xml_document * document = xml_open_document(xml_file);
  unsigned int * list_id = id_list(document);

  struct xml_node * root = xml_document_root(document);
  unsigned int nb_elements =  xml_node_children(root);

  // Tant que l'utilisateur n'a pas répondu à toutes les questions
  while(counter < nb_max_songs){

    printf("Question %hd !\n",questions);

    do{

      index = rand() % (nb_elements - 1) + 1;
      while(index == temp) //on évite que la prochaine musique soit la même que la précédente
        index = rand() % (nb_elements - 1) + 1;

      id_music = list_id[index];
      find_song(&current_song,document,id_music);

    }
    while(play_fmod_music(&current_song,config_ini,&system_song) != 0);

    SLEEP(15000);

    stop_music(&system_song);

    printf("L'%ccoute est maintenant termin%ce, veuillez saisir le titre de la musique \n",130,130);
    fflush(stdin);
    fgets(title_input,MAX_STR_USER - 1,stdin);
    printf("Veuillez %c pr%csent saisir l'artiste\n",133,130);
    fflush(stdin);
    fgets(artist_input,MAX_STR_USER - 1,stdin);

    if(artist_input[strlen(artist_input) - 1] == '\n')
      artist_input[strlen(artist_input) - 1] = '\0';

    if(title_input[strlen(title_input) - 1] == '\n')
      title_input[strlen(title_input) - 1] = '\0';

    // On compare le nom de l'artiste de la librairie avec celui données par l'utilisateur
    if(stricmp(current_song.artist,artist_input) == 0){

      printf("Bien jou%c ! Vous avez trouv%c l'artiste !\n",130,130);
      solo_player->score = solo_player->score + config_ini->artist_score;

    }else{

      printf("Rat%c ! Ce n'%ctait pas le bon artiste. Il s'agissait de %s \n",130,130,current_song.artist);

    }

    // On compare le nom de titre de la musique de la librairie avec celui données par l'utilisateur
    if(stricmp(current_song.title,title_input) == 0){

      printf("Bien jou%c ! Vous avez trouv%c le bon titre !\n",130,130);
      solo_player->score = solo_player->score + config_ini->title_score;

    }else{

      printf("Rat%c ! Ce n'%ctait pas le bon titre. Il s'agissait de %s \n",130,130,current_song.title);

    }

    counter++;
    temp = index;
    questions++;

  }

  free(artist_input);
  free(title_input);
  fclose(xml_file);
  xml_document_free(document, false);
}

// Fonction pour le mode de jeu multijoueur
void play_multi_mode(int16_t nb_max_songs, CONFIG * config_ini, int16_t nb_players, PLAYER * list_players){

  srand(time(NULL));
  int32_t id_music;
  int16_t index_music = -1;
  int16_t index_players = 0;
  int16_t temp = 0;
  int16_t questions = 1;
  SONG current_song;
  FMOD_SONG system_song;

  char * title_input = malloc(MAX_STR_USER * sizeof(char));
  char * artist_input = malloc(MAX_STR_USER * sizeof(char));

  check_memory(title_input);
  check_memory(artist_input);

  for(int8_t i = 0; i < nb_players; i++)
    list_players[i].score = 0;

  FILE * xml_file = NULL;
  xml_file = fopen("library.xml","rb");
  struct xml_document * document = xml_open_document(xml_file);
  unsigned int * list_id = id_list(document);

  struct xml_node * root = xml_document_root(document);
  unsigned int nb_elements =  xml_node_children(root);

  // Tant que l'utilisateur n'a pas répondu à toutes les questions
  while(nb_max_songs > 0){


    index_players = nb_max_songs % nb_players;
    printf("Question %hd pour %s\n",questions,list_players[index_players].pseudo);

    do{

      index_music = rand() % (nb_elements - 1) + 1;
      while(index_music == temp) //on évite que la prochaine musique soit la même que la précédente
        index_music = rand() % (nb_elements - 1) + 1;

      id_music = list_id[index_music];
      find_song(&current_song,document,id_music);

    }
    while(play_fmod_music(&current_song,config_ini,&system_song) != 0);

    SLEEP(15000);
    stop_music(&system_song);

    printf("L'%ccoute est maintenant termin%ce, veuillez saisir le titre de la musique \n",130,130);
    fflush(stdin);
    fgets(title_input,MAX_STR_USER - 1,stdin);
    printf("Veuillez %c pr%csent saisir l'artiste \n",133,130);
    fflush(stdin);
    fgets(artist_input,MAX_STR_USER - 1,stdin);

    if(artist_input[strlen(artist_input) - 1] == '\n')
      artist_input[strlen(artist_input) - 1] = '\0';

    if(title_input[strlen(title_input) - 1] == '\n')
      title_input[strlen(title_input) - 1] = '\0';

    // On compare le nom de l'artiste de la librairie avec celui données par l'utilisateur
    if(stricmp(current_song.artist,artist_input) == 0){

      printf("Bien jou%c ! Vous avez trouv%c l'artiste !\n",130,130);
      list_players[index_players].score = list_players[index_players].score + config_ini->artist_score;

    }else{

      printf("Rat%c ! Ce n'%ctait pas le bon artiste. Il s'agissait de %s \n",130,130,current_song.artist);

    }

    // On compare le nom de titre de la musique de la librairie avec celui données par l'utilisateur
    if(stricmp(current_song.title,title_input) == 0){

      printf("Bien jou%c ! Vous avez trouv%c le bon titre !\n",130,130);
      list_players[index_players].score = list_players[index_players].score + config_ini->title_score;

    }else{

      printf("Rat%c ! Ce n'%ctait pas le bon titre. Il s'agissait de %s \n",130,130,current_song.title);

    }

    nb_max_songs--;
    temp = index_music;
    questions++;

  }

  free(artist_input);
  free(title_input);
  fclose(xml_file);
  xml_document_free(document, false);

}

// Fonction qui permet de faire jouer la musique
int8_t play_fmod_music(SONG * current_song, CONFIG * config_ini, FMOD_SONG * system_song){

  char * song_path = malloc((strlen(current_song->file_path) + strlen(config_ini->songs_directory)) * sizeof(char));
  check_memory(song_path);

  FMOD_SYSTEM * sys;
  FMOD_SOUND * sound;
  FMOD_RESULT resultat;
  FMOD_CHANNEL * channel;

  FMOD_System_Create(&sys);
  FMOD_System_Init(sys, 1, FMOD_INIT_NORMAL, NULL);

  strcpy(song_path,config_ini->songs_directory);
  strcat(song_path,current_song->file_path);

  /* On ouvre la musique */
  resultat = FMOD_System_CreateSound(sys, song_path, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &sound);

   /* On vérifie si elle a bien été ouverte */
  if (resultat != FMOD_OK) return -1;

  FMOD_System_GetChannel(sys,1, &channel);
  FMOD_Channel_SetVolume(channel, config_ini->volume);

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
  FMOD_System_Release(system_song->sys);

}

// Fonction de sauvegarde du score en mode solo
int8_t save_score(PLAYER * solo_player){

  FILE * score_backup;
  score_backup = fopen("score.txt","ab");

  if(score_backup == NULL)
    return -1;

  fprintf(score_backup,"%s | Score : %hd\n",solo_player->pseudo,solo_player->score);
  return 0;

}

// Fonction d'affichage des scores en mode multi
void display_multi_score(int16_t nb_players, PLAYER * list_players){

  int8_t winner;
  int32_t max = 0;

  printf("Fin de la partie !\nVoici la liste des scores\n");
  for(int8_t i = 0; i<nb_players; i++){

    printf("%s, tu as obtenu un score de %hd !\n",list_players[i].pseudo,list_players[i].score);
    if(max < list_players[i].score){

      max = list_players[i].score;
      winner = i;

    }

  }

  printf("Le gagnant est %s avec un score de %hd, bravo %c toi !!\n",list_players[winner].pseudo,list_players[winner].score,133);

}

// Fonction d'affichage des 10 meilleurs joueurs (mode solo)
int8_t display_score(){

  FILE * score_list;
  score_list = fopen("score.txt","rb");
  if(score_list == NULL)
    return -1;

  int32_t size_file = nb_lines("score.txt");
  int16_t score;
  PLAYER temp;
  temp.pseudo = malloc(MAX_STR_USER * sizeof(char));
  check_memory(temp.pseudo);

  char * buffer = malloc(LINE_SCORE * sizeof(char));
  check_memory(buffer);
  PLAYER * players = malloc(size_file * sizeof(PLAYER));
  check_memory(players);

  for(int16_t i = 0; i < size_file; i++){

   players[i].pseudo = malloc(MAX_STR_USER * sizeof(char));
   check_memory(players[i].pseudo);

   fgets(buffer, LINE_SCORE - 1, score_list);
   sscanf(buffer, "%s | Score : %hd", players[i].pseudo,&score);
   players[i].score = score;
  }

  // Tri du tableau players en fonction du score des joueurs (tri décroissant)
  for(int16_t j = 0; j < size_file; j++) {
    for(int16_t k = j; k < size_file; k++) {

      if(players[k].score > players[j].score){

        temp = players[k];
        players[k] = players[j];
        players[j] = temp;

      }

    }
  }

  if(size_file > 10) // On affiche seulement les 10 meilleurs joueurs
    size_file = 10;

  for(int16_t m = 0; m < size_file; m++)
    printf("%hd : %s avec %hd point(s)\n",m,players[m].pseudo,players[m].score);

  printf("\n");
  free(players);
  free(buffer);

 return 0;

}
