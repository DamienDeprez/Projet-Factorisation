//
// Created by damien on 22/04/15.
//

#include <stdlib.h>
#include <math.h>
#include <stdint.h>

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
		if(ajout_element == 0 && (&facteurPremier1[*size-1]) == NULL) {
			struct facteurPremier *facteurPremier2;
			facteurPremier2->file = nbr->file;
			facteurPremier2->nombre = 2;
			facteurPremier2->multiplicite = count;
			facteurPremier1[*size-1] = *facteurPremier2;
			(*size)++;
		}
		else if (ajout_element == 0  && (&facteurPremier1[*size-1]) != NULL) {
			struct facteurPremier *facteurPremier2 = realloc(facteurPremier1,(sizeof facteurPremier1) * 2);
			facteurPremier2->file = nbr->file;
			facteurPremier2->nombre = 2;
			facteurPremier2->multiplicite = count;
			facteurPremier1[*size-1] = *facteurPremier2;
			(*size)++;
		}
	}

	for (i = 3; i < r ; i=i+2) {
		while (leNombre % i == 0) {
			leNombre = leNombre / i;
			count++;
			ajout_element = 0;
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
			if(ajout_element == 0 && (&facteurPremier1[*size-1]) == NULL) {
				struct facteurPremier *facteurPremier_i;
				facteurPremier_i->file = nbr->file;
				facteurPremier_i->nombre = (uint32_t) i;
				facteurPremier_i->multiplicite = count;
				int curseur2 = 0;
				while (&facteurPremier1[curseur2] != NULL) {
					curseur2 ++ ;
				}
				facteurPremier1[curseur2] = *facteurPremier_i;
				(*size)++;
			}
			else if (ajout_element == 0  && (&facteurPremier1[*size-1]) != NULL) {
				struct facteurPremier *facteurPremier_i = realloc(facteurPremier1, (sizeof facteurPremier1)* 2);
				facteurPremier_i->file = nbr->file;
				facteurPremier_i->nombre = (uint32_t) i;
				facteurPremier_i->multiplicite = count;
				facteurPremier1[*size-1] = *facteurPremier_i;
				(*size)++;
			}
			count = 0;
		}
	}
	//ajoute le dernier élement (qui est toujours un nbr premier) à la liste
	if (leNombre != 1) {
		if(ajout_element == 0 && (&facteurPremier1[*size-1]) == NULL) {
			struct facteurPremier *facteurPremier_l;
			facteurPremier_l->file = nbr->file;
			facteurPremier_l->nombre = (uint32_t) i;
			facteurPremier_l->multiplicite = count;
			int curseur2 = 0;
			while (&facteurPremier1[curseur2] != NULL) {
				curseur2 ++ ;
			}
			facteurPremier1[curseur2] = *facteurPremier_l;
			(*size)++;
		}
		else if (ajout_element == 0  && (&facteurPremier1[*size-1]) != NULL) {
			struct facteurPremier *facteurPremier_l = realloc ( facteurPremier1, (sizeof facteurPremier1) * 2);
			facteurPremier_l->file = nbr->file;
			facteurPremier_l->nombre = (uint32_t) leNombre;
			facteurPremier_l->multiplicite = 1;
			facteurPremier1[*size - 1] = *facteurPremier_l;
			(*size)++;
		}
	}
	return 0;
}

void* realloc_s (void **ptr, size_t taille)
{
	void *ptr_realloc = realloc(*ptr, taille);

	if (ptr_realloc != NULL) {
		*ptr = ptr_realloc;
	}
	return ptr_realloc;
}