//Mode de génération de config.ini
#define DEFAULT_GEN 0
#define GEN_EMM 1
#define GEN_MMM 2
#define GEN_HMM 3
#define GEN_ESM 4
#define GEN_MSM 5
#define GEN_HSM 6
#define GEN_SONGS 7
#define GEN_VOL 8

// Fonction qui génère le fichier config.ini

int8_t generate_config_ini(CONFIG * config_ini, int8_t mode);
