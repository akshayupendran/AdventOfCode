#include "main.h"

static FILE* fp;

void cleanup()
{
    fclose(fp);
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

/* Part 1 */
#if ((defined ENABLE_PART_ONE) || (defined ENABLE_PART_TWO))
    MainProcess(fp);
#else
#error Either ENABLE_PART_ONE or ENABLE_PART_TWO must be defined!!
#endif

    return 0;
}