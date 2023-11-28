//
// Created by rolho on 20/11/2023.
//
#include <stdbool.h>
#include <stdio.h>

#define MAX_NOEUDS 35
#define MAX_CONTRAINTES 21
#define MAX_NOM_FICHIER 256
#define NOMBRE_STATIONS 2

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

// Fonction pour compter le nombre d'arêtes liées à chaque nœud
void compterAretes(int matriceAdjacence[MAX_NOEUDS][MAX_NOEUDS], int nombreNoeuds, int degres[]) {
    for (int i = 0; i < nombreNoeuds; i++) {
        degres[i] = 0;
        for (int j = 0; j < nombreNoeuds; j++) {
            if (matriceAdjacence[i][j]) {
                degres[i]++;
            }
        }
    }
}

// Fonction pour trouver le nœud d'ordre le plus élevé
int trouverNoeudMaxDegre(int degres[], bool visite[], int nombreNoeuds) {
    int maxDegre = -1;
    int noeudMaxDegre = -1;

    for (int i = 0; i < nombreNoeuds; i++) {
        if (!visite[i] && degres[i] > maxDegre) {
            maxDegre = degres[i];
            noeudMaxDegre = i;
        }
    }

    return noeudMaxDegre;
}

// Fonction pour attribuer une station à une opération
void attribuerStation(int matriceAdjacence[MAX_NOEUDS][MAX_NOEUDS], int affectations[], int couleurs[], int op, int nombreNoeuds, int contraintes[MAX_CONTRAINTES][2], int nombreContraintes) {
    for (int station = 0; station < NOMBRE_STATIONS; station++) {  // Utilisation de NOMBRE_STATIONS stations
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

// Fonction pour effectuer la coloration du graphe en utilisant l'algorithme de Welsh-Powell
void colorationGrapheWelshPowell(int matriceAdjacence[MAX_NOEUDS][MAX_NOEUDS], int affectations[], int couleurs[], int nombreNoeuds, int contraintes[MAX_CONTRAINTES][2], int nombreContraintes) {
    int degres[MAX_NOEUDS];
    bool visite[MAX_NOEUDS] = {false};

    // Compter le nombre d'arêtes liées à chaque nœud
    compterAretes(matriceAdjacence, nombreNoeuds, degres);

    // Algorithme de Welsh-Powell
    for (int k = 0; k < nombreNoeuds; k++) {
        int noeud = trouverNoeudMaxDegre(degres, visite, nombreNoeuds);

        // Attribuer une couleur au nœud
        couleurs[noeud] = noeud;

        // Mettre à jour les degrés des nœuds adjacents
        for (int i = 0; i < nombreNoeuds; i++) {
            if (matriceAdjacence[noeud][i]) {
                degres[i]--;
            }
        }

        // Marquer le nœud comme visité
        visite[noeud] = true;
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

    // Appliquer la coloration du graphe en utilisant l'algorithme de Welsh-Powell
    colorationGrapheWelshPowell(matriceAdjacence, affectations, couleurs, nombreNoeuds, contraintes, nombreContraintes);

    // Affichage des stations attribuées aux nœuds (opérations)
    afficherAffectations(affectations, nombreNoeuds, NOMBRE_STATIONS);  // Utilisation de NOMBRE_STATIONS stations

    return 0;
}