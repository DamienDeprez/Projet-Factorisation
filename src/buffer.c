#include "buffer.h"

struct buffer * newBuffer(unsigned int size)
{
	struct buffer *buffer1 = (struct buffer *) malloc(sizeof(*buffer1));
	if (buffer1 == NULL)
		return NULL;
	sem_init(&(buffer1->empty),0,size);
	sem_init(&(buffer1->full),0,0);
	pthread_mutex_init(&(buffer1->lock),NULL);
	buffer1->memory = (struct nombre *) malloc(sizeof(*(buffer1->memory)) * size);
	buffer1->cursor = 0;
	buffer1->size = size;
	buffer1->nbrelem=0;
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
	buffer1 = NULL;
	return EXIT_SUCCESS;
}

int readBuffer(struct buffer *buffer1, struct nombre* nombre1)
{
	struct timespec timeout;
	clock_gettime(CLOCK_REALTIME,&timeout);
	timeout.tv_nsec=timeout.tv_nsec+TIMEOUTNANO;
	int test = sem_timedwait(&(buffer1->full),&timeout);// test s'il y a un slot rempli
	 if(test==-1)
	 {
		 if(errno == ETIMEDOUT)
		 {
			 return 1;
		 }
	 }
	pthread_mutex_lock(&(buffer1->lock)); // verouille l'accès à la mémoire
	size_t debut = buffer1->cursor;
	nombre1->nombre=buffer1->memory[buffer1->cursor].nombre;
	nombre1->file=buffer1->memory[buffer1->cursor].file;
	while (nombre1->nombre == 0) {
		buffer1->cursor++;
		if (buffer1->cursor == buffer1->size) // si on arrive au bout
		{
			buffer1->cursor = 0;
		}
		if (buffer1->cursor == debut)
		{
			pthread_mutex_unlock(&buffer1->lock);
			return 1; // si un tour complèt return avec 0
		}

		nombre1->nombre=buffer1->memory[buffer1->cursor].nombre;
		nombre1->file=buffer1->memory[buffer1->cursor].file;
	}
	buffer1->nbrelem--;
	buffer1->memory[buffer1->cursor].nombre=0;
	buffer1->memory[buffer1->cursor].file="";
	pthread_mutex_unlock(&(buffer1->lock)); // déverouille l'accès à la mémoire
	sem_post(&(buffer1->empty)); // augment le nombre de slot vide
	return 0;
}

void writeBuffer(struct buffer *buffer1, struct nombre nombre1)
{
	sem_wait(&(buffer1->empty)); // attente d'un slot vide
	pthread_mutex_lock(&(buffer1->lock)); // verouille l'accès à la mémoire
	struct nombre cursor = buffer1->memory[buffer1->cursor];
	while (cursor.nombre != 0) {
		buffer1->cursor++;
		if (buffer1->cursor == buffer1->size) {
			buffer1->cursor = 0;
		}
		cursor = buffer1->memory[buffer1->cursor];
	}
	buffer1->nbrelem++;
	buffer1->memory[buffer1->cursor] = nombre1;
	pthread_mutex_unlock(&(buffer1)->lock); // déverouille l'accès à la mémoire
	sem_post(&(buffer1->full)); // augment le nombre de slot rempli
}
