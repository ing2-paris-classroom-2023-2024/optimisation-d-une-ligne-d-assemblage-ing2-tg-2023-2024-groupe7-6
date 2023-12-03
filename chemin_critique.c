//
// Created by rolho on 03/12/2023.
//
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#define MAX_NOEUDS 100
#define CHEMIN_FICHIER "pert.txt"  // Chemin vers le fichier PERT.txt

// Structure pour représenter une tâche
typedef struct Tache{
    int debut;
    int fin;
    double duree;
} Tache;

// Fonction pour lire les tâches à partir du fichier
int lireTachesDepuisFichier(const char* cheminFichier, Tache taches[]) {
    FILE* fichier = fopen(cheminFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return -1;
    }

    int indice = 0;
    while (fscanf(fichier, "%d %d %lf", &taches[indice].debut, &taches[indice].fin, &taches[indice].duree) == 3) {
        indice++;
    }

    fclose(fichier);
    return indice;  // Retourne le nombre de tâches lues
}

// Fonction pour trouver le chemin critique
void trouverCheminCritique(Tache taches[], int nbTaches) {
    double plusLongChemin[MAX_NOEUDS] = {0};
    int predecesseurs[MAX_NOEUDS] = {0};

    for (int i = 0; i < nbTaches; i++) {
        if (plusLongChemin[taches[i].fin] < plusLongChemin[taches[i].debut] + taches[i].duree) {
            plusLongChemin[taches[i].fin] = plusLongChemin[taches[i].debut] + taches[i].duree;
            predecesseurs[taches[i].fin] = taches[i].debut;
        }
    }

    // Trouver le dernier nœud
    double dureeMax = 0;
    int dernierNoeud = 0;
    for (int i = 0; i < MAX_NOEUDS; i++) {
        if (plusLongChemin[i] > dureeMax) {
            dureeMax = plusLongChemin[i];
            dernierNoeud = i;
        }
    }

    // Retracer le chemin critique
    printf("Chemin critique (en sens inverse) : ");
    while (dernierNoeud != 0) {
        printf("%d ", dernierNoeud);
        dernierNoeud = predecesseurs[dernierNoeud];
    }
    printf("\nDuree totale : %f\n", dureeMax);
}

int main() {
    Tache taches[MAX_NOEUDS];
    int nbTaches = lireTachesDepuisFichier(CHEMIN_FICHIER, taches);

    if (nbTaches > 0) {
        trouverCheminCritique(taches, nbTaches);
    }

    return 0;
}