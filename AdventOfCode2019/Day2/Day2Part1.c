#include <stdio.h>

#define NUMBER_OF_INPUTS 177u

int input[NUMBER_OF_INPUTS];

int main()
{
    int i=0; // input counter
    
    //get opcode with i
    for(i=0; i<NUMBER_OF_INPUTS; i++)
    {
        scanf("%d,", &input[i]); // get input into array
        //printf("%d\n", input[i]); //verify input by printing
    }
    
    // restore "1202 program alarm" state
    input[1]=12;
    input[2]=2;
    
    
    // parse through opcode
    for(i=0; i<NUMBER_OF_INPUTS; i+=4)
    {
        if(input[i]==99)
        {
            i=NUMBER_OF_INPUTS;
        }
        else if(input[i]==1)
        {
            input[input[i+3]] = (input[input[i+1]] + input[input[i+2]]);
        }
        else if(input[i]==2)
        {
            input[input[i+3]] = (input[input[i+1]] * input[input[i+2]]);
        }
        else
        {
            printf("SHIT HAPPENS!!!!!\n");
        }
    }
    printf("%d\n", input[0]);
    
    return 0;
}