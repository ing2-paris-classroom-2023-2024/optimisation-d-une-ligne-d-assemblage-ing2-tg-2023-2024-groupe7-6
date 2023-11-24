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
