#include "factorisation.h"

/*
 * liste est null a l'appel de la fonction
 */
int factorisation (struct nombre* nbr, struct facteurPremier** facteurPremier1, int *size) {
	// on ne peut avoir de liste vide
	if (facteurPremier1 == NULL || *facteurPremier1 == NULL || nbr == NULL) {
		return 1;
	}
	// 0 et 1 ne sont pas des nombres premiers
	if (nbr->nombre == 0 || nbr->nombre == 1) {
		return 1;
	}

	int count = 0;
	uint64_t leNombre = nbr->nombre;
	uint64_t r = (uint64_t) sqrt(leNombre);
	int i = 2;
	int ajout_element = 0;        // variable qui permet de savoir si un element a ete ajoute ou pas
	int indice = 0;        // indice sera le nombre d'element present dans le tableau facteurPremier1 et en sera donc l'indice des cases a parcourir

	while (indice < *size && (*facteurPremier1)[indice].nombre != 0 ) {
		indice++;
	}
	while (leNombre % i == 0) {
		leNombre = leNombre / i;
		count++;
	}
	// ajout du nombre premier 2 si le nombre de depart est au moins une fois divisible par 2
	if (count != 0) {
		int curseur = 0;    // indice de deplacement dans le tableau
		for (curseur = 0; curseur < indice && ajout_element == 0; curseur++) {
			if ((*facteurPremier1)[curseur].nombre == 2) {

				//printf("multavant =  %d\n", (*facteurPremier1)[curseur].multiplicite);
				(*facteurPremier1)[curseur].multiplicite = (*facteurPremier1)[curseur].multiplicite + count;
				(*facteurPremier1)[curseur].file = nbr->file;
				ajout_element = 1;
				//printf("multapres =  %d\n", (*facteurPremier1)[curseur].multiplicite);
			}
		}
		if (ajout_element == 0) {
			if (indice == *size) {
				realloc_s((void **) facteurPremier1, ((size_t) *size) * (sizeof **facteurPremier1) * 2);
				*size = *size * 2;
				realloc_zeros(indice, *facteurPremier1, size);
			}
			if ((*facteurPremier1)[indice].nombre == 0) {
				(*facteurPremier1)[indice].nombre = (uint32_t) 2;
				(*facteurPremier1)[indice].multiplicite = count;
				(*facteurPremier1)[indice].file = nbr->file;
				indice++;
			}
		}
	}

	for (i = 3; i <= r; i = i + 2) {
		count = 0;
		while (leNombre % i == 0) {
			leNombre = leNombre / i;
			count++;
			ajout_element = 0;
		}
		if (count != 0) {
			int curseur = 0;
			for (curseur = 0; curseur < indice && ajout_element == 0; curseur++) {

				if ((*facteurPremier1)[curseur].nombre == i) {
					(*facteurPremier1)[curseur].multiplicite = (*facteurPremier1)[curseur].multiplicite + count;
					ajout_element = 1;

				}
			}
			if (ajout_element == 0) {
				if (indice == *size) {
					realloc_s((void **) facteurPremier1, ((size_t) *size) * (sizeof **facteurPremier1) * 2);
					*size = *size * 2;
					realloc_zeros(indice, *facteurPremier1, size);
				}
				if ((*facteurPremier1)[indice].nombre == 0) {
					(*facteurPremier1)[indice].file = nbr->file;
					(*facteurPremier1)[indice].nombre = (uint32_t) i;
					(*facteurPremier1)[indice].multiplicite = count;
					indice++;
				}
			}
		}
	}
	//ajoute le dernier élement (qui est toujours un nbr premier) à la liste
	if (leNombre != 1) {
		int curseur2 = 0;
		int true = 0;
		for (curseur2 = 0; curseur2 < indice && true == 0; curseur2++) {
			if ((*facteurPremier1)[curseur2].nombre == leNombre) {
				(*facteurPremier1)[curseur2].multiplicite = (*facteurPremier1)[curseur2].multiplicite + 1;
				(*facteurPremier1)[curseur2].file = nbr->file;
				true = 1;

			}
			curseur2++;
		}
		if (true == 0) {
			if (indice == *size) {

				realloc_s((void **) facteurPremier1, ((size_t) *size) * 2 * (sizeof **facteurPremier1));
				*size = *size * 2;
				realloc_zeros(indice, *facteurPremier1, size);
			}
			if ((*facteurPremier1)[indice].nombre == 0) {

				(*facteurPremier1)[indice].file = nbr->file;
				(*facteurPremier1)[indice].nombre = (uint32_t) leNombre;
				(*facteurPremier1)[indice].multiplicite = 1;
				indice++;
			}

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
}


void realloc_zeros(int indiceInitial, struct facteurPremier* facteurPremier1, int *size)
{
	int zeros = indiceInitial;
	for (zeros; zeros < *size; zeros++) {
		facteurPremier1[zeros].nombre = (uint32_t) 0;
		facteurPremier1[zeros].multiplicite = 0;
		facteurPremier1[zeros].file = '\0';
	}
}


int searchUniquePrime (struct facteurPremier* facteurPremier1, int *size)
{
	int curseur = 0;
	for (curseur =0 ;curseur < *size; curseur++){
		if (facteurPremier1[curseur].multiplicite == 1) {
			printf("%u\n", facteurPremier1[curseur].nombre);
			printf("%s\n", facteurPremier1[curseur].file);
			return 0;
		}
	}
	return 1;
}