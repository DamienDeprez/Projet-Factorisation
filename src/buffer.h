//
// Created by damien on 26/04/15.
//

#ifndef FACTORISATION_BUFFER_H
#define FACTORISATION_BUFFER_H

#define N 4 // nombre de slot du buffer

#include <stddef.h>
#include <semaphore.h>
#include "factorisation.h"

// %TODO complèter la doc

/*
 * structure représentant le buffer
 *
 * @memory : pointeur vers la zone mémoire réservé pour le buffer
 * @size : taille du buffer en nombre d'éléments
 * @cursor : position actuelle du curseur pour la lecture
 */
struct buffer
{
	struct nombre* memory;
	int size;
	int nbrelem;
	size_t cursor;
	pthread_mutex_t lock;
	sem_t empty;
	sem_t full;
};

/*
 * fonction allouant le buffer
 *
 * @return le pointeur vers le buffer sur le HEAP ou NULL si erreur
 */
struct buffer* newBuffer (int size);

/*
 * fonction libérant la mémoire allouée au buffer
 *
 * @return 0 si pas d'erreur et 1 si erreur
 */

int freeBuffer(struct buffer* buffer1);

/*
 * fonction retourant la structure nombre se trouvant au niveau du curseur et avance le curseur
 *
 * @buffer pointeur vers le buffer
 * @return structure nombre se trouvant à l'emplacement curseur
 */
int readBuffer (struct buffer* buffer1, struct nombre* nombre1 );

/*
 * fonction mettant la structure nombre à la place du curseur si c'est vide et avance le curseur.
 *
 */
int writeBuffer(struct buffer* buffer1,const struct nombre nombre1);

/*
 * fonction permettant de savoir si le buffer est vide
 */
int isBufferEmpty(struct buffer* buffer1);
#endif //FACTORISATION_BUFFER_H
