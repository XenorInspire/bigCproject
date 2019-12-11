//Prototypes pour l'ajout d'une musique dans la bibliotheque

int8_t copy_file(const char * source_path, const char * dest_path);

int8_t delete_file(const char * source_file);

long int file_size(const char * path);

int8_t create_xml(const char * file_name);

char * file_content(const char * file_name, int line_size);

int8_t verify_xml(const char * file_name);
