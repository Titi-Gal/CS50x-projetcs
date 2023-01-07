#include <cs50.h>
#include <stdio.h>
#include <math.h>

long ask_cardnumber(void);
int size_(long number);
int initial_digits(long cardnumber, int size, int slice);
int check_sum(long cardnumber, int size);


int main(void)
{
    long cardnumber = ask_cardnumber(); //asks users for card

    int size = size_(cardnumber); //returns the number of digits in card

    int initialDigits = initial_digits(cardnumber, size, 2); // returns the 2 initial digits
    int initialDigit = initial_digits(cardnumber, size, 1); // returns the 1 initial digit
    int checksum = check_sum(cardnumber, size); //checksum of card

    if (size == 15 && (initialDigits == 34 || initialDigits == 37) && checksum == 0) //conditions for amex
    {
        printf("AMEX\n");
    }
    else if (size == 16 && initialDigits >= 51 && initialDigits <= 55 && checksum == 0) //conditions for master
    {
        printf("MASTERCARD\n");
    }
    else if ((size == 13 || size == 16) && initialDigit == 4 && checksum == 0) //conditions for visa
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


int size_(long cardnumber)
{
    int mod = 10;
    int digits = 0;
    while (cardnumber / pow(mod, digits) >= 1)
    {
        digits++;
    }
    return digits;
}

int initial_digits(long cardnumber, int size, int slice)
{
    return (int)(cardnumber / pow(10, size - slice));
}

int check_sum(long cardnumber, int size)
{
    int checksum = 0;
    for (int digitPosition = 1; digitPosition <= size; digitPosition++)
    {
        int digit = cardnumber % 10;
        cardnumber = cardnumber / 10;

        if (digitPosition % 2 == 0)
        {
            int digitresult = digit * 2;
            int digitsize = size_(digitresult);
            for (int digitP = 1; digitP <= digitsize; digitP++)
            {
                checksum = checksum + digitresult % 10;
                digitresult = digitresult / 10;
            }
        }
        else
        {
            checksum = checksum + digit;
        }
    }
    return checksum % 10;
}
