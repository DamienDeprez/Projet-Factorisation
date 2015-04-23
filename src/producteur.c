//
// Created by damien on 22/04/15.
//

#include <stdio.h>

#include "producteur.h"
#include "factorisation.h"

struct nombre readOneFromFile (const int fd, const char* fileName)
{
	return NULL;
}

struct nombre readOneFromStdin ()
{
	return NULL;
}

struct nombre readOneFromInternet (const char* fileName)
{
	return NULL;
}

void produceFromFile(const char* filePath)
{
	printf("produceFromFile : %s\n",filePath);
}

void produceFromStdin(const char** stdin)
{
	printf("produceFromStdin\n");
}

void produceFromInternet(const char* fileLocation)
{
	printf("produceFromInternet : %s\n",fileLocation);
}
