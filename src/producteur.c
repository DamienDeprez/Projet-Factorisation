//
// Created by damien on 22/04/15.
//

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <curl/curl.h>

#include "producteur.h"
#include "factorisation.h"

struct nombre readOneFromLocal (const int fd, const char* inputName)
{
	struct nombre retour;
	uint64_t nombre;
	ssize_t isReadOK = read(fd,&nombre,sizeof(nombre));
	if(isReadOK == 0)
	{
		//retour = {0,"\0"};
	}
	else if (isReadOK == -1)
	{
		printf("erreur de lecture %d : %s\n",errno,strerror(errno));
	}
	else
	{
		//retour= {nombre,inputName};
	}
	return retour;
}


struct nombre readOneFromInternet (const char* fileName)
{
	//return NULL;
}

void produceFromFile(const char* filePath)
{
	printf("produceFromFile : %s\n",filePath);
}

void produceFromStdin()
{
	printf("produceFromStdin\n");
}

/*
 * TODO modifier pour utiliser le heap au lieux d'un fichier
 */
void produceFromInternet(const char* fileLocation)
{
	printf("produceFromInternet : %s\n",fileLocation);
	CURLcode error;
	CURL* url;
	FILE* temp = fopen("temp","wb");
	url=curl_easy_init();
	if(url)
	{
		curl_easy_setopt(url,CURLOPT_FAILONERROR,1); // retourne un erreur pour les serveurs http
		curl_easy_setopt(url,CURLOPT_WRITEDATA,temp);
		curl_easy_setopt(url,CURLOPT_WRITEFUNCTION,NULL);
		//curl_easy_setopt(url,CURLOPT_VERBOSE,1);
		curl_easy_setopt(url,CURLOPT_URL,fileLocation);
		error = curl_easy_perform(url);
		fclose(temp);
		if(error != CURLE_OK)
		{
			printf("erreur dans l'ouverture de l'url : %s\n\t%s\n",fileLocation,curl_easy_strerror(error));
			curl_easy_cleanup(url);
		}
		else
		{
			curl_easy_cleanup(url);
			produceFromFile("temp");
		}


	}
}
