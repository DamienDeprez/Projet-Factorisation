#include <stdio.h>
#include <stdlib.h>

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>

#include "../main/factorisation.h"

/*
 * Liste des variables globales
 */
struct nombre *nbr1 = NULL;
struct nombre *nbr2 = NULL;
struct nombre *nbr3 = NULL;
struct nombre *nbr4 = NULL;

struct listeFacteurPremier *list1 = NULL;
struct listeFacteurPremier *list2 = NULL;
struct listeFacteurPremier *list3 = NULL;
struct listeFacteurPremier *list4 = NULL;

int init_suite(void)
{
	nbr1 = (struct nombre *) malloc(sizeof(struct nombre));
	nbr2 = (struct nombre *) malloc(sizeof(struct nombre));
	nbr3 = (struct nombre *) malloc(sizeof(struct nombre));
	nbr4 = (struct nombre *) malloc(sizeof(struct nombre));
	if (nbr1 == NULL || nbr2 == NULL || nbr3 == NULL || nbr4 == NULL) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int clean_suite(void)
{
	if (nbr1 != NULL) {
		free(nbr1);
		nbr1 = NULL;
	}
	if (nbr2 != NULL) {
		free(nbr2);
		nbr2 = NULL;
	}
	if (nbr3 != NULL) {
		free(nbr3);
		nbr3 = NULL;
	}
	if (nbr4 != NULL) {
		free(nbr4);
		nbr4 = NULL;
	}
	if (nbr1 != NULL || nbr2 != NULL || nbr3 != NULL || nbr4 != NULL) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void test_factorisation_null(void)
{

}

/**

*/
int main(int argc, char **argv)
{
	CU_pSuite factorisation = NULL; // Suite de test

	if (CUE_SUCCESS != CU_initialize_registry()) //initialisation du registre de CUnit
		return CU_get_error();


	/*
		ajoute la suite au registre avec une fonction d'initialisation et une fonction de fin (clean et free)
	*/
	factorisation = CU_add_suite("suite de tese sur la factorisation", init_suite, clean_suite);
	if (NULL == factorisation) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/*
	 * met la suite inactive
	 */
	/*if (CU_set_suite_active(factorisation, CU_FALSE) != 0) {
		CU_cleanup_registry();
		return CU_get_error();
	}*/

	/*
		ajoute le test à la suite de test
	*/

	/*
		lance le test selon le mode choisi
	*/
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();    // mode sans interraction avec la console
	//CU_console_run_tests(); // mode interraction avec la console
	CU_automated_run_tests(); // mode automatique avec sortie vers un fichier

	//CU_list_tests_to_file();
	CU_cleanup_registry();
	return CU_get_error();
}
