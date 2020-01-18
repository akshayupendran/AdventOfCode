/* Headers */
#include <stdio.h>
#include <stdlib.h>

/* Typedefinitions */
typedef struct
{
    int posx;
    int posy;
    int posz;
    int velx;
    int vely;
    int velz;
    long long int PotentialEnergy;
    long long int KineticEnergy;
    long long int TotalEnergy;
}Moon_type_t;

#define NUMBER_OF_MOONS 4
/* Function Declarations */
void ReadInputValues(void);
void PrintCurrentValues(void);
void ApplyGravity(void);
void ApplyVelocity(void);
void CalculatePotentialEnergy(void);
void CalculateKineticEnergy(void);
void CalculateTotalEnergy(void);

/* Variables */
Moon_type_t Io, Europa, Ganymede, Callisto;
Moon_type_t *ListOfPointers2Moons[NUMBER_OF_MOONS]={&Io, &Europa, &Ganymede, &Callisto};
int Moon_Counter=0;
FILE *fp;

/* Implementations */
void CalculatePotentialEnergy()
{
    for(Moon_Counter=0; Moon_Counter<NUMBER_OF_MOONS; Moon_Counter++)
    {
        if(ListOfPointers2Moons[Moon_Counter]->posx < 0)
        {
            ListOfPointers2Moons[Moon_Counter]->PotentialEnergy-=ListOfPointers2Moons[Moon_Counter]->posx;
        }
        else
        {
            ListOfPointers2Moons[Moon_Counter]->PotentialEnergy+=ListOfPointers2Moons[Moon_Counter]->posx;
        }
        if(ListOfPointers2Moons[Moon_Counter]->posy < 1)
        {
            ListOfPointers2Moons[Moon_Counter]->PotentialEnergy-=ListOfPointers2Moons[Moon_Counter]->posy;
        }
        else
        {
            ListOfPointers2Moons[Moon_Counter]->PotentialEnergy+=ListOfPointers2Moons[Moon_Counter]->posy;
        }
        if(ListOfPointers2Moons[Moon_Counter]->posz < 1)
        {
            ListOfPointers2Moons[Moon_Counter]->PotentialEnergy-=ListOfPointers2Moons[Moon_Counter]->posz;
        }
        else
        {
            ListOfPointers2Moons[Moon_Counter]->PotentialEnergy+=ListOfPointers2Moons[Moon_Counter]->posz;
        }
    }
}

void CalculateKineticEnergy()
{
    for(Moon_Counter=0; Moon_Counter<NUMBER_OF_MOONS; Moon_Counter++)
    {
        if(ListOfPointers2Moons[Moon_Counter]->velx < 0)
        {
            ListOfPointers2Moons[Moon_Counter]->KineticEnergy-=ListOfPointers2Moons[Moon_Counter]->velx;
        }
        else
        {
            ListOfPointers2Moons[Moon_Counter]->KineticEnergy+=ListOfPointers2Moons[Moon_Counter]->velx;
        }
        if(ListOfPointers2Moons[Moon_Counter]->vely < 1)
        {
            ListOfPointers2Moons[Moon_Counter]->KineticEnergy-=ListOfPointers2Moons[Moon_Counter]->vely;
        }
        else
        {
            ListOfPointers2Moons[Moon_Counter]->KineticEnergy+=ListOfPointers2Moons[Moon_Counter]->vely;
        }
        if(ListOfPointers2Moons[Moon_Counter]->velz < 1)
        {
            ListOfPointers2Moons[Moon_Counter]->KineticEnergy-=ListOfPointers2Moons[Moon_Counter]->velz;
        }
        else
        {
            ListOfPointers2Moons[Moon_Counter]->KineticEnergy+=ListOfPointers2Moons[Moon_Counter]->velz;
        }
    }
}

