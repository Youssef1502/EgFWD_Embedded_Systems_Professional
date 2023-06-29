#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include"Terminal.h"

#define getTransactionDate_Main
//#define getTransactionDate_Test

#define isCardExpired_Main
//#define isCardExpired_Test

#define getTransactionAmount_Main
//#define getTransactionAmount_Test

#define isBelowMaxAmount_Main
//#define isBelowMaxAmount_Test

#define setMaxAmount_Main
//#define setMaxAmount_Test


ST_terminalData_t Terminal;
ST_terminalData_t* Terminal_Ptr = &Terminal;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	/*** Begin of Main Code ***/

	#ifdef getTransactionDate_Main

		uint8_t TransactionDate[15] = { 0 };
		uint8_t Day[2] = { 0 };
		uint8_t Month[2] = { 0 };
		uint8_t Year[4] = { 0 };
		uint8_t Day_Num = 0, Month_Num = 0;
		uint16_t Year_Num = 0;
		uint8_t TransactionDate_Num = 0;
		uint8_t i = 0;

		printf("Please Enter Your Transaction Date in Format DD/MM/YYYY : ");
		gets(TransactionDate);
		TransactionDate_Num = strlen(TransactionDate);

		if ((TransactionDate_Num != 10) || (TransactionDate[2] != '/') || (TransactionDate[5] != '/'))
			return WRONG_DATE;
		

		else
		{
			Day[0]   = TransactionDate[0];
			Day[1]   = TransactionDate[1];
			Month[0] = TransactionDate[3];
			Month[1] = TransactionDate[4];
			Year[0]  = TransactionDate[6];
			Year[1]  = TransactionDate[7];
			Year[2]  = TransactionDate[8];
			Year[3]  = TransactionDate[9];

			Day_Num = atoi(Day);
			Month_Num = atoi(Month);
			Year_Num = atoi(Year);

			if ((Day_Num > 31) || (Month_Num > 12) || (Year_Num < 2022))
				return WRONG_DATE;

			else
			{
				for (i = 0; i < 5; i++)
				{
					if ((isdigit(TransactionDate[i]) == 0) && (TransactionDate[i] != '/'))
						return WRONG_DATE;
				}
				strcpy(termData->transactionDate, TransactionDate);
				return TERMINAL_OK;
			}
		}

	#endif

	/*** End of Test Code ***/


	/*** Begin of Test Code ***/
	
	#ifdef getTransactionDate_Test

		uint8_t TransactionDate_Num = 0;
		uint8_t Day[2] = { 0 };
		uint8_t Month[2] = { 0 };
		uint8_t Year[4] = { 0 };
		uint8_t Day_Num = 0, Month_Num = 0;
		uint16_t Year_Num = 0;

		uint8_t Test_Array[15][15] =
		{
			"02/10/2022",
			"30/08/2022",
			"01/01/2023",
			"30/08/27",
			"3/08/2027",
			"30/8/2027",
			"/2008/2027",
			"/2/0042027",
			"02 10 2022",
			"30_08_2027",
			"ab/08/cdef",
			"3020832027",
			"30/08/227",
			"30/08/20278",
			"30/08/2020"
		};

		uint8_t Coloumn = 0;
		static Row = 0;

		printf("Input Data : %s\n", Test_Array[Row]);
		TransactionDate_Num = strlen(Test_Array[Row]);

		if ((TransactionDate_Num != 10) || (Test_Array[Row][2] != '/') || (Test_Array[Row][5] != '/'))
		{
			Row++;
			return WRONG_DATE;
		}


		else
		{
			Day[0] = Test_Array[Row][0];
			Day[1] = Test_Array[Row][1];
			Month[0] = Test_Array[Row][3];
			Month[1] = Test_Array[Row][4];
			Year[0] = Test_Array[Row][6];
			Year[1] = Test_Array[Row][7];
			Year[2] = Test_Array[Row][8];
			Year[3] = Test_Array[Row][9];

			Day_Num = atoi(Day);
			Month_Num = atoi(Month);
			Year_Num = atoi(Year);

			if ((Day_Num > 31) || (Month_Num > 12) || (Year_Num < 2022))
			{
				Row++;
				return WRONG_DATE;
			}

			else
			{
				for (Coloumn = 0; Coloumn < 15; Coloumn++)
				{
					if ( isdigit(Test_Array[Row][Coloumn] == 0) && (Test_Array[Row][Coloumn] != '/') )
					{
						Row++;
						return WRONG_EXP_DATE;
					}		
				}
				Row++;
				return TERMINAL_OK;
			}
		}

	#endif

	/*** End of Test Code ***/
}


EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	/*** Begin of Main Code ***/

	#ifdef isCardExpired_Main

		uint8_t Transaction_Month[2] = { 0 }; 
		uint8_t Transaction_Year[2] = { 0 } ;
		uint8_t Expire_Month[2] = { 0 };
		uint8_t Expire_Year[2] = { 0 };
		uint8_t Transaction_Month_Num = 0 , Transaction_Year_Num = 0;
		uint8_t Expire_Month_Num = 0, Expire_Year_Num = 0;

		Expire_Month[0] = cardData->cardExpirationDate[0];
		Expire_Month[1] = cardData->cardExpirationDate[1];
		Expire_Year[0] = cardData->cardExpirationDate[3];
		Expire_Year[1] = cardData->cardExpirationDate[4];
		Transaction_Month[0] = termData->transactionDate[3];
		Transaction_Month[1] = termData->transactionDate[4];
		Transaction_Year[0] = termData->transactionDate[8];
		Transaction_Year[1] = termData->transactionDate[9];

		Expire_Month_Num = atoi(Expire_Month);
		Expire_Year_Num = atoi(Expire_Year);

		Transaction_Month_Num = atoi(Transaction_Month);
		Transaction_Year_Num = atoi(Transaction_Year);

		if (Transaction_Year_Num > Expire_Year_Num)
			return EXPIRED_CARD;

		else if (Transaction_Year_Num < Expire_Year_Num)
			return TERMINAL_OK;

		else
		{
			if (Transaction_Month_Num > Expire_Month_Num)
				return EXPIRED_CARD;

			else
				return TERMINAL_OK;
		}

	#endif
	/*** Begin of Main Code ***/


	/*** Begin of Test Code ***/

	#ifdef isCardExpired_Test

		uint8_t Test_Array_Expiry[5][10] =
		{
			"10/23",
			"10/23",
			"05/30",
			"08/24",
			"01/23"
		};

		uint8_t Test_Array_Transaction[5][15] =
		{
			"02/10/2022",
			"02/11/2023",
			"01/01/2023",
			"30/08/2025",
			"01/01/2023"
		};

		uint8_t Coloumn = 0;
		static Row = 0;

		uint8_t Transaction_Month[2] = { 0 };
		uint8_t Transaction_Year[2] = { 0 };
		uint8_t Expire_Month[2] = { 0 };
		uint8_t Expire_Year[2] = { 0 };
		uint8_t Transaction_Month_Num = 0, Transaction_Year_Num = 0;
		uint8_t Expire_Month_Num = 0, Expire_Year_Num = 0;

		Expire_Month[0] = Test_Array_Expiry[Row][0];
		Expire_Month[1] = Test_Array_Expiry[Row][1];
		Expire_Year[0] = Test_Array_Expiry[Row][3];
		Expire_Year[1] = Test_Array_Expiry[Row][4];
		Transaction_Month[0] = Test_Array_Transaction[Row][3];
		Transaction_Month[1] = Test_Array_Transaction[Row][4];
		Transaction_Year[0] = Test_Array_Transaction[Row][8];
		Transaction_Year[1] = Test_Array_Transaction[Row][9];

		Expire_Month_Num = atoi(Expire_Month);
		Expire_Year_Num = atoi(Expire_Year);

		Transaction_Month_Num = atoi(Transaction_Month);
		Transaction_Year_Num = atoi(Transaction_Year);

		printf("Input Data : Expiry = %s   &   Transaction = %s\n", Test_Array_Expiry[Row] , Test_Array_Transaction[Row]);

		if (Transaction_Year_Num > Expire_Year_Num)
		{
			Row++;
			return EXPIRED_CARD;
		}

		else if (Transaction_Year_Num < Expire_Year_Num)
		{
			Row++;
			return TERMINAL_OK;
		}

		else
		{
			if (Transaction_Month_Num > Expire_Month_Num)
			{
				Row++;
				return EXPIRED_CARD;
			}
				
			else
			{
				Row++;
				return TERMINAL_OK;
			}
		}

	#endif

}


EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	/*** Begin of Main Code ***/

	#ifdef getTransactionAmount_Main

		uint16_t test[7] = {0};
		float TransactionAmount = 0.0;

		printf("please Enter Your Transaction Amount : ");
		gets(test);
		TransactionAmount = atof(test);

		if (TransactionAmount <= 0.0)
			return INVALID_AMOUNT;

		else
		{
			termData->transAmount = TransactionAmount;
			return TERMINAL_OK;
		}

	#endif

	/*** End of Main Code ***/

	
	/*** Begin of Test Code ***/

	#ifdef getTransactionAmount_Test

		uint8_t Test_Array[5][7] =
		{
			"2000.0",
			"3050.5",
			"0.0",
			"-1000",
			"-1550"
		};

		float TransactionAmount = 0.0;
		uint8_t Coloumn = 0;
		static Row = 0;

		printf("Input Data : %s\n", Test_Array[Row]);

		TransactionAmount = atof(Test_Array[Row]);

		if (TransactionAmount <= 0.0)
		{
			Row++;
			return INVALID_AMOUNT;
		}

		else
		{
			Row++;
			return TERMINAL_OK;
		}

	#endif

	/*** End of Test Code ***/
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	/*** Begin of Main Code ***/

	#ifdef isBelowMaxAmount_Main

		if (termData->transAmount > termData->maxTransAmount)
			return EXCEED_MAX_AMOUNT;

		else
			return TERMINAL_OK;

	#endif

	/*** End of Main Code ***/

		
	/*** Begin of Test Code ***/

	#ifdef isBelowMaxAmount_Test

		uint8_t Test_Array[5][10] =
		{
			"2000.0",
			"18500.5",
			"25000.0",
			"20000.0",
			"40000.0"
		};

		float MaxAmount = 0.0;
		uint8_t Coloumn = 0;
		static Row = 0;

		printf("Input Data : %s\n", Test_Array[Row]);

		MaxAmount = atof(Test_Array[Row]);

		if (MaxAmount > 20000.0)
		{
			Row++;
			return EXCEED_MAX_AMOUNT;
		}
		
		else
		{
			Row++;
			return TERMINAL_OK;
		}

	#endif

	/*** End of Test Code ***/


}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	/*** Begin of Main Code ***/

	#ifdef setMaxAmount_Main

		if (maxAmount <= 0.0)
			return INVALID_MAX_AMOUNT;

		else
		{
			termData->maxTransAmount = maxAmount;
			return TERMINAL_OK;
		}

	#endif

	/*** End of Main Code ***/


	/*** Begin of Test Code ***/

	#ifdef setMaxAmount_Test

		uint8_t Test_Array[5][10] =
		{
			"20000.0",
			"4000.500",
			"0.0",
			"-1000.0",
			"-1500.0"
		};

		float maxAmount_Val = 0.0;
		uint8_t Coloumn = 0;
		static Row = 0;

		maxAmount_Val = atof(Test_Array[Row]);

		printf("Input Data : %f\n", maxAmount_Val);


		if (maxAmount_Val <= 0.0)
		{
			Row++;
			return INVALID_MAX_AMOUNT;
		}

		else
		{
			Row++;
			return TERMINAL_OK;
		}

		#endif

	/*** End of Test Code ***/


}





void getTransactionDateTest(void)
{
	uint8_t Case_Num = 1, Result_Val = 0;
	static uint8_t i = 0;
	uint8_t Test_Array[15][15] =
	{
		"TERMINAL_OK",
		"TERMINAL_OK",
		"TERMINAL_OK",
		"WRONG_DATE",
		"WRONG_DATE",
		"WRONG_DATE",
		"WRONG_DATE",
		"WRONG_DATE",
		"WRONG_DATE",
		"WRONG_DATE",
		"WRONG_DATE",
		"WRONG_DATE",
		"WRONG_DATE",
		"WRONG_DATE",
		"WRONG_DATE"
	};

	printf("=========================================\n");
	printf("Tester Name : Youssef Adel Youssef\n");
	printf("Function Name : getTransactionDate\n");
	printf("=========================================\n\n");

	for (Case_Num = 1; Case_Num < 16; Case_Num++)
	{

		printf("Test Case : %d\n", Case_Num);
		Result_Val = getTransactionDate(Terminal_Ptr);


		printf("Expected Result : %s\n", Test_Array[i]);
		i++;

		if (Result_Val == TERMINAL_OK)
			printf("Actual Result : TERMINAL_OK\n");
		else
			printf("Actual Result : WRONG_DATE\n");

		printf("----------------------------------------\n");

	}

}


