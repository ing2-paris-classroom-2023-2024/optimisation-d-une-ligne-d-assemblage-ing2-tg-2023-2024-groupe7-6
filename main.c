//
// Created by quent on 20/11/2023.
//
#include <stdio.h>

int main(){

    FILE*fichier;

    char exclusion[]= "exclusions.txt.txt";
    char tableau[100];
    fichier = fopen(exclusion, "r");
    if(fichier == NULL){
        perror("erreur ouverture");
        return -1;
    }
    while(fgets(tableau, 1000, fichier)!= NULL){
        printf("%s", tableau);
    }
    fclose(fichier);
    printf("coucou");
    return 0;
}
