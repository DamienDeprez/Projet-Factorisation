//
// Created by damien on 22/04/15.
//

/**
 * Fonction principale du programme
 */

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "factorisation.h"
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
	char* argerror;
	char* internet="http://";
	printf("Programme de factorisation de nombre\n");
	if(argc>1) {
		int i;
		for (i = 0; i < argc; i++)
		{
			if(!strcmp(argv[i],"-stdin"))
			{
				//lecture depuis stdin
				printf("lecture depuis stdin\n");
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
			}
			else if(strstr(argv[i],internet)!=NULL)
			{
				//lecture depuis internet
				printf("lecture depuis l'URL : %s\n",argv[i]);
				produceFromInternet(argv[i]);
			}
			else
			{
				//lecture depuis le fichier
				printf("lecure depuis le fichier : %s\n",argv[i]);
			}
		}
	}
	return EXIT_SUCCESS;
}

