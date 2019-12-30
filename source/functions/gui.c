//Interface graphique avec GTK

#include <gtk/gtk.h>

void play_game();

void play_game(){

  GtkWidget *game_window;
  GtkWidget *pText2;

  //Creation de la fenetre
  game_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  //Position de la fenetre
  gtk_window_set_position(GTK_WINDOW(game_window), GTK_WIN_POS_CENTER);
  //Taille de la fenêtre
  gtk_window_set_default_size(GTK_WINDOW(game_window), 1080, 920);
  //Titre de la fenetre
  gtk_window_set_title(GTK_WINDOW(game_window), "Blind Test");

  //Creation du labelpour texte
  pText2 = gtk_label_new("Blind Test");
  //Ajout du label dans la fenêtre
  gtk_container_add(GTK_CONTAINER(game_window), pText2);

  //Affichage des widgets de la fenetre
  gtk_widget_show_all(game_window);
  //Mode plein ecran
  // gtk_window_fullscreen(GTK_WINDOW(pWindow2));

}

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
  g_signal_connect(G_OBJECT(play), "clicked", G_CALLBACK(play_game), NULL);
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

int main(int argc,char **argv){
    //Ini de GTK
    gtk_init(&argc,&argv);

    //Creation du wideget pour la fenttre principale
    GtkWidget *main_window;
    menu(main_window);
    //Boucle GTK
    gtk_main();

    return 0;
}

//Compiler avec Mysys64
//gcc `pkg-config --cflags gtk+-3.0` -o gui.exe gui.c `pkg-config --libs gtk+-3.0`

//Cacher la console lors du lancement du programme
//gcc -mwindows `pkg-config --cflags gtk+-3.0` -o gui.exe gui.c `pkg-config --libs gtk+-3.0`
