//
// Created by damien on 22/04/15.
//

/**
 * Fonction principale du programme
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include "buffer.h"
#include "producteur.h"

void exit_on_error(char * msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int main (int argc, char ** argv)
{
	long maxthreads=1;
	int threadNum=0;
	int numofThread=0;
	pthread_t* pthread= (pthread_t*) malloc(sizeof(*pthread)*(argc+maxthreads)); // talbeau de thread
	char* argerror;
	char* internet="http://";
	struct buffer* buffer1 = newBuffer(128);
	printf("Programme de factorisation de nombre\n");
	if(argc>1) {
		int i;
		for (i = 1; i < argc; i++)
		{
			if(!strcmp(argv[i],"-stdin"))
			{
				//lecture depuis stdin
				printf("lecture depuis stdin\n");
				struct thread_param param={buffer1,"stdin",0,1};
				pthread_create(&pthread[threadNum],NULL,produceFromFD,&param);
				numofThread++;
				threadNum++;
			}
			else if(!strcmp(argv[i],"-maxthreads"))
			{
				// max threads
				i++;
				if(i>=argc)
				{
					printf("erreur, pas assez d'argument\n");
				}
				else
				{
					maxthreads = strtol(argv[i],&argerror,10); // converti en long
					if(*argerror != '\0') // si erreur dans la conversion
					{
						printf("erreur, argument invalide\n");
						i--;
						maxthreads=1;
					}
				}
				printf("nombre maximum de consommateur : %ld\n",maxthreads);
				pthread_t* temp = realloc(pthread,sizeof(*pthread)*(argc+maxthreads));
				if(temp != NULL)
				{
					pthread=temp;
				}
				else
				{
					printf("erreur de realloc pour les threads");
				}
			}
			else if(strstr(argv[i],internet)!=NULL)
			{
				//lecture depuis internet
				printf("lecture depuis l'URL : %s\n",argv[i]);
				int fd[2];
				pipe(fd);
				struct thread_param param1={buffer1,argv[i],fd[0],fd[1]};
				pthread_create(&pthread[threadNum],NULL,produceFromInternet,&param1);
				numofThread++;
				threadNum++;
				struct thread_param param2={buffer1,argv[i],fd[0],fd[1]};
				pthread_create(&pthread[threadNum],NULL,produceFromFD,&param2);
				threadNum++;
				numofThread++;
				//produceFromInternet(argv[i]);
			}
			else
			{
				//lecture depuis le fichier
				int fd=open(argv[i],O_RDONLY);
				if(fd==-1)
				{
					printf("erreur de d'ouverture\n");
				}
				else
				{

					struct thread_param param = {buffer1,argv[i],fd,1};
					pthread_create(&pthread[threadNum],NULL,produceFromFD,&param);
					printf("lecure depuis le fichier : %s\n",argv[i]);
					numofThread++;
				}
			}
		}
		int cursor;

		for(cursor=0;cursor<numofThread;cursor++)
		{
			printf("join thread #%d\n",cursor);
			pthread_join(pthread[cursor],NULL);
		}
		freeBuffer(buffer1);
		free(pthread);
		printf("end\n");
	}
	return EXIT_SUCCESS;
}

