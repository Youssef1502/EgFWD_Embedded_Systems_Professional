#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include"card.h"

#define getCardHolderName_Main
//#define getCardHolderName_Test

#define getCardExpiryDate_Main
//#define getCardExpiryDate_Test

#define getCardPAN_Main
//#define getCardPAN_Test


ST_cardData_t Card;
ST_cardData_t* Card_Ptr = &Card;


EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	/*** Begin of Main Code ***/
	
	#ifdef getCardHolderName_Main 
	
		uint8_t CardName[30] = { 0 };
		uint8_t Characters_Num = 0;
		uint8_t i = 0;

		printf("Please Enter Your Name : ");
		gets(CardName);
		Characters_Num = strlen(CardName);

		if ((Characters_Num >= 20) && (Characters_Num <= 24))
		{
			for (i = 0; i < Characters_Num; i++)
			{
				if ( (isalpha(CardName[i]) == 0) && (CardName[i] != ' ') )
						return WRONG_NAME;
			}
			strcpy(cardData->cardHolderName , CardName);
			return CARD_OK;
		}

		else
		{
			return WRONG_NAME;
		}

	#endif
	
	/*** End of Main Code ***/


	/*** Begin of Test Code ***/

	#ifdef getCardHolderName_Test

		uint8_t Characters_Num = 0;
	
		uint8_t Test_Array[9][30] =
		{
			"YoussefAdelYoussefAmer",
			"ahmed adel youssef amer",
			"2oussefAdelYoussefAmer",
			"2456841525654957564754",
			"Youssef_Adel_youssef_A",
			"YoussefAdel $ # Youssef",
			"#*@(HD(@)!^#!H#(*!YE)@U",
			"Mahmoud Ali",
			"Ebrahmen Elsayed Abdelrhaman"
		};

		uint8_t Coloumn = 0;
		static Row = 0;

		printf("Input Data : %s\n", Test_Array[Row]);
		Characters_Num = strlen(Test_Array[Row]);
	
		if ((Characters_Num >= 20) && (Characters_Num <= 24))
		{
			for (Coloumn = 0; Coloumn < Characters_Num; Coloumn++)
			{
				if ((isalpha(Test_Array[Row][Coloumn]) == 0) && (Test_Array[Row][Coloumn] != ' '))
				{
					Row++;
					return WRONG_NAME;
				}
			}
			Row++;
			return CARD_OK;
		}
	
		else
		{
			Row++;
			return WRONG_NAME;
		}

	#endif

	/*** End of Test Code ***/

}


EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	/*** Begin of Main Code ***/

	#ifdef getCardExpiryDate_Main
	
		uint8_t CardExpiry[10] = { 0 };
		uint8_t Month[2] = { 0 };
		uint8_t Year[2] = { 0 };
		uint8_t Month_Num = 0, Year_Num = 0;
		uint8_t CardExpiry_Num = 0;
		uint8_t i = 0;

		printf("Please Enter Your Card Expiry Date in Format MM/YY : ");
		gets(CardExpiry);
		CardExpiry_Num = strlen(CardExpiry);

		if ((CardExpiry_Num != 5) || (CardExpiry[2] != '/'))
			return WRONG_EXP_DATE;

		else
		{
			Month[0] = CardExpiry[0];
			Month[1] = CardExpiry[1];
			Year[0]  = CardExpiry[3];
			Year[1]  = CardExpiry[4];

			Month_Num = atoi(Month);
			Year_Num  = atoi(Year);
			
			if ((Year_Num > 30) || (Month_Num > 12))
			{
				return WRONG_EXP_DATE;
			}

			else
			{
				for (i = 0; i < 5; i++)
				{
					if ((isdigit(CardExpiry[i]) == 0) && (CardExpiry[i] != '/'))
						return WRONG_EXP_DATE;
				}
				strcpy(cardData->cardExpirationDate, CardExpiry);
				return CARD_OK;
			}
		}

	#endif
	
	/*** End of Main Code ***/


	/*** Begin of Test Code ***/

	#ifdef getCardExpiryDate_Test
		
		uint8_t CardExpiry_Num = 0;
		uint8_t Month[2] = { 0 };
		uint8_t Year[2] = { 0 };
		uint8_t Month_Num = 0, Year_Num = 0;

		uint8_t Test_Array[13][10] =
		{
			"10/23",
			"08/23",
			"05/30",
			"12345",
			"154",
			"7856486",
			"8/023",
			"11/32",
			"15/24",
			"/1223",
			"0824/",
			"ab/cd",
			"03 27"
		};

		uint8_t Coloumn = 0;
		static Row = 0;

		printf("Input Data : %s\n", Test_Array[Row]);
		CardExpiry_Num = strlen(Test_Array[Row]);

		if ((CardExpiry_Num != 5) || (Test_Array[Row][2] != '/'))
		{
			Row++;
			return WRONG_EXP_DATE;
		}

		else
		{
			Month[0] = Test_Array[Row][0];
			Month[1] = Test_Array[Row][1];
			Year[0] = Test_Array[Row][3];
			Year[1] = Test_Array[Row][4];

			Month_Num = atoi(Month);
			Year_Num = atoi(Year);
			if ((Year_Num > 30) || (Month_Num > 12))
			{
				Row++;
				return WRONG_EXP_DATE;
			}

			else
			{
				for (Coloumn = 0; Coloumn < 5; Coloumn++)
				{
					if ((isdigit(Test_Array[Row][Coloumn]) == 0) && (Test_Array[Row][Coloumn] != '/'))
					{ 
						Row++;
						return WRONG_EXP_DATE;
					}
				}
				Row++;
				return CARD_OK;
			}
		}

	#endif

	/*** End of Test Code ***/
}



EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	/*** Begin of Main Code ***/
	
	#ifdef getCardPAN_Main

		uint8_t CardPAN[25] = { 0 };
		uint8_t CardPAN_Num = 0;

		printf("Please Enter card Primary Account Number : ");
		gets(CardPAN);
		CardPAN_Num = strlen(CardPAN);

		if ((CardPAN_Num < 16) || (CardPAN_Num > 19))
			return WRONG_PAN;

		else
		{
			strcpy(cardData->primaryAccountNumber, CardPAN);
			return CARD_OK;
		}
	
	#endif

	/*** End of Main Code ***/

	
	/*** Begin of Test Code ***/

	#ifdef getCardPAN_Test

		uint8_t CardPAN_Num = 0;

		uint8_t Test_Array[3][25] =
		{
			"1245123556",
			"15245697563548543",
			"1964354865374935163549"
		};

		uint8_t Coloumn = 0;
		static Row = 0;

		printf("Input Data : %s\n", Test_Array[Row]);
		CardPAN_Num = strlen(Test_Array[Row]);

		if ((CardPAN_Num < 16) || (CardPAN_Num > 19))
		{
			Row++;
			return WRONG_PAN;
		}

		else
		{
			Row++;
			return CARD_OK;
		}

	#endif

	/*** End of Test Code ***/
}







void getCardHolderNameTest(void)
{
	uint8_t Case_Num = 1, Result_Val = 0;
	static uint8_t i = 0;
	uint8_t Test_Array[9][30] =
	{
		"CARD_OK",
		"CARD_OK",
		"WRONG_NAME",
		"WRONG_NAME",
		"WRONG_NAME",
		"WRONG_NAME",
		"WRONG_NAME",
		"WRONG_NAME",
		"WRONG_NAME"
	};

	printf("=========================================\n");
	printf("Tester Name : Youssef Adel Youssef\n");
	printf("Function Name : getCardHolderName\n");
	printf("=========================================\n\n");
	
	for (Case_Num = 1; Case_Num < 10; Case_Num++)
	{

		printf("Test Case : %d\n", Case_Num);
		Result_Val = getCardHolderName(Card_Ptr);


		printf("Expected Result : %s\n" , Test_Array[i]);
		i++;
		
		if (Result_Val == CARD_OK)
			printf("Actual Result : CARD_OK\n");
		else
			printf("Actual Result : WRONG_NAME\n");

		printf("----------------------------------------\n");

	}

}


void getCardExpiryDateTest(void)
{
	uint8_t Case_Num = 1, Result_Val = 0;
	static uint8_t i = 0;
	uint8_t Test_Array[13][30] =
	{
		"CARD_OK",
		"CARD_OK",
		"CARD_OK",
		"WRONG_EXP_DATE",
		"WRONG_EXP_DATE",
		"WRONG_EXP_DATE",
		"WRONG_EXP_DATE",
		"WRONG_EXP_DATE",
		"WRONG_EXP_DATE",
		"WRONG_EXP_DATE",
		"WRONG_EXP_DATE",
		"WRONG_EXP_DATE",
		"WRONG_EXP_DATE"
	};

	printf("=========================================\n");
	printf("Tester Name: Youssef Adel Youssef\n");
	printf("Function Name: getCardExpiryDate\n");
	printf("=========================================\n\n");

	for (Case_Num = 1; Case_Num < 14; Case_Num++)
	{

		printf("Test Case : %d\n", Case_Num);
		Result_Val = getCardExpiryDate(Card_Ptr);


		printf("Expected Result : %s\n", Test_Array[i]);
		i++;

		if (Result_Val == CARD_OK)
			printf("Actual Result : CARD_OK\n");
		else
			printf("Actual Result : WRONG_EXP_DATE\n");

		printf("----------------------------------------\n");

	}
}


void getCardPANTest(void)
{
	uint8_t Case_Num = 1, Result_Val = 0;
	static uint8_t i = 0;
	uint8_t Test_Array[3][25] =
	{
		"WRONG_PAN",
		"CARD_OK",
		"WRONG_PAN",
	};

	printf("=========================================\n");
	printf("Tester Name: Youssef Adel Youssef\n");
	printf("Function Name: getCardPAN \n");
	printf("=========================================\n\n");

	for (Case_Num = 1; Case_Num < 4; Case_Num++)
	{

		printf("Test Case : %d\n", Case_Num);
		Result_Val = getCardPAN(Card_Ptr);


		printf("Expected Result : %s\n", Test_Array[i]);
		i++;

		if (Result_Val == CARD_OK)
			printf("Actual Result : CARD_OK\n");
		else
			printf("Actual Result : WRONG_PAN\n");

		printf("----------------------------------------\n");

	}
}