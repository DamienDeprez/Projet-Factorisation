//
// Created by damien on 22/04/15.
//

/**
 * Fonction principale du programme
 */

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "factorisation.h"
#include "buffer.h"

void exit_on_error(char * msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int main (int argc, char ** argv)
{
	printf("Programme de factorisation de nombre\n");
	//struct buffer* buffer1 = newBuffer(8);
	struct nombre n1 = {57,"file54"};
	struct listeFacteurPremier list1={NULL,NULL};
	/*int ret = writeBuffer(buffer1,n1);
	printf("retour ajout : %d\n",ret);
	ret = writeBuffer(buffer1,n1);
	printf("retour ajout : %d\n",ret);
	struct nombre n2 = readBuffer(buffer1);
	printf("get -> nombre : nombre=%"PRIu64" - file : %s\n",n2.nombre,n2.file);
	n2=readBuffer(buffer1);
	printf("get -> nombre : nombre=%"PRIu64" - file : %s\n",n2.nombre,n2.file);
	n2=readBuffer(buffer1);
	printf("get -> nombre : nombre=%"PRIu64" - file : %s\n",n2.nombre,n2.file);
	ret=writeBuffer(buffer1,n1);
	printf("retour ajout : %d\n",ret);
	ret=writeBuffer(buffer1,n1);
	printf("retour ajout : %d\n",ret);
	ret=writeBuffer(buffer1,n1);
	printf("retour ajout : %d\n",ret);
	ret=writeBuffer(buffer1,n1);
	printf("retour ajout : %d\n",ret);
	ret=writeBuffer(buffer1,n1);
	printf("retour ajout : %d\n",ret);
	freeBuffer(buffer1);*/
	printf("factorisation de 57 : %d\n",factorisation(&n1,&list1));
	return EXIT_SUCCESS;
}

