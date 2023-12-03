//
// Created by rolho on 03/12/2023.
//
#include <stdio.h>
#include <stdlib.h>

#define MAX_TACHES 36 // Nombre maximal de tâches

struct Tache {
    int id;
    float duree;
    float debutPlusTot;
};

float pert(int graphe[MAX_TACHES][MAX_TACHES], struct Tache taches[MAX_TACHES], int num_taches) {
    // Calcul des dates au plus tôt (DPT) pour chaque tâche
    for (int i = 0; i < num_taches; ++i) {
        float maxDebutPlusTot = 0;
        for (int j = 0; j < num_taches; ++j) {
            if (graphe[j][i] == 1) {
                if (taches[j].debutPlusTot + taches[j].duree > maxDebutPlusTot) {
                    maxDebutPlusTot = taches[j].debutPlusTot + taches[j].duree;
                }
            }
        }
        taches[i].debutPlusTot = maxDebutPlusTot;
    }

    // Recherche de la tâche finale pour obtenir la durée minimale du projet
    float minDuree = 0;
    for (int i = 0; i < num_taches; ++i) {
        if (taches[i].debutPlusTot + taches[i].duree > minDuree) {
            minDuree = taches[i].debutPlusTot + taches[i].duree;
        }
    }

    return minDuree;
}

int main() {
    FILE *fichier = fopen("operation.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    int graphe[MAX_TACHES][MAX_TACHES] = {0}; // Matrice d'adjacence pour représenter le graphe
    struct Tache taches[MAX_TACHES];

    int a, b;
    float duree;
    int num_taches = 0;

    while (fscanf(fichier, "%d %d %f", &a, &b, &duree) == 3) {
        graphe[a - 1][b - 1] = 1;
        taches[num_taches].id = b;
        taches[num_taches].duree = duree;
        taches[num_taches].debutPlusTot = 0;
        num_taches++;
    }

    fclose(fichier);

    float minDuree = pert(graphe, taches, num_taches);
    printf("Duree minimale du projet : %.2f seconde(s).\n", minDuree);

    return 0;
}
