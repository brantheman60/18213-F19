#include <stdio.h>
#include<string.h>

void phase_1(char *input)
{
    char str[] = "Hello World";
    if(strcmp(str, input)==0) printf("Works");
    return;
}

int main()
{
    char *input;
    input = read_line();
    phase_1(input);
    return 0;
}
