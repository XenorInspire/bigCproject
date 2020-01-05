#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>


#include "../includes/gui.h"
#include "../includes/struct.h"
#include "../includes/game.h"
#include "../includes/xml.h"
#include "../includes/manage_song.h"
#include "../includes/verify.h"
#include "../../lib/fmod/fmod.h"

enum {
  LIST_ITEM = 0,
  N_COLUMNS
};
GtkWidget *list;


//Ajout de la musique
void append_item(GtkWidget *widget, gpointer * song_data) {

  GtkListStore *store;
  GtkTreeIter iter;

  const gchar *file_path = gtk_entry_get_text(song_data[0]);
  const gchar *title = gtk_entry_get_text(song_data[1]);
  const gchar *artist = gtk_entry_get_text(song_data[2]);

  //Insertion dans la lsit de la fenetre
  gchar song_full_data[255] = "";
  sprintf(song_full_data,"%s - %s",title,artist);
  store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
  gtk_list_store_append(store, &iter);
  gtk_list_store_set(store, &iter, LIST_ITEM, song_full_data, -1);


  // printf("%s, %s, %s\n",file_path,title,artist);

  // //Suppression du chemin du fichier source pour mettre le bon chemin dans le xml
  char file_name[255] = "";
  const char back_slash = '\\';
  char * res = NULL;
  res = strrchr(file_path,back_slash);

  if (res != NULL) {
    strcpy(file_name,res+1);
    // sprintf(file_name,"musics\\%s",res+1);
  }else{
    // sprintf(file_name,"musics\\%s",file_path);
    strcpy(file_name,file_path);
  }


  SONG song;
  strcpy(song.title,title);
  strcpy(song.artist,artist);
  strcpy(song.file_path,file_name);

  insert_song_data("library.xml",&song);

  copy_file(file_path,"../music");


  //Enleve ce qu'on a tape
  gtk_entry_set_text(song_data[0], "");
  gtk_entry_set_text(song_data[1], "");
  gtk_entry_set_text(song_data[2], "");
}

//Retirer la Musique
void remove_item(GtkWidget *widget, gpointer delete_entry) {

  GtkListStore *store;
  GtkTreeModel *model;
  GtkTreeIter  iter;

  unsigned int delete_id = atoi(gtk_entry_get_text(delete_entry));


  //Recherche du path
  FILE * xml_file = NULL;
  xml_file = fopen("library.xml","r");

  struct xml_document * document = xml_open_document(xml_file);

  SONG delete_song;
  find_song(&delete_song, document, delete_id);
  char delete_file_path[255];
  sprintf(delete_file_path,"../music/%s",delete_song.file_path);
  printf("%s\n",delete_file_path );
  delete_file(delete_file_path);

  delete_music("library.xml", delete_id);

  store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
  model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

  if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) {
      return;
  }

  fclose(xml_file);

  // if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(delete_entry),&model, &iter)) {
  //   gtk_list_store_remove(store, &iter);
  // }


}

//Retier toute la Musique
void remove_all(GtkWidget *widget, gpointer selection) {

  GtkListStore *store;
  GtkTreeModel *model;
  GtkTreeIter  iter;

  store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
  model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

  if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) {
      return;
  }

  gtk_list_store_clear(store);
}

//Initialisation de la liste pour la fenetre
void init_list(GtkWidget *list) {

  GtkCellRenderer    *renderer;
  GtkTreeViewColumn  *column;
  GtkListStore       *store;

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes("List Item",renderer, "text", LIST_ITEM, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

  store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

  gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

  g_object_unref(store);
}

//ajout dans la liste
void add_to_list(GtkWidget *list, const gchar *str) {

  GtkListStore *store;
  GtkTreeIter iter;

  store = GTK_LIST_STORE(gtk_tree_view_get_model
      (GTK_TREE_VIEW(list)));

  gtk_list_store_append(store, &iter);
  gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);
}



//FENETRES

