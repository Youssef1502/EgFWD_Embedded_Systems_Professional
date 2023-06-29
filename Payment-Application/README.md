# EgFWD Payment Application Project

## Payment Application Simulation
This is a Payment Application Simulation project for the EgFWD Embedded Systems Professional NanoDegree Scholarship. This project was written in C. It includes card PAN generation and validation.

There are different types of transactions you can make, SALE, REFUND, Pre-Authorization, and VOID.

  - SALE: means to buy something and its price will be deducted from your bank account.
  - REFUND: this means that you will return something and wants your money back to your bank account.
  - Pre-Authorization: means holding an amount of money from your account, e.g Hotel reservation.
  - VOID: this means canceling the transaction, e.g if the seller entered the wrong amount.

## Program Flow Chart
![payment-flowchart](https://user-images.githubusercontent.com/62207434/183305187-4d1241fb-fa97-4daf-8a6b-a1f41a540ac7.jpg)

## Functions

These are some of the functions I thought I should highlight:
- `appStart()` : this would be called in `Main.c` to start the application
- `getTransactionDate()` : asks for a date in the form `DD/MM/YYYY`
- `getCardPAN()` : This function asks you to enter a valid card PAN
- `getCardHolderName()` : This function asks either to generate a valid card name
- `isCardExpired()` : This function checks if this card is expired or not
- `getTransactionAmount()` : This function asks you to enter the amount required to the transaction

## Instructions
The test cases describe different scenarios that would happen:
  - `EXCEED_MAX_AMOUNT` : means that the user tried to make a transaction with more than specified max amount for card
  - `DECLINED_STOLEN_CARD` & `INVALID_ACCOUNT` : the card number is not present in the account database for the bank
  - `DECLINED_INSUFFECIENT_FUND` : transaction amount is greater than account balance
  -  `APPROVED` : the transaction was successful and saved to transactions database
