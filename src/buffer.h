//
// Created by damien on 26/04/15.
//

#ifndef FACTORISATION_BUFFER_H
#define FACTORISATION_BUFFER_H

#define TIMEOUTNANO 10000000

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
 * @lock : mutex pour protéger l'accès au buffer
 * @empty: sémaphore comptant le nombre de slot vide du buffer
 * @full: sémaphore comptant le nombre de slot utilisé du buffer
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
 * @size: nombre de slot du buffer
 * @return le pointeur vers le buffer sur le HEAP ou NULL si erreur
 */
struct buffer* newBuffer (unsigned int size);

/*
 * fonction libérant la mémoire allouée au buffer
 *
 * @return 0 si pas d'erreur et 1 si erreur
 */

int freeBuffer(struct buffer* buffer1);

/*
 * fonction retournant la première strucutre nombre qui n'est pas null à partir du curseur
 * @buffer1: pointeur vers le buffer
 * @nombre1: pointeur permettant de retourner le nombre lu
 *
 * @return 0 si pas d'erreur et 1 si erreur (buffer vide)
 */
int readBuffer (struct buffer* buffer1, struct nombre* nombre1 );

/*
 * fonction mettant la structure nombre à la première place vide à partir du curseur. Attend si le buffer est plein
 */
void writeBuffer(struct buffer* buffer1,const struct nombre nombre1);

#endif //FACTORISATION_BUFFER_H
