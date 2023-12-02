//
// Created by rolho on 20/11/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Définition de la structure Noeud
struct Noeud {
    int sommet;
    struct Noeud* suivant;
};

// Définition de la structure Graphe
struct Graphe {
    int numSommets;
    struct Noeud** listesAdjacence;
};

// Structure pour le degré des sommets
struct DegreSommet {
    int sommet;
    int degre;
};

// Création d'un nouveau nœud
struct Noeud* creerNoeud(int v) {
    struct Noeud* nouveauNoeud = malloc(sizeof(struct Noeud));
    nouveauNoeud->sommet = v;
    nouveauNoeud->suivant = NULL;
    return nouveauNoeud;
}

// Création d'un graphe
struct Graphe* creerGraphe(int sommets) {
    struct Graphe* graphe = malloc(sizeof(struct Graphe));
    graphe->numSommets = sommets;

    graphe->listesAdjacence = malloc(sommets * sizeof(struct Noeud*));
    for (int i = 0; i < sommets; i++) {
        graphe->listesAdjacence[i] = NULL;
    }
    return graphe;
}

// Ajout d'une arête au graphe
void ajouterArete(struct Graphe* graphe, int src, int dest) {
    src--; // Ajuster pour l'indexation à partir de 0
    dest--;

    struct Noeud* nouveauNoeud = creerNoeud(dest);
    nouveauNoeud->suivant = graphe->listesAdjacence[src];
    graphe->listesAdjacence[src] = nouveauNoeud;

    nouveauNoeud = creerNoeud(src);
    nouveauNoeud->suivant = graphe->listesAdjacence[dest];
    graphe->listesAdjacence[dest] = nouveauNoeud;
}

// Fonction pour calculer le degré de chaque sommet
void calculerDegres(struct Graphe* graphe, struct DegreSommet degres[]) {
    for (int i = 0; i < graphe->numSommets; i++) {
        struct Noeud* temp = graphe->listesAdjacence[i];
        degres[i].sommet = i;
        degres[i].degre = 0;
        while (temp) {
            degres[i].degre++;
            temp = temp->suivant;
        }
    }
}

// Fonction de comparaison pour le tri
int comparerDegres(const void* a, const void* b) {
    struct DegreSommet* a1 = (struct DegreSommet*)a;
    struct DegreSommet* b1 = (struct DegreSommet*)b;
    return b1->degre - a1->degre;
}

// Coloriage du graphe selon l'algorithme de Welsh-Powell
void colorerGrapheWelshPowell(struct Graphe* graphe) {
    struct DegreSommet degres[graphe->numSommets];
    calculerDegres(graphe, degres);

    qsort(degres, graphe->numSommets, sizeof(degres[0]), comparerDegres);

    int couleur[graphe->numSommets];
    bool disponible[graphe->numSommets];

    int maxCouleur = 0;

    for (int i = 0; i < graphe->numSommets; i++) {
        couleur[i] = -1;
        disponible[i] = true;
    }

    for (int i = 0; i < graphe->numSommets; i++) {
        int u = degres[i].sommet;

        struct Noeud* temp = graphe->listesAdjacence[u];
        while (temp) {
            if (couleur[temp->sommet] != -1) {
                disponible[couleur[temp->sommet]] = false;
            }
            temp = temp->suivant;
        }

        int cr;
        for (cr = 0; cr < graphe->numSommets; cr++) {
            if (disponible[cr]) break;
        }

        couleur[u] = cr;

        for (int j = 0; j < graphe->numSommets; j++) {
            disponible[j] = true;
        }

        if (cr > maxCouleur) {
            maxCouleur = cr;
        }
    }

    // Affichage des stations
    printf("Optimisation en fonction de la contrainte d'exclusion : \n");
    printf("Nombre optimal de stations : %d\n", maxCouleur + 1);
    for (int i = 0; i <= maxCouleur; i++) {
        printf("->WS%d(", i + 1);
        for (int u = 0; u < graphe->numSommets; u++) {
            if (couleur[u] == i) {
                printf("%d, ", u + 1);
            }
        }
        printf(")\n");
    }
}

