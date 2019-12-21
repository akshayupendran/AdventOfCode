/**************************************************************************
 Author: Akshay Krishna Upendran
 BUILD COMMAND: Windows -> gcc %1 -Wall -Wextra -pedantic-errors -o %1.exe
                Linux   -> gcc %1 -Wall -Wextra -pedantic-errors -o %1
***************************************************************************/


/* Headers */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <openssl/evp.h>
/* Defines */
#define BLOCK_SIZE 256

/* Variables */
static FILE *fp;
/* Keep Message digest in a global array */
static unsigned char MdValue_uc_g[16384][32];
static long int counter_g=0;


/* Declarations */
void cleanup();
void CalculateSha256HashOverData(char *Message2Hash, unsigned char *MdValue, int SizeOfMessage);

void cleanup()
{
    if(0 != fclose(fp))
    {
        exit(EXIT_FAILURE);
    }
}

void CalculateSha256HashOverData(char *Message2Hash, unsigned char *MdValue, int SizeOfMessage)
{
    /* Refer man EVP_DigestInit for the reasoning out of following code */
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned int md_len;
    uint8_t i;
    
    /* Mutex Lock from here -> Critical Section */
    md = EVP_get_digestbyname("sha256");
    if (md == NULL) {
        printf("Unknown message digest %s\n", "sha256");
        exit(1);
    }

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    
    EVP_DigestUpdate(mdctx, Message2Hash, SizeOfMessage);
    EVP_DigestFinal_ex(mdctx, MdValue, &md_len);
    EVP_MD_CTX_free(mdctx);

    printf("Digest is: ");
    for (i = 0; i < md_len; i++)
        printf("%02x", MdValue[i]);
    printf("\n");
}

int main(int argc, char**argv)
{
    uint8_t MbCounter_ui08, NumberOfChunks_ui08;
    uint16_t KbCounter_ui16;
    int RetVal_i=1;
	char ReadBlockFromFile_c[BLOCK_SIZE+1];
    /* Check Input Arguments */
    if(2 != argc)
    {
        printf("No arguments / one argument _FILENAME_ needed");
        return EXIT_FAILURE;
    }
    
    fp = fopen(argv[1], "rb");
    if(fp == NULL)
    {
        perror("Failed to read file");
        exit(EXIT_FAILURE);
    }
    /* Register callback to cleanup on any kind of closure*/
    RetVal_i = atexit(cleanup);
    if (RetVal_i != 0)
    {
       fprintf(stderr, "cannot set exit function\n");
       exit(EXIT_FAILURE);
    }
    
	/* Run over 1M*4 = 4M */
    for(MbCounter_ui08=0; MbCounter_ui08<4; MbCounter_ui08++)
    {
        /* Run over 1k*1k = 1M */
        for(KbCounter_ui16=0;KbCounter_ui16<1024;KbCounter_ui16++)
        {
            /* Run over 256 * 4 bytes = 1k */
            for(NumberOfChunks_ui08=0; NumberOfChunks_ui08<4; NumberOfChunks_ui08++)
            {
				/* Read 256 bytes from file */
                fgets(ReadBlockFromFile_c, BLOCK_SIZE, fp);
				/* Hash the 256 bytes and store it in global array */
                CalculateSha256HashOverData(ReadBlockFromFile_c, MdValue_uc_g[counter_g], BLOCK_SIZE);
                counter_g++;
                printf("Current Counter Value is: %ld\n", counter_g);
            }
        }
    }
	
    return EXIT_SUCCESS;
}