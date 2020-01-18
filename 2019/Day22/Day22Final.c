#include <stdint.h> /* Types */
#include <stdio.h>  /* FILE, printf */
#include <stdlib.h> /* EXIT */
#include <string.h> /* Memcmp */

/* Local Function Declarations */
#define LOCAL static
void              cleanup(void);
LOCAL __uint128_t DealIntoNewStack(const __uint128_t NumberOfCards,
                                   const __uint128_t CurrentCardPosition);
LOCAL __uint128_t CutNCards(const __uint128_t NumberOfCards,
                            const __uint128_t CurrentCardPosition,
                            const int16_t     CutAtPosition);
LOCAL __uint128_t DealWithIncrementN(const __uint128_t NumberOfCards,
                                     const __uint128_t CurrentCardPosition,
                                     const uint8_t     Increment);
LOCAL __uint128_t ReadAndExecuteCommands(const __uint128_t NumberOfCards,
                                         const __uint128_t CurrentCardPosition,
                                         FILE*             fp);

/* Global Variables */
LOCAL FILE* fp_g;

/* Function to cleanup executable in case of a close or crash */
void cleanup(void)
{
    fclose(fp_g);
}

/* Function to Deal the deck upside down and return the NewCardPosition */
LOCAL __uint128_t DealIntoNewStack(const __uint128_t NumberOfCards,
                                   const __uint128_t CurrentCardPosition)
{
    __uint128_t NewCardPosition = -1;
    /* Sanity Check -> Check if NumberOfCards > 0 & CurrentCardPosition >=0 */
    if (NumberOfCards == 0)
    {
        printf("Error in Input to DealIntoNewStack");
        exit(EXIT_FAILURE);
    }
    NewCardPosition = NumberOfCards - CurrentCardPosition - 1;
    return NewCardPosition;
}

/* Function to Cut the cards at CutAtPosition and return NewCardPosition */
LOCAL __uint128_t CutNCards(const __uint128_t NumberOfCards,
                            const __uint128_t CurrentCardPosition,
                            const int16_t     CutAtPosition)
{
    __uint128_t NewCardPosition = -1;
    /* Sanity Check -> Check if NumberOfCards > 0 & CurrentCardPosition >=0 */
    if ((NumberOfCards == 0) || (0 == CutAtPosition))
    {
        printf("Error in Input to CutNCards");
        exit(EXIT_FAILURE);
    }
    NewCardPosition = (NumberOfCards + CurrentCardPosition - CutAtPosition) % NumberOfCards;
    return NewCardPosition;
}

/* Function to DealWithIncrementN and return a NewCardPosition */
LOCAL __uint128_t DealWithIncrementN(const __uint128_t NumberOfCards,
                                     const __uint128_t CurrentCardPosition,
                                     const uint8_t     Increment)
{
    __uint128_t NewCardPosition = -1;
    /* Sanity Check -> Check if NumberOfCards > 0 & CurrentCardPosition >=0 */
    if ((NumberOfCards == 0) || (0 == Increment))
    {
        printf("Error in Input to DealWithIncrementN");
        exit(EXIT_FAILURE);
    }
    NewCardPosition = (CurrentCardPosition * Increment) % NumberOfCards;
    return NewCardPosition;
}

/* Read And Execute Commands From File */
LOCAL __uint128_t ReadAndExecuteCommands(const __uint128_t NumberOfCards,
                                         const __uint128_t CurrentCardPosition,
                                         FILE*             fp)
{
    /* Let there be a new card position for return */
    __uint128_t NewCardPosition = CurrentCardPosition;
    /* Let getline allocate some buffer for me which i will free */
    char* lineptr = NULL;
    /* Ignored as input is NULL -> will be filled by getline */
    size_t input_buf = 0;
    /* A Variable to hold either Cut or increment value */
    int16_t CutOrIncrementValue = 0;
    /* If number of characters read greater than 0 */
    while (getline(&lineptr, &input_buf, fp) > 0)
    {
        /* Check if our  line starts with "deal with" -> If so call
         * DealWithIncrementN */
        if (!strncmp(lineptr, "deal with", 9))
        {
            CutOrIncrementValue = atoi(lineptr + 19);
            NewCardPosition = DealWithIncrementN(NumberOfCards, NewCardPosition,
                                                 CutOrIncrementValue);
        }
        /* Check if our  line starts with "deal" and not "deal with" -> If so
         * call DealIntoNewStack */
        else if (!strncmp(lineptr, "deal", 4))
        {
            NewCardPosition = DealIntoNewStack(NumberOfCards, NewCardPosition);
        }
        /* If not the above 2 cases must be CutNCards */
        else if (!strncmp(lineptr, "cut", 3))
        {
            CutOrIncrementValue = atoi(lineptr + 4);
            NewCardPosition =
                CutNCards(NumberOfCards, NewCardPosition, CutOrIncrementValue);
        }
        else
        {
            printf(
                "\nREAD AND EXECUTE COMMANDS ERROR -> UNKNOWN INPUT LINE IN "
                "FILE");
            exit(EXIT_FAILURE);
        }
    }
    return NewCardPosition;
}

int main(int argc, char** argv)
{
    __uint128_t i = 0;
    uint64_t    PrintNumber;
    __uint128_t Card2Track    = 2019;
    __uint128_t NumberOfCards = 10007;
    if (argc != 2)
    {
        printf("Please enter exactly one Input File Name\n");
        return EXIT_FAILURE;
    }
    fp_g = fopen(argv[1], "r");
    if (NULL == fp_g)
    {
        perror("Main:opening of Input.txt-> failed\n");
        return EXIT_FAILURE;
    }
    atexit(cleanup);

    /* Main Implementation */
    Card2Track = ReadAndExecuteCommands(NumberOfCards, Card2Track, fp_g);

    /* Print a uint128 */
    printf("The current card Position is:");
    PrintNumber = (uint64_t)((Card2Track >> 64) & 0xFFFFFFFFFFFFFFFF);
    printf("%lu", PrintNumber);
    PrintNumber = (uint64_t)(Card2Track & 0xFFFFFFFFFFFFFFFF);
    printf("%lu", PrintNumber);
    printf("\n");
    return EXIT_SUCCESS;
}