void CalculateTotalEnergy()
{
    for(Moon_Counter=0; Moon_Counter<NUMBER_OF_MOONS; Moon_Counter++)
    {
        ListOfPointers2Moons[Moon_Counter]->TotalEnergy=ListOfPointers2Moons[Moon_Counter]->PotentialEnergy*ListOfPointers2Moons[Moon_Counter]->KineticEnergy;
    }
}

void ApplyGravity()
{
    int Moon_Counter2=0;
    /* Update Velocities based on Moon Positions */
    for(Moon_Counter=0; Moon_Counter<NUMBER_OF_MOONS; Moon_Counter++)
    {
        for(Moon_Counter2=0; Moon_Counter2<NUMBER_OF_MOONS; Moon_Counter2++)
        {
            if(Moon_Counter2 != Moon_Counter)
            {
                if(ListOfPointers2Moons[Moon_Counter]->posx == ListOfPointers2Moons[Moon_Counter2]->posx)
                {
                    /* Do nothing */
                }
                else if(ListOfPointers2Moons[Moon_Counter]->posx < ListOfPointers2Moons[Moon_Counter2]->posx)
                {
                    ListOfPointers2Moons[Moon_Counter]->velx++;
                }
                else if(ListOfPointers2Moons[Moon_Counter]->posx > ListOfPointers2Moons[Moon_Counter2]->posx)
                {
                    ListOfPointers2Moons[Moon_Counter]->velx--;
                }
                else
                {
                    printf("Apply Gravity for velx Failed with unknown error");
                }
                if(ListOfPointers2Moons[Moon_Counter]->posy == ListOfPointers2Moons[Moon_Counter2]->posy)
                {
                    /* Do nothing */
                }
                else if(ListOfPointers2Moons[Moon_Counter]->posy < ListOfPointers2Moons[Moon_Counter2]->posy)
                {
                    ListOfPointers2Moons[Moon_Counter]->vely++;
                }
                else if(ListOfPointers2Moons[Moon_Counter]->posy > ListOfPointers2Moons[Moon_Counter2]->posy)
                {
                    ListOfPointers2Moons[Moon_Counter]->vely--;
                }
                else
                {
                    printf("Apply Gravity for vely Failed with unknown error");
                }
                if(ListOfPointers2Moons[Moon_Counter]->posz == ListOfPointers2Moons[Moon_Counter2]->posz)
                {
                    /* Do nothing */
                }
                else if(ListOfPointers2Moons[Moon_Counter]->posz < ListOfPointers2Moons[Moon_Counter2]->posz)
                {
                    ListOfPointers2Moons[Moon_Counter]->velz++;
                }
                else if(ListOfPointers2Moons[Moon_Counter]->posz > ListOfPointers2Moons[Moon_Counter2]->posz)
                {
                    ListOfPointers2Moons[Moon_Counter]->velz--;
                }
                else
                {
                    printf("Apply Gravity for velz Failed with unknown error");
                }
            }
        }
    }
}

void ApplyVelocity()
{
    for(Moon_Counter=0; Moon_Counter<NUMBER_OF_MOONS; Moon_Counter++)
    {
        ListOfPointers2Moons[Moon_Counter]->posx+=ListOfPointers2Moons[Moon_Counter]->velx;
        ListOfPointers2Moons[Moon_Counter]->posy+=ListOfPointers2Moons[Moon_Counter]->vely;
        ListOfPointers2Moons[Moon_Counter]->posz+=ListOfPointers2Moons[Moon_Counter]->velz;
    }
}

void ReadInputValues()
{
    for(Moon_Counter=0; Moon_Counter<NUMBER_OF_MOONS; Moon_Counter++)
    {
        fscanf(fp, "<x=%d, y=%d, z=%d>\n", &(ListOfPointers2Moons[Moon_Counter]->posx), &(ListOfPointers2Moons[Moon_Counter]->posy), &(ListOfPointers2Moons[Moon_Counter]->posz));
        ListOfPointers2Moons[Moon_Counter]->velx=0;
        ListOfPointers2Moons[Moon_Counter]->vely=0;
        ListOfPointers2Moons[Moon_Counter]->velz=0;
        ListOfPointers2Moons[Moon_Counter]->PotentialEnergy=0;
        ListOfPointers2Moons[Moon_Counter]->KineticEnergy=0;
        ListOfPointers2Moons[Moon_Counter]->TotalEnergy=0;
    }
}

