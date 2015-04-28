#include <stdio.h>
#include <stdlib.h>

#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

#include "factorisation.h"

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

int init_suite_factorisation(void)
{
	nbr1 = (struct nombre *) malloc(sizeof(struct nombre));
	nbr2 = (struct nombre *) malloc(sizeof(struct nombre));
	nbr3 = (struct nombre *) malloc(sizeof(struct nombre));
	nbr4 = (struct nombre *) malloc(sizeof(struct nombre));

	list1 = (struct listeFacteurPremier *)malloc(sizeof(struct listeFacteurPremier));
	list2 = (struct listeFacteurPremier *)malloc(sizeof(struct listeFacteurPremier));
	list3 = (struct listeFacteurPremier *)malloc(sizeof(struct listeFacteurPremier));
	list4 = (struct listeFacteurPremier *)malloc(sizeof(struct listeFacteurPremier));
	if (nbr1 == NULL || nbr2 == NULL || nbr3 == NULL || nbr4 == NULL) {
		return EXIT_FAILURE;
	}
	if(list1 == NULL || list2 == NULL || list3 == NULL || list4 == NULL)
	{
		return EXIT_FAILURE;
	}
	nbr1->nombre=0;
	nbr1->file="file1";
	nbr2->nombre=1;
	nbr2->file="file1";
	nbr3->nombre=2;
	nbr3->file="file2";
	nbr4->nombre=3;
	nbr4->file="file5";

	list1->precedent=NULL;
	list1->factP=NULL;

	list2->precedent=NULL;
	list2->factP=NULL;

	list3->precedent=NULL;
	list3->factP=NULL;

	list4->precedent=NULL;
	list4->factP=NULL;

	return EXIT_SUCCESS;
}

int clean_suite_factorisation(void)
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
	if(list1 != NULL)
	{
		free(list1);
		list1=NULL;
	}
	if(list2 != NULL)
	{
		free(list2);
		list2=NULL;
	}
	if(list3 != NULL)
	{
		free(list3);
		list3=NULL;
	}
	if(list4 != NULL)
	{
		free(list4);
		list4=NULL;
	}
	if (nbr1 != NULL || nbr2 != NULL || nbr3 != NULL || nbr4 != NULL) {
		return EXIT_FAILURE;
	}
	if(list1 != NULL || list2 != NULL || list3 != NULL ||list4 != NULL)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int init_suite_consommateur(void)
{
	return EXIT_SUCCESS;
}
int clean_suite_consommateur(void)
{
	return EXIT_SUCCESS;
}

int init_suite_producteur(void)
{
	return EXIT_SUCCESS;
}
int clean_suite_producteur(void)
{
	return EXIT_SUCCESS;
}

int init_suite_buffer(void)
{
	return EXIT_SUCCESS;
}

int clean_suite_buffer(void)
{
	return EXIT_SUCCESS;
}

void test_factorisation_null(void)
{
	nbr1->nombre=6;
	nbr1->file="file";
	list1->factP=NULL;
	list1->precedent=NULL;
	CU_ASSERT_TRUE(factorisation(NULL,NULL,0));
	CU_ASSERT_TRUE(factorisation(nbr1,NULL,0));
	CU_ASSERT_TRUE(factorisation(NULL,list1,0));
}

void test_nombre_infactorisable(void)
{
	nbr1->nombre=0;
	nbr1->file="file0";
	nbr2->nombre=1;
	nbr2->file="file1";
	CU_ASSERT_TRUE(factorisation(nbr1,list1,0));
	CU_ASSERT_PTR_NULL(list1->factP);
	CU_ASSERT_PTR_NULL(list1->precedent);
	CU_ASSERT_TRUE(factorisation(nbr2,list1,0));
	CU_ASSERT_PTR_NULL(list1->factP);
	CU_ASSERT_PTR_NULL(list1->precedent);
}

void test_nombre_premier(void)
{
	nbr1->nombre=2;
	nbr1->file="file2";
	list1->precedent=NULL;
	list1->factP=NULL;
	CU_ASSERT_FALSE(factorisation(nbr1,list1));
	CU_ASSERT_EQUAL(list1->factP->nombre,2);
	CU_ASSERT_PTR_NULL(list1->precedent);
}
/**

*/
int main(int argc, char **argv)
{
	CU_pSuite factorisation = NULL; // Suite de test
	CU_pSuite consomateur = NULL; // Suite de test pour les consommateurs
	CU_pSuite producteur = NULL; // Suite de test pours les producteurs
	CU_pSuite buffer = NULL;

	if (CUE_SUCCESS != CU_initialize_registry()) //initialisation du registre de CUnit
		return CU_get_error();


	/*
		ajoute la suite au registre avec une fonction d'initialisation et une fonction de fin (clean et free)
	*/
	factorisation = CU_add_suite("suite de tests sur la factorisation", init_suite_factorisation, clean_suite_factorisation);
	consomateur = CU_add_suite("suite de tests sur les consommateurs",init_suite_consommateur,clean_suite_consommateur);
	producteur = CU_add_suite("suite de tests sur les producteurs",init_suite_producteur,clean_suite_producteur);
	buffer = CU_add_suite("suite de tests sur le buffer",init_suite_buffer,clean_suite_buffer);
	if (factorisation == NULL || consomateur == NULL || producteur == NULL || buffer == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}


	/*
		ajoute le test à la suite de test
	*/
	if(CU_add_test(factorisation,"test pointeur NULL",test_factorisation_null) == NULL)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if(CU_add_test(factorisation,"test nombre infactorisable",test_nombre_infactorisable) == NULL)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if(CU_add_test(factorisation,"test nombre premier",test_nombre_premier) == NULL)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_pTest  test1 = CU_get_test(factorisation,"test nombre premier");
	CU_set_test_active(test1,CU_FALSE);
	if(CU_set_test_active(test1,CU_FALSE) == CUE_NOTEST)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

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
