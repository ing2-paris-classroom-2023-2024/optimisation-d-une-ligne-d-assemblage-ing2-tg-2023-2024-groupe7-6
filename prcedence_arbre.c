//
// Created by rolho on 03/12/2023.
//
#include <stdio.h>
#include <stdlib.h>

#define NOMBRE_MAX_NOEUDS 100

int n = 0;
int adj[NOMBRE_MAX_NOEUDS][NOMBRE_MAX_NOEUDS];
int degre_entrant[NOMBRE_MAX_NOEUDS];
int file[NOMBRE_MAX_NOEUDS];

// Fonction pour initialiser la matrice d'adjacence et le tableau de degré entrant
void initialiser_graphe() {
    for (int i = 0; i < NOMBRE_MAX_NOEUDS; i++) {
        degre_entrant[i] = -1;
        for (int j = 0; j < NOMBRE_MAX_NOEUDS; j++) {
            adj[i][j] = 0;
        }
    }
}

// Fonction pour lire le graphe depuis un fichier
void lire_graphe_depuis_fichier(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NOMBRE_MAX_NOEUDS; i++) {
        degre_entrant[i] = -1;
    }

    int de, vers;
    while (fscanf(fichier, "%d %d", &de, &vers) == 2) {
        if (degre_entrant[de] == -1) degre_entrant[de] = 0;
        if (degre_entrant[vers] == -1) degre_entrant[vers] = 0;
        adj[de][vers] = 1;
        degre_entrant[vers]++;
        if (de > n) n = de;
        if (vers > n) n = vers;
    }

    fclose(fichier);
}

// Fonction pour effectuer un tri topologique sur le graphe
void tri_topologique() {
    int debut = 0, fin = -1;
    int count = 0;
    int ordre[NOMBRE_MAX_NOEUDS];

    for (int i = 0; i < NOMBRE_MAX_NOEUDS; i++) {
        ordre[i] = -1;
    }

    for (int i = 1; i <= n; i++) {
        if (degre_entrant[i] == 0) {
            file[++fin] = i;
        }
    }

    while (debut <= fin) {
        int actuel = file[debut++];
        ordre[count++] = actuel;

        for (int i = 1; i <= n; i++) {
            if (adj[actuel][i] == 1) {
                if (--degre_entrant[i] == 0) {
                    file[++fin] = i;
                }
            }
        }
    }

    for (int i = 0; i < count; i++) {
        if (ordre[i] != -1) {
            printf("%d -> ", ordre[i]);
        }
    }
    printf("\n");
}

int main() {
    initialiser_graphe();
    lire_graphe_depuis_fichier("precedence.txt");
    tri_topologique();

    return 0;
}
