//
// Created by damien on 22/04/15.
//

#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

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
	int indice = 0;		// indice sera le nombre d'element present dans le tableau facteurPremier1 et en sera donc l'indice des cases a parcourir

	while (facteurPremier1[indice].nombre != 0)
	{
		indice++;
	}
	while (leNombre % i == 0)
	{
		leNombre = leNombre/i;
		count++;
	}
	// ajout du nombre premier 2 si le nombre de depart est au moins une fois divisible par 2
	if (count != 0)
	{
		int curseur = 0;	// indice de deplacement dans le tableau
		for (curseur; curseur < indice && ajout_element == 0;curseur++) {
			//printf("print le nombre%"PRIu64"\n", leNombre);
			if(facteurPremier1[curseur].nombre == 2) {
				facteurPremier1[curseur].multiplicite += count;
				facteurPremier1[curseur].file = nbr->file;
				ajout_element = 1;
			}
		}
		if (ajout_element == 0  && indice == *size) {
			void *pointeurFacteurPremier = facteurPremier1;
			void **ptrx = *(&pointeurFacteurPremier);
			realloc_s (ptrx,(sizeof *facteurPremier1) * 2);
			facteurPremier1[indice].file = nbr->file;
			facteurPremier1[indice].nombre = (uint32_t) 2;
			facteurPremier1[indice].multiplicite = count;
			indice ++;
		}
		else if (ajout_element == 0 && (facteurPremier1[indice].nombre) == 0) {
			//printf("coucou1""\n");
			//printf("leNombre1 = %"PRIu64"\n",leNombre);
			//printf("count1 =  %d\n", count);
			//printf("indice1 =  %d\n", indice);
			//printf("curseur1 =  %d\n", curseur);
			facteurPremier1[indice].file = nbr->file;
			facteurPremier1[indice].nombre = (uint32_t) 2;
			facteurPremier1[indice].multiplicite = count;
			indice ++;
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
			for(curseur; curseur < indice && ajout_element == 0;curseur++) {

				if(facteurPremier1[curseur].nombre == i) {
					facteurPremier1[curseur].multiplicite += count;
					ajout_element = 1;
				}
			}
			if (ajout_element == 0  && indice == *size) {
				void *pointeurFacteurPremier = facteurPremier1;
				void **ptrx = *(&pointeurFacteurPremier);
				realloc_s (ptrx,(sizeof *facteurPremier1) * 2);		// realloc modifi-t-il *size ???
				facteurPremier1[indice].file = nbr->file;
				facteurPremier1[indice].nombre = (uint32_t) i;
				facteurPremier1[indice].multiplicite = count;
				indice ++;
			}
			else if(ajout_element == 0 && (facteurPremier1[indice].nombre) == 0) {
				facteurPremier1[indice].file = nbr->file;
				facteurPremier1[indice].nombre = (uint32_t) i;
				facteurPremier1[indice].multiplicite = count;
				indice ++;
			}
			count = 0;
		}
	}
	//ajoute le dernier élement (qui est toujours un nbr premier) à la liste
	if (leNombre != 1) {
		int curseur2 = 0;
		int true = 0;
		for (curseur2; curseur2 < indice && true == 0;curseur2++) {
			if(facteurPremier1[curseur2].nombre == leNombre) {
				facteurPremier1[curseur2].multiplicite += count;
				true = 1;
			}
			curseur2 ++;
		}
		if (true == 0  && indice == *size) {
			void *pointeurFacteurPremier = facteurPremier1;
			void **ptrx = *(&pointeurFacteurPremier);
			realloc_s (ptrx,(sizeof *facteurPremier1) + (sizeof facteurPremier1[0]));		// verifier le +1
			facteurPremier1[indice].file = nbr->file;
			facteurPremier1[indice].nombre = (uint32_t) leNombre;
			facteurPremier1[indice].multiplicite = 1;
			indice ++;
		}
		else if(true == 0 && (facteurPremier1[indice].nombre) == 0) {
			facteurPremier1[indice].file = nbr->file;
			facteurPremier1[indice].nombre = (uint32_t) leNombre;
			facteurPremier1[indice].multiplicite = 1;
			indice ++;
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

void searchUniquePrime (struct facteurPremier* facteurPremier1, int *size)
{
	int curseur = 0;
	int indice = 0; // nombre de case(s) remplie(s) dans la liste de nombre(s) premier(s) unique
	struct facteurPremier* resultat = (struct facteurPremier*) malloc(sizeof resultat);
	if(resultat ==NULL){
		EXIT_FAILURE;
	}
	else {
		int i = 0;
		for (i; i < sizeof resultat; i++) {
			resultat[i].nombre = 0;
			resultat[i].multiplicite = 0;
			resultat[i].file = "\0";
		}
	}
	for (curseur; curseur < *size; curseur++){
		if (facteurPremier1[curseur].multiplicite == 1){
			if(resultat[indice-1].nombre == 0){
				void *pointeurResultat = resultat;
				void **ptrx = *(&pointeurResultat);
				realloc_s (ptrx,(sizeof *resultat) + 1);
			}
			resultat[indice].nombre = facteurPremier1[curseur].nombre;
			resultat[indice].multiplicite = facteurPremier1[curseur].multiplicite;
			resultat[indice].file = facteurPremier1[curseur].file;
			indice ++;
		}
	}
	printf("resultat(s) : ");
	int curseur2 = 0;
	for(curseur2; curseur2 < indice; curseur2++){
		printf("%d\n le nombre premier : ",resultat[curseur2].nombre);
		printf("%d apparait : ",resultat[curseur2].multiplicite);
		printf("%s seule fois dans tout les fichiers et vient du fichier : ",resultat[curseur2].file);
	}
	if (indice == 0){
		printf("\n il n'y a pas de nombre premier unique dans ces fichiers ");
	}
	free(resultat);
}
