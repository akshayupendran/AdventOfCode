/* Headers */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Configurations */
/* #define NUMBER_OF_CARDS_IN_DECK 10007u */
#define NUMBER_OF_CARDS_IN_DECK      10

/* Variables */
uint16_t SpaceCardsDeck_g_ui16[NUMBER_OF_CARDS_IN_DECK];


/* Declarations */
void PrintDeck();
void FactoryOrder();
void DealIntoNewStack();

void PrintDeck()
{
    uint16_t Counter_ui16=0;
    for(Counter_ui16=0; Counter_ui16< NUMBER_OF_CARDS_IN_DECK; Counter_ui16++)
    {
        printf("%d\n", SpaceCardsDeck_g_ui16[Counter_ui16]);
    }
}

void FactoryOrder()
{
    uint16_t Counter_ui16;
    for(Counter_ui16=0; Counter_ui16< NUMBER_OF_CARDS_IN_DECK; Counter_ui16++)
    {
        SpaceCardsDeck_g_ui16[Counter_ui16] = Counter_ui16;
    }
}

void DealIntoNewStack()
{
    uint16_t Counter_ui16;
    uint16_t SpaceCardsDeckTemp_ui16[NUMBER_OF_CARDS_IN_DECK];
    
    for(Counter_ui16=0; Counter_ui16< NUMBER_OF_CARDS_IN_DECK; Counter_ui16++)
    {
        SpaceCardsDeckTemp_ui16[Counter_ui16]=SpaceCardsDeck_g_ui16[NUMBER_OF_CARDS_IN_DECK-1-Counter_ui16];
        printf("%d\n", SpaceCardsDeckTemp_ui16[Counter_ui16]);
    }
    (void) memcpy(SpaceCardsDeck_g_ui16, SpaceCardsDeckTemp_ui16, NUMBER_OF_CARDS_IN_DECK*sizeof(uint16_t));
}

int main()
{
    FactoryOrder();
    DealIntoNewStack();
    printf("\n Current Deck After DealWithIncrementN is:\n");
    PrintDeck();
    
    return 0;
}