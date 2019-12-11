#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {

  char choice = 'o';
  char choice_launch;

  printf("Avec lancement automatique du programme ? (o/n)\n");
  scanf("%c",&choice_launch);

  while(choice == 'o'){

    system("gcc -c ../source/functions/generate.c");
    system("gcc -c ../source/functions/init.c");
    system("gcc -c ../source/functions/verify.c");
    system("gcc -c ../source/functions/manage_song.c");
    system("gcc -c ../source/functions/xml.c");
    system("gcc -c ../source/blindtest.c");
    system("gcc blindtest.o xml.o init.o generate.o verify.o manage_song.o -o blindtest.exe");

    system("mv generate.o ../source/functions/generate.o");
    system("mv init.o ../source/functions/init.o");
    system("mv verify.o ../source/functions/verify.o");
    system("mv manage_song.o ../source/functions/manage_song.o");
    system("mv xml.o ../source/functions/xml.o");
    system("mv blindtest.o ../source/blindtest.o");
    system("mv blindtest.exe ../source/blindtest.exe");

    if(choice_launch == 'o') {
      system("start ../source/blindtest.exe");
    }

    printf("Recompiler ? (o/n) \n");
    fflush(stdin);
    scanf("%c",&choice);

  }

  return 0;
}
