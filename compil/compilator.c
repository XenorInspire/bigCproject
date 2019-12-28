#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {

  char choice = 'o';
  while(choice == 'o'){

    if((argv[1] != NULL) && ((strnicmp(argv[1],"-c",2)) == 0)) system("clear");

    system("gcc -c ../source/functions/generate.c");
    system("gcc -c ../source/functions/init.c");
    system("gcc -c ../source/functions/verify.c");
    system("gcc -c ../source/functions/manage_song.c");
    system("gcc -c ../source/functions/xml.c");
    system("gcc -c ../source/blindtest.c");
    system("gcc -c ../source/functions/settings.c");
    system("gcc blindtest.o ../lib/fmod/libfmodex.a xml.o settings.o init.o generate.o verify.o manage_song.o -o blindtest.exe");

    system("mv generate.o ../source/functions/generate.o");
    system("mv init.o ../source/functions/init.o");
    system("mv settings.o ../source/functions/settings.o");
    system("mv verify.o ../source/functions/verify.o");
    system("mv manage_song.o ../source/functions/manage_song.o");
    system("mv xml.o ../source/functions/xml.o");
    system("mv blindtest.o ../source/blindtest.o");
    system("mv blindtest.exe ../source/blindtest.exe");

    printf("Recompiler ? (o/n) \n");
    fflush(stdin);
    scanf("%c",&choice);

  }

  return 0;
}