// Fonction principale
int main() {
    FILE *file = fopen("graphe.txt", "r");
    if (file == NULL) {
        printf("Erreur à l'ouverture du fichier\n");
        return -1;
    }

    int maxIndex = 0;
    int src, dest;
    while (fscanf(file, "%d %d", &src, &dest) != EOF) {
        if (src > maxIndex) maxIndex = src;
        if (dest > maxIndex) maxIndex = dest;
    }

    struct Graphe* graphe = creerGraphe(maxIndex + 1);
    fseek(file, 0, SEEK_SET);

    while (fscanf(file, "%d %d", &src, &dest) != EOF) {
        ajouterArete(graphe, src, dest);
    }

    colorerGrapheWelshPowell(graphe);

    fclose(file);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Définition de la structure Noeud
struct Noeud {
    int sommet;
    struct Noeud* suivant;
};

// Définition de la structure Graphe
struct Graphe {
    int numSommets;
    struct Noeud** listesAdjacence;
};

// Structure pour le degré des sommets
struct DegreSommet {
    int sommet;
    int degre;
};

// Création d'un nouveau nœud
struct Noeud* creerNoeud(int v) {
    struct Noeud* nouveauNoeud = malloc(sizeof(struct Noeud));
    nouveauNoeud->sommet = v;
    nouveauNoeud->suivant = NULL;
    return nouveauNoeud;
}

// Création d'un graphe
struct Graphe* creerGraphe(int sommets) {
    struct Graphe* graphe = malloc(sizeof(struct Graphe));
    graphe->numSommets = sommets;

    graphe->listesAdjacence = malloc(sommets * sizeof(struct Noeud*));
    for (int i = 0; i < sommets; i++) {
        graphe->listesAdjacence[i] = NULL;
    }
    return graphe;
}

// Ajout d'une arête au graphe
void ajouterArete(struct Graphe* graphe, int src, int dest) {
    src--; // Ajuster pour l'indexation à partir de 0
    dest--;

    struct Noeud* nouveauNoeud = creerNoeud(dest);
    nouveauNoeud->suivant = graphe->listesAdjacence[src];
    graphe->listesAdjacence[src] = nouveauNoeud;

    nouveauNoeud = creerNoeud(src);
    nouveauNoeud->suivant = graphe->listesAdjacence[dest];
    graphe->listesAdjacence[dest] = nouveauNoeud;
}

// Fonction pour calculer le degré de chaque sommet
void calculerDegres(struct Graphe* graphe, struct DegreSommet degres[]) {
    for (int i = 0; i < graphe->numSommets; i++) {
        struct Noeud* temp = graphe->listesAdjacence[i];
        degres[i].sommet = i;
        degres[i].degre = 0;
        while (temp) {
            degres[i].degre++;
            temp = temp->suivant;
        }
    }
}

// Fonction de comparaison pour le tri
int comparerDegres(const void* a, const void* b) {
    struct DegreSommet* a1 = (struct DegreSommet*)a;
    struct DegreSommet* b1 = (struct DegreSommet*)b;
    return b1->degre - a1->degre;
}

// Coloriage du graphe selon l'algorithme de Welsh-Powell
void colorerGrapheWelshPowell(struct Graphe* graphe) {
    struct DegreSommet degres[graphe->numSommets];
    calculerDegres(graphe, degres);

    qsort(degres, graphe->numSommets, sizeof(degres[0]), comparerDegres);

    int couleur[graphe->numSommets];
    bool disponible[graphe->numSommets];

    int maxCouleur = 0;

    for (int i = 0; i < graphe->numSommets; i++) {
        couleur[i] = -1;
        disponible[i] = true;
    }

    for (int i = 0; i < graphe->numSommets; i++) {
        int u = degres[i].sommet;

        struct Noeud* temp = graphe->listesAdjacence[u];
        while (temp) {
            if (couleur[temp->sommet] != -1) {
                disponible[couleur[temp->sommet]] = false;
            }
            temp = temp->suivant;
        }

        int cr;
        for (cr = 0; cr < graphe->numSommets; cr++) {
            if (disponible[cr]) break;
        }

        couleur[u] = cr;

        for (int j = 0; j < graphe->numSommets; j++) {
            disponible[j] = true;
        }

        if (cr > maxCouleur) {
            maxCouleur = cr;
        }
    }

    // Affichage des stations
    printf("Optimisation en fonction de la contrainte d'exclusion : \n");
    printf("Nombre optimal de stations : %d\n", maxCouleur + 1);
    for (int i = 0; i <= maxCouleur; i++) {
        printf("->WS%d(", i + 1);
        for (int u = 0; u < graphe->numSommets; u++) {
            if (couleur[u] == i) {
                printf("%d, ", u + 1);
            }
        }
        printf(")\n");
    }
}

// Fonction principale
int main() {
    FILE *file = fopen("contrainte_exclusion.txt", "r");
    if (file == NULL) {
        printf("Erreur à l'ouverture du fichier\n");
        return -1;
    }

    int maxIndex = 0;
    int src, dest;
    while (fscanf(file, "%d %d", &src, &dest) != EOF) {
        if (src > maxIndex) maxIndex = src;
        if (dest > maxIndex) maxIndex = dest;
    }

    struct Graphe* graphe = creerGraphe(maxIndex + 1);
    fseek(file, 0, SEEK_SET);

    while (fscanf(file, "%d %d", &src, &dest) != EOF) {
        ajouterArete(graphe, src, dest);
    }

    colorerGrapheWelshPowell(graphe);

    fclose(file);
    return 0;
}
