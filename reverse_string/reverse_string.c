#include <stdio.h>
#include <stdlib.h>

void reverseString(char* s, int sSize) {
    char trailing_char;
    int size_without_s_termination = sSize --;

    for(int i = 0; i < (size_without_s_termination / 2); i ++)
    {
        trailing_char = s[sSize - i];
        s[sSize - i] = s[i];
        s[i] = trailing_char;
    }
}

int main ()
{
    char s[5] = {
        'h','e','l','l','o'
    };

    reverseString(&s[0], 5);

    printf("%s\n", s);

    return EXIT_SUCCESS;
}