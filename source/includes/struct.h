#include "../../lib/fmod/fmod.h"

typedef struct config {

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
  char * fonts_directory;

} CONFIG;

typedef struct song {

  int32_t id;
  char title[255];
  char artist[255];
  char file_path[255];

} SONG;

typedef struct fmod_song {

  FMOD_SYSTEM * sys;
  FMOD_SOUND * sound;

} FMOD_SONG;

typedef struct player {

  char * pseudo;
  int16_t score;

} PLAYER;
