//
// Created by rolho on 20/11/2023.
//
#include <stdbool.h>
#include <stdio.h>

#define MAX_NOEUDS 35
#define MAX_CONTRAINTES 21
#define MAX_NOM_FICHIER 256

// Fonction pour vérifier si deux opérations peuvent être affectées à la même station
bool peutAffecter(int matriceAdjacence[MAX_NOEUDS][MAX_NOEUDS], int affectations[], int op, int station, int nombreNoeuds) {
    for (int i = 0; i < nombreNoeuds; i++) {
        if (matriceAdjacence[op][i] && station == affectations[i]) {
            return false; // Les opérations adjacentes ne peuvent pas être dans la même station
        }
    }
    return true;
}

// Fonction pour vérifier si deux opérations sont exclues de la même station
bool sontExclues(int contraintes[MAX_CONTRAINTES][2], int op1, int op2, int nombreContraintes) {
    for (int i = 0; i < nombreContraintes; i++) {
        if ((contraintes[i][0] == op1 && contraintes[i][1] == op2) ||
            (contraintes[i][0] == op2 && contraintes[i][1] == op1)) {
            return true; // Les opérations sont exclues l'une de l'autre
        }
    }
    return false;
}

// Fonction pour attribuer une station à une opération
void attribuerStation(int matriceAdjacence[MAX_NOEUDS][MAX_NOEUDS], int affectations[], int couleurs[], int op, int nombreNoeuds, int contraintes[MAX_CONTRAINTES][2], int nombreContraintes) {
    for (int station = 0; station < 3; station++) {  // Utilisation de 3 stations
        // Vérifier si la station est autorisée pour cette opération en fonction des contraintes
        bool stationAutorisee = true;
        for (int i = 0; i < nombreNoeuds; i++) {
            // Vérifier si les opérations sont exclues l'une de l'autre
            if (sontExclues(contraintes, op, i, nombreContraintes) && station == affectations[i]) {
                stationAutorisee = false;
                break;
            }
        }

        // Si la station est autorisée, l'attribuer à l'opération
        if (stationAutorisee && peutAffecter(matriceAdjacence, affectations, op, station, nombreNoeuds)) {
            affectations[op] = station;
            couleurs[op] = station;  // Utilisation de la couleur pour la station
            break;
        }
    }
}

// Fonction pour effectuer la coloration du graphe
void colorationGraphe(int matriceAdjacence[MAX_NOEUDS][MAX_NOEUDS], int affectations[], int couleurs[], int nombreNoeuds, int contraintes[MAX_CONTRAINTES][2], int nombreContraintes) {
    // Initialiser les couleurs à -1 (non attribuées)
    for (int i = 0; i < nombreNoeuds; i++) {
        couleurs[i] = -1;
    }

    // Algorithme de coloration de Welsh-Powell
    for (int i = 0; i < nombreNoeuds; i++) {
        if (couleurs[i] == -1) {
            couleurs[i] = i;  // Attribuer une couleur à un nœud non coloré
            for (int j = i + 1; j < nombreNoeuds; j++) {
                if (couleurs[j] == -1 && !matriceAdjacence[i][j]) {
                    // Si le nœud j n'est pas coloré et n'est pas adjacent au nœud i, lui attribuer la même couleur
                    couleurs[j] = i;
                }
            }
        }
    }

    // Attribuer les stations aux opérations en fonction des couleurs
    for (int op = 0; op < nombreNoeuds; op++) {
        attribuerStation(matriceAdjacence, affectations, couleurs, op, nombreNoeuds, contraintes, nombreContraintes);
    }
}

// Fonction pour imprimer la répartition des opérations sur les stations
void afficherAffectations(int affectations[], int nombreNoeuds, int nombreStations) {
    printf("Repartition des operations sur les stations:\n");
    for (int station = 0; station < nombreStations; station++) {
        printf("Station %d -> ", station);
        for (int i = 0; i < nombreNoeuds; i++) {
            if (affectations[i] == station) {
                printf("Op%d ", i + 1);
            }
        }
        printf("\n");
    }
}

int main() {
    int nombreNoeuds = MAX_NOEUDS; // Directement défini à 35

    // Initialisation de la matrice d'adjacence
    int matriceAdjacence[MAX_NOEUDS][MAX_NOEUDS] = {{0}};

    // Lecture des arêtes du graphe depuis le fichier
    FILE *fichierGrapheAretes = fopen("graphe.txt", "r");
    if (fichierGrapheAretes == NULL) {
        perror("Erreur lors de l'ouverture du fichier graphe.txt");
        return 1;
    }

    int noeud1, noeud2;
    while (1) {
        if (fscanf(fichierGrapheAretes, "%d %d", &noeud1, &noeud2) != 2) {
            break;
        }
        matriceAdjacence[noeud1 - 1][noeud2 - 1] = 1;
        matriceAdjacence[noeud2 - 1][noeud1 - 1] = 1;
    }

    fclose(fichierGrapheAretes);

    // Saisie du nom du fichier contenant les contraintes d'exclusion
    char nomFichier[MAX_NOM_FICHIER];
    printf("Entrez le nom du fichier contenant les contraintes d'exclusion : ");
    scanf("%s", nomFichier);

    // Lecture des contraintes d'exclusion depuis le fichier
    FILE *fichierContraintes = fopen(nomFichier, "r");
    if (fichierContraintes == NULL) {
        perror("Erreur lors de l'ouverture du fichier de contraintes");
        return 1;
    }

    // Tableau pour suivre les stations attribuées à chaque opération
    int affectations[MAX_NOEUDS] = {0};

    // Tableau pour stocker les contraintes d'exclusion
    int contraintes[MAX_CONTRAINTES][2] = {{0}};
    int nombreContraintes = 0;

    // Boucle pour lire les contraintes d'exclusion depuis le fichier
    while (fscanf(fichierContraintes, "%d %d", &contraintes[nombreContraintes][0], &contraintes[nombreContraintes][1]) == 2) {
        nombreContraintes++;
    }

    fclose(fichierContraintes);

    // Tableau pour stocker les couleurs attribuées à chaque nœud
    int couleurs[MAX_NOEUDS];

    // Appliquer la coloration du graphe
    colorationGraphe(matriceAdjacence, affectations, couleurs, nombreNoeuds, contraintes, nombreContraintes);

    // Affichage des stations attribuées aux nœuds (opérations)
    afficherAffectations(affectations, nombreNoeuds, 3);  // Utilisation de 3 stations

    return 0;
}