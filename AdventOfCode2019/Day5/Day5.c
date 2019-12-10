#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* INTOCDE COMPUTER DEFINES */

#define NUMBER_OF_INPUTS 678u

long long int input[NUMBER_OF_INPUTS];
FILE *fp;
long long int IntcodeProgram[NUMBER_OF_INPUTS];

void GetInputs();
void PrintInputs();
void RunIntCodeComputer();

void RunIntCodeComputer()
{
	int ProgramCounter=0;
    /* Sanity Check before running Code */
	int Parameter1Mode, Parameter2Mode, Parameter3Mode, Opcode;
	long long int *Parameter1, *Parameter2, *Parameter3;
	
    for(ProgramCounter=0; ProgramCounter<NUMBER_OF_INPUTS;)
    {
		Opcode = (int)((IntcodeProgram[ProgramCounter])%100);
		Parameter1Mode = (int)(((IntcodeProgram[ProgramCounter])/100)%10);
		Parameter2Mode = (int)(((IntcodeProgram[ProgramCounter])/1000)%10);
		Parameter3Mode = (int)(((IntcodeProgram[ProgramCounter])/10000)%10);
		
		/* Sanity Check of Parameter Modes */
		if((1 < Parameter1Mode) || (1 < Parameter2Mode) || (1 < Parameter3Mode))
		{
			printf("Shit Happens in Parameter Modes");
		}
		
		/* Get Parameters as pointers */
		if(Parameter1Mode == 0)
		{
			Parameter1= &(IntcodeProgram[IntcodeProgram[ProgramCounter+1]]);
		}
		else
		{
			Parameter1= &(IntcodeProgram[ProgramCounter+1]);
		}
		if(Parameter2Mode == 0)
		{
			Parameter2= &(IntcodeProgram[IntcodeProgram[ProgramCounter+2]]);
		}
		else
		{
			Parameter1= &(IntcodeProgram[ProgramCounter+2]);
		}
		if(Parameter3Mode == 0)
		{
			Parameter3= &(IntcodeProgram[IntcodeProgram[ProgramCounter+3]]);
		}
		else
		{
			Parameter1= &(IntcodeProgram[ProgramCounter+3]);
		}
		
		printf("Current Opcode, Parameters Modes and Parameters are: %d %d %d %d %lld %lld %lld\n", Opcode, Parameter1Mode, Parameter2Mode, Parameter3Mode, Parameter1[0], Parameter2[0], Parameter3[0]);
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
        else
        {
            printf("SHIT HAPPENS2!!!!!\n");
        }
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