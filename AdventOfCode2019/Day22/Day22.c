/* Headers */
#include <stdio.h>  /* Printf */
#include <stdint.h> /* UINT16 */
#include <string.h> /* Memcpy */
#include <stdlib.h> /* StrToIMax */

/* Configurations */
/* #define NUMBER_OF_CARDS_IN_DECK 10007u */
#define NUMBER_OF_CARDS_IN_DECK      119315717514047
#define NUMBER_OF_CARDS_IN_DECK_BY_2  5003
//#define LOGGING_ENABLE

/* Variables */
uint64_t SpaceCardsDeck_g_ui16[NUMBER_OF_CARDS_IN_DECK];
FILE *fp;

/* Declarations */
#ifdef LOGGING_ENABLE
void PrintDeck();
#endif
void FactoryOrder();
void DealIntoNewStack();
void CutNCards(int16_t N);
void DealWithIncrementN(uint64_t N);
void ReadInputValueAndExecuteCommand();
/* Implementations */
#ifdef LOGGING_ENABLE
void PrintDeck()
{
    uint64_t Counter_ui16;
    for(Counter_ui16=0; Counter_ui16< NUMBER_OF_CARDS_IN_DECK; Counter_ui16++)
    {
        printf("%d\n", SpaceCardsDeck_g_ui16[Counter_ui16]);
    }
}
#endif

void FactoryOrder()
{
    uint64_t Counter_ui16;
    for(Counter_ui16=0; Counter_ui16< NUMBER_OF_CARDS_IN_DECK; Counter_ui16++)
    {
        SpaceCardsDeck_g_ui16[Counter_ui16] = Counter_ui16;
    }
}

void DealIntoNewStack()
{
    uint64_t Counter_ui16;
    uint64_t SpaceCardsDeckTemp_ui16[NUMBER_OF_CARDS_IN_DECK_BY_2];
    for(Counter_ui16=0; Counter_ui16< NUMBER_OF_CARDS_IN_DECK; Counter_ui16++)
    {
        if(Counter_ui16 < NUMBER_OF_CARDS_IN_DECK_BY_2)
        {
            SpaceCardsDeckTemp_ui16[Counter_ui16] = SpaceCardsDeck_g_ui16[Counter_ui16];
            SpaceCardsDeck_g_ui16[Counter_ui16] = SpaceCardsDeck_g_ui16[NUMBER_OF_CARDS_IN_DECK-1-Counter_ui16];
        }
        else
        {
            SpaceCardsDeck_g_ui16[Counter_ui16] = SpaceCardsDeckTemp_ui16[NUMBER_OF_CARDS_IN_DECK-1-Counter_ui16];
        }
        
    }
}

void CutNCards(int16_t N)
{
    uint16_t O;
    if(N < 0)
        O = (NUMBER_OF_CARDS_IN_DECK+N);
    uint64_t Counter_ui16=0;
    uint64_t SpaceCardsDeckTemp_ui16[NUMBER_OF_CARDS_IN_DECK];
    for(Counter_ui16=0; Counter_ui16< NUMBER_OF_CARDS_IN_DECK; Counter_ui16++)
    {
        if((Counter_ui16+O) < NUMBER_OF_CARDS_IN_DECK)
        {
            SpaceCardsDeckTemp_ui16[Counter_ui16] = SpaceCardsDeck_g_ui16[Counter_ui16];
            SpaceCardsDeck_g_ui16[Counter_ui16] = SpaceCardsDeck_g_ui16[Counter_ui16+O];
        }
        else
        {
            if(Counter_ui16 < O)
            {
                SpaceCardsDeckTemp_ui16[Counter_ui16] = SpaceCardsDeck_g_ui16[Counter_ui16];
            }
            SpaceCardsDeck_g_ui16[Counter_ui16] = SpaceCardsDeckTemp_ui16[Counter_ui16-(NUMBER_OF_CARDS_IN_DECK-O)];
        }
    }
}

void DealWithIncrementN(uint64_t N)
{
    uint64_t Counter_ui16, Position_ui16=0;
    uint64_t SpaceCardsDeckTemp_ui16[NUMBER_OF_CARDS_IN_DECK];
    for(Counter_ui16 =0; Counter_ui16<NUMBER_OF_CARDS_IN_DECK; Counter_ui16++)
    {
        SpaceCardsDeckTemp_ui16[Position_ui16]=SpaceCardsDeck_g_ui16[Counter_ui16];
        Position_ui16 += N;
        while(Position_ui16 >= NUMBER_OF_CARDS_IN_DECK)
        {
            Position_ui16 = Position_ui16 - NUMBER_OF_CARDS_IN_DECK;
        }
    }
    (void) memcpy(SpaceCardsDeck_g_ui16, SpaceCardsDeckTemp_ui16, NUMBER_OF_CARDS_IN_DECK*sizeof(uint64_t));
}

void ReadInputValueAndExecuteCommand()
{
    
    char *input = NULL; /* Let getline allocate some buffer for me which i will free */
    uint64_t input_buf = 0; /* Ignored as input is NULL -> will be filled by getline */
    int n=0;
    while ( getline( &input, &input_buf, fp ) > 0 ) /* If number of characters read greater than 0 */
    {
        if( !strncmp( input, "deal with", 9 ) )
        {
            n = atoi(input + 19);
            DealWithIncrementN(n);
        } else if ( !strncmp( input, "deal", 4 ) ) {
            // no number
            //printf("n3 is\n");
            DealIntoNewStack();
        } else {
            n = atoi(input + 4);
            //printf("n2 is %d\n", n);
            CutNCards(n);
        }
    }
}

int main(int argc, char **argv)
{
    // uint64_t i=0;
    // uint64_t Counter_ui16;
    if(argc!=2)
    {
        printf("Please enter exactly one Input File Name");
        return EXIT_FAILURE;
    }
    /* Open File called Input.txt with r only mode
        and stream positioned at begining*/
    fp = fopen(argv[1], "r");
    if(fp == NULL)
    {
        perror("Main:opening of Input.txt-> failed");
        return EXIT_FAILURE;
    }
    /* Track the given input card */

    while (i< 101741582076661)
    {
        ReadInputValueAndExecuteCommand();
        i++;
    }
    for(Counter_ui16=0; Counter_ui16< NUMBER_OF_CARDS_IN_DECK; Counter_ui16++)
    {
        if(SpaceCardsDeck_g_ui16[Counter_ui16] == 2019)
        printf("The position of 2019 is:%ld\n", Counter_ui16);
    }
    return 0;
}