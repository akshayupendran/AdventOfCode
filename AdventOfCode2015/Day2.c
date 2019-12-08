#include <stdio.h>

int main()
{
    int dimensions[1000][3]; // 1000 boxes each with l b h
    int i=0; // LoopCounter
    long long int paperreqd[1000], ribbonreqdforbow[1000], ribbonreqd2wrap[1000];
    long long int a=0, b=0, c=0, d=0, totalpaperreqd=0, totalribbonreqd=0; // paper required for each sqare in cube
    // Get inputs into array
    for(i=0; i<1000; i++)
    {
        scanf("%dx%dx%d", &dimensions[i][0], &dimensions[i][1], &dimensions[i][2]);
    }

    // Debug: Check if input is printed
    // for(i=0; i<1000; i++)
    // {
        // printf("lbh is:%d %d %d\n", dimensions[i][0], dimensions[i][1], dimensions[i][2]);
    // }

    //Get the squareFeet Of Sheet per present
    for(i=0; i<1000; i++)
    {
        ribbonreqdforbow[i] = (dimensions[i][0]*dimensions[i][1]*dimensions[i][2]);
        if(dimensions[i][0] < dimensions[i][1])
        {
            if(dimensions[i][1] < dimensions[i][2])
            {
                ribbonreqd2wrap[i] = dimensions[i][0]+dimensions[i][0]+dimensions[i][1]+dimensions[i][1];
            }
            else
            {
                ribbonreqd2wrap[i] = dimensions[i][0]+dimensions[i][0]+dimensions[i][2]+dimensions[i][2];
            }
        }
        else
        {
            if(dimensions[i][0] < dimensions[i][2])
            {
                ribbonreqd2wrap[i] = dimensions[i][0]+dimensions[i][0]+dimensions[i][1]+dimensions[i][1];
            }
            else
            {
                ribbonreqd2wrap[i] = dimensions[i][1]+dimensions[i][1]+dimensions[i][2]+dimensions[i][2];
            }
        }
        totalribbonreqd += (ribbonreqd2wrap[i]+ribbonreqdforbow[i]);
        a = (2*dimensions[i][0]*dimensions[i][1]);
        b = (2*dimensions[i][1]*dimensions[i][2]);
        c = (2*dimensions[i][0]*dimensions[i][2]);
        if(a<b)
        {
            if(a<c)
            {
                d = a/2;
            }
            else
            {
                d = c/2;
            }
        }
        else
        {
            if(b<c)
            {
                d = b/2;
            }
            else
            {
                d = c/2;
            }
        }
        paperreqd[i] = a+b+c+d;
        totalpaperreqd += paperreqd[i];
    }
    printf("TotalRibbonReqd: %lld\n", totalribbonreqd);
    printf("TotalPaper Required: %lld\n", totalpaperreqd);
    return 0;
}
