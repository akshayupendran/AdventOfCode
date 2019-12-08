#include <stdio.h>
#include <string.h>

#define NUMBER_OF_INPUTS 177u

#define NOUN       IntcodeProgram[1]
#define VERB       IntcodeProgram[2]
#define OPCODE     IntcodeProgram[ProgramCounter]
#define PARAMETER1 IntcodeProgram[IntcodeProgram[ProgramCounter+1]]
#define PARAMETER2 IntcodeProgram[IntcodeProgram[ProgramCounter+2]]
#define PARAMETER3 IntcodeProgram[IntcodeProgram[ProgramCounter+3]]

#define ResetMemory() memcpy(IntcodeProgram, input, sizeof(input))

int input[NUMBER_OF_INPUTS];
int IntcodeProgram[NUMBER_OF_INPUTS];

void Restore1202AlarmState(void);
void GetInput(void);
void RunIntCodeComputer(void);

void RunIntCodeComputer()
{
    int ProgramCounter;
    
    for(ProgramCounter=0; ProgramCounter<NUMBER_OF_INPUTS; ProgramCounter+=4)
    {
        if(99 == OPCODE)
        {
            ProgramCounter=NUMBER_OF_INPUTS;
        }
        else if(1 == OPCODE)
        {
            PARAMETER3 = (PARAMETER1 + PARAMETER2);
        }
        else if(2 == OPCODE)
        {
            PARAMETER3 = (PARAMETER1 * PARAMETER2);
        }
        else
        {
            printf("SHIT HAPPENS!!!!!\n");
        }
    }
}

void GetInput()
{
    int i;
    for(i=0; i<NUMBER_OF_INPUTS; i++)
    {
        scanf("%d,", &input[i]);
    }
}

void PrintInput()
{
    int i;
    for(i=0; i<NUMBER_OF_INPUTS; i++)
    {
        printf("%d,", input[i]);
    }
}

void Restore1202AlarmState()
{
    NOUN=12;
    VERB=2;
}

int main()
{
    int Noun_GravityAssistMoon=-1, Verb_GravityAssistMoon=0;
    
    GetInput();
    memcpy(IntcodeProgram, input, sizeof(input));
    Restore1202AlarmState();
    RunIntCodeComputer();
    printf("FirstOpcodeInOutputIs:%d\n", IntcodeProgram[0]);
    
    do
    {
        Noun_GravityAssistMoon++;
        if(100 == Noun_GravityAssistMoon)
        {
            Noun_GravityAssistMoon=0;
            Verb_GravityAssistMoon++;
        }
        if(100 == Verb_GravityAssistMoon)
        {
            printf("SHIT HAPPENS!!!\n");
            return -1;
        }
        ResetMemory();
        NOUN=Noun_GravityAssistMoon;
        VERB=Verb_GravityAssistMoon;
        RunIntCodeComputer();
    }while(19690720 != IntcodeProgram[0]);
    
    printf("100*NOUN+VERB IS:%d\n", (100*Noun_GravityAssistMoon+Verb_GravityAssistMoon));
    return 0;
}