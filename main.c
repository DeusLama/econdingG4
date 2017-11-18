#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>


int main(int argc, char ** argv)
{
  char* pathOfFile = "D:\\Users\\Luis Valdez\\Documents\\ESGI\\Annee 2017 - 2018\\Langage C\\Projet\\seven.txt";
  char* stringUserBinary;
  char hexaTemp[3] = "00\0", tempChar, binaryTemp[9] = "00000000\0";
  FILE* userFile = NULL;
  int i, y, tempHexa;
  int sizeOfFile = 0, currenChar;


  userFile = fopen(pathOfFile, "r"); //Ouverture du userFile en mode lecture

  if(userFile != NULL){

    printf("good job (ligne 20)\n");

    fseek(userFile, 0, SEEK_END);
    sizeOfFile = ftell (userFile);
    printf("la taille du userFile est %d (ligne 24)\n",sizeOfFile);

    stringUserBinary = (char*)malloc(sizeof(char)*sizeOfFile*8 + 2);
    stringUserBinary[0] = '\0';
    if(stringUserBinary!= NULL){
      printf("all Good (ligne 29)\n");
      printf("phrase à coder (ligne 30) : ");
      fseek (userFile , 0 , SEEK_SET );
      printf("%s\n", stringUserBinary);
      while(currenChar != EOF){

        currenChar = fgetc(userFile);
        if(currenChar == EOF) break;
        printf("%c", currenChar);
        tempChar = currenChar;
        for(i = 1; i > -1; i--){
          hexaTemp[i] = (int)tempChar % 16;
          tempChar = (int)tempChar / 16;
          tempHexa = hexaTemp[i];
          for(y = 7; y > -1; y--){
            if(i == 1 && y >=4){
              binaryTemp[y] = (tempHexa % 2) + 48;
              tempHexa /= 2;

            }
            else if(i == 0 && y < 4){
              binaryTemp[y] = (tempHexa % 2) + 48;
              tempHexa = tempHexa / 2;
            }
          }
        }
        fclose(userFile);
        strcat(stringUserBinary, binaryTemp);
      }
      //printf("\n%s\n", stringUserBinary);
      i = 0;
      printf("\n******** conversion binaire ********\n");
      while(stringUserBinary[i] != '\0'){
        if(i % 8 == 0 && i != 0) printf(" ");
        printf("%c", stringUserBinary[i]);
        i++;
      }
      printf("\n");
      free(stringUserBinary);
    }
    else return 0;


  }
  else printf("ouverture impossible\n");


  return 0;
}
