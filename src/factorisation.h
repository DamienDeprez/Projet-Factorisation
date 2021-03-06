/**
 * Liste de fonctions utilisées pour la décomposition de nombre en facteur premier et l'analyse des résultats
 */

#ifndef FACTORISATION_FACTORISATION_H
#define FACTORISATION_FACTORISATION_H

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <inttypes.h>

/*
 * structure représentant un facteur premier
 *
 * @nombre : valeur du nombre premier
 * @multiplicite : nombre de fois que le nombre premier est rencontré
 * @file : dernier input danslequel le nombre a été trouvé
 */
struct facteurPremier {
	uint32_t nombre;
	int multiplicite;
	char *file;
};


/*
 * structure représentant un nombre provenant de l'entrée
 *
 * @nombre : valeur du nombre
 * @file : fichier source du nombre
 * @err: indique si il y a eu une erreur (fin du fichier :1 ou autre:-1 )
 */
struct nombre
{
	uint64_t nombre;
	char * file;
	int err;
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

int factorisation (struct nombre* nbr, struct facteurPremier** facteurPremier1, int *size);


/*
 * Version sécurisée de realloc
 * source : http://openclassrooms.com/courses/allocation-dynamique-en-c-complement/realloc-prototype-fonctionnement
 */
void realloc_s (void **ptr, size_t taille) ;

/*
 * realloc_zeros
 * met à 0 la mémoire de la partie réallouée
 *
 * @indiceInitial: position de départ de la mise à 0 de la liste
 * @facteurPremier1: liste des facteurs premier
 * @size: taille de la liste
 */
void realloc_zeros(int indiceInitial, struct facteurPremier* facteurPremier1, int *size);

/*
 *  searchUniquePrime
 *  cherche dans la liste globale le(s) nombre(s) premier(s) dont la multiplicite est unique7
 *
 *   @facteurPremier1: liste globale des facteur premier
 *   @size: taille de la liste
 *   @return 0 si un facteur premier a été trouvé et 1 sinon
 */
int searchUniquePrime (struct facteurPremier* facteurPremier1, int *size);

#endif //FACTORISATION_FACTORISATION_H