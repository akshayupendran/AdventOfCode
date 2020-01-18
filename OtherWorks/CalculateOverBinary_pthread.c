/* Headers */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
/* High Level OpenSSL Header */
#include <openssl/evp.h>
/* Use Low Level header in extreme case*/
/* #include <openssl/sha.h> */
#include <pthread.h>

/* Configuration Defines */
/* #define CREATE_BINARY_FILE */
#define MAX_CORES 8

/* Variables */
static FILE *fp;
static unsigned char md_value_global[16384][32];
static long int counter=-1;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_t *thread_group;

/* Declarations */
#ifdef CREATE_BINARY_FILE
void CreateBinaryFile(char *argv);
#endif
void cleanup();
void Hash256Bytes(char *Message2Hash, unsigned char *md_value, int SizeOfMessage);

/* Implementations */
#ifdef CREATE_BINARY_FILE
void CreateBinaryFile(char *argv)
{
    uint16_t j,k;
    uint8_t i=1, l;
    fp = fopen(argv, "wb");
    if(fp == NULL)
    {
        perror("Failed to create file");
        exit(EXIT_FAILURE);
    }
    /* Write 4MB byte by byte -> just do somw junk way not useful code*/
    for(l=0; l<4; l++)
    {
        /* Write 1 MB */
        for(k=0; k<1024; k++)
        {
            /* Write 1KB */
            for(j=0; j<1024; j++)
            {
                fprintf(fp, "%d", i);
            }
        }
    }
    if(0 != fclose(fp))
    {
        exit(EXIT_FAILURE);
    }
}    
#endif

void cleanup()
{
    if(0 != fclose(fp))
    {
        exit(EXIT_FAILURE);
    }
    free(thread_group);
}

void Hash256Bytes(char *Message2Hash, unsigned char *md_value, int SizeOfMessage)
{
    printf("Current Counter Value is: %ld\n", counter);
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
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);

    printf("Digest is: ");
    for (i = 0; i < md_len; i++)
        printf("%02x", md_value[i]);
    printf("\n");
}

void *start_hashing(void* arg)
{
    char a[257];
    pthread_mutex_lock(&mutex);
    fgets(a, 256, fp);
    counter++;
    pthread_mutex_unlock(&mutex);
    Hash256Bytes(a, md_value_global[counter], 256);
    return NULL;
}

int main(int argc, char**argv)
{
    int i;
    uint16_t k;
    uint8_t j,l;
    // char b[65];
    // long int m;
    
    /* Check Input Arguments */
    if(2 != argc)
    {
        printf("No arguments / one argument _FILENAME_ needed");
        return EXIT_FAILURE;
    }
    
    #ifdef CREATE_BINARY_FILE
    CreateBinaryFile(argv[1]);  
    #endif
    
    fp = fopen(argv[1], "rb");
    if(fp == NULL)
    {
        perror("Failed to create file");
        exit(EXIT_FAILURE);
    }
    /* Register callback to cleanup on any kind of closure*/
    i = atexit(cleanup);
    if (i != 0)
    {
       fprintf(stderr, "cannot set exit function\n");
       exit(EXIT_FAILURE);
    }
    //Create a thread group the size of MAX_CORES
    thread_group= malloc(sizeof(pthread_t) * MAX_CORES);
    /* Start Actual Implementation via for loop so that it will easier to migrate to pthread in future*/
    /* Run over 4 M */
    for(j=0; j<4; j++)
    {
        /* Run over 2k*0.5k = 1M */
        for(k=0;k<512;k++)
        {
            /* Run over 256 * 8 bytes = 2k */
            // start all threads
            for(l=0; l<MAX_CORES; l++)
            {
                pthread_create(&thread_group[i], NULL, start_hashing, NULL);
            }
            // wait for all threads to sync up
            for(l=0; l<MAX_CORES; l++)
            {
                pthread_join(thread_group[i], NULL);
            }
        }
    }
 
    // Implemenation to be confirmed with baliga
    // /* Now we have all hashes -> lets Hash the hashes */
    // for(; counter/2 !=0;)
    // {
        // for(m=0; m<16384;m+=2)
        // {
            // printf("Counter Value now is:%ld and m is %ld\n", counter, m);
            // memcpy(b, md_value_global[m], 32);
            // strncat(b, (char*)md_value_global[m+1], 32);
            // Hash256Bytes(b, md_value_global[m], 64);
        // }
        // counter = counter/2;
    // }
    /* we will have m/2 hashes till now */
    return EXIT_SUCCESS;
}