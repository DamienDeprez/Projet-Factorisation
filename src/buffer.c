//
// Created by damien on 26/04/15.
//


#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "buffer.h"

struct buffer * newBuffer(int size)
{
	struct buffer *buffer1 = (struct buffer *) malloc(sizeof(*buffer1));
	if (buffer1 == NULL)
		return NULL;
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
	free(buffer1);
	//buffer1 = NULL;
	return EXIT_SUCCESS;
}

struct nombre readBuffer(struct buffer *buffer1)
{
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
	return retour;
}

int writeBuffer(struct buffer *buffer1, struct nombre nombre1)
{
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
	return 0;
}
