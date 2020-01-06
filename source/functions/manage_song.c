#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../includes/struct.h"
#include "../includes/verify.h"
#include "../includes/xml.h"
#include "../includes/manage_song.h"

#define SIZE_LINE 200

#define XML_DEFAULT 0
#define XML_MODIFIED 1

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
int8_t create_xml(const char * file_name, int8_t mode, char ** content){

  int32_t i = 0;
  FILE * xml_file = NULL;
  xml_file = fopen(file_name,"wb");

  if(xml_file == NULL)
    return -1;

  if(mode == XML_DEFAULT){

    // char * root;
    // root = malloc(100 * sizeof(char));
    // check_memory(root);
    //
    // strcpy(root, "<songs>\n</songs>");
    // fprintf(xml_file, "%s\n",root);
    char * xml_default_content = ""
    "<songs>\n"
      "<song>\n"
        "<id>0</id>\n"
        "<title></title>\n"
        "<artist></artist>\n"
        "<file_path></file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>1</id>\n"
        "<title>Les quatre saisons</title>\n"
        "<artist>Vivaldi</artist>\n"
        "<file_path>4 saisons - Vivaldi.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>2</id>\n"
        "<title>Dream On</title>\n"
        "<artist>Aerosmith</artist>\n"
        "<file_path>Aerosmith - Dream On.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>3</id>\n"
        "<title>Be Mine</title>\n"
        "<artist>Ofenbach</artist>\n"
        "<file_path>Ofenbach - Be Mine.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>4</id>\n"
        "<title>Attention</title>\n"
        "<artist>Charlie Puth</artist>\n"
        "<file_path>Charlie Puth - Attention.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>5</id>\n"
        "<title>Dangerous</title>\n"
        "<artist>David Guetta</artist>\n"
        "<file_path>David Guetta - Dangerous.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>6</id>\n"
        "<title>Highway to Hell</title>\n"
        "<artist>ACDC</artist>\n"
        "<file_path>ACDC - Highway to Hell.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>7</id>\n"
        "<title>Fly Me To The Moon</title>\n"
        "<artist>Frank Sinatra</artist>\n"
        "<file_path>Frank Sinatra Fly Me To The Moon.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>8</id>\n"
        "<title>Giant</title>\n"
        "<artist>RagNBoneMan</artist>\n"
        "<file_path>Giant.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>9</id>\n"
        "<title>Girls Like You</title>\n"
        "<artist>Maroon five</artist>\n"
        "<file_path>Girls Like You.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>10</id>\n"
        "<title>Welcome To The Jungle</title>\n"
        "<artist>Guns N Roses</artist>\n"
        "<file_path>Guns N Roses - Welcome To The Jungle.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>11</id>\n"
        "<title>Believer</title>\n"
        "<artist>Imagine Dragons</artist>\n"
        "<file_path>imagine-dragons-believer.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>12</id>\n"
        "<title>Old Town Road</title>\n"
        "<artist>Lil Nas X</artist>\n"
        "<file_path>Lil_Nas_X - Old Town Road.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>13</id>\n"
        "<title>Lucid Dreams</title>\n"
        "<artist>Juice WRLD</artist>\n"
        "<file_path>Lucid Dreams.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>14</id>\n"
        "<title>Smells Like Teen Spirit</title>\n"
        "<artist>Nirvana</artist>\n"
        "<file_path>Nirvana - Smells Like Teen Spirit.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>15</id>\n"
        "<title>Counting Stars</title>\n"
        "<artist>Onerepublic</artist>\n"
        "<file_path>Onerepublic - Counting Stars.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>16</id>\n"
        "<title>High Hopes</title>\n"
        "<artist>Panic! At The Disco</artist>\n"
        "<file_path>Panic! At The Disco_ High Hopes.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>17</id>\n"
        "<title>Temperature</title>\n"
        "<artist>Sean Paul</artist>\n"
        "<file_path>Sean Paul - Temperature.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>18</id>\n"
        "<title>Wake me Up</title>\n"
        "<artist>Avicii</artist>\n"
        "<file_path>Wake me Up - Avicii.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>19</id>\n"
        "<title>Havana</title>\n"
        "<artist>Camilla Cabello</artist>\n"
        "<file_path>Havana.mp3</file_path>\n"
      "</song>\n"
      "<song>\n"
        "<id>20</id>\n"
        "<title>Better Now</title>\n"
        "<artist>Post Malone</artist>\n"
        "<file_path>Post Malone-Better Now.mp3</file_path>\n"
      "</song>\n"
    "</songs>";
    printf("Print\n");
    fprintf(xml_file, "%s",xml_default_content);

  }else{

    i = 0;
    while(strchr(content[i],'<') != NULL){
      fprintf(xml_file,"%s",content[i]);
      i++;
    }

  }


  fclose(xml_file);
  return 0;
}

