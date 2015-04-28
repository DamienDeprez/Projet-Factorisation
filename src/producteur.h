//
// Created by damien on 22/04/15.
//

/**
 * Liste des fonctions utlisées par le producteur
 */

#ifndef FACTORISATION_PRODUCTEUR_H
#define FACTORISATION_PRODUCTEUR_H

/**
 * readOneFromLocal
 * lit un nombre depuis le descripteur fd
 *
 * @fd : descripteur correspondant à l'entreé d'où il faut lire les données
 * @inputName : nom de l'entrée d'origine du nombre
 * @return : structure nombre si erreur le nombre vaut 0
 */
struct nombre readOneFromLocal (const int fd, const char* inputName);

/**
 * readOneFromInternet
 * lit un nombre depuis un fichier se trouvant sur le résau
 *
 * @URL : URL du fichier à lire
 * @return : structure nombre si erreur le nombre vaut 0
 */
struct nombre readOneFromInternet (const char* URL);

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
 */
void produceFromStdin();

/**
 * produceFromInternet
 * lit le fichier distant et place le contenu dans le buffer
 *
 * @fileLocation : URL du fichier
 */
void produceFromInternet(const char* fileLocation);

#endif //FACTORISATION_PRODUCTEUR_H
