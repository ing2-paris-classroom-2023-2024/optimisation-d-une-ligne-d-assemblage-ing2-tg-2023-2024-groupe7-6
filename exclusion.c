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

