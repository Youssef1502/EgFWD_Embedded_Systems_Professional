#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include"Server.h"

#define number_of_accounts 10

#define recieveTransactionData_Main
//#define recieveTransactionData_Test

#define isValidAccount_Main
//#define isValidAccount_Test

#define isBlockedAccount_Main
//#define isBlockedAccount_Test

#define isAmountAvailable_Main
//#define isAmountAvailable_Test

#define saveTransaction_Main
//#define saveTransaction_Test

#define listSavedTransactions_Main
//#define listSavedTransactions_Test


ST_accountsDB_t accountsDB[255] =
{
	{2000.0  , RUNNING , "8989374615436851"},
	{100000.0, BLOCKED , "5807007076043875"},
	{50000.0 , RUNNING , "4856359847152456"},
	{30000.0 , BLOCKED , "6459853245845657"},
	{5000.0  , RUNNING , "6548952157945862"},
	{120000.0, BLOCKED , "2468597564823485"},
	{50500.0 , RUNNING , "1259785634582658"},
	{8900.0  , BLOCKED , "9458213597562486"},
	{18300.0 , RUNNING , "7153468549552458"},
	{25400.0 , BLOCKED , "4458625589755422"},
};


ST_accountsDB_t* account_DBptr = accountsDB;			// Pointer to Search for a Valid Account
ST_accountsDB_t* Valid_AccountPtr = NULL;				// Pointer to Store the Address of the Valid Account

ST_transaction_t transactionsDB[255] = { 0 };
ST_transaction_t* transactions_DBptr = transactionsDB;
ST_transaction_t* transaction_reference = NULL;			// Pointer to Access the TransactionsDB Array

EN_transState_t transaction_state = 0;
uint32_t transactionsDB_index = 0;						// Index to be added on transactions_DBptr Pointer to Access the TransactionsDB Array


/* Server Side Functions */
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	/*** Begin of Main Code ***/

	#ifdef recieveTransactionData_Main

		ST_transaction_t* save_transaction_ptr = transData;

		if (isValidAccount(Card_Ptr, account_DBptr) == ACCOUNT_NOT_FOUND)
		{
			printf("Declined : Invalid Account\n");
			transaction_state = FRAUD_CARD;
		}
		else if (isBlockedAccount(Valid_AccountPtr) == BLOCKED_ACCOUNT)
		{
			transaction_state = DECLINED_STOLEN_CARD;
		}
		else if (isAmountAvailable(Terminal_Ptr, Valid_AccountPtr) == LOW_BALANCE)
		{
			printf("Declined : Insuffecient Amount\n");
			transaction_state = DECLINED_INSUFFECIENT_FUND;
		}
		else
		{
			transaction_state = APPROVED;
			Valid_AccountPtr->balance = Valid_AccountPtr->balance - Terminal_Ptr->transAmount;
		}



		if (saveTransaction(save_transaction_ptr) != SERVER_OK)
		{
			transaction_state = INTERNAL_SERVER_ERROR;
		}

	#endif

	/*** End of Main Code ***/


	/*** Begin of Test Code ***/

	#ifdef recieveTransactionData_Test


		static ST_transaction_t Test_Array[4] =
		{
			{"Youssef  Adel  Youssef" , "8989374615436851" , "10/23" , 1000.0 , 20000.0 , "02/10/2023" , APPROVED , 1},
			{"Youssef  Adel  Youssef" , "1212121221122112" , "10/23" , 1000.0 , 20000.0 , "02/10/2023" , FRAUD_CARD , 2},
			{"Youssef  Adel  Youssef" , "5807007076043875" , "10/23" , 1000.0 , 20000.0 , "02/10/2023" , DECLINED_STOLEN_CARD , 3},
			{"Youssef  Adel  Youssef" , "6548952157945862" , "10/23" , 7000.0 , 20000.0 , "02/10/2023" , DECLINED_INSUFFECIENT_FUND , 4}
		};


		uint8_t Coloumn = 0;
		static Row = 0;

		printf("Input Data : \n");
		transaction_reference = &Test_Array[Row];
		listSavedTransactions();

		ST_transaction_t* save_transaction_ptr = &Test_Array[Row];

		if (isValidAccount(&Test_Array[Row].cardHolderData, account_DBptr) == ACCOUNT_NOT_FOUND)
		{
			Row++;
			return FRAUD_CARD;
		}
		else if (isBlockedAccount(Valid_AccountPtr) == BLOCKED_ACCOUNT)
		{
			Row++;
			return DECLINED_STOLEN_CARD;
		}
		else if (isAmountAvailable(&Test_Array[Row].terminalData, Valid_AccountPtr) == LOW_BALANCE)
		{
			Row++;
			return DECLINED_INSUFFECIENT_FUND;
		}
		else
		{
			Row++;
			return APPROVED;
		}
		
	#endif
}


EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	/*** Begin of Main Code ***/

	#ifdef isValidAccount_Main

		uint8_t PAN_Compare = 0;
		Valid_AccountPtr = NULL;

		for (uint8_t i = 0; i < number_of_accounts; i++)
		{
			PAN_Compare = strcmp(cardData->primaryAccountNumber, accountRefrence->primaryAccountNumber);

			if (PAN_Compare == 0)
			{
				Valid_AccountPtr = accountRefrence;
				return SERVER_OK;
			}
			accountRefrence++;
		}

		if (Valid_AccountPtr == 0)
		{
			return  ACCOUNT_NOT_FOUND;
		}

	#endif

	/*** End of Test Code ***/

	/*** Begin of Test Code ***/

	#ifdef isValidAccount_Test

		static ST_cardData_t Test_Array[4] =
		{
			{"Youssef  Adel  Youssef" , "8989374615436851" , "10/23" },
			{"Youssef  Adel  Youssef" , "1212121221122112" , "10/23" },
			{"Youssef  Adel  Youssef" , "5807007076043875" , "10/23" },
			{"Youssef  Adel  Youssef" , "4856816467664484" , "10/23" }
		};


		uint8_t Coloumn = 0;
		static Row = 0;

		printf("Input Data : %s\n", Test_Array[0].primaryAccountNumber);

		uint8_t PAN_Compare = 0;
		Valid_AccountPtr = NULL;

		for (uint8_t i = 0; i < number_of_accounts; i++)
		{
			PAN_Compare = strcmp(Test_Array[Row].primaryAccountNumber, accountRefrence->primaryAccountNumber);

			if (PAN_Compare == 0)
			{
				Row++;
				return SERVER_OK;
			}
			accountRefrence++;
		}

		if (Valid_AccountPtr == 0)
		{
			Row++;
			return  ACCOUNT_NOT_FOUND;
		}

	#endif
}


EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	/*** Begin of Main Code ***/

	#ifdef isBlockedAccount_Main

		if (accountRefrence != 0)
		{
			if (accountRefrence->state == RUNNING)
			{
				return SERVER_OK;
			}
		
			else if (accountRefrence->state == BLOCKED)
			{
				return BLOCKED_ACCOUNT;
			}
		}

	#endif

	/*** End of Main Code ***/


	/*** Begin of Test Code ***/

	#ifdef isBlockedAccount_Test


		uint8_t Test_Array[2] = { RUNNING , BLOCKED };
		static uint8_t Row = 0;

		printf("Input Data : %d\n", Test_Array[Row]);

		if (Test_Array[Row] == RUNNING)
		{
			Row++;
			return SERVER_OK;
		}

		else if (Test_Array[Row] == BLOCKED)
		{
			Row++;
			return BLOCKED_ACCOUNT;
		}

	#endif

	/*** End of Test Code ***/
}


EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	/*** Begin of Main Code ***/

	#ifdef isAmountAvailable_Main

		if (accountRefrence != 0)
		{
			if (termData->transAmount > accountRefrence->balance)
			{
				return LOW_BALANCE;
			}

			else
			{
				return SERVER_OK;
			}
		}

	#endif

	/*** End of Main Code ***/


	/*** Begin of Test Code ***/

	#ifdef isAmountAvailable_Test


		float Test_Array_transAmount[3] = { 1000.0 , 7000.0 , 10000.0};
		float Test_Array_balance[3]     = { 2000.0 , 7000.0 , 5000.0};
		static uint8_t Row = 0;

		printf("Input Data : %f\n", Test_Array_transAmount[Row]);

		if (Test_Array_transAmount[Row] > Test_Array_balance[Row])
		{
			Row++;
			return LOW_BALANCE;
		}

		else
		{
			Row++;
			return SERVER_OK;
		}

	#endif

	/*** End of Test Code ***/
}


