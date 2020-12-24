/*
 * mmb_functions.c
 *
 *  Created on: Dec 24, 2020
 *      Author: hanus
 */
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include "mmb_structures.h"

uint64_t customers       = 0;
uint64_t num_SB_ACCOUNT      = 0;
uint64_t num_CURRENT_ACCOUNT = 0;
uint64_t num_SALARY_ACCOUNT  = 0;
uint64_t num_JOINT_ACCOUNT   = 0;
uint64_t num_STUDENT_ACCOUNT = 0;

//return Account type after creating account
Account  open_account(char name[], char joint_name[], uint8_t age[], char pan[], uint16_t phone, float init_deposit, char account_type)
{
	Account acc;
	strcpy(acc.name, name);

	if (account_type == JOINT_ACCOUNT)
	{
		assert(joint_name != NULL);
		strcpy(acc.joint_name, joint_name);
	}

	acc.age = age;

	if (account_type == STUDENT_ACCOUNT)
	{
		if (pan != NULL)
		{
			strcpy(acc.pan, pan);
		}
		else
		{
			strcpy(acc.pan, NULL);
		}
	}

	strcpy(acc.pan, pan);

	assert(len(phone) != 10);
	acc.phone = phone;


	if (account_type != STUDENT_ACCOUNT)
	{
		if (init_deposit < 2000)
		{
			acc.acc_bal = init_deposit - 1000
		}
	}
	else
	{
		acc.acc_bal = init_deposit;
	}

	strcpy(acc.acc_num, gen_acc_num(acc));

	customers = customers + 1;
	switch(account_type)
	{
	   case SB_ACCOUNT  :
		   num_SB_ACCOUNT = num_SB_ACCOUNT + 1;
	      break;
	   case CURRENT_ACCOUNT  :
		   num_CURRENT_ACCOUNT = num_CURRENT_ACCOUNT + 1;
	      break;
	   case SALARY_ACCOUNT  :
		   num_SALARY_ACCOUNT = num_SALARY_ACCOUNT + 1;
	      break;
	   case JOINT_ACCOUNT  :
		   num_JOINT_ACCOUNT = num_JOINT_ACCOUNT + 1;
	      break;
	   case STUDENT_ACCOUNT  :
		   num_STUDENT_ACCOUNT = num_STUDENT_ACCOUNT + 1;
	      break;
	}

	return acc;
}

// return balance as float
Account  credit(Account a, float amount)
{
	a.acc_bal = a.acc_bal + amount;
	a.credit_count = a.credit_count + 1
	return a;
}
Account  debit(Account a, float amount)
{
	if (a.acc_num.account_type != STUDENT_ACCOUNT)
	{
		assert(a.debit_count <= 5);
	}
	if (a.acc_num.account_type == STUDENT_ACCOUNT)
	{
		assert(a.debit_count <= 10);
		a.acc_bal = a.acc_bal - amount;
	}

	a.acc_bal = a.acc_bal - amount;
	if (a.acc_bal < 2000)
	{
		a.acc_bal = a.acc_bal - 1000;
	}
	a.debit_count = a.debit_count + 1

	return a;
}

// return balance as float
float    balance_enquiry(Account a)
{
	return a.acc_bal;
}

// return count of cr/dr as int
uint64_t credit_count(Account a)
{
	return a.credit_count;
}
uint64_t debit_count(Account a)
{
	return a.debit_count;
}

// bank staff operations
uint64_t total_customers()
{
	return customers;
}
uint64_t category_customers(char account_type[])
{
	uint64_t cat_count = 0;
	switch(account_type)
	{
	   case SB_ACCOUNT  :
		   cat_count = num_SB_ACCOUNT;
	      break;
	   case CURRENT_ACCOUNT  :
		   cat_count = num_CURRENT_ACCOUNT;
	      break;
	   case SALARY_ACCOUNT  :
		   cat_count = num_SALARY_ACCOUNT;
	      break;
	   case JOINT_ACCOUNT  :
		   cat_count = num_JOINT_ACCOUNT;
	   case STUDENT_ACCOUNT  :
		   cat_count = num_STUDENT_ACCOUNT;
	      break;
	}

	return cat_count;
}

// private function
Account_num gen_acc_num(char account_type[])
{
	uint8_t branch_acc_num = 0;
	char branch_acc_num_char[];
	Account_num a_num;
	strcpy(a_num.bank_code, '12'); // 2
	strcpy(a_num.area_code, '2020'); // 4
	strcpy(a_num.account_type, account_type); // 2

	branch_acc_num = category_customers(a_num.account_type);
	branch_acc_num = branch_acc_num + 1;
	strcpy(a_num.acc_num_branch, tostring(branch_acc_num_char,branch_acc_num)); // 4

}

// convert int to string - took from internet
void tostring(char str[], int num)
{
    int i, rem, len = 0, n;

    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}
