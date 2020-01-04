//Interface graphique avec GTK

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>


#include "includes/gui.h"
#include "includes/struct.h"
#include "includes/game.h"
#include "includes/xml.h"
#include "includes/manage_song.h"
#include "includes/verify.h"
#include "../lib/fmod/fmod.h"
#include "includes/settings.h"

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


//Si on veut cacher la console lors du lancement du programme
//gcc -mwindows `pkg-config --cflags gtk+-3.0` -o gui.exe gui.c `pkg-config --libs gtk+-3.0`
