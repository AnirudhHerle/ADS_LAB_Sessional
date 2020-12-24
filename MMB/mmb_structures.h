/*
 * mmb_structures.h
 *
 *  Created on: Dec 24, 2020
 *      Author: hanus
 */

#ifndef MMB_STRUCTURES_H_
#define MMB_STRUCTURES_H_
#include <stdint.h>
#include <string.h>
#include "app_constants.h"

//keeping acc_num as char to impose length restriction
typedef struct _acc_num_ Account_num;
struct _acc_num_
{
	char bank_code [2];
	char area_code [4];
	char account_type [2];
	char acc_num_branch[4];
};

typedef struct _account_ Account;
struct _account_
{
    char     name[NAME_LEN]; // 64
    char     joint_name[NAME_LEN]; // 64
    uint8_t age;
    char     pan[PAN_NUM]; // 10
    uint16_t phone;
    float    acc_bal;
    Account_num acc_num;
    uint64_t debit_count;
    uint64_t credit_count;
    //Slist transactions;  // SLL to store cr or dr and amount information
};

//interfaces

//return Account type after creating account
Account  open_account(char name[], char joint_name[], uint16_t age[], char pan[], uint16_t phone, float init_deposit, char account_type);

// return zero if credit/debit failure - else return 1
Account  credit(Account a, float amount);
Account  debit(Account a, float amount);

// return balance as float
float    balance_enquiry(Account a);

// return count of cr/dr as int
uint64_t credit_count(Account a);
uint64_t debit_count(Account a);

// bank staff operations
uint64_t total_customers();
uint64_t category_customers(char account_type[]);

// private function
Account_num gen_acc_num(char account_type[]);

#endif /* MMB_STRUCTURES_H_ */
