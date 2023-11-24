//
// Created by rolho on 20/11/2023.
//
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
void attribuerStation(int matriceAdjacence[MAX_NOEUDS][MAX_NOEUDS], int affectations[], int op, int nombreNoeuds, int contraintes[MAX_CONTRAINTES][2], int nombreContraintes) {
    for (int station = 0; station < MAX_NOEUDS; station++) {
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
            break;
        }
    }
}



/ Fonction pour imprimer la répartition des opérations sur les stations
void afficherAffectations(int affectations[], int nombreNoeuds) {
    printf("Repartition des operations sur les stations:\n");
    for (int i = 0; i < nombreNoeuds; i++) {
        printf("Operation %d : Station %d\n", i + 1, affectations[i]);
    }
}



int main() {
    int nombreNoeuds;
    printf("Entrez le nombre total de noeuds (operations) : ");
    scanf("%d", &nombreNoeuds);

    // Initialisation de la matrice d'adjacence
    int matriceAdjacence[MAX_NOEUDS][MAX_NOEUDS] = {{0}};

    // Saisie des arêtes du graphe depuis la console
    printf("Saisissez les aretes du graphe (noeud1 noeud2, -1 pour terminer) :\n");
    int noeud1, noeud2;
    while (1) {
        scanf("%d %d", &noeud1, &noeud2);
        if (noeud1 == -1 || noeud2 == -1) {
            break;
        }
        matriceAdjacence[noeud1 - 1][noeud2 - 1] = 1;
        matriceAdjacence[noeud2 - 1][noeud1 - 1] = 1;
    }

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

    // Boucle pour attribuer les stations aux opérations en tenant compte des contraintes d'exclusion
    for (int op = 0; op < nombreNoeuds; op++) {
        attribuerStation(matriceAdjacence, affectations, op, nombreNoeuds, contraintes, nombreContraintes);
    }

    // Affichage des stations attribuées aux nœuds (opérations)
    afficherAffectations(affectations, nombreNoeuds);

    return 0;
}