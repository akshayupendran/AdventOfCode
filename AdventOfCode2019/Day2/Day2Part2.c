#include <stdio.h>
#include <string.h>

#define NUMBER_OF_INPUTS 177u

long long int input[NUMBER_OF_INPUTS];
long long int opcodes[NUMBER_OF_INPUTS];

int noun=0, verb=0;
int main()
{
    int i=0; // input counter
    int flag=0;
    //get opcode with i
    for(i=0; i<NUMBER_OF_INPUTS; i++)
    {
        scanf("%lld,", &input[i]); // get input into array
        //printf("%lld\n", input[i]); //verify input by printing
    }
    
    do
    {
        if(flag!=0)
        {
            noun++;
            if(noun == NUMBER_OF_INPUTS)
            {
                noun=0;
                verb++;
                if(verb == NUMBER_OF_INPUTS)
                {
                    printf("ERROR!");
                    return -1;
                }
            }
        }
        else
        {
            flag++;
        }
        
        printf("%lld %lld\n", noun, verb);
        memcpy(opcodes, input, sizeof(input));
        opcodes[1]=noun;
        opcodes[2]=verb;
        
        for(i=0; i<NUMBER_OF_INPUTS; i+=4)
        {
            if(opcodes[i]==99)
            {
                i=NUMBER_OF_INPUTS;
            }
            else if(opcodes[i]==1)
            {
                opcodes[opcodes[i+3]] = (opcodes[opcodes[i+1]] + opcodes[opcodes[i+2]]);
            }
            else if(opcodes[i]==2)
            {
                opcodes[opcodes[i+3]] = (opcodes[opcodes[i+1]] * opcodes[opcodes[i+2]]);
            }
            else
            {
                printf("SHIT HAPPENS!!!!!\n");
                i=NUMBER_OF_INPUTS;
            }
        }
        
    }while(opcodes[0]!=19690270);
    
    
    
    return 0;
}