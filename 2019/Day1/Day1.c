#include <stdio.h>

#define NUMBER_OF_INPUTS 100u
// Mass of 100 input modules
int mass[NUMBER_OF_INPUTS];
int CalculateFuel2(int mass_of_input);
int CalculateFuel1(int mass_of_input);

int CalculateFuel1(int mass_of_input)
{
    int fuel_required;
    fuel_required=((mass_of_input/3)-2);
    return fuel_required;
}

int CalculateFuel2(int mass_of_input)
{
    int fuel_required;
    fuel_required=((mass_of_input/3)-2);
    if(fuel_required<=0)
        return 0;
    else
        return (fuel_required+CalculateFuel2(fuel_required));
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
    }

    //calculate fuel 1 for each mass
    for(i=0; i<100; i++)
    {
        fuel[i] = CalculateFuel1(mass[i]);
        total_fuel_required+=fuel[i];
    }
    printf("Solution to Part1:%lld\n", total_fuel_required);
    
    // Calculate Fuel for Part 2 for each mass
    total_fuel_required=0;
    for(i=0; i<100; i++)
    {
        fuel[i] = CalculateFuel2(mass[i]);
        total_fuel_required+=fuel[i];
    }
    printf("Solution to Part2:%lld\n", total_fuel_required);
    return 0;
}
