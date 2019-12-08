/* Headers */
#include<stdio.h> /* For Printf*/
#include <string.h>

/* Defines */
#define Minimum_Number 359282
#define Maximum_Number 820401

/* GLobal Variables */
static long long int number = 0;

void SplitNumberIntoDigits(long long int number, int *a);
int CheckIfTwoAdjaccentDigitsAreSame(int *a);
int CheckIfDigitsAscending(int *a);

void SplitNumberIntoDigits(long long int number, int *a)
{
    int i;
    for (i=0; i<6; i++)
    {
        a[5-i]=number%10;
        number=number/10;
    }
}

int CheckIfTwoAdjaccentDigitsAreSame(int *a)
{
    int LoopCounter, RetVal=0;
    int number_of_occurances[10]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    for(LoopCounter=0; LoopCounter<6; LoopCounter++)
    {
        number_of_occurances[a[LoopCounter]] +=1;
        if((a[LoopCounter]==a[LoopCounter+1]) && (LoopCounter!=5))
        {
            RetVal = 1;
        }
    }

    if(1 == RetVal)
    {
        RetVal = 0;
        for(LoopCounter=9; LoopCounter>=0; LoopCounter--)
        {
            if(number_of_occurances[LoopCounter] > 1)
            {
                //Check if this largest repeating number only repeats twice
                if(number_of_occurances[LoopCounter] == 2)
                {
                    return 1;
                }
            }
            else
            {
                // Move Onto Next Number;
            }
        }
    }
    return 0;
}

int CheckIfDigitsAscending(int *a)
{
    int i, flag=1;
    for(i=0; i<5; i++)
    {
        if(a[i]>a[i+1])
        {
            flag = 0;
        }
    }
    return flag;
}

int main()
{
    int number_split[6];
    
    int i;
    int number_of_passwords=0;
    
    for(number=Minimum_Number; number<=Maximum_Number; number++)
    {
        //printf("CurrentNumberIs:%d\n", number);
        SplitNumberIntoDigits(number, number_split);
        if(1 == CheckIfDigitsAscending(number_split))
        {
            if(1 == CheckIfTwoAdjaccentDigitsAreSame(number_split))
            {
                number_of_passwords++;
            }
        }
    }
    printf("Number Of Passwords:%d", number_of_passwords);
    
    return 0;
}