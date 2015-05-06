/**
 * Fonction principale du programme
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include "buffer.h"
#include "producteur.h"
#include "consommateur.h"

int isProducing;
pthread_mutex_t lock;
pthread_mutex_t lockGlobal;
struct facteurPremier** global;
int *size;


int main (int argc, char ** argv)
{
	struct timeval start,stop;
	if(gettimeofday(&start,NULL) == -1)
	{
		perror("clock gettime\n");
	}
	pthread_mutex_init(&lockGlobal,NULL);
	pthread_mutex_init(&lock,NULL);
	pthread_mutex_lock(&lockGlobal);
	size = (int*) malloc(sizeof size);
	*size = 16;
	global = (struct facteurPremier**)malloc(sizeof(*global));
	*global = (struct facteurPremier*) malloc(sizeof(**global) * (*size));
	int i;
	for(i=0;i<*size;i++)
	{
		(*global)[i].nombre=0;
		(*global)[i].multiplicite=0;
		(*global)[i].file='\0';
	}
	pthread_mutex_unlock(&lockGlobal);

	pthread_mutex_lock(&lock);
	isProducing=0;
	pthread_mutex_unlock(&lock);


	long maxthreads=1;
	int threadNum=0;
	int numofThread=0;
	pthread_t* prodcuteur= (pthread_t*) malloc(sizeof(*prodcuteur)*argc);// talbeau de thread producteur
	pthread_t* consommateur=(pthread_t*) malloc(sizeof(*consommateur)*maxthreads);
	char* argerror;
	char* internet="http://";
	struct buffer* buffer1 = newBuffer(128);
	if(argc>1) {
		isProducing=1;
		for (i = 1; i < argc; i++)
		{
			if(!strcmp(argv[i],"-stdin"))
			{
				struct producteur_param* param=(struct producteur_param*)malloc(sizeof(*param));
				if(param==NULL)
				{
					printf("erreur, pas assez de place\n");
				}
				else
				{
					param->inputName="stdin";
					param->buffer1=buffer1;
					param->fd_read=0;
					param->fd_write=1;
					pthread_create(&prodcuteur[threadNum],NULL,produceFromFD,param);
					numofThread++;
					threadNum++;
				}
			}
			else if(!strcmp(argv[i],"-maxthreads"))
			{
				i++;
				if(i>=argc)
				{
					printf("erreur, pas assez d'argument\n");
				}
				else {
					maxthreads = strtol(argv[i], &argerror, 10); // converti en long
					if (*argerror != '\0') // si erreur dans la conversion
					{
						printf("erreur, argument invalide\n");
						i--;
						maxthreads = 1;
					}
					else
					{
						pthread_t* temp = realloc(consommateur,sizeof(*consommateur)*maxthreads);
						if(temp==NULL)
						{
							printf("erreur de realloc de consommateur\n");
						}
						else
						{
							consommateur=temp;
						}
					}

				}
			}
			else if(strstr(argv[i],internet)!=NULL)
			{
				int fd[2];
				pipe(fd);
				struct producteur_param* param1=(struct producteur_param*)malloc(sizeof(*param1));
				struct producteur_param* param2=(struct producteur_param*)malloc(sizeof(*param2));
				if(param1==NULL)
				{
					printf("erreur pas assez de mémoire\n");
				}
				else
				{
					param1->buffer1=buffer1;
					param1->inputName=argv[i];
					param1->fd_read=fd[0];
					param1->fd_write=fd[1];
					param2->buffer1=buffer1;
					param2->inputName=argv[i];
					param2->fd_read=fd[0];
					param2->fd_write=fd[1];
					pthread_create(&prodcuteur[threadNum],NULL,produceFromInternet,param1);
					numofThread++;
					threadNum++;
					pthread_create(&prodcuteur[threadNum],NULL,produceFromFD,param2);
					threadNum++;
					numofThread++;
				}
			}
			else
			{
				//lecture depuis le fichier
				int fd=open(argv[i],O_RDONLY);
				if(fd==-1)
				{
					printf("erreur de d'ouverture du ficher : %s\n",argv[i]);
				}
				else
				{

					struct producteur_param* param = (struct producteur_param*)malloc(sizeof(*param));
					if(param==NULL)
					{
						printf("erreur pas assez de mémoire\n");
					}
					else
					{
						param->buffer1=buffer1;
						param->inputName=argv[i];
						param->fd_read=fd;
						param->fd_write=1;
						pthread_create(&prodcuteur[threadNum],NULL,produceFromFD,param);
						numofThread++;
						threadNum++;
					}

				}
			}
		}
		int j;
		for(j = 0; j<maxthreads;j++)
		{
			struct consommateur_param* param = (struct consommateur_param*)malloc(sizeof(*param));
			param->lock=&lock;
			param->buffer1=buffer1;
			param->isProducing=&isProducing;
			param->num=j;
			param->global=global;
			param->lockGlobal=&lockGlobal;
			param->size = size;
			pthread_create(&consommateur[j],NULL,consumme,param);
		}

		int cursor;
		for(cursor=0;cursor<numofThread;cursor++)
		{
			pthread_join(prodcuteur[cursor],NULL);
		}
		pthread_mutex_lock(&lock);
		isProducing=0;
		pthread_mutex_unlock(&lock);
		for(cursor=0;cursor<maxthreads;cursor++)
		{
			pthread_join(consommateur[cursor],NULL);
		}

		int succes = searchUniquePrime(*global,size);
		if(gettimeofday(&stop,NULL) == -1)
		{
			perror("clock gettime\n");
		}
		long int sec = stop.tv_sec-start.tv_sec;
		long long int usec = (1000000-start.tv_usec+stop.tv_usec);
		printf("%ld.%lld s\n",sec,usec/1000);
		freeBuffer(buffer1);
		free(consommateur);
		free(size);
		free(*global);
		free(global);
		free(prodcuteur);
		consommateur=NULL;
		size=NULL;
		*global=NULL;
		global=NULL;
		prodcuteur=NULL;
		pthread_mutex_destroy(&lockGlobal);
		pthread_mutex_destroy(&lock);

		return succes;
	}
	return EXIT_FAILURE;
}

