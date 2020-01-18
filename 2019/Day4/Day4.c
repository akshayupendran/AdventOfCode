/* Headers */
#include<stdio.h> /* For Printf*/
#include <string.h> /* For MEMCPY */

/* Defines */
#define Minimum_Number 359282
#define Maximum_Number 820401

/* GLobal Variables */
static long long int number;
int number_split[6];
int number_of_passwords=0;
int number_of_passwords_2=0;

void SplitNumberIntoDigits();
int CheckIfTwoAdjaccentDigitsAreSame();
int CheckIfDigitsAscending();
int CheckLargestRepNoRepsOnly2Times();

int CheckLargestRepNoRepsOnly2Times()
{
    int repeating_count[10];
    int LoopCounter;
    
    printf("Number Is: %lld\n", number);
    memset(repeating_count, 0, sizeof(repeating_count));
    
    for(LoopCounter=0; LoopCounter<6; LoopCounter++)
    {
            repeating_count[number_split[LoopCounter]]+=1;
            if(repeating_count[number_split[LoopCounter]] > 1)
            {
                printf("RepeatingCount of %d is %d\n", number_split[LoopCounter], repeating_count[number_split[LoopCounter]]);
            }
    }
    for(LoopCounter = 9; LoopCounter>=0; LoopCounter--)
    {
        if(2==repeating_count[LoopCounter])
        {
            printf("Number is good!!\n");
            return 1;
        }
        else
        {
            
        }
    }
    printf("Number is bad!!\n");
    return 0;
}

void SplitNumberIntoDigits()
{
    int i, number_temp;
    number_temp=number;
    for (i=0; i<6; i++)
    {
        number_split[5-i]=number_temp%10;
        number_temp=number_temp/10;
    }
}

int CheckIfTwoAdjaccentDigitsAreSame()
{
    int LoopCounter, RetVal=0;
    
    for(LoopCounter=0; LoopCounter<6; LoopCounter++)
    {
        if((number_split[LoopCounter]==number_split[LoopCounter+1]) && (LoopCounter!=5))
        {
            RetVal = 1;
        }
    }
    return RetVal;
}

int CheckIfDigitsAscending()
{
    int i, RetVal=1;
    for(i=0; i<5; i++)
    {
        if(number_split[i]>number_split[i+1])
        {
            RetVal = 0;
        }
    }
    return RetVal;
}

int main()
{
    for(number=Minimum_Number; number<=Maximum_Number; number++)
    {
        //printf("Number Is:%d\n", number);
        SplitNumberIntoDigits();
        if(1 == CheckIfDigitsAscending())
        {
            if(1 == CheckIfTwoAdjaccentDigitsAreSame())
            {
                number_of_passwords++;
                if(1 == CheckLargestRepNoRepsOnly2Times())
                {
                    number_of_passwords_2++;
                }
            }
        }
    }
    printf("Number Of Passwords Part1:%d\n", number_of_passwords);
    printf("Number Of Passwords Part2:%d\n", number_of_passwords_2);
    
    return 0;
}