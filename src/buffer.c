//
// Created by damien on 26/04/15.
//


#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <pthread.h>
#include "buffer.h"

struct buffer * newBuffer(int size)
{
	struct buffer *buffer1 = (struct buffer *) malloc(sizeof(*buffer1));
	if (buffer1 == NULL)
		return NULL;
	sem_init(&(buffer1->empty),0,size);
	sem_init(&(buffer1->full),0,0);
	pthread_mutex_init(&(buffer1->lock),NULL);
	printf("taille memory : %lu\n", sizeof(struct nombre)*size);
	printf("taille memory : %lu\n", sizeof(*(buffer1->memory))*size);
	buffer1->memory = (struct nombre *) malloc(sizeof(*(buffer1->memory)) * size);
	buffer1->cursor = 0;
	buffer1->size = size;
	int cursor;
	for (cursor = 0; cursor < buffer1->size; cursor++) {
		buffer1->memory[cursor].nombre = 0;
		buffer1->memory[cursor].file = "\0";
	}
	return buffer1;
}

int freeBuffer(struct buffer *buffer1)
{
	free(buffer1->memory);
	buffer1->memory = NULL;
	sem_destroy(&(buffer1->full));
	sem_destroy(&(buffer1->empty));
	pthread_mutex_destroy(&(buffer1->lock));
	free(buffer1);
	//buffer1 = NULL;
	return EXIT_SUCCESS;
}

struct nombre readBuffer(struct buffer *buffer1)
{
	sem_wait(&(buffer1->full)); // attente d'un slot rempli
	pthread_mutex_lock(&(buffer1->lock)); // verouille l'accès à la mémoire
	size_t debut = buffer1->cursor;
	struct nombre retour = buffer1->memory[buffer1->cursor];
	while (retour.nombre == 0) {
		buffer1->cursor++;
		if (buffer1->cursor == buffer1->size) // si on arrive au bout
		{
			buffer1->cursor = 0;
		}
		printf("get at buffer [%lu] - begin : %lu \n",buffer1->cursor,debut);
		if (buffer1->cursor == debut)
			return retour; // si un tour complèt return avec 0
		retour = buffer1->memory[buffer1->cursor];
	}
	buffer1->memory[buffer1->cursor].nombre=0;
	buffer1->memory[buffer1->cursor].file="";
	pthread_mutex_unlock(&(buffer1->lock)); // déverouille l'accès à la mémoire
	sem_post(&(buffer1->empty)); // augment le nombre de slot vide
	return retour;
}

int writeBuffer(struct buffer *buffer1, struct nombre nombre1)
{
	sem_wait(&(buffer1->empty)); // attente d'un slot vide
	pthread_mutex_lock(&(buffer1->lock)); // verouille l'accès à la mémoire
	size_t debut = buffer1->cursor;
	struct nombre cursor = buffer1->memory[buffer1->cursor];
	while (cursor.nombre != 0) {
		buffer1->cursor++;
		if (buffer1->cursor == buffer1->size) {
			buffer1->cursor = 0;
		}
		if (buffer1->cursor == debut) {
			return 1;
		}
		printf("set at buffer [%lu] - begin : %lu \n",buffer1->cursor,debut);
		cursor = buffer1->memory[buffer1->cursor];
	}
	buffer1->memory[buffer1->cursor] = nombre1;
	pthread_mutex_unlock(&(buffer1)->lock); // déverouille l'accès à la mémoire
	sem_post(&(buffer1->full)); // augment le nombre de slot rempli
	return 0;
}
