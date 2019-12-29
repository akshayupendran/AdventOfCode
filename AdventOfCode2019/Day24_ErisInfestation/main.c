#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define TESTCASE
#define SIZE_OF_GRID_X 5u
#define SIZE_OF_GRID_Y 5u

uint8_t *BugLocationLayoutHistory;
uint8_t NumberOfLayouts=0;

void PrintBugLocationLayoutHistory()
{
    uint8_t LoopCounter=0;
    uint8_t LoopCounter2=0;
    uint8_t LoopCounter3=0;
    printf("CurrentMapOfErisIs:\n");
    for(LoopCounter = 0; LoopCounter < NumberOfLayouts; LoopCounter++)
    {
        for(LoopCounter2 = 0; LoopCounter2 < SIZE_OF_GRID_X; LoopCounter2 ++)
        {
            for(LoopCounter3 = 0; LoopCounter3 < SIZE_OF_GRID_Y; LoopCounter3 ++)
            {
                if(1 == BugLocationLayoutHistory[LoopCounter + LoopCounter2*(SIZE_OF_GRID_X+)] 
                {
                    printf("#");
                }
                else
                {
                    printf(".");
                }
            }
            printf("\n");
        }
        printf("Next Layout is:");
    }
}

void SkipNMinutes(uint8_t BugLocations[SIZE_OF_GRID_X][SIZE_OF_GRID_Y], const uint8_t Minutes)
{
    uint8_t BugLocations_temp[SIZE_OF_GRID_X][SIZE_OF_GRID_Y];
    uint8_t LoopCounter=0;
    uint8_t LoopCounter2=0;
    uint8_t LoopCounter3=0;
    uint8_t NumberOfAdjacentBugs=0;

    for(LoopCounter = 0; LoopCounter < Minutes; LoopCounter++)
    {
        NumberOfLayouts++;
        BugLocationLayoutHistory = (uint8_t*) realloc(BugLocationLayoutHistory, NumberOfLayouts*SIZE_OF_GRID_X*SIZE_OF_GRID_Y);
        for(LoopCounter2 = 0; LoopCounter2 < SIZE_OF_GRID_X; LoopCounter2 ++)
        {
            for(LoopCounter3 = 0; LoopCounter3 < SIZE_OF_GRID_Y; LoopCounter3 ++)
            {
                //printf("CurrentLoopCounterX,YAndNumberOfAdjacentBugsIs:%d,%d&", LoopCounter2, LoopCounter3);
                /* CheckNumberOfAdjacentBugs */
                if((LoopCounter2 != 4) && (1 == BugLocations[LoopCounter2+1][LoopCounter3]))
                {
                    NumberOfAdjacentBugs ++;
                }
                if((LoopCounter3 != 4) && (1 == BugLocations[LoopCounter2][LoopCounter3+1]))
                {
                    NumberOfAdjacentBugs++;
                }
                if((LoopCounter2 != 0) && (1 == BugLocations[LoopCounter2-1][LoopCounter3]))
                {
                    NumberOfAdjacentBugs++;
                }
                if((LoopCounter3 != 0) && (1 == BugLocations[LoopCounter2][LoopCounter3-1])) 
                {
                    NumberOfAdjacentBugs++;
                }

                if(0 == BugLocations[LoopCounter2][LoopCounter3])
                {
                    /* There is no bug for now*/
                    if((1 == NumberOfAdjacentBugs) || (2 == NumberOfAdjacentBugs))
                    {
                        BugLocations_temp[LoopCounter2][LoopCounter3] = 1;
                    }
                    else
                    {
                        BugLocations_temp[LoopCounter2][LoopCounter3] = 0;
                    }
                }
                else if (1 == BugLocations[LoopCounter2][LoopCounter3])
                {
                    /* There is a bug */
                    if(1 == NumberOfAdjacentBugs)
                    {
                        BugLocations_temp[LoopCounter2][LoopCounter3] = 1;
                    }
                    else
                    {
                        BugLocations_temp[LoopCounter2][LoopCounter3] = 0;
                    }
                }
                else
                {
                    printf("ShitHappens\n");
                }
                //printf("%d\n",NumberOfAdjacentBugs);
                NumberOfAdjacentBugs = 0;
            }
        }
    }
    memcpy(BugLocations, BugLocations_temp, (SIZE_OF_GRID_X*SIZE_OF_GRID_Y));
    memcpy((BugLocationLayoutHistory+(SIZE_OF_GRID_X*SIZE_OF_GRID_Y*(NumberOfLayouts-1))), BugLocations, (SIZE_OF_GRID_X*SIZE_OF_GRID_Y));
}

int main()
{
    uint8_t BugLocations[SIZE_OF_GRID_X][SIZE_OF_GRID_Y];
    
    #ifdef TESTCASE
    memset(BugLocations, 0x00, (SIZE_OF_GRID_X*SIZE_OF_GRID_Y));
    BugLocations[0][4] = 1;
    BugLocations[1][0] = 1;
    BugLocations[1][3] = 1;
    BugLocations[2][0] = 1;
    BugLocations[2][3] = 1;
    BugLocations[2][4] = 1;
    BugLocations[3][2] = 1;
    BugLocations[4][0] = 1;
    #endif
    SkipNMinutes(BugLocations, 1);
    SkipNMinutes(BugLocations, 1);
    SkipNMinutes(BugLocations, 1);
    SkipNMinutes(BugLocations, 1);
    PrintBugLocationLayoutHistory();
    return 0;
}