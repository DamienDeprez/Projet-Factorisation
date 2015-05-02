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

