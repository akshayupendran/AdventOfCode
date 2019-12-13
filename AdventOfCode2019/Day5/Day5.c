#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* INTOCDE COMPUTER DEFINES */

#define NUMBER_OF_INPUTS 678

long long int input[NUMBER_OF_INPUTS];
FILE *fp;
long long int IntcodeProgram[NUMBER_OF_INPUTS];
int Parameter1Mode=0, Parameter2Mode=0, Parameter3Mode=0, Opcode, ProgramCounter=0;
long long int *Parameter1, *Parameter2, *Parameter3;
    
void GetInputs();
void PrintInputs();
void RunIntCodeComputer();
void AssignParameters();

void AssignParameters()
{
    Opcode = (int)((IntcodeProgram[ProgramCounter])%100);
    if(99 != Opcode)
    {
        /* Paramter 1*/
        Parameter1Mode = (int)(((IntcodeProgram[ProgramCounter])/100)%10);
        if(1 < Parameter1Mode)
        {
            printf("Shit Happens in Parameter Mode1\n");
        }
        if(Parameter1Mode == 0)
        {
            Parameter1= &(IntcodeProgram[IntcodeProgram[ProgramCounter+1]]);
        }
        else
        {
            Parameter1= &(IntcodeProgram[ProgramCounter+1]);
        }
            
            
        if((3!=Opcode) && (4!=Opcode))
        {
            /* Paramter 2*/
            Parameter2Mode = (int)(((IntcodeProgram[ProgramCounter])/1000)%10);
            if(1 < Parameter2Mode)
            {
                printf("Shit Happens in Parameter Mode1\n");
            }
            if(Parameter2Mode == 0)
            {
                Parameter2= &(IntcodeProgram[IntcodeProgram[ProgramCounter+2]]);
            }
            else
            {
                Parameter2= &(IntcodeProgram[ProgramCounter+2]);
            }
                
            
            if((5!=Opcode) && (6!=Opcode))
            {
                /* Paramter 3*/
                Parameter3Mode = (int)(((IntcodeProgram[ProgramCounter])/10000)%10);
                if(1 < Parameter3Mode)
                {
                    printf("Shit Happens in Parameter Mode1\n");
                }
                if(Parameter3Mode == 0)
                {
                    Parameter3= &(IntcodeProgram[IntcodeProgram[ProgramCounter+3]]);
                }
                else
                {
                    Parameter3= &(IntcodeProgram[ProgramCounter+3]);
                }
            }
        }
    }
}
void RunIntCodeComputer()
{
    /* Sanity Check before running Code */
    for(ProgramCounter=0; ProgramCounter<NUMBER_OF_INPUTS;)
    {
		AssignParameters();
        /* Start the INTCODE COMPUTER */
        if(99 == Opcode)
        {
            ProgramCounter=NUMBER_OF_INPUTS;
        }
        else if(1 == Opcode)
        {
            Parameter3[0] = Parameter2[0] + Parameter1[0];
			ProgramCounter+=4;
        }
        else if(2 == Opcode)
        {
            Parameter3[0] = Parameter2[0] * Parameter1[0];
			ProgramCounter+=4;
        }
		else if(3 == Opcode)
		{
			printf("Please enter input parameter1:");
			scanf("%lld",Parameter1);
			ProgramCounter+=2;
		}
		else if(4 == Opcode)
		{
			printf("Output of parameter1 is:");
			printf("%lld\n",Parameter1[0]);
			ProgramCounter+=2;
		}
        else if(5 == Opcode)
		{
			if(0 != Parameter1[0])
            {
                ProgramCounter= Parameter2[0];
            }
            else
            {
                /* Do Nothing */
                ProgramCounter+=3;
            }
		}
        else if(6 == Opcode)
		{
			if(0 == Parameter1[0])
            {
                ProgramCounter= Parameter2[0];
            }
            else
            {
                /* Do Nothing */
                ProgramCounter+=3;
            }
		}
        else if(7 == Opcode)
		{
			if(Parameter1[0] < Parameter2[0])
            {
                Parameter3[0]=1;
            }
            else
            {
                Parameter3[0]=0;
            }
            ProgramCounter+=4;
		}
        else if(8 == Opcode)
		{
			if(Parameter1[0] == Parameter2[0])
            {
                Parameter3[0]=1;
            }
            else
            {
                Parameter3[0]=0;
            }
            ProgramCounter+=4;
		}
        else
        {
            printf("SHIT HAPPENS2!!!!!\n");
        }
        //printf("Next Program Counter is: %d!!!!!\n", ProgramCounter);
    }
}

void GetInputs()
{
	int i;
	/* Copy inputs to our input array */
    for(i=0; i<NUMBER_OF_INPUTS; i++)
    {
		if(i!=NUMBER_OF_INPUTS-1)
		{
			fscanf(fp, "%lld,", &input[i]);
		}
        else
		{
			fscanf(fp, "%lld\n", &input[i]);
		}
    }
}

void PrintInputs()
{
	int i;
	/* Print Given Input */
	for(i=0; i<NUMBER_OF_INPUTS; i++)
    {
		if(i!=NUMBER_OF_INPUTS-1)
		{
			printf("%lld,", input[i]);
		}
        else
		{
			printf("%lld\n", input[i]);
		}
    }
}

int main()
{
	/* Open Given Input File */
	fp = fopen("input.txt", "r");
	GetInputs();
	//PrintInputs();
	memcpy(IntcodeProgram, input, sizeof(input));
	RunIntCodeComputer();
	//PrintInputs();
	fclose(fp);
	return 0;
}