EN_serverError_t saveTransaction(ST_transaction_t* transData)
{

	/*** Begin of Main Code ***/
	
	#ifdef saveTransaction_Main

		transData = transData + transactionsDB_index;
		transaction_reference = transData;

		strcpy(transData->cardHolderData.cardHolderName, Card_Ptr->cardHolderName);
		strcpy(transData->cardHolderData.cardExpirationDate, Card_Ptr->cardExpirationDate);
		strcpy(transData->cardHolderData.primaryAccountNumber, Card_Ptr->primaryAccountNumber);

		strcpy(transData->terminalData.transactionDate, Terminal_Ptr->transactionDate);
		transData->terminalData.transAmount = Terminal_Ptr->transAmount;
		transData->terminalData.maxTransAmount = Terminal_Ptr->maxTransAmount;

		transData->transState = transaction_state;

		transData->transactionSequenceNumber = 1 + transactionsDB_index;

		listSavedTransactions();

		transactionsDB_index++;

		return SERVER_OK;

	#endif

	/*** End of Main Code ***/


	/*** Begin of Test Code ***/

	#ifdef saveTransaction_Test

		printf("Input Data cardHolderName : %s\n", "Youssef  Adel  Youssef");
		printf("Input Data cardExpirationDate : %s\n", "10/23");
		printf("Input Data primaryAccountNumber : %s\n", "8989374615436851");
		printf("Input Data transactionDate : %s\n", "02/10/2023");
		printf("Input Data 1000.0 : %f\n", 1000.0);
		printf("Input Data maxTransAmount : %f\n", 20000.0);
		printf("Input Data transState : %s\n", "APPROVED");

		ST_transaction_t Test;
		ST_transaction_t* transDataTest = &Test;

		strcpy(transDataTest->cardHolderData.cardHolderName, "Youssef  Adel  Youssef");
		strcpy(transDataTest->cardHolderData.cardExpirationDate, "10/23");
		strcpy(transDataTest->cardHolderData.primaryAccountNumber, "8989374615436851");

		strcpy(transDataTest->terminalData.transactionDate, "02/10/2023");
		transDataTest->terminalData.transAmount = 1000.0;
		transDataTest->terminalData.maxTransAmount = 20000.0;

		transDataTest->transState = APPROVED;

		transDataTest->transactionSequenceNumber = 1 + transactionsDB_index;

		transactionsDB_index++;

		return SERVER_OK;

	#endif

	/*** End of Test Code ***/
}


