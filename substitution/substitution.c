#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    if (argc != 2) //command argument must be 2
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    int n = strlen(argv[1]);
    if (n != 26) //argument 1 must be lenght 26
    {
        printf("Key must contain unique 26 letters.\n");
        return 1;
    }

    char key[n]; //all the letters in the command arguments will be stored here as uppercase
    for (int i = 0; i < n; i++) //all characters in command argument
    {
        if (isalpha(argv[1][i])) //if charatcer in command argument is alphabetic
        {
            char letter = toupper(argv[1][i]); //variable letter stores its uppercase value

            for (int j = 0; j < i; j++) //verifies if letter is already in key
            {
                if (key[j] == letter) //if yes returns error
                {
                    printf("Key must contain UNIQUE 26 letters.\n");
                    return 1;
                }
            }
            key[i] = letter; //if not in key adds it

        }
        else //if not alphabetic returns error
        {
            printf("Key must contain unique 26 LETTERS.\n");;
            return 1;
        }
    }

    string plaintext = get_string("plaintext: ");
    n = strlen(plaintext);
    char ciphertext[n];

    printf("ciphertext: ");
    for (int i = 0; i < n; i++)
    {
        if (isupper(plaintext[i]))
        {
            printf("%c", key[plaintext[i] - 65]);
        }
        else if (islower(plaintext[i]))
        {
            printf("%c", tolower(key[plaintext[i] - 97]));
        }
        else
        {
            printf("%c", plaintext[i]);
            continue;
        }
    }
    printf("\n");
    return 0;
}