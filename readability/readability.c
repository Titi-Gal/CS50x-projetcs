#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int compute_ColemanLiau_index(string text);

int main(void)
{
    string text = get_string("text: "); //get text from user
    int ColemanLiauIndex = compute_ColemanLiau_index(text); //compute Coleman-Liau Index

    if (ColemanLiauIndex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (ColemanLiauIndex >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", ColemanLiauIndex);
    }
}

int compute_ColemanLiau_index(string text)
{
    /*loop to count letters, words and setences
    a to z or A to Z are letters
    space is end of word
    . ! ? is end of sentence*/
    int letters = 0;
    int words = 1; //by definition sentences don't end in space, so last words is counted already
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            letters++; //sum of letters
        }
        else if (text[i] == ' ')
        {
            words++; //sum of words
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++; //sum of sentences
        }
    }
    /*Coleman-Liau_index = 0.0588 * L - 0.296 * S - 15.8
    L average letters per 100 words
    S average sentences per 100 words*/
    return round(0.0588 * (letters / (float)words * 100) - 0.296 * (sentences / (float)words * 100) - 15.8);
}