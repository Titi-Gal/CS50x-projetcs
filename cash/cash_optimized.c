#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int Ncoins_change(int cents, int coinValue);

int main(void)
{
    int quarterValue = 25;
    int dimeValue = 10;
    int nickelValue = 5;
    int pennieValue = 1;

    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int Nquarters = Ncoins_change(cents, quarterValue);
    cents = cents - Nquarters * quarterValue;

    // Calculate the number of quarters to give the customer
    int Ndimes = Ncoins_change(cents, dimeValue);
    cents = cents - Ndimes * dimeValue;

    // Calculate the number of quarters to give the customer
    int Nnickels = Ncoins_change(cents, nickelValue);
    cents = cents - Nnickels * nickelValue;

    // Calculate the number of quarters to give the customer
    int Npennies = Ncoins_change(cents, pennieValue);
    cents = cents - Npennies * pennieValue;

    // Sum coins
    int coins = Nquarters + Ndimes + Nnickels + Npennies;

    // Print total number of coins to give the customer
    printf("\nTotal coins in change: %i\n\nQuarters: %i\nDimes: %i\nNickels: %i\nPennies: %i\n",
            coins, Nquarters, Ndimes, Nnickels, Npennies);
}

int get_cents(void)
{
    //asks user for value in cents
    int cents;
    do
    {
        cents = get_int("Value in cents: ");
    }
    while (cents < 0);
    return cents;
}

int Ncoins_change(int cents, int coinValue)
{
    return cents / coinValue;
}