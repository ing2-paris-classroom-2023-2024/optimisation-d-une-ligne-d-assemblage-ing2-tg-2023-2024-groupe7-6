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
#include <stdio.h>
#include "projet.h"

    int main(void){
        int nbre_operations=0;
        int nb_op_max=0;
        int nv_stations=0;

        nbre_operations=nb_operations("../operations.txt");
        nb_op_max=num_operation_max("../operations.txt");

        printf("operations maximum :%d\n",nb_op_max);

        t_graphe *graphe1=creer_graphe(nb_op_max);
        t_graphe *graphe_exclu_temps;

        graphe1->tab_operations_reelles=creation_tab_op_reelles("../operations.txt", graphe1);

        graphe1=fichier_exclusion("../exclusions.txt", graphe1);
        graphe1->nb_stations=nb_mini_stations_exclu(graphe1);

        t_graphe *stations_excl=creation_graphe_stations_exclusion(graphe1,"../operations.txt","../temps_cycle.txt");

        printf("\nTemps de cycle : %.2f\n",stations_excl->temps_cycle);

        //Affichage_stations(stations_excl);
        nv_stations=nb_nv_stations_necessaires_exclusion_temps(stations_excl);

        t_graphe *mix_exclu_temps=creation_stations_temps_exclusion(stations_excl, nv_stations);

        stations_excl->nb_stations=graphe1->nb_stations;
        mix_exclu_temps->nb_stations=stations_excl->nb_stations+nv_stations;

        printf("Nouvelles stations:%d\n",nv_stations);
        printf("Temps de cycle graphe mix: %.2f\n",mix_exclu_temps->temps_cycle);

        Affichage_stations(mix_exclu_temps);
        mix_exclu_temps=associer_operations_exclusion_temps(mix_exclu_temps,nv_stations);
        Affichage_stations(mix_exclu_temps);
        free(graphe1->tab_operations_reelles);
        liberation_memoire_graphe_stations(stations_excl);
        libeartion_memoire_graphe_contraintes(graphe1);

        return 0;
    }



    return 0;
    
}