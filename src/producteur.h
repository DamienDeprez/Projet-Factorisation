//
// Created by damien on 22/04/15.
//

/**
 * Liste des fonctions utlisées par le producteur
 */

#ifndef FACTORISATION_PRODUCTEUR_H
#define FACTORISATION_PRODUCTEUR_H

#include "buffer.h"

struct thread_param
{
    struct buffer* buffer1;
    char* inputName;
    int fd_read;
    int fd_write;
    int mustJoin;
    pthread_t toJoin;
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
 * lit depuis le descripteur de fichier et le place dans le buffer
 *
 * @inputName: nom de l'entrée
 * @fd: file descripteur utilisé pour la lecture
 * @buffer1: pointeur vers le buffer
 */

void* produceFromFD(void * param);

/**
 * produceFromInternet
 * lit le fichier distant et place le contenu dans un pipe
 *
 * @fileLocation : URL du fichier
 * @fd: pipe où les données lue depuis le serveur seront écrite
 */
void* produceFromInternet(void * param);

#endif //FACTORISATION_PRODUCTEUR_H