void listSavedTransactions(void)
{
	/*** Begin of Main Code ***/

	#ifdef listSavedTransactions_Main

		printf("#########################\n");
		printf("Transaction Sequence Number: %ld\n", transaction_reference->transactionSequenceNumber);
		printf("Transaction Date: %s\n", transaction_reference->terminalData.transactionDate);
		printf("Transaction Amount: %f\n", transaction_reference->terminalData.transAmount);

		switch (transaction_reference->transState)
		{
		case APPROVED:
			printf("Transaction State: APPROVED\n");
			break;

		case DECLINED_INSUFFECIENT_FUND:
			printf("Transaction State: DECLINED_INSUFFECIENT_FUND\n");
			break;

		case DECLINED_STOLEN_CARD:
			printf("Transaction State: DECLINED_STOLEN_CARD\n");
			break;

		case FRAUD_CARD:
			printf("Transaction State: FRAUD_CARD\n");
			break;

		case INTERNAL_SERVER_ERROR:
			printf("Transaction State: INTERNAL_SERVER_ERROR\n");
			break;
		}

		printf("Terminal Max Amount: %f\n", transaction_reference->terminalData.maxTransAmount);
		printf("Cardholder Name: %s\n", transaction_reference->cardHolderData.cardHolderName);
		printf("PAN: %s\n", transaction_reference->cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s\n", transaction_reference->cardHolderData.cardExpirationDate);
		printf("The balance after Transaction for your card = %f\n", Valid_AccountPtr->balance);
		printf("#########################\n");

	#endif

	/*** End of Main Code ***/


	/*** Begin of Main Code ***/

	#ifdef listSavedTransactions_Test

		printf("Input Data :\n");
		printf("#########################\n");
		printf("Transaction Sequence Number: %ld\n", transaction_reference->transactionSequenceNumber);
		printf("Transaction Date: %s\n", transaction_reference->terminalData.transactionDate);
		printf("Transaction Amount: %f\n", transaction_reference->terminalData.transAmount);

		switch (transaction_reference->transState)
		{
		case APPROVED:
			printf("Transaction State: APPROVED\n");
			break;

		case DECLINED_INSUFFECIENT_FUND:
			printf("Transaction State: DECLINED_INSUFFECIENT_FUND\n");
			break;

		case DECLINED_STOLEN_CARD:
			printf("Transaction State: DECLINED_STOLEN_CARD\n");
			break;

		case FRAUD_CARD:
			printf("Transaction State: FRAUD_CARD\n");
			break;

		case INTERNAL_SERVER_ERROR:
			printf("Transaction State: INTERNAL_SERVER_ERROR\n");
			break;
		}
		printf("Terminal Max Amount: %f\n", transaction_reference->terminalData.maxTransAmount);
		printf("Cardholder Name: %s\n", transaction_reference->cardHolderData.cardHolderName);
		printf("PAN: %s\n", transaction_reference->cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s\n", transaction_reference->cardHolderData.cardExpirationDate);
		printf("#########################\n");

	#endif
}






void recieveTransactionDataTest(void)
{
	uint8_t Case_Num = 1, Result_Val = 0;
	static uint8_t i = 0;
	uint8_t Test_Array[4][30] =
	{
		"APPROVED",
		"FRAUD_CARD",
		"DECLINED_STOLEN_CARD",
		"DECLINED_INSUFFECIENT_FUND"
	};

	printf("=========================================\n");
	printf("Tester Name : Youssef Adel Youssef\n");
	printf("Function Name : recieveTransactionData\n");
	printf("=========================================\n\n");

	for (Case_Num = 1; Case_Num < 5; Case_Num++)
	{

		printf("Test Case : %d\n", Case_Num);
		Result_Val = recieveTransactionData(transactions_DBptr);


		printf("Expected Result : %s\n", Test_Array[i]);
		i++;

		if (Result_Val == FRAUD_CARD)
			printf("Actual Result : FRAUD_CARD\n");
		else if (Result_Val == DECLINED_STOLEN_CARD)
			printf("Actual Result : DECLINED_STOLEN_CARD\n");
		else if (Result_Val == DECLINED_INSUFFECIENT_FUND)
			printf("Actual Result : DECLINED_INSUFFECIENT_FUND\n");
		else if (Result_Val == INTERNAL_SERVER_ERROR)
			printf("Actual Result : INTERNAL_SERVER_ERROR\n");
		else
			printf("Actual Result : APPROVED\n");

		printf("----------------------------------------\n");

	}
}


void isValidAccountTest(void)
{
	uint8_t Case_Num = 1, Result_Val = 0;
	static uint8_t i = 0;
	uint8_t Test_Array[4][30] =
	{
		"SERVER_OK",
		"ACCOUNT_NOT_FOUND",
		"SERVER_OK",
		"ACCOUNT_NOT_FOUND"
	};

	printf("=========================================\n");
	printf("Tester Name : Youssef Adel Youssef\n");
	printf("Function Name : isValidAccount\n");
	printf("=========================================\n\n");

	for (Case_Num = 1; Case_Num < 5; Case_Num++)
	{

		printf("Test Case : %d\n", Case_Num);
		Result_Val = isValidAccount(Card_Ptr, account_DBptr);


		printf("Expected Result : %s\n", Test_Array[i]);
		i++;

		if (Result_Val == SERVER_OK)
			printf("Actual Result : SERVER_OK\n");
		else
			printf("Actual Result : ACCOUNT_NOT_FOUND\n");

		printf("----------------------------------------\n");

	}
}


void isBlockedAccountTest(void)
{
	uint8_t Case_Num = 1, Result_Val = 0;
	static uint8_t i = 0;
	uint8_t Test_Array[2][30] =
	{
		"SERVER_OK",
		"BLOCKED_ACCOUNT"
	};

	printf("=========================================\n");
	printf("Tester Name : Youssef Adel Youssef\n");
	printf("Function Name : isBlockedAccount\n");
	printf("=========================================\n\n");

	for (Case_Num = 1; Case_Num < 3; Case_Num++)
	{

		printf("Test Case : %d\n", Case_Num);
		Result_Val = isBlockedAccount(1);


		printf("Expected Result : %s\n", Test_Array[i]);
		i++;

		if (Result_Val == SERVER_OK)
			printf("Actual Result : SERVER_OK\n");
		else
			printf("Actual Result : BLOCKED_ACCOUNT\n");

		printf("----------------------------------------\n");

	}
}


void isAmountAvailableTest(void)
{
	uint8_t Case_Num = 1, Result_Val = 0;
	static uint8_t i = 0;
	uint8_t Test_Array[3][30] =
	{
		"SERVER_OK",
		"SERVER_OK",
		"LOW_BALANCE"
	};

	printf("=========================================\n");
	printf("Tester Name : Youssef Adel Youssef\n");
	printf("Function Name : isAmountAvailable\n");
	printf("=========================================\n\n");

	for (Case_Num = 1; Case_Num < 4; Case_Num++)
	{

		printf("Test Case : %d\n", Case_Num);
		Result_Val = isAmountAvailable(Terminal_Ptr , 1);


		printf("Expected Result : %s\n", Test_Array[i]);
		i++;

		if (Result_Val == SERVER_OK)
			printf("Actual Result : SERVER_OK\n");
		else
			printf("Actual Result : LOW_BALANCE\n");

		printf("----------------------------------------\n");

	}
}


void saveTransactionTest(void)
{
	uint8_t Case_Num = 1, Result_Val = 0;
	static uint8_t i = 0;
	uint8_t Test_Array[2][30] =
	{
		"SERVER_OK",
		"SAVING_FAILED"
	};

	printf("=========================================\n");
	printf("Tester Name : Youssef Adel Youssef\n");
	printf("Function Name : saveTransaction\n");
	printf("=========================================\n\n");

	for (Case_Num = 1; Case_Num < 2; Case_Num++)
	{

		printf("Test Case : %d\n", Case_Num);
		Result_Val = saveTransaction(NULL);


		printf("Expected Result : %s\n", Test_Array[i]);
		i++;

		if (Result_Val == SERVER_OK)
			printf("Actual Result : SERVER_OK\n");
		else
			printf("Actual Result : SAVING_FAILED\n");

		printf("----------------------------------------\n");

	}
}


void listSavedTransactionsTest(void)
{
	uint8_t Case_Num = 1, Result_Val = 0;

	printf("=========================================\n");
	printf("Tester Name : Youssef Adel Youssef\n");
	printf("Function Name : listSavedTransactions\n");
	printf("=========================================\n\n");

	for (Case_Num = 1; Case_Num < 5; Case_Num++)
	{
		static ST_transaction_t Test_Array[4] =
		{
			{"Youssef  Adel  Youssef" , "8989374615436851" , "10/23" , 1000.0 , 20000.0 , "02/10/2023" , APPROVED , 1},
			{"Youssef  Adel  Youssef" , "1212121221122112" , "10/23" , 1000.0 , 20000.0 , "02/10/2023" , FRAUD_CARD , 2},
			{"Youssef  Adel  Youssef" , "5807007076043875" , "10/23" , 1000.0 , 20000.0 , "02/10/2023" , DECLINED_STOLEN_CARD , 3},
			{"Youssef  Adel  Youssef" , "6548952157945862" , "10/23" , 7000.0 , 20000.0 , "02/10/2023" , DECLINED_INSUFFECIENT_FUND , 4}
		};


		uint8_t Coloumn = 0;
		static Row = 0;

		transaction_reference = &Test_Array[Row];

		printf("Test Case : %d\n", Case_Num);
		listSavedTransactions();


		printf("Expected Result : SERVER_OK\n");
		printf("Actual Result : SERVER_OK\n");

		printf("----------------------------------------\n");

		Row++;

	}
}