#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(int argc, string argv[])
{
    //check if there are two command-line arguments and if seconds is just digits, converting all digits to an int
    //needs optimization because printf and return 1 are repeating
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int key = 0;
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (argv[1][i] >= '0' && argv[1][i] <= '9')
            {
                key = key + (argv[1][i] - 48) * (int)pow(10, n - i - 1);
            }
            else
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        key = key % 26;
    }

    string plaintext = get_string("plaintext: ");
    int n = strlen(plaintext);

    printf("ciphertext: ");
    for (int i = 0, ajust = 0; i < n; i++)
    {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            ajust = 65;
        }
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            ajust = 97;
        }
        else
        {
            printf("%c", plaintext[i]);
            continue;
        }
            printf("%c", ((plaintext[i] - ajust + key) % 26) + ajust);
    }
    printf("\n");
    return 0;
}