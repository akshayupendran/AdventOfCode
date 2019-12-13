/* Headers */
#include <stdio.h>

/* Defines */
#define TOTAL_NUMBER_OF_LINES_IN_INPUT 859u
/* Global Variables */
static FILE *fp;

/* Function Declarations */
void GetInputs();

/* Linked List */
typedef struct
{
    char Name[4];
    struct Planet* OrbitsThisPlanet;
}Planet;

/* Variables */
struct Planet *FirstPlanet;

int main()
{
    unsigned int NumberOfLinesInInput;
    char input1[4];
    char input2[4];
	/* Open Given Input File */
	fp = fopen("input.txt", "r");
	for(NumberOfLinesInInput=0; NumberOfLinesInInput<1; NumberOfLinesInInput++)
    {
        fscanf(fp, "%3s)", input1);
        fscanf(fp, "%3s\n", input2);
        struct Planet *PlanetPtr = (struct Planet*)malloc(sizeof(struct Planet));
            
            if(NULL == PlanetPtr)
            {
                printf("Node creation failed \n");
                return -1;
            }
            memcpy(PlanetPtr->Name, input2, )
        }
        for(;)
    }
    fclose(fp);
	return 0;
}