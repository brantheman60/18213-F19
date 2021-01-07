#include <stdio.h>

int main()
{
    int i;
    int count_3 = 0;
    int count_5 = 0;
    int count_3_and_5 = 0;
    int count_3_or_5 = 0;
    int count_3_xor_5 = 0;
    int count_not_3_5 = 0;

    for(i=1; i<=1000; i++)
    {
        if(i%3 == 0 || i%5 == 0)
        {
            count_3_or_5++;
            if(i%3 == 0)
            {
                count_3++;
                if(i%5 == 0)
                {
                    count_5++;
                    count_3_and_5++;
                }
                else count_3_xor_5++;
            }

            else if(i%5 == 0)
            {
                count_5++;
                if(i%3 == 0)
                {
                    count_3++;
                    count_3_and_5++;
                }
                else count_3_xor_5++;
            }
        }
        else
            count_not_3_5++;
    }
    printf("count_3 = %d\n", count_3);
    printf("count_5 = %d\n", count_5);
    printf("count_3_and_5 = %d\n", count_3_and_5);
    printf("count_3_or_5 = %d\n", count_3_or_5);
    printf("count_3_xor_5 = %d\n", count_3_xor_5);
    printf("count_not_3_5 = %d\n", count_not_3_5);

    return 0;
}
