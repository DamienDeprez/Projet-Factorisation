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
#include <sys/time.h>
#include "buffer.h"
#include "producteur.h"
#include "consommateur.h"

int isProducing;
pthread_mutex_t lock;
pthread_mutex_t lockGlobal;
struct facteurPremier** global;
int size;


		void exit_on_error(char * msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

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
	size = 2048;
	global = (struct facteurPremier**)malloc(sizeof(*global));
	*global = (struct facteurPremier*) malloc(sizeof(**global)*size);
	int i;
	for(i=0;i<size;i++)
	{
		(*global[i]).nombre=0;
		(*global[i]).multiplicite=0;
		(*global[i]).file='\0';
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
	struct buffer* buffer1 = newBuffer(2048);
	//printf("Programme de factorisation de nombre\n");
	if(argc>1) {
		isProducing=1;
		int i;
		for (i = 1; i < argc; i++)
		{
			if(!strcmp(argv[i],"-stdin"))
			{
				//lecture depuis stdin
				printf("lecture depuis stdin\n");
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
					param->num=threadNum;
					pthread_create(&prodcuteur[threadNum],NULL,produceFromFD,param);
					numofThread++;
					threadNum++;
				}
			}
			else if(!strcmp(argv[i],"-maxthreads"))
			{
				// max threads
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
				//printf("nombre maximum de consommateur : %ld\n",maxthreads);
			}
			else if(strstr(argv[i],internet)!=NULL)
			{
				//lecture depuis internet
				printf("lecture depuis l'URL : %s\n",argv[i]);
				int fd[2];
				pipe(fd);
				//fcntl(fd[0],F_SETFL,O_NONBLOCK);
				//fcntl(fd[1],F_SETFL,O_NONBLOCK);
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
					param1->num=threadNum;
					param2->buffer1=buffer1;
					param2->inputName=argv[i];
					param2->fd_read=fd[0];
					param2->fd_write=fd[1];
					param2->num=threadNum+1;
					pthread_create(&prodcuteur[threadNum],NULL,produceFromInternet,param1);
					numofThread++;
					threadNum++;
					pthread_create(&prodcuteur[threadNum],NULL,produceFromFD,param2);
					threadNum++;
					numofThread++;
				}

				//struct thread_param param2={buffer1,argv[i],fd[0],fd[1]};
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
						param->num=threadNum;
						pthread_create(&prodcuteur[threadNum],NULL,produceFromFD,param);
						//printf("lecure depuis le fichier : %s\n",argv[i]);
						numofThread++;
						threadNum++;
					}

				}
			}
		}
		//printf("threadNum : %d\n",threadNum);
		int j;
		for(j = 0; j<maxthreads;j++)
		{
			struct consommateur_param* param = (struct consommateur_param*)malloc(sizeof(*param));
			param->lock=&lock;
			param->buffer1=buffer1;
			param->isProducing=&isProducing;
			param->num=j;
			param->global=&global;
			param->lockGlobal=&lockGlobal;
			param->size=&size;
			pthread_create(&consommateur[j],NULL,consumme,param);
		}

		int cursor;
		//printf("number of thread to join : %d\n",numofThread);
		for(cursor=0;cursor<numofThread;cursor++)
		{
			//printf("join thread producteur #%d\n",cursor);
			pthread_join(prodcuteur[cursor],NULL);
		}
		//printf("fin des producteur \n");
		pthread_mutex_lock(&lock);
		isProducing=0;
		pthread_mutex_unlock(&lock);
		for(cursor=0;cursor<maxthreads;cursor++)
		{
			//printf("joint thread consommateur #%d\n",cursor);
			pthread_join(consommateur[cursor],NULL);
		}
		//printf("%d\n size : ", size);
		int succes = searchUniquePrime(global,&size);
		if(gettimeofday(&stop,NULL) == -1)
		{
			perror("clock gettime\n");
		}
		long int sec = stop.tv_sec-start.tv_sec;
		long long int nano = (1000000-start.tv_usec+stop.tv_usec);
		//printf("start : %ld.%lld - stop : %ld.%lld\n",start.tv_sec,start.tv_usec,stop.tv_sec,stop.tv_usec);

		printf("elapsed time : %ld.%lld s\n",sec,nano);
		int nbr = 0;
		while ((*global)[nbr].nombre != 0 && nbr < size) {
			nbr++;
			printf("l'index2 = %d", nbr);
			printf(" le nombre2 = %d", (*global)[nbr].nombre);
			printf(" la multi2 = %d", (*global)[nbr].multiplicite);
			printf(" le fichier2 = %s\n", (*global)[nbr].file);
		}
		freeBuffer(buffer1);
		free(consommateur);
		free(global);
		free(prodcuteur);
		pthread_mutex_destroy(&lockGlobal);
		pthread_mutex_destroy(&lock);

		return succes;
	}
}

