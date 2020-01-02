//Fonctions nécessairent pour les modes de jeu solo et multijoueur

int8_t game_solo_init(CONFIG * config_ini);

void play_solo_mode(int16_t nb_max_songs, CONFIG * config_ini, int16_t nb_players);

int8_t play_fmod_music(SONG * current_song, CONFIG * config_ini, FMOD_SONG * system_song);

void stop_music(FMOD_SONG * system_song);
