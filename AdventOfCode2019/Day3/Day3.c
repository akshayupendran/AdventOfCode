/* Includes */
#include<stdio.h>

/* Defines */
#define NUMBER_OF_INPUTS_BY_2 301u

/* Types */
typedef struct
{
    unsigned int NumberOfSteps;
    char Direction;
}input_type_t;

typedef struct
{
    int x;
    int y;
}CoordListType;

/*Declarations */
void GetInputsFromFile(void);
void PrintInputs(void);
void ConvertInputsToCoordinates(void);
void PrintCoords(void);
void FindAndPrintMaxMinXYValues(void);

/* Global Variables */
input_type_t wire1_input[NUMBER_OF_INPUTS_BY_2];
input_type_t wire2_input[NUMBER_OF_INPUTS_BY_2];
CoordListType wire1Coords[NUMBER_OF_INPUTS_BY_2];
CoordListType wire2Coords[NUMBER_OF_INPUTS_BY_2];
int maxXCoord=0;
int minXCoord=0;
int maxYCoord=0;
int minYCoord=0;

/* Functions */
void GetInputsFromFile()
{
    int i;
    
    for(i=0; i<NUMBER_OF_INPUTS_BY_2; i++)
    {
        if(i == (NUMBER_OF_INPUTS_BY_2-1))
        {
            scanf("%c%d\n", &(wire1_input[i].Direction), &(wire1_input[i].NumberOfSteps));
        }
        else
        {
            scanf("%c%d,", &(wire1_input[i].Direction), &(wire1_input[i].NumberOfSteps));
        }
    }
    
    for(i=0; i<NUMBER_OF_INPUTS_BY_2; i++)
    {
        if(i == (NUMBER_OF_INPUTS_BY_2-1))
        {
            scanf("%c%d\n", &(wire2_input[i].Direction), &(wire2_input[i].NumberOfSteps));
        }
        else
        {
            scanf("%c%d,", &(wire2_input[i].Direction), &(wire2_input[i].NumberOfSteps));
        }
    }
}

void PrintInputs()
{
    int i;
    for(i=0; i<NUMBER_OF_INPUTS_BY_2; i++)
    {
        if(i == (NUMBER_OF_INPUTS_BY_2-1))
        {
            printf("%c%d\n", wire1_input[i].Direction, wire1_input[i].NumberOfSteps);
        }
        else
        {
            printf("%c%d,", wire1_input[i].Direction, wire1_input[i].NumberOfSteps);
        }
    }
    
    for(i=0; i<NUMBER_OF_INPUTS_BY_2; i++)
    {
        if(i == (NUMBER_OF_INPUTS_BY_2-1))
        {
            printf("%c%d\n", wire2_input[i].Direction, wire2_input[i].NumberOfSteps);
        }
        else
        {
            printf("%c%d,", wire2_input[i].Direction, wire2_input[i].NumberOfSteps);
        }
    }
}

