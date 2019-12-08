#include <stdio.h>

// input as per text file
int mass[100];

long long int CalculateFuel(long long int a)
{
    int b;
    b=((a/3)-2);
    if(b<=0)
        return 0;
    else
        return (b+CalculateFuel(b));
}

int main()
{
    int i; // input counter 0-99
    int fuel[100]; // fuel 0-99 based on mass 0-99
    long long int total_fuel_required=0;

    //get mass with i
    for(i=0; i<100; i++)
    {
        scanf("%d", &mass[i]); // get input into array
        //printf("%d\n", mass[i]); //verify input by printing
    }

    //calculate fuel for each mass
    for(i=0; i<100; i++)
    {
        fuel[i] = CalculateFuel(mass[i]);
        printf("%lld\n",fuel[i]);
        total_fuel_required+=fuel[i];
    }
    printf("%lld", total_fuel_required);
    return 0;
}