//Fentre pour ajouter la musique
void add_music(){
  GtkWidget *window;
  GtkWidget *sw;

  GtkWidget *remove;
  GtkWidget *add;
  GtkWidget *removeAll;
  GtkWidget *path_entry;
  GtkWidget *title_entry;
  GtkWidget *artist_entry;
  GtkWidget *delete_entry;

  GtkWidget *vbox;
  GtkWidget *hbox;

  GtkTreeSelection *selection;

  GtkWidget *path_text;
  GtkWidget *title_text;
  GtkWidget *artist_text;
  GtkWidget *delete_text;


  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title(GTK_WINDOW(window), "Musiques");
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER (window), 20);
  gtk_widget_set_size_request(window, 500, 500);

  sw = gtk_scrolled_window_new(NULL, NULL);
  list = gtk_tree_view_new();
  gtk_container_add(GTK_CONTAINER(sw), list);

  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw),GTK_SHADOW_ETCHED_IN);

  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);

  vbox = gtk_box_new(TRUE, 0);

  gtk_box_pack_start(GTK_BOX(vbox), sw, TRUE, TRUE, 5);

  hbox = gtk_box_new(FALSE, 5);

  add = gtk_button_new_with_label("Ajouter");
  remove = gtk_button_new_with_label("Supprimer");
  removeAll = gtk_button_new_with_label("Tout supprimer");

  path_entry = gtk_entry_new();
  gtk_widget_set_size_request(path_entry, 120, -1);
  path_text = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(path_text), "Chemin :");//Permettre les markup avec Pango

  title_entry = gtk_entry_new();
  gtk_widget_set_size_request(title_entry, 120, -1);
  title_text = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(title_text), "Titre :");//Permettre les markup avec Pango

  artist_entry = gtk_entry_new();
  gtk_widget_set_size_request(artist_entry, 120, -1);
  artist_text = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(artist_text), "Titre :");//Permettre les markup avec Pango

  delete_entry = gtk_entry_new();
  gtk_widget_set_size_request(delete_entry, 120, -1);
  delete_text = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(delete_text), "id :");//Permettre les markup avec Pango


  //Placement des widgets en bas
  gtk_box_pack_start(GTK_BOX(hbox), path_text, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), path_entry, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), title_text, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), title_entry, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), artist_text, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), artist_entry, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), add, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), delete_text, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), delete_entry, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), remove, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), removeAll, FALSE, TRUE, 3);

  gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, TRUE, 3);

  gtk_container_add(GTK_CONTAINER(window), vbox);

  init_list(list);

  //Recherche donnees Musiques
  FILE * xml_file = NULL;
  xml_file = fopen("library.xml","r");

  struct xml_document * document = xml_open_document(xml_file);

  struct xml_node * root = xml_document_root(document);
  unsigned int children =  xml_node_children(root);

  SONG song;
  char content[255];

  //Ajout dans la liste des musiques
  unsigned int * id_list(struct xml_document * document);

  unsigned int * list_id = id_list(document);

  for (int i = 1; i < children; i++) {
    find_song(&song,document,*(list_id+i));
    sprintf(content,"%u) %s - %s\n",song.id,song.title, song.artist);
    add_to_list(list, content);
  }

  fclose(xml_file);

  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

  // SONG_GTK * song_data = malloc(sizeof(SONG_GTK));
  // song_data->path = path_entry;
  // song_data->title = title_entry;
  // song_data->artist = artist_entry;

  //Tableau pour inserer les donnees entrees par l'utilisateur
  gpointer *song_data = g_new (gpointer, 3);
  song_data[0] = path_entry;
  song_data[1] = title_entry;
  song_data[2] = artist_entry;


  //Signaux des boutons
  g_signal_connect(G_OBJECT(add), "clicked",G_CALLBACK(append_item), song_data);

  g_signal_connect(G_OBJECT(remove), "clicked",G_CALLBACK(remove_item), delete_entry);

  g_signal_connect(G_OBJECT(removeAll), "clicked",G_CALLBACK(remove_all), selection);

  // g_signal_connect(G_OBJECT(window), "destroy",
  //         G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

}


