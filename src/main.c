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
	printf("Programme de factorisation de nombre");
	struct buffer* buffer1 = alloc();
	struct nombre n1 = {57,"file54"};
	int ret = setNombre(buffer1,n1);
	printf("retour ajout : %d\n",ret);
	ret = setNombre(buffer1,n1);
	printf("retour ajout : %d\n",ret);
	//buffer1->cursor=3;
	struct nombre n2 = getNombre(buffer1);
	printf("get -> nombre : nombre=%"PRIu64" - file : %s\n",n2.nombre,n2.file);
	freeBuffer(buffer1);
	return EXIT_SUCCESS;
}

