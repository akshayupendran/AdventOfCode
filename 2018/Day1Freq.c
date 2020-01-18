#include <stdio.h>

#define LAST_NUMBER -114806
int main()
{
    int i=0; // counter
    int a[1025]; // input array
    long long total=0; // total of whole array
    int total_a[8000]; // array of totals
    total_a[0]=0; // let first total be 0
    int total_counter=0;
    int counter=0;
    while(i<=1024) // 0-1024
    {
        scanf("%d", &a[i]); // get the number
        //printf("%d\n", a[i]); // print the number
        i++; // move onto next element
    }

    // Calculate Total
    while(1)
    {
        i=0;
        while(i<=1024)
        {
            total += a[i];
            printf("new total is:%d\n", total);
            total_counter++;
            printf("total counter:%d\n", total_counter);
            total_a[total_counter]= total;
            for(counter=0; counter<total_counter; counter++)
            {
                if(total == total_a[counter])
                {
                    printf("found = yes %d", total);
                    return 0;
                }
            }
            i++;
        }
    }
    printf("Total is:%d", total);

    //Check reaching of
    return 0;
}
