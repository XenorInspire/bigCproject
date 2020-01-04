//Fonctions nécessairent pour les modes de jeu solo et multijoueur

int8_t game_solo_init(CONFIG * config_ini);

void play_solo_mode(int16_t nb_max_songs, CONFIG * config_ini, PLAYER * solo_player);

int8_t play_fmod_music(SONG * current_song, CONFIG * config_ini, FMOD_SONG * system_song);

void stop_music(FMOD_SONG * system_song);

int8_t save_score(PLAYER * solo_player);

int8_t game_multi_init(CONFIG * config_ini);

int16_t * play_multi_mode(int16_t nb_max_songs, CONFIG * config_ini, int16_t nb_players);
