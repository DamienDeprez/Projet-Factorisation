//
// Created by damien on 22/04/15.
//

/**
 * Liste de fonctions utilisées par le consommateur
 */

#ifndef FACTORISATION_CONSOMMATEUR_H
#define FACTORISATION_CONSOMMATEUR_H

#define SIZE 2048

struct consommateur_param
{
	struct buffer* buffer1;
	pthread_mutex_t* lock;
	int* isProducing;
};

void* consumme(void* param);

/*
 * retourne 1 si il y a un problème et 0 sinon (doit update la liste globale a partir de la liste locale)
 * prend en argument trois pointeurs (un vers la liste locale, un vers la liste globale
 * et un vers le mutex de protection de la liste globale) e 2 entiers (les tailles
 * des listes globale et locale.
 */
int publish_result(struct facteurPremier* facteurPremier, int *size, struct facteurPremier* resultatsLocaux, int *localSize, pthread_mutex_t* protectGlobalList);


#endif //FACTORISATION_CONSOMMATEUR_H
