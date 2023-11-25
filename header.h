//
// Created by Hugo on 25/11/2023.
//

#ifndef PROJET_INGE2_HEADER_H
#define PROJET_INGE2_HEADER_H
#define MAX_STATIONS 30
#define MAX_OPERATIONS 150

//Structure pour stocker les informations sur chaque opération
typedef struct
{
    int numero;
    double temps_execution;
}t_Operation;

//Structure pour stocker les informations sur chaque station
typedef struct
{
    int numero;
    double temps_occupe;
}t_Station;
#endif //PROJET_INGE2_HEADER_H
