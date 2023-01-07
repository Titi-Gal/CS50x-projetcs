from cs50 import get_int


def main():
    cardnumber = str(get_int("Number: "))  # Works with digits as a string, digits are converted back to int when necessary
    len_cardnumber = len(cardnumber)
    initial_digits = int(cardnumber[0:2])
    initial_digit = int(cardnumber[0])
    checksum = f_checksum(cardnumber)

    if len_cardnumber == 15 and (initial_digits == 34 or initial_digits == 37) and checksum == 0:  # Conditions for AMEX.
        print("AMEX")
    elif len_cardnumber == 16 and (51 <= initial_digits <= 55) and checksum == 0:  # Conditions for MASTERCARD.
        print("MASTERCARD")
    elif (len_cardnumber == 13 or len_cardnumber == 16) and initial_digit == 4 and checksum == 0:  # Conditions for VISA.
        print("VISA")
    else:  # Else INVALID.
        print("INVALID")


def f_checksum(cardnumber):
    sum_of_products_of_even_digits = 0
    for i in range(len(cardnumber) - 2, -1, -2):  # Digits in even position starting from second to last
        product_of_digit = str(int(cardnumber[i]) * 2)
        for digit in product_of_digit:
            sum_of_products_of_even_digits += int(digit)

    sum_of_odd_digits = 0
    for i in range(len(cardnumber) - 1, -1, -2):  # Digits in odd digits startting from last
        sum_of_odd_digits += int(cardnumber[i])

    return int(str(sum_of_products_of_even_digits + sum_of_odd_digits)[-1])


if __name__ == "__main__":
    main()