#include <stdio.h>

//#define PART2

int main()
{
    FILE *fp;
    int a[1000], i=0, j, k, l;
    
    fp = fopen("input.txt", "r");

    while(EOF != fscanf(fp, "%d", &a[i]))
    {
        i++;
    }
    
    for(j=0; j<=i; j++)
    {
        for(k=j+1; k<=i; k++)
        {
#ifdef PART2
            for(l=k+1; l<=i; l++)
#endif
            {
#ifdef PART2
                if((a[j]+a[k]+a[l]) == 2020)
#else
                if((a[j]+a[k]) == 2020)
#endif
                {
#ifdef PART2
                    printf("%d\n", a[j]*a[k]*a[l]);
#else
                    printf("%d\n", a[j]*a[k]);
#endif
                    return 0;
                }
            }

        }
    }
    return 1;
}
