#include <cs50.h>
#include <stdio.h>
#include <math.h>

long ask_cardnumber(void);
int lenth(long number);
int initial_digits(long cardnumber, int lenthcard, int slice);
int check_sum(long cardnumber);


int main(void)
{
    long cardnumber = ask_cardnumber(); //asks users for card
    int lenthcard = lenth(cardnumber); //returns the number of digits in card
    int initialDigits = initial_digits(cardnumber, lenthcard, 2); // returns 2 initial digits
    int initialDigit = initial_digits(cardnumber, lenthcard, 1); // returns 1 initial digit
    int checksum = check_sum(cardnumber); //checksum of card

    if (lenthcard == 15 && (initialDigits == 34 || initialDigits == 37) && checksum == 0) //conditions for amex
    {
        printf("AMEX\n");
    }
    else if (lenthcard == 16 && initialDigits >= 51 && initialDigits <= 55 && checksum == 0) //conditions for master
    {
        printf("MASTERCARD\n");
    }
    else if ((lenthcard == 13 || lenthcard == 16) && initialDigit == 4 && checksum == 0) //conditions for visa
    {
        printf("VISA\n");
    }
    else //else invalid
    {
        printf("INVALID\n");
    }
}

long ask_cardnumber(void)
{
    return get_long("Card Number: ");
}

int lenth(long cardnumber)
{
    int lenthcard;
    for (lenthcard = 0; cardnumber != 0; cardnumber /= 10)
    {
        lenthcard++;
    }
    return lenthcard;
}

int initial_digits(long cardnumber, int lenthcard, int slice)
{
    return (int)(cardnumber / pow(10, lenthcard - slice));
}

int check_sum(long cardnumber)
{
    int checksum = 0;
    for (int digitPosition = 1; cardnumber != 0; digitPosition++) //digitspositions until number lenth
    {
        int digit = cardnumber % 10; //digit value
        cardnumber /= 10;

        if (digitPosition % 2 == 0) //if position is even
        {
            int digitresult = digit * 2; //multiplie by 2
            for (int digitP = 1; digitresult != 0; digitresult /= 10, digitP++) //taks each digit in resul and add to checksum
            {
                checksum = checksum + digitresult % 10;
            }
        }
        else //just add digit to sum
        {
            checksum = checksum + digit;
        }
    }
    return checksum % 10; //returns 0 if ends in 0
}