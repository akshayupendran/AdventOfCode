#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Local Function Declarations */
#define LOCAL static
LOCAL uint8_t ReadAndExecuteCommands(FILE* fp, const __uint128_t NumberOfCards,
                                     __uint128_t* Card2Track);
void          cleanup(void);
LOCAL uint8_t DealWithIncrementN(int8_t n, __uint128_t NumberOfCards,
                                 __uint128_t* Card2Track);

/* Global Variables */
LOCAL FILE* fp_g;

/* Function to cleanup executable in case of a close or crash */
void cleanup(void)
{
    fclose(fp_g);
}

/* Function to Deal With Increment N -> N shall only be +ve in this function*/
LOCAL uint8_t DealWithIncrementN(int8_t n, __uint128_t NumberOfCards,
                                 __uint128_t* Card2Track)
{
    uint8_t Retval = EXIT_FAILURE;

    if (n <= 0)
    {
        printf("\nWRONG INPUT FROM FILE FOR DEAL WITH INCREMENT");
    }
    else
    {
        (*Card2Track) = ((n * (*Card2Track)) % NumberOfCards);
        Retval        = EXIT_SUCCESS;
    }
    return Retval;
}

/* Function accepts a file pointer to an open file in read  mode */
/* Function reads the given input and executes one of the other internal
 * functions */
LOCAL uint8_t ReadAndExecuteCommands(FILE* fp, const __uint128_t NumberOfCards,
                                     __uint128_t* Card2Track)
{
    /* Let getline allocate some buffer for me which i will free */
    char* lineptr = NULL;
    /* Ignored as input is NULL -> will be filled by getline */
    size_t  input_buf = 0;
    int8_t  n         = 0;
    uint8_t Retval    = EXIT_FAILURE;
    /* If number of characters read greater than 0 */
    while (getline(&lineptr, &input_buf, fp) > 0)
    {
        /* Check if our  line starts with "deal with" -> If so call
         * DealWithIncrementN */
        if (!strncmp(lineptr, "deal with", 9))
        {
            n = atoi(lineptr + 19);
            Retval |= DealWithIncrementN(n, NumberOfCards, Card2Track);
        }
        /* Check if our  line starts with "deal" and not "deal with" -> If so
         * call DealIntoNewStack */
        else if (!strncmp(lineptr, "deal", 4))
        {
            // Retval |= DealIntoNewStack(NumberOfCards, Card2Track);
            Retval = EXIT_SUCCESS;
        }
        /* If not the above 2 cases must be CutNCards */
        else if (!strncmp(lineptr, "cut", 3))
        {
            n = atoi(lineptr + 4);
            // Retval |= CutNCards(n, NumberOfCards, Card2Track);
            Retval = EXIT_SUCCESS;
        }
        else
        {
            printf(
                "\nREAD AND EXECUTE COMMANDS ERROR -> UNKNOWN INPUT LINE IN "
                "FILE");
            return EXIT_FAILURE;
        }
    }
    return Retval;
}

int main(int argc, char** argv)
{
    int RetVal = EXIT_FAILURE;
    // __uint128_t Card2Track    = 2019;
    // __uint128_t NumberOfCards = 10007;
    __uint128_t Card2Track    = 4;
    __uint128_t NumberOfCards = 10;
    uint8_t printNumber;
    if (argc != 2)
    {
        printf("Please enter exactly one Input File Name\n");
        return RetVal;
    }
    fp_g = fopen(argv[1], "r");
    if (NULL == fp_g)
    {
        perror("Main:opening of Input.txt-> failed\n");
        return RetVal;
    }
    atexit(cleanup);

    RetVal = ReadAndExecuteCommands(fp_g, NumberOfCards, &Card2Track);
    Card2Track = 128;
    // if(EXIT_SUCCESS == RetVal)
    // {
        printf("The current card Position is:");
        for(printNumber = 0; printNumber < 16; printNumber++)
        {
            uint8_t temp;
            temp = Card2Track & 0xFF;
            Card2Track = Card2Track >> 8;
            printf("%u", temp);
        }
        printf("\n");
    // }
    // else
    // {
    //     printf("ReadAndExecuteCommands returned negative!!\n");
    // }
    return RetVal;
}