#include"App.h"

#define Max_Amount 20000.0

void appStart(void)
{
	/* Card Module Enumeration Status*/
	EN_cardError_t Get_Card_Holder_Name = 0;
	EN_cardError_t Get_Card_Expiry_Date = 0;
	EN_cardError_t Get_Card_PAN = 0;

	/* Terminal Module Enumeration Status*/
	EN_terminalError_t Get_Transaction_Date = 0;
	EN_terminalError_t Is_Card_Expiry = 0;
	EN_terminalError_t Transaction_Amount = 0;
	EN_terminalError_t Is_Below_Max_Amount = 0;

	/* Card Module Test Functions */
	//getCardHolderNameTest();
	//getCardExpiryDateTest();
	//getCardPANTest();

	/* Termainal Module Test Functions */
	//getTransactionDateTest();
	//isCardExpriedTest();
	//getTransactionAmountTest();
	//isBelowMaxAmountTest();
	//setMaxAmountTest();

	/* Server Module Test Functions */
	//recieveTransactionDataTest();
	//isValidAccountTest();
	//isBlockedAccountTest();
	//isAmountAvailableTest();
	//saveTransactionTest();
	//listSavedTransactionsTest();

	setMaxAmount(Terminal_Ptr, Max_Amount);
	while (1)
	{	
		/* Card Module Flow Chart */
		do
		{
			Get_Card_Holder_Name = getCardHolderName(Card_Ptr);
		} while (Get_Card_Holder_Name != CARD_OK);

		do
		{
			Get_Card_Expiry_Date = getCardExpiryDate(Card_Ptr);
		} while (Get_Card_Expiry_Date != CARD_OK);

		do
		{
			Get_Card_PAN = getCardPAN(Card_Ptr);
		} while (Get_Card_PAN != CARD_OK);

		/* Terminal Module Flow Chart */
		do
		{
			Get_Transaction_Date = getTransactionDate(Terminal_Ptr);
		} while (Get_Transaction_Date != TERMINAL_OK);

		Is_Card_Expiry = isCardExpired(Card_Ptr, Terminal_Ptr);
		if (Is_Card_Expiry != TERMINAL_OK)
		{
			printf("Declined : Expired Card\n");
			continue;
		}

		do
		{
			Transaction_Amount = getTransactionAmount(Terminal_Ptr);
		} while (Transaction_Amount != TERMINAL_OK);

		Is_Below_Max_Amount = isBelowMaxAmount(Terminal_Ptr);
		if (Is_Below_Max_Amount != TERMINAL_OK)
		{
			printf("Declined : Amount Exceeding Limit\n");
			continue;
		}

		/* Server Module Flow Chart */
		recieveTransactionData(transactions_DBptr);
		printf("\n");
	}
	

}

int main()
{
	appStart();
	return 0;
}