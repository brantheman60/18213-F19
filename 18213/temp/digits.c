/**
 * There are 999,999 natural numbers less than 1,000,000. For 1≤k≤6, how many
 * of them have k distinct digits? Pad with zeros (treat 111 as 000111).
 *
 * Treat problem as choosing 6 digits from {0,1,2,3,4,5,6,7,8,9}.
 */

#include <stdio.h>
#include <stdlib.h>

int numDistinct(int *arr, int k)
// arr has length k
{
    int *digits = calloc(k, sizeof(int));
    digits[0] = arr[0];
    int numDigits = 1;
    int i, index, repeat;
    for(i=1; i<k; i++)
    {
        repeat = 0;
        for(index=0; index<numDigits; index++)
            if(arr[i] == digits[index])
                repeat = 1;

        if(!repeat) // new digit
        {
            digits[numDigits] = arr[i];
            numDigits++;
        }
    }
    free(digits);
    return numDigits;
}

int tenPowK(int k)
{
    int result = 1;
    int i;
    for(i=0; i<k; i++)
        result*=10;
    return result;
}

void runProblem(int k)
//k is the number of digits, k>0; the actual problem uses 6
{
    printf("Running with %d digits:\n", k);
    int i;
    int *arr = calloc(k, sizeof(int)); //digits from left to right
    int *kDistinct = calloc(k, sizeof(int)); //tracks number of distinctions
    for(i=0; i<k; i++)
        kDistinct[i] = 0;

    for(i=1; i<tenPowK(k); i++)
    {
        int digit;
        for(digit=0; digit<k; digit++)
            arr[digit] = (i / tenPowK(digit)) % 10;

        int tmp = numDistinct(arr, k);
        switch(tmp)
        {
            case 1: kDistinct[0]++; break;
            case 2: kDistinct[1]++; break;
            case 3: kDistinct[2]++; break;
            case 4: kDistinct[3]++; break;
            case 5: kDistinct[4]++; break;
            case 6: kDistinct[5]++; break;
            default: printf("What?!"); break;
        }
    }
    for(i=0; i<k; i++)
        printf("%d Distinct = %d\n", i+1, kDistinct[i]);
    free(arr);
    free(kDistinct);
}

int main()
{
    /*
    int *arr = calloc(6, sizeof(int));
    arr[0] = 1;
    arr[1] = 1;
    arr[2] = 1;
    arr[3] = 1;
    arr[4] = 2;
    arr[5] = 1;
    printf("Number of Distincts: %d\n", numDistinct(arr));
    */
    runProblem(1);
    runProblem(2);
    //runProblem(3);
    //runProblem(4);
    //runProblem(5);
    //runProblem(6);
    return 0;
}
