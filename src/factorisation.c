//
// Created by damien on 22/04/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <bits/mathcalls.h>

#include "factorisation.h"

struct facteurPremier
{
	unsigned int nombre;
	int multiplicite;
	char ** file;
};
struct listeFacteurPremier
{
	struct facteurPremier* factP;
	struct listeFacteurPremier* suivant;
}

struct nombre
{
	unsigned int nombre;
	char * file;
	int multiplicite;
};

/*
 * liste est null a l'appel de la fonction
 */
struct facteurPremier* factorisation (struct nombre* nbr, struct listeFacteurPremier* liste)
{
	int count = 0;
	int i = 2;
	double r = sqrt(nbr);
	int leNombre = nbr->nombre;

	while (leNombre % i == 0)
	{
		leNombre = leNombre/i;
		count++;
	}
	if (count != 0)
	{
		struct facteurPremier* facteurPremier2;
		facteurPremier2->file = (char**) nbr->file;
		facteurPremier2->nombre = (unsigned) i;
		facteurPremier2->multiplicite = count;
		liste->factP = facteurPremier2;
		liste->suivant = null;
	}

	for (i=3; i<r ; i+=2) {
		count = 0;
		while (leNombre % i == 0) {
			leNombre = leNombre / i;
			count++;
		}
		if (count != 0)
		{
			struct facteurPremier* facteurPremier_i;
			facteurPremier_i->file = (char**) nbr->file;
			facteurPremier_i->nombre = (unsigned) i;
			facteurPremier_i->multiplicite = count;
			if (liste != null) {
				liste->factP = facteurPremier_i;
				liste->suivant = null;
			}
			else
			{
				liste->factP = facteurPremier_i;
				liste->suivant = null;
			}
		}
	}
}