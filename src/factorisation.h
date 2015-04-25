//
// Created by damien on 22/04/15.
//

/**
 * Liste de fonctions utilisées pour la décomposition de nombre en facteur premier et l'analyse des résultats
 */

#ifndef FACTORISATION_FACTORISATION_H
#define FACTORISATION_FACTORISATION_H

/*
 * structure représentant un facteur premier
 *
 * @nombre : valeur du nombre premier
 * @multiplicite : nombre de fois que le nombre premier est rencontré
 * @file : fichier dans lequel le facteur premier a été trouvé
 */
struct facteurPremier
{
	unsigned int nombre;
	int multiplicite;
	char ** file;
};
/*
 * structure représantant une liste de facteur premier %TODO type de liste (stack/queue ?)
 *
 * @factP : %TODO complèter la description
 * @precedent : %TODO complèter la description
 */
struct listeFacteurPremier
{
	struct facteurPremier* factP;
	struct listeFacteurPremier* precedent;
};

/*
 * structure représentant un nombre provenant de l'entrée
 *
 * @nombre : valeur du nombre
 * @file : fichier source du nombre
 */
struct nombre
{
	unsigned int nombre;
	char * file;
};

/*
 * factorisation
 * Factorise un nombre et ajoute le résultat au tableau des facteurs premiers
 *
 * @param nombre1 : nombre a factoriser
 * @param facteurPremier1 : tableau contenant les facteurs premiers déjà utilisé non
 * @return : 0 si pas d'erreur et 1 si erreur liste ou nombre1 sont NULL ou nombre1 n'est pas factorisable (cas 0 et 1)
 */

int factorisation (struct nombre* nombre1, struct listeFacteurPremier* liste);

#endif //FACTORISATION_FACTORISATION_H