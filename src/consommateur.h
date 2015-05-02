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


#endif //FACTORISATION_CONSOMMATEUR_H
