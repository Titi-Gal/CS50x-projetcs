#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What's your name? "); //asks for for name and stores it in a string
    printf("hello,  %s\n", name); //prints "hello, name"
}
