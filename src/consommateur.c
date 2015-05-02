//
// Created by damien on 22/04/15.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <inttypes.h>
#include "consommateur.h"
#include "factorisation.h"
#include "buffer.h"

void* consumme(void* param)
{
	struct consommateur_param* consommateurParam=(struct consommateur_param*)param;
	struct facteurPremier* local = malloc(sizeof(*local)*SIZE);
	struct nombre n1;
	int count=0;
	if(local)
	{
		int isBufferEmpty=0;
		/*pthread_mutex_lock(consommateurParam->lock);
		int isProducing=*(consommateurParam->isProducing);
		pthread_mutex_unlock(consommateurParam->lock);*/
		int isProducing=1;

		while(isProducing || !isBufferEmpty)
		{
			pthread_mutex_lock(consommateurParam->lock);
			isProducing=*(consommateurParam->isProducing);
			pthread_mutex_unlock(consommateurParam->lock);
			isBufferEmpty = readBuffer(consommateurParam->buffer1, &n1);
			if (isBufferEmpty != 0 || n1.nombre==0) {
				n1.nombre = 0;
				n1.file = "end";
			}
			else {
				printf("n1 : %"PRIu64"\n",n1.nombre);
				count++;
			}
		}
	}
	printf("count : %d\n",count);
	free(param);
	free(local);
	return NULL;
}

int publish_result(struct facteurPremier* facteurPremierG, int *size, struct facteurPremier* resultatsLocaux, int *localSize, pthread_mutex_t* protectGlobalList)
{
	int indice = 0;

	while (facteurPremierG[indice].nombre != 0 && indice < *size)
	{
		indice++;
	}

	int curseur1 = 0;	// curseur voyageant dans la liste locale
	for (curseur1; curseur1 < *localSize; curseur1++) {

		int deja = 0;	//booleen qui sert a savoir si l'update a ete faite apres parcours de toute la liste ou si il faut ajouter un nouvel element a la liste globale
		int curseur2 = 0; // curseur voyageant dans la liste globale

		for (curseur2; curseur2 < *size && deja ==0; curseur2++) {
			if(resultatsLocaux[curseur1].nombre == facteurPremierG[curseur2].nombre) {

				facteurPremierG[curseur2].multiplicite += resultatsLocaux[curseur1].multiplicite;
				facteurPremierG[curseur2].file = resultatsLocaux[curseur1].file;
				deja = 1;
			}
		}
		if (deja == 0) {
			if (indice == *size) {

				void *pointeurFacteurPremierG = facteurPremierG;
				void **ptrx = *(&pointeurFacteurPremierG);
				realloc_s (ptrx,(sizeof *facteurPremierG) * 2);
			}
			if(facteurPremierG[indice].nombre == 0) {

				facteurPremierG[indice].nombre = resultatsLocaux[curseur1].nombre ;
				facteurPremierG[indice].multiplicite = resultatsLocaux[curseur1].multiplicite;
				facteurPremierG[indice].file = resultatsLocaux[curseur1].file;
				indice ++;
			}
		}
	}
	return indice;
}