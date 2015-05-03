//
// Created by damien on 22/04/15.
//

/**
 * Liste des fonctions utlisées par le producteur
 */

#ifndef FACTORISATION_PRODUCTEUR_H
#define FACTORISATION_PRODUCTEUR_H

#include "buffer.h"

/*
 * Structure constenant les paramètres utilisés par le producteur
 *
 * @buffer1: buffer utilisé pour partager les données
 * @inputName: nom de l'entrée
 * @fd_read: descripteur de fichier pour la lecture
 * @fd_write: descripteur de fichier pour l'écriture
 */
struct producteur_param
{
    struct buffer* buffer1;
    char* inputName;
    int fd_read;
    int fd_write;
};

/**
 * readOneFromFD
 * lit un nombre depuis le descripteur fd
 *
 * @fd : descripteur correspondant à l'entreé d'où il faut lire les données
 * @inputName : nom de l'entrée d'origine du nombre
 * @return : structure nombre si erreur le nombre vaut 0
 */
struct nombre readOneFromFD (const int fd, char* inputName);

/**
 * produceFromFD
 * lit les données depuis le descripteur de fichier et les place dans le buffer
 *
 * @param: pointeur vers la structure contenant les paramètre du producteur
 */

void* produceFromFD(void * param);

/**
 * produceFromInternet
 * lit le fichier distant et place le contenu dans un pipe
 *
 * @param: pointeur vers la structure contenant les paramètres du producteur
 */
void* produceFromInternet(void * param);

#endif //FACTORISATION_PRODUCTEUR_H
