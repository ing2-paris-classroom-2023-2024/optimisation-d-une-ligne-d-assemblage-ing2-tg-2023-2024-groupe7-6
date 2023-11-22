//
// Created by rolho on 22/11/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_GROUPE7_6_EXCLUSION_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_GROUPE7_6_EXCLUSION_H

#include <stdio.h>
#include <stdbool.h>

#define MAX_NOEUDS 35
#define MAX_CONTRAINTES 21

bool peutAffecter(int affectations[], int op1, int op2);
void attribuerStation(int affectations[], int op, int station);
void afficherAffectations(int affectations[], int nombreNoeuds);

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_GROUPE7_6_EXCLUSION_H
