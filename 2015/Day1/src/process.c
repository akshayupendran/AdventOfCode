#include "main.h"

void MainProcess(FILE* fp)
{
    char    c;
    int32_t CurrentFloor_lli = 0;
#ifdef ENABLE_PART_TWO
    uint32_t InputNumber_lli = 0;
    uint8_t  Part2Finished   = 0;
#endif
    /* Get a single character until EOF */
    c = fgetc(fp);
    while ((c == '(') || (c == ')'))
    {
        if (c == '(')
        {
            CurrentFloor_lli++;
        }
        else
        {
            CurrentFloor_lli--;
        }
#ifdef ENABLE_PART_TWO
        if (Part2Finished != 1)
        {
            InputNumber_lli++;
            if ((CurrentFloor_lli < 0) && (Part2Finished != 1))
            {
                Part2Finished = 1;
                printf("Part2 Solution is: %u\n", InputNumber_lli);
            }
        }
#endif
        c = fgetc(fp);
    }
#ifdef ENABLE_PART_ONE
    printf("Part1 Solution is:%d\n", CurrentFloor_lli);
#endif
#ifdef ENABLE_PART_TWO
    if (0 == Part2Finished)
    {
        printf("Could not find a solution for part2!!");
    }
#endif
}
