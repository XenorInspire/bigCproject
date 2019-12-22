#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../includes/struct.h"
#include "../includes/verify.h"
#include "../includes/xml.h"
#include "../includes/manage_song.h"


//Copie d'un fichier vers le nom du dossier
int8_t copy_file(const char * source_path, const char * dest_path){

  uint16_t ARRAY_LENGHT = 1000;
  char command[1000];

  //Suppression du chemin du fichier source
  char file_name[ARRAY_LENGHT];
  const char back_slash = '\\';
  char * res = NULL;
  res = strrchr(source_path,back_slash);

  if (res != NULL) {
    strcpy(file_name,res+1);
  }else{
    strcpy(file_name,source_path);
  }

  //Verification de la presence du fichier source
  if (does_file_exist(source_path)){
      return -1;
    }

  //Creation du dossier si inexistant
  if (does_file_exist(dest_path)) {
    sprintf(command,"mkdir %s",dest_path);
    system(command);
  }

  //Copie du fichier
  char path[ARRAY_LENGHT];
  sprintf(path,"%s\\%s",dest_path,file_name);
  sprintf(command,"cp %s %s > nul 2>&1",source_path,path);
  system(command);

  return 0;
}

//Suppression d'un fichier
int8_t delete_file(const char * source_file){

  if (remove(source_file) == 0) {
    return 0;
  }else{
    return 1;
  }

}

//Donne la taille du fichier
long int file_size(const char * path){
  if (does_file_exist(path))
    return -1;

  FILE * fp = NULL;
  fp = fopen(path,"r");

  fseek(fp, 0, SEEK_END);
  long int sz = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  fclose(fp);

  return sz;

}

//Recreation du fichier xml
int8_t create_xml(const char * file_name){
  FILE * xml_file = NULL;
  xml_file = fopen(file_name,"wb");
  char * root;
  root = malloc(100 * sizeof(char));
  if (root == NULL)
    return -1;

  strcpy(root, "<songs>\n</songs>");
  fprintf(xml_file, "%s\n",root);

  fclose(xml_file);
  return 0;
}

//Retourne le pointeur du contenu du fichier dans un buffer
char * file_content(const char * file_name, int line_size){

  char * pointer_content = NULL;
  pointer_content = malloc(file_size(file_name) + 1 * sizeof(char));
  check_memory(pointer_content);

  strcpy(pointer_content,"\0");

  char buffer[line_size];
  FILE * fp = NULL;
	fp = fopen(file_name,"r");

	while (fgets(buffer,line_size,fp) != NULL) {

		strcat(pointer_content,buffer);
	}

	fclose(fp);

  return pointer_content;
}

//Verif si le fichier xml existe sinon le cree, sa structure
int8_t verify_xml(const char * file_name){
  if (does_file_exist(file_name)) {
    create_xml("library.xml");
  }
  return 0;
}

//Obtenir le dernier id song du fichier xml
uint8_t * root_last_id(struct xml_document * document){

  unsigned int children =  xml_node_children(xml_document_root(document));

  struct xml_node * root = xml_document_root(document);

  //Song node
  struct xml_node* node_song = xml_node_child(root,children-1);
  struct xml_node * node_id = xml_node_child(node_song,0);

  //Afficher le contenu du node
  struct xml_string* id = xml_node_content(node_id);

  uint8_t * content = calloc(xml_string_length(id) + 1, sizeof(uint8_t));
	xml_string_copy(id, content, xml_string_length(id));

  return content;
}

//Ajout de la musique dans le fichier xml
int8_t insert_song_data(const char *file_name, SONG * input_song){
  //recher id puis incrementation

  FILE * xml_file = NULL;
  xml_file = fopen(file_name,"r+");

  struct xml_document * document = xml_open_document(xml_file);
  int last_id = find_id_gap(document);

  xml_file = fopen(file_name,"r+");
  fseek(xml_file,-10,SEEK_END);
  fprintf(xml_file, "\t<song>\n\t\t<id>%d</id>\n\t\t<title>%s</title>\n\t\t<artist>%s</artist>\n\t\t<file_path>%s</file_path>\n\t</song>\n</songs>\n",last_id,input_song->title,input_song->artist,input_song->file_path);

  fclose(xml_file);
  xml_document_free(document, false);
  return 0;

}

//Essaie de chercher un id non utilise
unsigned int find_id_gap(struct xml_document * document){

  unsigned int counter = 0;
  unsigned int last_id;
  unsigned int new_id = 0;

  struct xml_node * root = xml_document_root(document);
  unsigned int children =  xml_node_children(root);

  unsigned int ids[children];

  while (counter < children) {
    //Song node
    struct xml_node* node_song = xml_node_child(root,counter);
    struct xml_node * node_id = xml_node_child(node_song,0);
    //Afficher le contenu du node
    struct xml_string* id = xml_node_content(node_id);
    uint8_t * content = calloc(xml_string_length(id) + 1, sizeof(uint8_t));
  	xml_string_copy(id, content, xml_string_length(id));

    last_id = atoi(content);

    ids[counter] = last_id;

    counter++;
  }

  array_sort(ids,children);

  new_id = ids[children-1] +1;

  for (size_t i = 0; i < children; i++) {
    if (i+1 != ids[i]) {
      new_id = i+1;
    }
  }

  return new_id;
}