//Retourne le pointeur du contenu du fichier dans un buffer
char * file_content(const char * file_name, int line_size){

  char * pointer_content = NULL;
  pointer_content = malloc(file_size(file_name));
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

// Supprime les informations d'une musique à partir de son ID
int8_t delete_music(const char * file_name, uint16_t id){

  uint16_t number = id;
  int32_t i = 0;
  int16_t j = 0;

  do {
      j++;
  }
  while ((number = number / 10) > 0);

  char * id_string = malloc((j + 10) * sizeof(char)); // 10 = 1 (\0) + 9 (balises <id></id>)
  check_memory(id_string);
  sprintf(id_string,"<id>%hd</id>",id);

  FILE * library = fopen(file_name,"rb");
  if (library == NULL)
    return -1;

  char * xml_content = file_content(file_name,SIZE_LINE);

  if(strstr(xml_content,id_string) == NULL)
    return -1; //l'ID en question n'existe pas

  long int number_of_lines = nb_lines(file_name);

  char * buffer = malloc(SIZE_LINE * sizeof(char));
  check_memory(buffer);

  char ** content = malloc(number_of_lines * sizeof(char *));
  if(content == NULL)
    return -2;

  for(i = 0; i < number_of_lines; i++){
    content[i] = malloc(SIZE_LINE * sizeof(char));
    check_memory(content[i]);
  }

  i = 0;
  while(fgets(buffer,SIZE_LINE,library) != NULL){

    strcpy(content[i],buffer);
    if(strstr(buffer,id_string) != NULL){

      for(j = 0; j < 6; j++){

        fgets(buffer,SIZE_LINE,library);
        if(strstr(buffer,"</songs>") != NULL){

          j = -1;
          strcpy(content[i-1],"</songs>");
          strcpy(content[i],"\0");
          break;

        }

      }
        if(j > 0)
          strcpy(content[i],buffer);

    }

    i++;
  }

  if(create_xml(file_name,XML_MODIFIED,content) != 0)
    return -1;

  return 0;

}

// Compte le nombre de lignes de la librairie XML
int32_t nb_lines(const char * file_name){

  int32_t number_of_lines = 0;
  FILE * xml_file = fopen(file_name, "r");
  int character;

  while((character = fgetc(xml_file)) != EOF)
  {

  	if(character == '\n')
  		number_of_lines++;
}

  fclose(xml_file);
  return number_of_lines;

}

//Vérifie si le fichier de librairie library.xml existe
void verify_xml(const char * file_name){
  if (does_file_exist(file_name) != 0) {
    create_xml("library.xml",XML_DEFAULT,NULL);
  }

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
  //recherche id puis incrémentation

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

//Recherche des donnes de la musique ID
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
    // ID introuvable
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

//Retourne la liste des id
unsigned int * id_list(struct xml_document * document){

  unsigned int counter = 0;
  unsigned int last_id;
  unsigned int new_id = 0;

  struct xml_node * root = xml_document_root(document);
  unsigned int children =  xml_node_children(root);

  unsigned int* ids = malloc(sizeof(unsigned int) *children);

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

  return ids;
}
