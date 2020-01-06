// Fonctions de vérification qui permettent le bon fonctionnement du programme

int8_t does_file_exist(const char *);

int8_t does_folder_exist(const char *);

int8_t verify_values(CONFIG *);

void check_memory(void *);

#ifdef _WIN32
  #include <windows.h>
  #define SLEEP(x) Sleep(x)
#else
  #include <unistd.h>
  #define SLEEP(x) sleep(x * 0.001)
#endif
