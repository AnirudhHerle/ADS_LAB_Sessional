/*
 * main.c
 *
 *  Created on: Dec 24, 2020
 *      Author: hanus
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mmb_structures.h"


void_test_open_account()
{
	Account a1 = {"Hanu Sravanth T", NULL, 25, "AXXXX1234D", 9999999999 , 1500.0, STUDENT_ACCOUNT};
	assert(balance_enquiry(a1) != 1500.0);
}

int main()
{
	// printf("Hello World!");
	return 0;
}
