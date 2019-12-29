#include <openssl/evp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define ENABLE_PART_ONE
#define ENABLE_PART_TWO

FILE* fp;

void cleanup()
{
    fclose(fp);
}

void MainProcess()
{
    /* Refer man EVP_DigestInit for the reasoning out of following code */
    char          Message2Hash[10000];
    uint64_t      a = 0;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    EVP_MD_CTX*   mdctx;
    const EVP_MD* md;
    unsigned int  md_len;
    uint8_t       i, b = 0;
    md = EVP_get_digestbyname("md5");
    if (md == NULL)
    {
        printf("Unknown message digest %s\n", "md5");
        exit(1);
    }

    do
    {
        b = 0;
        sprintf(Message2Hash, "iwrupvqb%lu", a);
        mdctx = EVP_MD_CTX_new();
        EVP_DigestInit_ex(mdctx, md, NULL);
        EVP_DigestUpdate(mdctx, Message2Hash, strlen(Message2Hash));
        EVP_DigestFinal_ex(mdctx, md_value, &md_len);
        EVP_MD_CTX_free(mdctx);
#ifndef ENABLE_PART_TWO
#ifdef ENABLE_PART_ONE
        for (i = 0; i < 2; i++)
#endif
#endif
#ifdef ENABLE_PART_TWO
            for (i = 0; i < 3; i++)
#endif
            {
                if (0 == md_value[i])
                {
                    b++;
                }
            }
#ifdef ENABLE_PART_ONE
        if (md_value[i] < 16)
        {
            b++;
        }
#endif
        a++;
    } while (b != 3);
    printf("%lu\n", a - 1);
}

int main()
{
#if ((defined ENABLE_PART_ONE) || (defined ENABLE_PART_TWO))
    MainProcess();
#else
#error Either ENABLE_PART_ONE or ENABLE_PART_TWO must be defined!!
#endif

    return 0;
}
