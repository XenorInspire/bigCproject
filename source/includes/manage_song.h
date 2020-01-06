//Prototypes pour l'ajout d'une musique dans la bibliotheque

int8_t copy_file(const char * source_path, const char * dest_path);

int8_t delete_file(const char * source_file);

long int file_size(const char * path);

int8_t create_xml(const char * file_name, int8_t mode, char ** content);

char * file_content(const char * file_name, int line_size);

void verify_xml(const char * file_name);

uint8_t * root_last_id(struct xml_document * document);

int8_t insert_song_data(const char *file_name, SONG * input_song);

unsigned int find_id_gap(struct xml_document * document);

void array_sort(unsigned int array[],unsigned int array_size);

void find_song(SONG * song, struct xml_document * document, int id_song);

uint8_t verify_song_insert(SONG * input_song, struct xml_document * document);

int8_t delete_music(const char * file_name, uint16_t id);

int32_t nb_lines(const char * file_name);

unsigned int * id_list(struct xml_document * document);
