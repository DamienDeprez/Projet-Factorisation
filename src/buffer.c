//
// Created by damien on 26/04/15.
//


#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "buffer.h"

struct buffer *alloc()
{
	struct buffer *buffer1 = (struct buffer *) malloc(sizeof(buffer1));
	if (buffer1 == NULL)
		return NULL;
	printf("taille memory : %lu\n", sizeof(struct nombre));
	buffer1->memory = (struct nombre *) malloc(sizeof(struct nombre) * N);
	buffer1->cursor = 0;
	buffer1->size = N;
	int cursor;
	for (cursor = 0; cursor < N; cursor++) {
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

struct nombre getNombre(struct buffer *buffer1)
{
	size_t debut = buffer1->cursor;
	struct nombre retour = buffer1->memory[buffer1->cursor];
	while (retour.nombre == 0) {
		buffer1->cursor++;
		if (buffer1->cursor == debut)
			return retour; // si un tour complèt return avec 0
		if (buffer1->cursor == N) // si on arrive au bout
		{
			buffer1->cursor = 0;
		}
		retour = buffer1->memory[buffer1->cursor];
	}
	buffer1->cursor++;
	if (buffer1->cursor == N) {
		buffer1->cursor = 0;
	}
	return retour;
}

int setNombre(struct buffer *buffer1, struct nombre nombre1)
{
	size_t debut = buffer1->cursor;
	struct nombre cursor = buffer1->memory[buffer1->cursor];
	while (cursor.nombre != 0) {
		buffer1->cursor++;
		if (buffer1->cursor == debut) {
			return 1;
		}
		if (buffer1->cursor == N) {
			buffer1->cursor = 0;
		}
		cursor = buffer1->memory[buffer1->cursor];
	}

	buffer1->memory[buffer1->cursor].nombre = nombre1.nombre;
	buffer1->memory[buffer1->cursor].file = nombre1.file;
	buffer1->cursor++;
	if (buffer1->cursor == N) {
		buffer1->cursor = 0;
	}
	return 0;
}
