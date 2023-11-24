
#ifndef PROJET_ING_2_HEADER_H
#define PROJET_ING_2_HEADER_H


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


#endif //PROJET_ING_2_HEADER_H
