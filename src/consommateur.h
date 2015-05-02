//
// Created by damien on 22/04/15.
//

/**
 * Liste de fonctions utilisées par le consommateur
 */

#ifndef FACTORISATION_CONSOMMATEUR_H
#define FACTORISATION_CONSOMMATEUR_H

#include <stdint.h>

/*
 *  searchUniquePrime cherche dans la liste globale le(s) nombre(s) premier(s) dont la multiplicite est unique
 */
struct facteurPremier *searchUniquePrime (struct facteurPremier *facteurPremier1, int *size);



#endif //FACTORISATION_CONSOMMATEUR_H
