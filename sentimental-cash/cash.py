def Get_float():
    """Returns a user input only if its a float, else keeps asking."""
    while True:
        try:
            change_owed = float(input("Change owed: "))
            if change_owed > 0:
                break
        except ValueError:
            pass
    return change_owed


def Number_of_coins(change_owed, coin_value):
    """Returns the number of coins_values fits in change_owed."""
    return int(change_owed / coin_value)


def main():
    """Prints the minimun number of coin values to give the change."""
    coin_values = [0.25, 0.10, 0.05, 0.01]
    change_owed = Get_float()  # Asks for user input of type float.

    total_number_of_coins = 0
    for coin_value in coin_values:  # For each coin value.
        number_of_coins = Number_of_coins(change_owed, coin_value)  # Number of that coins fits that fits in change.
        change_owed = round(change_owed - (number_of_coins * coin_value), 2)  # Rest of change minus the values of this coin.
        total_number_of_coins += number_of_coins
        if change_owed == 0:  # If change is 0 its done.
            break
    print(total_number_of_coins)


if __name__ == '__main__':
    main()