//tri par ordre croissant les valeurs du tableau
void array_sort(unsigned int array[],unsigned int array_size){
  int tmp;
  for(int i=0; i<array_size; i++){
    for(int j=i; j<array_size; j++){
      if(array[j]<array[i]) {
        tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
      }
    }
  }
}

//Recherche des deonnes de la musique ID
void find_song(SONG * song, struct xml_document * document, int id_song){
  unsigned int counter = 0;
  int current_id = 0;

  struct xml_node * root = xml_document_root(document);
  unsigned int children =  xml_node_children(root);

  do {
    //Song node
    struct xml_node* node_song = xml_node_child(root,counter);
    //Song id
    struct xml_node * node_id = xml_node_child(node_song,0);
    //Afficher le contenu du node id
    struct xml_string* id = xml_node_content(node_id);
    uint8_t * content = calloc(xml_string_length(id) + 1, sizeof(uint8_t));
    xml_string_copy(id, content, xml_string_length(id));
    //Conversion string en int
    current_id = atoi(content);
    counter++;

  } while(current_id != id_song && counter < children);

  if (current_id != id_song) {
    printf("Id non trouvable\n");
    song -> id = 0;
    strcpy(song -> title,"NULL");
    strcpy(song -> artist, "NULL");
    strcpy(song -> file_path, "NULL");
  } else {
    //Song node
    struct xml_node* node_song = xml_node_child(root,counter -1);

    struct xml_node * node_title = xml_node_child(node_song,1);
    struct xml_node * node_artist = xml_node_child(node_song,2);
    struct xml_node * node_file_path = xml_node_child(node_song,3);

    //Afficher le contenu du node
    struct xml_string* title = xml_node_content(node_title);
    struct xml_string* artist = xml_node_content(node_artist);
    struct xml_string* file_path = xml_node_content(node_file_path);

    uint8_t * title_content = calloc(xml_string_length(title) + 1, sizeof(uint8_t));
    xml_string_copy(title,title_content, xml_string_length(title));
    strcpy(song -> title,title_content);

    uint8_t * artist_content = calloc(xml_string_length(artist) + 1, sizeof(uint8_t));
    xml_string_copy(artist,artist_content, xml_string_length(artist));
    strcpy(song -> artist,artist_content);

    uint8_t * file_path_content = calloc(xml_string_length(file_path) + 1, sizeof(uint8_t));
    xml_string_copy(file_path,file_path_content, xml_string_length(file_path));
    strcpy(song -> file_path,file_path_content);

    song -> id = current_id;

  }
}

//Verifier si les donnees de la musique ont deja ete inscrites
uint8_t verify_song_insert(SONG * input_song, struct xml_document * document){

  unsigned int counter = 0;
  struct xml_node * root = xml_document_root(document);
  unsigned int children =  xml_node_children(root);
  SONG researched_song;

  while (counter < children) {
    //Song node
    struct xml_node* node_song = xml_node_child(root,counter);

    struct xml_node * node_title = xml_node_child(node_song,1);
    struct xml_node * node_artist = xml_node_child(node_song,2);
    struct xml_node * node_file_path = xml_node_child(node_song,3);

    //Afficher le contenu du node
    struct xml_string* title = xml_node_content(node_title);
    struct xml_string* artist = xml_node_content(node_artist);
    struct xml_string* file_path = xml_node_content(node_file_path);

    uint8_t * title_content = calloc(xml_string_length(title) + 1, sizeof(uint8_t));
    xml_string_copy(title,title_content, xml_string_length(title));
    strcpy(researched_song.title,title_content);

    uint8_t * artist_content = calloc(xml_string_length(artist) + 1, sizeof(uint8_t));
    xml_string_copy(artist,artist_content, xml_string_length(artist));
    strcpy(researched_song.artist,artist_content);

    uint8_t * file_path_content = calloc(xml_string_length(file_path) + 1, sizeof(uint8_t));
    xml_string_copy(file_path,file_path_content, xml_string_length(file_path));
    strcpy(researched_song.file_path,file_path_content);

    if (strcmp(researched_song.title,input_song->title) == 0 && strcmp(researched_song.artist,input_song->artist) == 0) {
      return -1;//Le titre et l'artiste existent deja
    }

    if (strcmp(researched_song.file_path,input_song->file_path) == 0) {
      printf("Cette musique existe deja\n");
      return -2;//cette musique existe deja
    }

    counter++;
  }
	return 0;
}
