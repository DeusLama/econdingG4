#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

int main(int argc, char ** argv)
{
  char* pathOfFile = "D:\\Users\\Luis Valdez\\Documents\\ESGI\\Annee 2017 - 2018\\Langage C\\Projet\\seven.txt";
  char* pathOfKey = "D:\\Users\\Luis Valdez\\Documents\\ESGI\\Annee 2017 - 2018\\Langage C\\Projet\\key.txt";
  char* stringUserBinary;
  char stringOfKey[36] = "\0";
  char * stringX;
  char hexaTemp[3] = "00\0", tempChar, binaryTemp[9] = "00000000\0", userChoice[2];
  FILE* userFile = NULL;
  int i, y, tempHexa;
  int sizeOfFile = 0, currentChar, count = 0, finalChar;
  do{
    printf("/******************************************** CODEC WITH G4 MODIFIED ********************************************/\n");
    printf(" 1 - encoder un fichier\n");
    printf(" 2 - decoder un fichier\n");
    printf(" 3 - quitter\n");
    do{
      fgets(userChoice, 2, stdin);
    }while(atoi(userChoice) >= 4 && atoi(userChoice) <= 0);

    switch (userChoice[0]) {
      case '1':
      userFile = fopen(pathOfFile, "r"); //Ouverture du userFile en mode lecture
      /******************************************** lecture et conversion en binaire du fichier ********************************************/
      if(userFile != NULL){

        printf("good job (ligne 25)\n");

        fseek(userFile, 0, SEEK_END);
        sizeOfFile = ftell (userFile);
        printf("la taille du userFile est %d (ligne 29)\n",sizeOfFile);
        stringUserBinary = (char*)malloc(sizeof(char)*sizeOfFile*8 + 2);
        stringUserBinary[0] = '\0';
        if(stringUserBinary!= NULL){
          printf("all Good (ligne 34)\n");
          printf("phrase a coder (ligne 35) : \n");
          fseek (userFile , 0 , SEEK_SET );

          while(currentChar != EOF){
            currentChar = fgetc(userFile);
            if(currentChar == EOF) break;
            printf("%c", currentChar);
            tempChar = currentChar;
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
            strcat(stringUserBinary, binaryTemp);
          }
          fclose(userFile);
          //printf("\n%s\n", stringUserBinary);
          i = 0;
          printf("\n******** conversion binaire ********\n");
          printf("%s\n", stringUserBinary);


          userFile = fopen(pathOfKey, "r");
          if(userFile != NULL){

            /******************************************** vérification de la clé et enregistrement de celle-ci ********************************************/
            fseek(userFile, 0, SEEK_END);
            sizeOfFile = ftell (userFile);
            fseek (userFile , 5 , SEEK_SET );
            if(sizeOfFile != 43){
              printf("the key is not supported");
              break;
            }

            currentChar = '\0';
            while(currentChar != 93 || currentChar == EOF){
              currentChar = fgetc(userFile);
              if(currentChar == ']') break;
              count++;
              if(currentChar != 48 && currentChar != 49 && currentChar != ' '){
                printf("%c\n", currentChar);
                printf("the key is not supported\n");
                break;
              }
            }

            if(count != 35){
              printf("the key is not supported\n");
              break;
            }
            stringOfKey[0] = '\0';
            fseek (userFile , 5 , SEEK_SET );
            i = 0;
            currentChar = '\0';
            while(currentChar != ']' || currentChar != EOF){
              currentChar = fgetc(userFile);
              if(currentChar == ']') break;
              if(currentChar == ' ')continue;
              stringOfKey[i] = currentChar;
              i++;
            }
            stringOfKey[35] = '\0';
            printf("\nkey(ligne 113) : %s, taille : %d\n", stringOfKey, strlen(stringOfKey));
            close(userFile);

            /******************************************** encodage avec la matrice G4 ********************************************/
            stringX = malloc(strlen(stringUserBinary) *2 + 1);
            if(stringX != NULL){
              stringX[0] = '\0';
              count = 0;
              for(i = 0; i < strlen(stringUserBinary);){
                //  if(i % 4 == 0) y = 0;
                for(y = 0; y < 8; y++){
                  if(((stringUserBinary[i] - '0' && stringOfKey[y] - '0') + (stringUserBinary[i + 1] - '0' && stringOfKey[y + 8] - '0') + (stringUserBinary[i + 2] - '0' && stringOfKey[y + 8 * 2] - '0') + (stringUserBinary[i + 3] - '0' && stringOfKey[y + 8 * 3] - '0')) % 2){
                    stringX[count] = '1';
                  }
                  else stringX[count] = '0';
                  count++;
                }
                i += 4;
              }
              stringX[count] = '\0';
              printf("\nencoded binary : %s\n", stringX);
              free(stringUserBinary);


              /******************************************** conversion du binaire encodé en ASCII ********************************************/
              i = 0;
              y = 128;
              finalChar = 0;
              stringUserBinary = malloc(sizeof(char) * strlen(pathOfFile) + 2);
              strcpy(stringUserBinary, pathOfFile);
              stringUserBinary[strlen(pathOfFile)] = 'c';
              stringUserBinary[strlen(pathOfFile) + 1] = '\0';
              userFile = fopen(stringUserBinary, "w+");
              if(userFile != NULL){
                while(stringX[i] != '\0'){
                  if(i % 8 == 0 && i != 0){
                    y = 128;
                    printf("%d, ", finalChar);
                    fputc(finalChar, userFile);
                    finalChar = 0;
                  }
                  finalChar += (stringX[i] - 48) * y;
                  y /= 2;
                  i++;
                }
                printf("%d, ", finalChar);
                fputc(finalChar, userFile);
                fclose(userFile);
              }
              else break;
            }
            else break;

            free(stringX);

          }
          else break;

        }
        else break;

      }
      else printf("ouverture impossible\n");
      break;

      case '2':
      break;

      case '3':
      break;

      default:
      break;
    }

  }while(userChoice[0] == 3);
  return 0;
}
