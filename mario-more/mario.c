#include <cs50.h>
#include <stdio.h>

//prints a string a number of times
void prints_string_ntimes(string toPrint, int times);

int main(void)
{
    int steps_total; // numbers of steps on the stairs. User defined, beetwenn min and max inclusive
    int min = 1;
    int max = 8;
    int between_stairs = 2; //number of spaces betwenn stairscheck

    //asks user for steps_total
    do
    {
        steps_total = get_int("Height: ");
    }
    while (steps_total < min || steps_total > max);

    //for each line prints the corresponding number of steps. line one 1 step, line 2 two steps, etc.
    for (int steps_line = 1; steps_line <= steps_total; steps_line++)
    {
        //space to be printed in each line is the total steps on the stairs minus the steps printed on the line
        int spaces_line = steps_total - steps_line;

        prints_string_ntimes(" ", spaces_line); //spaces in stairs up
        prints_string_ntimes("#", steps_line); //steps in stairs up
        prints_string_ntimes(" ", between_stairs); //space betwenn stais
        prints_string_ntimes("#", steps_line); //steps in down stairs
        printf("\n");
    }
}

void prints_string_ntimes(string toPrint, int times)
{
    for (int i = 0; i < times; i++)
    {
        printf("%s", toPrint);
    }
}