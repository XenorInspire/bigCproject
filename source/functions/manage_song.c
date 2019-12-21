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
int8_t insert_song_data(const char *file_name, const char * title, const char * artist, const char * path){
  //recherche id puis incrementation

  FILE * xml_file = NULL;
  xml_file = fopen(file_name,"r+");

  struct xml_document * document2 = xml_open_document(xml_file);
  int last_id = atoi(root_last_id(document2)) + 1;

  xml_file = fopen(file_name,"r+");
  fseek(xml_file,-10,SEEK_END);
  fprintf(xml_file, "\t<song>\n\t\t<id>%d</id>\n\t\t<title>%s</title>\n\t\t<artist>%s</artist>\n\t\t<file_path>%s</file_path>\n\t</song>\n</songs>\n",last_id,title,artist,path);

  fclose(xml_file);
  xml_document_free(document2, false);
  return 0;

}