//Fentre menu
void menu(GtkWidget* main_window){

  GtkWidget *pText;
  GtkWidget *box;
  GtkWidget *play;
  GtkWidget *musics;
  GtkWidget *settings;
  GtkWidget *quit;
  GtkWidget *separator;

  //Creation de la fenetre
  main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  //Creation de la fenetre
  gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);
  //Taille de la fenetre
  gtk_window_set_default_size(GTK_WINDOW(main_window), 500, 500);
  //Titre de la fenetre
  gtk_window_set_title(GTK_WINDOW(main_window), "Blind Test");
  //Padding interieur
  gtk_container_set_border_width(GTK_CONTAINER(main_window), 20);

  //Creation de la box contenant les widgets
  box = gtk_box_new(TRUE, 10);//TRUE = Horizontal
  gtk_container_add(GTK_CONTAINER(main_window), box);

  //Creation du label avec text
  pText = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(pText), "<u><b>The Blind Test</b></u>");//Permettre les markup avec Pango

  //Creation des bouttons
  separator = gtk_separator_new(TRUE);
  play = gtk_button_new_with_label("Jouer");
  musics = gtk_button_new_with_label("Musiques");
  settings = gtk_button_new_with_label("Paramètres");
  quit = gtk_button_new_with_label("Quitter");

  //Signaux pour les evenements
  // g_signal_connect(G_OBJECT(play), "clicked", G_CALLBACK(play_game), NULL);
  g_signal_connect(G_OBJECT(musics), "clicked", G_CALLBACK(add_music), NULL);
  g_signal_connect(G_OBJECT(quit), "clicked", G_CALLBACK(gtk_main_quit), NULL);

  //Ajouts des bouttons dans la box
  gtk_box_pack_start(GTK_BOX(box), pText, TRUE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), separator, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), play, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), musics, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), settings, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), quit, FALSE, FALSE, 0);

  //Affichage de la fenttre
  gtk_widget_show_all(main_window);

  //Signal destroy pour quitter correctetment le programme par la croix de la fenetre
  g_signal_connect(G_OBJECT(main_window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

}

// //Fenetre jeu
// void play_game(){
//
//   GtkWidget *game_window;
//   GtkWidget *pText2;
//
//   //Creation de la fenetre
//   game_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//   //Position de la fenetre
//   gtk_window_set_position(GTK_WINDOW(game_window), GTK_WIN_POS_CENTER);
//   //Taille de la fenêtre
//   gtk_window_set_default_size(GTK_WINDOW(game_window), 1080, 920);
//   //Titre de la fenetre
//   gtk_window_set_title(GTK_WINDOW(game_window), "Blind Test");
//
//   //Creation du labelpour texte
//   pText2 = gtk_label_new("Blind Test");
//   //Ajout du label dans la fenêtre
//   gtk_container_add(GTK_CONTAINER(game_window), pText2);
//
//   //Affichage des widgets de la fenetre
//   gtk_widget_show_all(game_window);
//   //Mode plein ecran
//   // gtk_window_fullscreen(GTK_WINDOW(pWindow2));
//
//
//   srand(time(NULL));
//   int id_music;
//   int16_t index = -1;
//   int16_t temp = 0;
//   SONG current_song;
//   FMOD_SONG system_song;
//
//
//   FILE * xml_file = NULL;
//   xml_file = fopen("library.xml","rb");
//   struct xml_document * document = xml_open_document(xml_file);
//   unsigned int * list_id = id_list(document);
//
//   struct xml_node * root = xml_document_root(document);
//   unsigned int nb_elements =  xml_node_children(root);
//
//   do{
//
//     index = rand() % (nb_elements - 1) + 1;
//     while(index == temp) //on évite que la prochaine musique soit la même que la précédente
//       index = rand() % (nb_elements - 1) + 1;
//
//     id_music = list_id[index];
//     find_song(&current_song,document,id_music);
//
//   }
//   while(play_fmod_music(&current_song,config_ini,&system_song) != 0);
//
//   Sleep(15000);
//   stop_music(&system_song);
//
// }
