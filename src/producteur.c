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
	ssize_t retour = write(*fd,ptr,size*nmem); // écris dans le pipe
	return (size_t ) retour;
}

struct nombre readOneFromFD (const int fd, char* inputName)
{
	struct nombre retour={0,"\0",0};
	uint64_t nombre;
	ssize_t isReadOK = read(fd,&nombre,sizeof(nombre));
	if(isReadOK == 0)
	{
		retour.err=1;
	}
	else if (isReadOK == -1)
	{
		retour.err=-1;
	}
	else if(isReadOK == sizeof(uint64_t))
	{
		nombre = be64toh(nombre);
		retour.nombre=nombre;
		retour.file=inputName;
		retour.err=0;
	}
	else{ // cas où la lecture est incomplète
		size_t toRead=sizeof(nombre)-isReadOK;
		uint64_t temp=nombre;
		while(toRead != 0 && isReadOK !=0)
		{
			isReadOK=read(fd,&nombre,toRead);
			nombre = nombre << toRead*8;
			temp = temp | nombre;
			toRead=toRead-isReadOK;
		}
		nombre = be64toh(temp);
		retour.nombre=nombre;
		retour.file=inputName;
		retour.err=0;
	}
	return retour;
}

void* produceFromFD(void* param)
{
	struct producteur_param* threadParam = (struct producteur_param*)param;
	struct nombre nombre1 = {0,"null"};
	while(nombre1.err==0) // tant que l'on est pas à la fin du fichier ou qu'il n'y a pas d'erreur
	{
		nombre1 = readOneFromFD(threadParam->fd_read,threadParam->inputName);
		if(nombre1.err==0)
		{
			writeBuffer(threadParam->buffer1,nombre1);
		}
	}
	if(threadParam->fd_read!=STDIN_FILENO) //si le descripteur de lecture n'est pas stdin, on le ferme
	{
		close(threadParam->fd_read);
	}
	free(param);
	param=NULL;
	return NULL;
}

void* produceFromInternet(void* param)
{
	struct producteur_param* threadParam = (struct producteur_param*)param;

	CURLcode error;
	CURL* url;
	url=curl_easy_init(); // initialisation
	if(url)
	{
		curl_easy_setopt(url,CURLOPT_FAILONERROR,1); // retourne un erreur pour les serveurs http
		curl_easy_setopt(url,CURLOPT_WRITEFUNCTION,WriteMemoryPipe); // fonction d'écriture des données
		curl_easy_setopt(url,CURLOPT_WRITEDATA,&threadParam->fd_write); // paramètre de la fonction d'écriture des données
		curl_easy_setopt(url,CURLOPT_URL,threadParam->inputName); // url du fichier
		error = curl_easy_perform(url); // lancement
		if(error != CURLE_OK) {
			printf("erreur dans l'ouverture de l'url : %s\n\t%s\n", threadParam->inputName, curl_easy_strerror(error));
		}
	}
	curl_easy_cleanup(url); // netoyage
	close(threadParam->fd_write);
	free(param);
	param=NULL;
	return NULL;
}