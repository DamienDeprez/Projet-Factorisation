//
// Created by damien on 22/04/15.
//

#include <stdlib.h>
#include <math.h>

#include "factorisation.h"


/*
 * liste est null a l'appel de la fonction
 */
int factorisation (struct nombre* nbr, struct facteurPremier* facteurPremier1, int *size)
{
	// on ne peut avoir de liste vide
	if(facteurPremier1 == NULL || nbr == NULL)
	{
		return 1;
	}
	// 0 et 1 ne sont pas des nombres premiers
	if(nbr ->nombre == 0 || nbr->nombre == 1)
	{
		return 1;
	}

	int count = 0;
	uint64_t leNombre = nbr->nombre;
	uint64_t r = (uint64_t) sqrt(leNombre);
	int i = 2;
	int ajout_element = 0;


	while (leNombre % i == 0)
	{
		leNombre = leNombre/i;
		count++;
	}
	// ajout du nombre premier 2 si le nombre de depart est au moins une fois divisible par 2
	if (count != 0)
	{
		int curseur = 0;	// indice de deplacement dans le tableau
		for(facteurPremier1[curseur]; curseur < *size ;curseur++) {

			if(facteurPremier1[curseur].nombre == 2) {
				facteurPremier1[curseur].multiplicite += count;
				ajout_element = 1;
			}
		}
		if (ajout_element == 0) {
			struct facteurPremier *facteurPremier2 = realloc(facteurPremier1,sizeof facteurPremier1+1);
			facteurPremier2->file = nbr->file;
			facteurPremier2->nombre = (uint32_t) 2;
			facteurPremier2->multiplicite = count;
		}
	}

	for (i = 3; i < r ; i=i+2) {
		count = 0;
		while (leNombre % i == 0) {
			leNombre = leNombre / i;
			count++;
		}
		if (count != 0)
		{
			int curseur = 0;
			for(facteurPremier1[curseur]; curseur < *size ;curseur++) {

				if(facteurPremier1[curseur].nombre == i) {
					facteurPremier1[curseur].multiplicite += count;
					ajout_element = 1;
				}
			}
			if (ajout_element == 0) {
				struct facteurPremier *facteurPremier_i = realloc(facteurPremier1, sizeof facteurPremier1 + 1);
				facteurPremier_i->file =  nbr->file;
				facteurPremier_i->nombre = (uint32_t) i;
				facteurPremier_i->multiplicite = count;
			}

		}
	}
	if (leNombre != 1) {
		//ajoute le dernier élement (qui est toujours un nbr premier) à la liste
		struct facteurPremier *facteurPremier_l = realloc(facteurPremier1, sizeof facteurPremier1 + 1);
		facteurPremier_l->file = nbr->file;
		facteurPremier_l->nombre = (unsigned) leNombre;
		facteurPremier_l->multiplicite = 1;
	}
	return 0;
}