void PrintCurrentValues()
{
    for(Moon_Counter=0; Moon_Counter<NUMBER_OF_MOONS; Moon_Counter++)
    {
        printf("pos=<x=%d, y=%d, z=%d>, vel=<x=%d, y=%d, z=%d>\n", ListOfPointers2Moons[Moon_Counter]->posx, ListOfPointers2Moons[Moon_Counter]->posy, ListOfPointers2Moons[Moon_Counter]->posz, ListOfPointers2Moons[Moon_Counter]->velx, ListOfPointers2Moons[Moon_Counter]->vely, ListOfPointers2Moons[Moon_Counter]->velz);
    }
}

void PrintCurrentEnergyValues()
{
    for(Moon_Counter=0; Moon_Counter<NUMBER_OF_MOONS; Moon_Counter++)
    {
        printf("pot:  %d + %d +  %d = %lld;   kin: %d +  %d + %d = %lld;   total: %lld * %lld = %lld\n", ListOfPointers2Moons[Moon_Counter]->posx, ListOfPointers2Moons[Moon_Counter]->posy, ListOfPointers2Moons[Moon_Counter]->posz, ListOfPointers2Moons[Moon_Counter]->PotentialEnergy, ListOfPointers2Moons[Moon_Counter]->velx, ListOfPointers2Moons[Moon_Counter]->vely, ListOfPointers2Moons[Moon_Counter]->velz, ListOfPointers2Moons[Moon_Counter]->KineticEnergy, ListOfPointers2Moons[Moon_Counter]->PotentialEnergy, ListOfPointers2Moons[Moon_Counter]->KineticEnergy, ListOfPointers2Moons[Moon_Counter]->TotalEnergy);
    }
}
int main(int argc, char **argv)
{
    long long int SumOfTotalEnergies=0;
    int NumberOfSteps=0;
    if(argc!=2)
    {
        printf("Please enter exactly one Input File Name");
        return EXIT_FAILURE;
    }
    /* Open File called Input.txt with r only mode
        and stream positioned at begining*/
    fp = fopen("Input.txt", "r");
    if(fp == NULL)
    {
        perror("Main:opening of Input.txt->");
        return EXIT_FAILURE;
    }
    
    ReadInputValues();
    printf("After 0 steps:\n");
    PrintCurrentValues();
    
    for(NumberOfSteps=1; NumberOfSteps<1001; NumberOfSteps++)
    {
        ApplyGravity();
        ApplyVelocity();
        //printf("After %d steps:\n", NumberOfSteps);
        //PrintCurrentValues();
    }
    CalculatePotentialEnergy();
    CalculateKineticEnergy();
    CalculateTotalEnergy();
    printf("Energy after %d steps:\n", NumberOfSteps-1);
    PrintCurrentEnergyValues();
    printf("Sum of total energy:");
    
    for(Moon_Counter=0; Moon_Counter<NUMBER_OF_MOONS; Moon_Counter++)
    {
        SumOfTotalEnergies+=ListOfPointers2Moons[Moon_Counter]->TotalEnergy;
        if(Moon_Counter != (NUMBER_OF_MOONS-1))
        {
            printf(" %lld +", ListOfPointers2Moons[Moon_Counter]->TotalEnergy);
        }
        else
        {
            printf(" %lld =", ListOfPointers2Moons[Moon_Counter]->TotalEnergy);
        }
    }
    
    printf("%lld\n", SumOfTotalEnergies);
    /* Cleanup */
    if(0 != fclose(fp))
    {
        perror("Main:Closig of Input.txt->");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}