//Interface graphique avec GTK

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include "includes/struct.h"
#include "includes/verify.h"
#include "includes/xml.h"
#include "includes/manage_song.h"
#include "includes/gui.h"




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
//gcc -c `pkg-config --cflags gtk+-3.0` gui.c `pkg-config --libs gtk+-3.0`
//gcc -c functions/xml.c
//gcc -c functions/verify.c
//gcc -c functions/manage_song.c


//gcc `pkg-config --cflags gtk+-3.0` -o blindtestGUI.exe blindtestGUI.c gui.o xml.o verify.o manage_song.o `pkg-config --libs gtk+-3.0`

//Cacher la console lors du lancement du programme
//gcc -mwindows `pkg-config --cflags gtk+-3.0` -o gui.exe gui.c `pkg-config --libs gtk+-3.0`
