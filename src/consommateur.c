#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <inttypes.h>
#include "consommateur.h"

void* consumme(void* param)
{
	struct consommateur_param* consommateurParam=(struct consommateur_param*)param;
	int size = SIZE;
	struct facteurPremier* local = (struct facteurPremier*) malloc(sizeof(*local)*size);
	int i;
	for(i=0;i<size;i++)
	{
		local[i].nombre=0;
		local[i].multiplicite=0;
		local[i].file='\0';
	}
	struct nombre n1;

		int isBufferEmpty=0;
		int isProducing=1;

		while(isProducing || !isBufferEmpty)
		{
			pthread_mutex_lock(consommateurParam->lock);
			isProducing=*(consommateurParam->isProducing);
			pthread_mutex_unlock(consommateurParam->lock);
			isBufferEmpty = readBuffer(consommateurParam->buffer1, &n1);
			if (isBufferEmpty != 0 || n1.nombre==0) {
				n1.nombre = 0;
				n1.file = "\0";
			}
			else {
				factorisation(&n1,&local,&size);
			}
		}
	publish_result(consommateurParam->global,consommateurParam->size,local,&size,consommateurParam->lockGlobal);
	free(param);
	free(local);
	param=NULL;
	local=NULL;
	return NULL;
}

int publish_result(struct facteurPremier** facteurPremierG, int *size, struct facteurPremier* resultatsLocaux, int *localSize, pthread_mutex_t *protectGlobalList)
{
	pthread_mutex_lock(protectGlobalList);
	int indice = 0;
	int nbr = 0;
	int countUpdate = 0; 		// nombre d'element ajouté

	while (indice < *size && (*facteurPremierG)[indice].nombre != 0)
	{
		indice++;
	}
	while (nbr < *localSize && resultatsLocaux[nbr].nombre != 0) {
		nbr ++;
	}

	int curseur1 = 0;	// curseur voyageant dans la liste locale
	for (curseur1; curseur1 < *localSize; curseur1++) {
		int deja = 0;	//booleen qui sert a savoir si l'update a ete faite apres parcours de toute la liste ou si il faut ajouter un nouvel element a la liste globale
		int curseur2 = 0; // curseur voyageant dans la liste globale

		for (curseur2; curseur2 < *size && deja ==0; curseur2++) {
			if((*facteurPremierG)[curseur2].nombre == resultatsLocaux[curseur1].nombre) {

				(*facteurPremierG)[curseur2].multiplicite = resultatsLocaux[curseur1].multiplicite + (*facteurPremierG)[curseur2].multiplicite;
				(*facteurPremierG)[curseur2].file = resultatsLocaux[curseur1].file;
				deja = 1;
				countUpdate ++;
			}
		}
		if (deja == 0) {
			if (indice == *size) {

				realloc_s ((void **) facteurPremierG,((size_t) *size) * (sizeof **facteurPremierG) * 2);
				*size = (*size )* 2;
				realloc_zeros(indice, *facteurPremierG, size);
			}
			if((*facteurPremierG)[indice].nombre == 0) {

				(*facteurPremierG)[indice].nombre = resultatsLocaux[curseur1].nombre ;
				(*facteurPremierG)[indice].multiplicite  = resultatsLocaux[curseur1].multiplicite;
				(*facteurPremierG)[indice].file  = resultatsLocaux[curseur1].file;
				indice ++;
				countUpdate ++;
			}
		}
	}

	if (countUpdate == nbr) {
		pthread_mutex_unlock(protectGlobalList);
		return 0;
	}
	else {
		pthread_mutex_unlock(protectGlobalList);
		return 1;
	}
}
