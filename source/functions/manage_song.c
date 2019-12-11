#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../includes/verify.h"
#include "../include/xml.h"

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
  pointer_content = malloc(file_size(file_name) * sizeof(char));
  check_memory(pointer_content);

  strcpy(pointer_content,"\0");

  char buffer[line_size];
  FILE * fp = NULL;
	fp = fopen(file_name,"r");

	while (fgets(buffer,line_size,fp) != NULL) {

		strcat(pointer_content,buffer);
	}
  // printf("%s",pointer_content);
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
