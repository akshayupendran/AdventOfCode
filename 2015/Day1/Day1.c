#include<stdio.h>

int main()
{
    unsigned char AlreadyEntered_ui08=0;
    char c;
    long long int CurrentFloor_lli =0;
    long long int InputNumber_lli=0;
    c=getchar();
    while((c == '(') || (c == ')'))
    {
        InputNumber_lli++;
        if(c == '(')
        {
            CurrentFloor_lli++;
        }
        else
        {
            CurrentFloor_lli--;
        }
        if((CurrentFloor_lli == -1) && (0 == AlreadyEntered_ui08))
        {
            printf("First Character to Enter Basement is %lli\n", InputNumber_lli);
            AlreadyEntered_ui08 = 1;
        }
        c=getchar();
    }
    printf("Last Floor is: %lld\n", CurrentFloor_lli);
    return 0;
}
