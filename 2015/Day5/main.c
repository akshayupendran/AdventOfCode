#include <openssl/evp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENABLE_PART_ONE
//#define ENABLE_PART_TWO

FILE* fp;

void cleanup()
{
    fclose(fp);
}

void MainProcess()
{
    uint16_t LineNumber=1, NumberOfNiceStrings=0;
    char*   line = NULL;
    size_t  len  = 0;
    ssize_t read;
    uint8_t NumberOfVowels = 0, VowelConditionFlag = 0, i, TwiceInARowFlag = 0;
    uint8_t NaughtySubstringPresent = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        /* All read are of length 18 = 16characters + 1 null + 1newline(delim)
         */
        NumberOfVowels = 0;
        VowelConditionFlag = 0;
        TwiceInARowFlag = 0;
        NaughtySubstringPresent = 0;
        for (i = 0; i < 16; i++)
        {
            if ((line[i] == 'a') || (line[i] == 'e') || (line[i] == 'i') ||
                (line[i] == 'o') || (line[i] == 'u'))
            {
                NumberOfVowels++;
                if (NumberOfVowels == 3)
                    VowelConditionFlag = 1;
            }
            if (i != 0)
            {
                if (line[i] == line[i - 1])
                {
                    TwiceInARowFlag = 1;
                }
                if (((line[i] == 'b') && (line[i - 1] == 'a')) ||
                    ((line[i] == 'd') && (line[i - 1] == 'c')) ||
                    ((line[i] == 'q') && (line[i - 1] == 'p')) ||
                    ((line[i] == 'y') && (line[i - 1] == 'c')))
                {
                    NaughtySubstringPresent = 1;
                }
            }
        }
        if((NaughtySubstringPresent != 1) && (VowelConditionFlag == 1) && (TwiceInARowFlag == 1))
        {
            printf("%d LineNumber is a nice string\n", LineNumber);
            NumberOfNiceStrings++;
        }
        LineNumber ++;
    }
    printf("Total Number of Nice Strings is:%d\n", NumberOfNiceStrings);
}

int main(int argc, char** argv)
{
    /* Check if input file name exists */
    if (argc != 2)
    {
        printf("Please enter exactly one Input File Name\n");
        return EXIT_FAILURE;
    }
    /* Get Input from file */
    /* Open File called Input.txt with r only mode
        and stream positioned at begining*/
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror("Main:opening of Input.txt-> failed\n");
        return EXIT_FAILURE;
    }
    /* Register Closure Function */
    atexit(cleanup);

#if ((defined ENABLE_PART_ONE) || (defined ENABLE_PART_TWO))
    MainProcess();
#else
#error Either ENABLE_PART_ONE or ENABLE_PART_TWO must be defined!!
#endif

    return 0;
}
