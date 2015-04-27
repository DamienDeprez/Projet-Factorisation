//
// Created by damien on 22/04/15.
//

#include <stdlib.h>
#include <math.h>

#include "factorisation.h"


/*
 * liste est null a l'appel de la fonction
 */
int factorisation (struct nombre* nbr, struct listeFacteurPremier* liste)
{
	if(liste == NULL || nbr == NULL)
	{
		return 1;
	}

	if(nbr ->nombre == 0 || nbr->nombre == 1)
	{
		return 1;
	}

	int count = 0;
	int i = 2;
	int leNombre = nbr->nombre;
	double r = sqrt(leNombre);

	while (leNombre % i == 0)
	{
		leNombre = leNombre/i;
		count++;
	}
	if (count != 0)
	{
		struct facteurPremier* facteurPremier2 = malloc(sizeof *facteurPremier2);
		facteurPremier2->file = (char**) nbr->file; // %TODO ok
		facteurPremier2->nombre = (unsigned) 2;
		facteurPremier2->multiplicite = count;
		liste->factP = facteurPremier2;
		liste->precedent = NULL;
	}

	for (i=3; i<r ; i+=2) {
		count = 0;
		while (leNombre % i == 0) {
			leNombre = leNombre / i;
			count++;
		}
		if (count != 0)
		{
			struct facteurPremier* facteurPremier_i = malloc(sizeof *facteurPremier_i);
			facteurPremier_i->file = (char**) nbr->file;
			facteurPremier_i->nombre = (unsigned) i;
			facteurPremier_i->multiplicite = count;
			if (liste != NULL) {
				struct listeFacteurPremier* suivantListe;
				suivantListe->factP = facteurPremier_i;
				suivantListe->precedent = liste;
			}
			else
			{
				liste->factP = facteurPremier_i;
				liste->precedent = NULL;
			}
		}
	}
	//ajoute le dernier élement (qui est toujours un nbr premier) à la liste
	struct facteurPremier* facteurPremier_l = malloc(sizeof *facteurPremier_l);
	facteurPremier_l->file = (char**) nbr->file;
	facteurPremier_l->nombre = (unsigned) leNombre;
	facteurPremier_l->multiplicite = 1;
	return 0;
}