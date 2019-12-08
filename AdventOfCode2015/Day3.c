#include<stdio.h>
#include <string.h>

int main()
{
    int houses[500][500];
    //let us start at center houses
    int  i1=250, j1=250, i2=250, j2=250, totalhouses=0;
    int k,l;
    char direction;
    // initialise presents to 0 for each house
    memset(houses, 0, sizeof(houses));
    // for(k=0; k<500; k++)
    // {
        // for(l=0; l<500; l++)
        // {
            // printf("%d\n", houses[k][l]);
        // }
    // }

    //set current house to 1 present
    houses[i1][j1]=1; // santa
    houses[i2][j2]=1; // robot

    //get santa move
    direction=getchar();
    printf("santa_direction %c\t", direction);

    while((direction == '<') || (direction == '>') || (direction == '^') || (direction == 'v'))
    {
        if('<' == direction)
        {
            i1--;
        }
        else if('>' == direction)
        {
            i1++;
        }
        else if('^' == direction)
        {
            j1--;
        }
        else
        {
            j1++;
        }
        printf("santa_ij %d %d\n", i1, j1);
        if((i1<=0) || (i1>=500) || (j1<=0) || (j1>=500))
        {
            printf("ERROR ERROR ERROR ERROR!!!!!!");
            return -1;
        }

        houses[i1][j1]=houses[i1][j1] + 1; // increase present given by santa to house

        // get robot move
        direction=getchar();
        printf("Robot_direction %c\t", direction);
        if('<' == direction)
        {
            i2--;
        }
        else if('>' == direction)
        {
            i2++;
        }
        else if('^' == direction)
        {
            j2--;
        }
        else
        {
            j2++;
        }
        if((i2<=0) || (i2>=500) || (j2<=0) || (j2>=500))
        {
            printf("ERROR ERROR ERROR ERROR!!!!!!");
            return -1;
        }
        // move the robot
        printf("santa_ij %d %d\n", i2, j2);
        // give present by robot
        houses[i2][j2]=houses[i2][j2] + 1;

        //get santa next move
        direction=getchar();
        printf("Santa_ij %c\t", direction);

    }

    // number of houses with more than 1 present
    for(k=0; k<500; k++)
    {
        for(l=0; l<500; l++)
        {
            if(houses[k][l]!=0)
            {
                totalhouses++;
            }
        }
    }

    printf("\nTotalHousesWithPresents:%d\n", totalhouses);
    return 0;
}
