//
// Created by damien on 22/04/15.
//

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <curl/curl.h>
#include <inttypes.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>

#include "producteur.h"


/*
 * Fonction écrivant les données du flux ouvert par curl (ptr) dans data
 * @ptr: flux de donnée brute lu depuis le résaux
 * @size: taille des éléments lu depuis le résaux
 * @nmem: nombre d'élément lu depuis le résaux
 * @data pointeur vers l'endoir où écrire les données
 */
static size_t WriteMemoryPipe (void * ptr, size_t size, size_t nmem, void* data)
{
	int* fd  = (int*) data; // pointeur vers le pipe
	printf("pipe : fd %d\n",*fd);
	ssize_t retour = write(*fd,ptr,size*nmem); // écris dans le pipe
	printf("writen return : %lu\t donnée à lire %lu\n",retour,size*nmem);
	return size*nmem;
}

struct nombre readOneFromFD (const int fd, char* inputName)
{
	struct nombre retour={0,"\0"};
	uint64_t nombre;
	ssize_t isReadOK = read(fd,&nombre,sizeof(nombre));
	//printf("isReadOK %d\n",isReadOK);
	if(isReadOK == 0)
	{
		printf("isReadOK %lu\n",isReadOK);
		retour.file="eof";
	}
	else if (isReadOK == -1)
	{
		printf("erreur de lecture %d : %s\n",errno,strerror(errno));
		printf("file descriptore : %d\n",fd);
		retour.file="err";
	}
	else if(isReadOK == sizeof(uint64_t))
	{
		nombre = be64toh(nombre);
		retour.nombre=nombre;
		retour.file=inputName;
	}
	else{ // cas où la lecture est incomplète
		size_t toRead=sizeof(nombre)-isReadOK;
		uint64_t temp=nombre;
		while(toRead != 0 && isReadOK !=0)
		{
			printf("to read : %lu - temp : %"PRIx64"\n",toRead,temp);
			isReadOK=read(fd,&nombre,toRead);
			nombre = nombre << toRead*8;
			temp = temp | nombre;
			toRead=toRead-isReadOK;
		}
		nombre = be64toh(temp);
		retour.nombre=nombre;
		retour.file=inputName;
	}
	return retour;
}

void* produceFromFD(void* param)
{
	printf("lancement producefromFD\n");
	struct producteur_param* threadParam = (struct producteur_param*)param;
	printf("thread param : fd:%d\n",threadParam->fd_read);
	struct nombre nombre1 = {0,"null"};
	printf("condition : %d\n",!strcmp(nombre1.file,"eof"));
	while(strcmp(nombre1.file,"eof"))
	{
		nombre1 = readOneFromFD(threadParam->fd_read,threadParam->inputName);
		printf("read number %"PRIu64" from %s\n",nombre1.nombre,nombre1.file);
		if(strcmp(nombre1.file,"eof"))
		{
			writeBuffer(threadParam->buffer1,nombre1);
		}
	}
	if(threadParam->fd_read!=STDIN_FILENO) //si le descripteur de lecture n'est pas stdin, on le ferme
	{
		printf("close fd : %d\n",threadParam->fd_read);
		close(threadParam->fd_read);
	}
	/*if(threadParam->fd_write!=STDERR_FILENO && threadParam->fd_write != STDOUT_FILENO) // si le descritpeur d'écriture n'est pas stdout ou stderr, on le ferme
	{
		close(threadParam->fd_write);
	}*/
	printf("fin de produceFromFD\n");
	free(param);
	return NULL;
}

/*
 * TODO modifier pour utiliser le heap au lieux d'un fichier
 */
void* produceFromInternet(void* param) // écrit
{
	struct producteur_param* threadParam = (struct producteur_param*)param;
	printf("produceFromInternet : %s\n",threadParam->inputName);
	CURLcode error;
	CURL* url;
	url=curl_easy_init();
	if(url)
	{
		curl_easy_setopt(url,CURLOPT_FAILONERROR,1); // retourne un erreur pour les serveurs http
		curl_easy_setopt(url,CURLOPT_WRITEFUNCTION,WriteMemoryPipe);
		curl_easy_setopt(url,CURLOPT_WRITEDATA,&threadParam->fd_write);
		//curl_easy_setopt(url,CURLOPT_VERBOSE,1);
		curl_easy_setopt(url,CURLOPT_URL,threadParam->inputName);
		error = curl_easy_perform(url);
		if(error != CURLE_OK) {
			printf("erreur dans l'ouverture de l'url : %s\n\t%s\n", threadParam->inputName, curl_easy_strerror(error));
		}
	}
	curl_easy_cleanup(url);
	close(threadParam->fd_write);
	//produceFromFD(param);
	free(param);
	return NULL;
}
