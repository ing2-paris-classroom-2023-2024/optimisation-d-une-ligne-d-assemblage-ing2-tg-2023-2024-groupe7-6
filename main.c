//
// Created by quent on 20/11/2023.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct noeud {
    int sommet;
    struct noeud* suivant;
} Noeud;

typedef struct graphe {
    int nbSommets;
    Noeud** listesAdj;
    Noeud** listesPred;
} Graphe;

Noeud* creerNoeud(int v) {
    Noeud* nouveauNoeud = malloc(sizeof(Noeud));
    nouveauNoeud->sommet = v;
    nouveauNoeud->suivant = NULL;
    return nouveauNoeud;
}

Graphe* creerGraphe(int sommets) {
    Graphe* graphe = malloc(sizeof(Graphe));
    graphe->nbSommets = sommets ;

    graphe->listesAdj = malloc((sommets) * sizeof(Noeud*));
    graphe->listesPred = malloc(sommets * sizeof(Noeud*));

    for (int i = 0; i < sommets; i++) {
        graphe->listesAdj[i] = NULL;
        graphe->listesPred[i] = NULL;
    }

    return graphe;
}

void ajouterArc(Graphe* graphe, int src, int dest) {
    Noeud* nouveauNoeud = creerNoeud(dest);
    nouveauNoeud->suivant = graphe->listesAdj[src];
    graphe->listesAdj[src] = nouveauNoeud;
}

void ajouterPredecesseur(Graphe* graphe, int sommet, int predecesseur) {
    Noeud* nouveauNoeud = creerNoeud(predecesseur);
    nouveauNoeud->suivant = graphe->listesPred[sommet];
    graphe->listesPred[sommet] = nouveauNoeud;
}

void chargerGrapheDepuisFichier(Graphe* graphe, char* nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("erreur ouverture\n");
        return;
    }

    int src, dest;
    while (fscanf(fichier, "%d %d", &src, &dest) != EOF) {
        ajouterArc(graphe, src, dest);
        ajouterPredecesseur(graphe, dest, src);

    }

    fclose(fichier);
}

int compterArcs (Graphe* graphe){
    int nombreArcs = 0;
    for (int i = 0; i < graphe->nbSommets; i++) {
        Noeud* temp = graphe->listesAdj[i];
        while (temp != NULL) {
            nombreArcs++;
            temp = temp->suivant;
        }
    }
    return nombreArcs;
}
/*
void afficherGraphe(Graphe* graphe) {
    for (int v = 0; v < graphe->nbSommets; v++) {
        Noeud* temp = graphe->listesAdj[v];
        printf("Liste d'adjacence du sommet %d\n tete", v);
        while (temp) {
            printf(" -> %d", temp->sommet);
            temp = temp->suivant;
        }
        printf("\n");
    }
}
*/
void afficherPredecesseurs(Graphe* graphe) {

    for (int i = 1; i < graphe->nbSommets; i++) {
        printf("Predecesseurs du sommet %d: ", i);
        Noeud* temp = graphe->listesPred[i];
        if (temp == NULL) {
            printf("Aucun");
        }
        while (temp) {
            printf("%d ", temp->sommet);
            temp = temp->suivant;
        }
        printf("\n");
    }
}


int main() {

    int nbSommets = 68; // Modifier cette valeur en fonction du nombre de sommets dans votre graphe
    Graphe* graphe = creerGraphe(nbSommets);

    chargerGrapheDepuisFichier(graphe, "precedences.txt.txt");

    // afficherGraphe(graphe);
    int totalArcs = compterArcs(graphe);
    printf("\nLe nombre d'arcs total est %d\n", totalArcs);
    afficherPredecesseurs(graphe);

    // Libérer la mémoire et autres tâches de nettoyage ici si nécessaire

    return 0;


}