void isCardExpriedTest(void)
{
	uint8_t Case_Num = 1, Result_Val = 0;
	static uint8_t i = 0;
	uint8_t Test_Array[5][15] =
	{
		"TERMINAL_OK",
		"EXPIRED_CARD",
		"TERMINAL_OK",
		"EXPIRED_CARD",
		"TERMINAL_OK"
	};

	printf("=========================================\n");
	printf("Tester Name : Youssef Adel Youssef\n");
	printf("Function Name : isCardExpried\n");
	printf("=========================================\n\n");

	for (Case_Num = 1; Case_Num < 6; Case_Num++)
	{

		printf("Test Case : %d\n", Case_Num);
		Result_Val = isCardExpired(Card_Ptr,Terminal_Ptr);


		printf("Expected Result : %s\n", Test_Array[i]);
		i++;

		if (Result_Val == TERMINAL_OK)
			printf("Actual Result : TERMINAL_OK\n");
		else
			printf("Actual Result : EXPIRED_CARD\n");

		printf("----------------------------------------\n");

	}
}


void getTransactionAmountTest(void)
{
	uint8_t Case_Num = 1, Result_Val = 0;
	static uint8_t i = 0;
	uint8_t Test_Array[5][15] =
	{
		"TERMINAL_OK",
		"TERMINAL_OK",
		"INVALID_AMOUNT",
		"INVALID_AMOUNT",
		"INVALID_AMOUNT"
	};

	printf("=========================================\n");
	printf("Tester Name : Youssef Adel Youssef\n");
	printf("Function Name : getTransactionAmount\n");
	printf("=========================================\n\n");

	for (Case_Num = 1; Case_Num < 6; Case_Num++)
	{

		printf("Test Case : %d\n", Case_Num);
		Result_Val = getTransactionAmount(Terminal_Ptr);


		printf("Expected Result : %s\n", Test_Array[i]);
		i++;

		if (Result_Val == TERMINAL_OK)
			printf("Actual Result : TERMINAL_OK\n");
		else
			printf("Actual Result : INVALID_AMOUNT\n");

		printf("----------------------------------------\n");

	}
}


void isBelowMaxAmountTest(void)
{
	uint8_t Case_Num = 1, Result_Val = 0;
	static uint8_t i = 0;
	uint8_t Test_Array[5][20] =
	{
		"TERMINAL_OK",
		"TERMINAL_OK",
		"EXCEED_MAX_AMOUNT",
		"TERMINAL_OK",
		"EXCEED_MAX_AMOUNT",
	};

	printf("=========================================\n");
	printf("Tester Name : Youssef Adel Youssef\n");
	printf("Function Name : isBelowMaxAmount\n");
	printf("=========================================\n\n");

	for (Case_Num = 1; Case_Num < 6; Case_Num++)
	{

		printf("Test Case : %d\n", Case_Num);
		Result_Val = isBelowMaxAmount(Terminal_Ptr);


		printf("Expected Result : %s\n", Test_Array[i]);
		i++;

		if (Result_Val == TERMINAL_OK)
			printf("Actual Result : TERMINAL_OK\n");
		else
			printf("Actual Result : EXCEED_MAX_AMOUNT\n");

		printf("----------------------------------------\n");

	}
}


void setMaxAmountTest(void)
{
	uint8_t Case_Num = 1, Result_Val = 0;
	static uint8_t i = 0;
	uint8_t Test_Array[5][20] =
	{
		"TERMINAL_OK",
		"TERMINAL_OK",
		"INVALID_MAX_AMOUNT",
		"INVALID_MAX_AMOUNT",
		"INVALID_MAX_AMOUNT",
	};

	printf("=========================================\n");
	printf("Tester Name : Youssef Adel Youssef\n");
	printf("Function Name : setMaxAmount\n");
	printf("=========================================\n\n");

	for (Case_Num = 1; Case_Num < 6; Case_Num++)
	{

		printf("Test Case : %d\n", Case_Num);
		Result_Val = setMaxAmount(Terminal_Ptr , 1000.0);


		printf("Expected Result : %s\n", Test_Array[i]);
		i++;

		if (Result_Val == TERMINAL_OK)
			printf("Actual Result : TERMINAL_OK\n");
		else
			printf("Actual Result : INVALID_MAX_AMOUNT\n");

		printf("----------------------------------------\n");

	}
}