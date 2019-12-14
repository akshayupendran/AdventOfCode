#include <stdio.h>
#include <stdlib.h>

/* Let us create a structure as follows:
    A "Name" which contains the chemical name.
    The "number" of such chemicals needed in the reaction
    The "NextChemical" that its going to react with.
    In case of an output the "NextChemical" becomes NULL */
// typedef struct
// {
    // char *Name;
    // unsigned int Number;
    // int IsOutput;
// }Element;

int main(int argc, char **argv)
{
    /* Dynamically have an array as we do not know how many elements is
        required in the input file */
    // struct Element *ElementList;
    /* File Pointer which contains the input file */
    FILE *fp;
    // char s;
    
    if(argc!=2)
    {
        printf("Please enter exactly one Input File Name");
        return EXIT_FAILURE;
    }
    
    /* Open File called Input.txt with r only mode
        and stream positioned at begining*/
    fp = fopen("Input.txt", "r");
    // if(fp == NULL)
    // {
        // perror("Main:opening of Input.txt->");
        // return EXIT_FAILURE;
    // }
    
    /* Create and Read first Element -> Assuming it surely exists*/
    // ElementList = malloc(1*sizeof(Element));
    // if(ElementList == NULL)
    // {
        // perror("Main:Allocating 1st Memory for Element List");
        // return EXIT_FAILURE;
    // }
    // if(EOF != fscanf("%d %s", ElementList->Number, ElementList->Name))
    
    /* Cleanup */
    if(0 != fclose(fp))
    {
        perror("Main:Closig of Input.txt->");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}