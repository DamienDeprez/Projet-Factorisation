//
// Created by damien on 22/04/15.
//

/**
 * Liste des fonctions utlisées par le producteur
 */

#ifndef FACTORISATION_PRODUCTEUR_H
#define FACTORISATION_PRODUCTEUR_H

/**
 * readOneFromFile
 * lit un nombre depuis le fichier
 *
 * @fd : descripteur de fichier correspondant au fichier où il faut lire une entrée
 * @fileName : nom du fichier d'origine du nombre
 * @return : structure nombre ou NULL si erreur
 */
struct nombre readOneFromFile (const int fd, const char* fileName);

/**
 * readOneFromStdin
 * lit un nombre depuis l'entrée standard
 *
 * %TODO compléter les arguments de la fonction
 * @return : structure nombre ou NULL si erreur
 */
struct nombre readOneFromStdin ();

/**
 * readOneFromInternet
 * lit un nombre depuis un fichier se trouvant sur le résau
 *
 * %TODO compléter les arguments de la fonction
 * @fileName : nom du fichier d'origine du nombre
 * @return : structure nombre ou NULL si erreur
 */
struct nombre readOneFromInternet (const char* fileName);

/**
 * produceFromFile
 * lit le fichier et place le contenu dans le buffer
 *
 * @filePath : chemin du fichier
 */
void produceFromFile(const char* filePath);

/**
 * produceFromStdin
 * lit l'entrée standard et place le contenu dans le buffer
 *
 * @stdin : contenu de l'entrée standard
 */
void produceFromStdin(const char** stdin);

/**
 * produceFromInternet
 * lit le fichier distant et place le contenu dans le buffer
 *
 * @fileLocation : URL du fichier
 */
void produceFromInternet(const char* fileLocation);

#endif //FACTORISATION_PRODUCTEUR_H
