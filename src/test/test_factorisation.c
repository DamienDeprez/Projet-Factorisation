
#include <stdio.h>
#include <stdlib.h>

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>

int init_suite(void)
{
	printf("********Initialisation de la suite de Test********\n");
	return EXIT_SUCCESS;
}

int clean_suite(void)
{
	printf("\n\n********Fin de la suite de Test********");
	return EXIT_SUCCESS;
}


void test_assert_true(void)
{
	CU_ASSERT(1);
}
void test_assert_2_not_equal_minus_1(void)
{
	CU_ASSERT_NOT_EQUAL(2, -1);
}
void test_string_equals(void)
{
	CU_ASSERT_STRING_EQUAL("string #1", "string #1");
}
void test_failure(void)
{
	CU_ASSERT(0);
}
void test_string_equals_failure(void)
{
	CU_ASSERT_STRING_EQUAL("string #1", "string #2");
}

/**

*/
int main (int argc, char ** argv)
{
	CU_pSuite testSuite=NULL; // Suite de test

	if(CUE_SUCCESS != CU_initialize_registry()) //initialisation du registre de CUnit
		return CU_get_error();


	/*
		ajoute la suite au registre avec une fonction d'initialisation et une fonction de fin (clean et free)
	*/
	testSuite = CU_add_suite("Suite", init_suite, clean_suite);
	if (NULL == testSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	/*
		ajoute le test à la suite de test
	*/
	if(NULL == CU_add_test(testSuite, "test assert ok\n", test_assert_true))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(testSuite,"test assert failure\n",test_failure))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if(NULL == CU_add_test(testSuite,"test assert not equals\n",test_assert_2_not_equal_minus_1))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if(NULL == CU_add_test(testSuite, "test string equals failure\n",test_string_equals_failure))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(testSuite,"test string equals\n",test_string_equals))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/*
		lance le test selon le mode choisi
	*/
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();	// mode sans interraction avec la console
	//CU_console_run_tests(); // mode interraction avec la console
	CU_automated_run_tests(); // mode automatique avec sortie vers un fichier

	//CU_list_tests_to_file();
	CU_cleanup_registry();
	return CU_get_error();
}
