//
// Created by damien on 22/04/15.
//

/**
 * Liste de fonctions utilisées pour la décomposition de nombre en facteur premier et l'analyse des résultats
 */

#ifndef FACTORISATION_FACTORISATION_H
#define FACTORISATION_FACTORISATION_H

#include <stdint.h>

/*
 * structure représentant un facteur premier
 *
 * @nombre : valeur du nombre premier
 * @multiplicite : nombre de fois que le nombre premier est rencontré
 * @file : dernier input danslequel le nombre a été trouvé
 */
struct facteurPremier
{
	uint32_t nombre;
	int multiplicite;
	char * file;
};

/*
 * structure représentant un nombre provenant de l'entrée
 *
 * @nombre : valeur du nombre
 * @file : fichier source du nombre
 */
struct nombre
{
	uint64_t nombre;
	char * file;
};

/*
 * factorisation
 * Factorise un nombre et ajoute le résultat au tableau des facteurs premiers
 *
 * @param nombre1 : nombre a factoriser
 * @param facteurPremier1 : tableau contenant les facteurs premiers déjà utilisé non (doit être alloué par malloc ou calloc)
 * @param size : nombre de facteur premier contenu dans facteurPremier1
 * @return : 0 si pas d'erreur et 1 si erreur liste ou nombre1 sont NULL ou nombre1 n'est pas factorisable (cas 0 et 1)
 */

int factorisation (struct nombre* nombre1, struct facteurPremier* facteurPremier1, int *size);

#endif //FACTORISATION_FACTORISATION_H