void ConvertInputsToCoordinates()
{
    int i;
    for(i=0; i<NUMBER_OF_INPUTS_BY_2; i++)
    {
        if('R' == wire1_input[i].Direction)
        {
            if(i == 0)
            {
                wire1Coords[i].x = 0 + wire1_input[i].NumberOfSteps;
                wire1Coords[i].y = 0;
            }
            else
            {
                wire1Coords[i].x = wire1Coords[i-1].x + wire1_input[i].NumberOfSteps;
                wire1Coords[i].y = wire1Coords[i-1].y;
            }
        }
        else if('L' == wire1_input[i].Direction)
        {
            if(i == 0)
            {
                wire1Coords[i].x = 0 - wire1_input[i].NumberOfSteps;
                wire1Coords[i].y = 0;
            }
            else
            {
                wire1Coords[i].x = wire1Coords[i-1].x - wire1_input[i].NumberOfSteps;
                wire1Coords[i].y = wire1Coords[i-1].y;
            }
        }
        else if('U' == wire1_input[i].Direction)
        {
            if(i == 0)
            {
                wire1Coords[i].x = 0;
                wire1Coords[i].y = 0 + wire1_input[i].NumberOfSteps;
            }
            else
            {
                wire1Coords[i].x = wire1Coords[i-1].x;
                wire1Coords[i].y = wire1Coords[i-1].y + wire1_input[i].NumberOfSteps;
            }
        }
        else if('D' == wire1_input[i].Direction)
        {
            if(i == 0)
            {
                wire1Coords[i].x = 0;
                wire1Coords[i].y = 0 - wire1_input[i].NumberOfSteps;
            }
            else
            {
                wire1Coords[i].x = wire1Coords[i-1].x;
                wire1Coords[i].y = wire1Coords[i-1].y - wire1_input[i].NumberOfSteps;
            }
        }
        else
        {
            printf("SHIT HAPPENS\n");
        }
    }
    
    
    for(i=0; i<NUMBER_OF_INPUTS_BY_2; i++)
    {
        if('R' == wire2_input[i].Direction)
        {
            if(i == 0)
            {
                wire2Coords[i].x = 0 + wire2_input[i].NumberOfSteps;
                wire2Coords[i].y = 0;
            }
            else
            {
                wire2Coords[i].x = wire2Coords[i-1].x + wire2_input[i].NumberOfSteps;
                wire2Coords[i].y = wire2Coords[i-1].y;
            }
        }
        else if('L' == wire2_input[i].Direction)
        {
            if(i == 0)
            {
                wire2Coords[i].x = 0 - wire2_input[i].NumberOfSteps;
                wire2Coords[i].y = 0;
            }
            else
            {
                wire2Coords[i].x = wire2Coords[i-1].x - wire2_input[i].NumberOfSteps;
                wire2Coords[i].y = wire2Coords[i-1].y;
            }
        }
        else if('U' == wire2_input[i].Direction)
        {
            if(i == 0)
            {
                wire2Coords[i].x = 0;
                wire2Coords[i].y = 0 + wire2_input[i].NumberOfSteps;
            }
            else
            {
                wire2Coords[i].x = wire2Coords[i-1].x;
                wire2Coords[i].y = wire2Coords[i-1].y + wire2_input[i].NumberOfSteps;
            }
        }
        else if('D' == wire2_input[i].Direction)
        {
            if(i == 0)
            {
                wire2Coords[i].x = 0;
                wire2Coords[i].y = 0 - wire2_input[i].NumberOfSteps;
            }
            else
            {
                wire2Coords[i].x = wire2Coords[i-1].x;
                wire2Coords[i].y = wire2Coords[i-1].y - wire2_input[i].NumberOfSteps;
            }
        }
        else
        {
            printf("SHIT HAPPENS\n");
        }
    }
}

void PrintCoords()
{
    int i;
    for(i=0; i<NUMBER_OF_INPUTS_BY_2; i++)
    {
        printf("%d %d, ", wire1Coords[i].x, wire1Coords[i].y); 
    }
    printf("\n");
    for(i=0; i<NUMBER_OF_INPUTS_BY_2; i++)
    {
        printf("%d %d, ", wire2Coords[i].x, wire2Coords[i].y); 
    }
    printf("\n");
}

void FindAndPrintMaxMinXYValues()
{
    int i;
    for(i=0; i<NUMBER_OF_INPUTS_BY_2; i++)
    {
        if(wire1Coords[i].x > maxXCoord)
        {
            maxXCoord = wire1Coords[i].x;
        }
        if(wire2Coords[i].x > maxXCoord)
        {
            maxXCoord = wire2Coords[i].x;
        }
        if(wire1Coords[i].y > maxYCoord)
        {
            maxYCoord = wire1Coords[i].y;
        }
        if(wire2Coords[i].y > maxYCoord)
        {
            maxYCoord = wire2Coords[i].y;
        }
        if(wire1Coords[i].x < minXCoord)
        {
            minXCoord = wire1Coords[i].x;
        }
        if(wire2Coords[i].x < minXCoord)
        {
            minXCoord = wire2Coords[i].x;
        }
        if(wire1Coords[i].y < minYCoord)
        {
            minYCoord = wire1Coords[i].y;
        }
        if(wire2Coords[i].y < minYCoord)
        {
            minYCoord = wire2Coords[i].y;
        }
    }
    printf("MinX:%d, MaxX:%d, MinY:%d, MaxY:%d\n", minXCoord, maxXCoord, minYCoord, maxYCoord);
    printf("RangeOfX:%d, RangeOfY:%d\n", (maxXCoord-minXCoord), (maxYCoord-minYCoord));
}

int main()
{
    GetInputsFromFile();
    ConvertInputsToCoordinates();
    FindAndPrintMaxMinXYValues();
    return 0;
}