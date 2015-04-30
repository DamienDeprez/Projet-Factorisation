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
		if(ajout_element == 0 && (facteurPremier1[*size-1].nombre) == 0) {
			(facteurPremier1[*size-1].file) = nbr->file;
			(facteurPremier1[*size-1].nombre) = (uint32_t) 2;
			(facteurPremier1[*size-1].multiplicite) = count;
			(*size)++;
		}
		else if (ajout_element == 0  && (facteurPremier1[*size-1].nombre) != 0) {
			void *pointeurFacteurPremier = facteurPremier1;
			void **ptrx = *(&pointeurFacteurPremier);
			realloc_s (ptrx,(sizeof *facteurPremier1) * 2);
			(facteurPremier1[*size].file) = nbr->file;
			(facteurPremier1[*size].nombre) = (uint32_t) 2;
			(facteurPremier1[*size].multiplicite) = count;
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
			if(ajout_element == 0 && (facteurPremier1[*size-1].nombre) == 0) {
				int curseur2 = 0;
				while (&facteurPremier1[curseur2] != NULL) {
					curseur2 ++ ;
				}
				facteurPremier1[curseur2].file = nbr->file;
				facteurPremier1[curseur2].nombre = (uint32_t) i;
				facteurPremier1[curseur2].multiplicite = count;
				(*size)++;
			}
			else if (ajout_element == 0  && (facteurPremier1[*size-1].nombre) != 0) {
				void *pointeurFacteurPremier = facteurPremier1;
				void **ptrx = *(&pointeurFacteurPremier);
				realloc_s (ptrx,(sizeof *facteurPremier1) * 2);
				(facteurPremier1[*size].file) = nbr->file;
				(facteurPremier1[*size].nombre) = (uint32_t) i;
				(facteurPremier1[*size].multiplicite) = count;
				(*size)++;
			}
			count = 0;
		}
	}
	//ajoute le dernier élement (qui est toujours un nbr premier) à la liste
	if (leNombre != 1) {
		if(ajout_element == 0 && (facteurPremier1[*size-1].nombre) == 0) {
			int curseur2 = 0;
			int true = 1;
			while (facteurPremier1[curseur2].nombre != 0  && true == 1) {
				if(facteurPremier1[curseur2].nombre == leNombre ) {
					facteurPremier1[curseur2].multiplicite += count;
					(*size)++;
					ajout_element = 1;
					true = 0;
				}
				curseur2 ++ ;
			}
			if (ajout_element == 0) {
				facteurPremier1[curseur2].file = nbr->file;
				facteurPremier1[curseur2].nombre = (uint32_t) leNombre;
				facteurPremier1[curseur2].multiplicite = count;
				(*size)++;
			}
		}
		else if (ajout_element == 0  && (facteurPremier1[*size-1].nombre) != 0) {
			void *pointeurFacteurPremier = facteurPremier1;
			void **ptrx = *(&pointeurFacteurPremier);
			realloc_s (ptrx,(sizeof *facteurPremier1) * 2);
			facteurPremier1[*size].file = nbr->file;
			facteurPremier1[*size].nombre = (uint32_t) leNombre;
			facteurPremier1[*size].multiplicite = count;
			(*size)++;
		}
	}
	return 0;
}

void realloc_s (void **ptr, size_t taille)
{
	void *ptr_realloc = realloc(*ptr, taille);

	if (ptr_realloc != NULL) {
		*ptr = ptr_realloc;
	}
	// MANQUE PAS UN ELSE ??
}