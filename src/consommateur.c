//
// Created by damien on 22/04/15.
//

#include "factorisation.h"
#include "consommateur.h"

struct facteurPremier *searchUniquePrime (struct facteurPremier* facteurPremier1, int *size)
{
    int curseur = 0;
    int indice = 0; // nombre de case(s) remplie(s) dans la liste de nombre(s) premier(s) unique
    struct facteurPremier *result;
    for (curseur; curseur < *size; curseur++){
        if (facteurPremier1[curseur].multiplicite == 1){
            result[indice].nombre = facteurPremier1[curseur].nombre;

        }

    }

    return result;
}
