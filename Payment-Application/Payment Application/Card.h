#ifndef CARD_H_
#define CARD_H_

#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>

typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
    CARD_OK, 
    WRONG_NAME, 
    WRONG_EXP_DATE, 
    WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);


void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);

extern ST_cardData_t* Card_Ptr;

#endif // CARD_H_