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