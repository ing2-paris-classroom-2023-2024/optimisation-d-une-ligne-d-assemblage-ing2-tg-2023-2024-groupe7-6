//
// Created by Hugo on 25/11/2023.
//
//
// Created by Hugo on 25/11/2023.
//
#include <stdio.h>
#include "header.h"

void assignerOperationsAuxStations(t_Operation operations[], int nombre_operations, t_Station stations[], int *nombre_stations, double temps_cycle) {
    int i, j;

    // Réinitialiser le temps occupé de chaque station
    for (i = 0; i < *nombre_stations; i++) {
        stations[i].temps_occupe = 0.0;
    }

    // Assigner les opérations aux stations
    for (i = 0; i < nombre_operations; i++) {
        // Trouver la station avec le temps occupé minimum
        int min_station = 0;
        for (j = 1; j < *nombre_stations; j++) {
            if (stations[j].temps_occupe < stations[min_station].temps_occupe) {
                min_station = j;
            }
        }

        // Assigner l'opération à la station
        printf("Assigner l'opération %d à la station %d\n", operations[i].numero, stations[min_station].numero);
        stations[min_station].temps_occupe += operations[i].temps_execution;
    }

    // Mettre à jour le nombre de stations
    *nombre_stations = *nombre_stations;  // Vous devrez remplacer cela par la logique réelle pour mettre à jour le nombre de stations
}