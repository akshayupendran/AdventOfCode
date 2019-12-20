/**************************************************************************
 Author: Akshay Krishna Upendran
 BUILD COMMAND: Windows -> gcc %1 -Wall -Wextra -pedantic-errors -o %1.exe
                Linux   -> gcc %1 -Wall -Wextra -pedantic-errors -o %1
***************************************************************************/


/* Headers */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/* Openssl is not readily available in windows */
/* Windows expects us to use CNG */
/* https://docs.microsoft.com/en-us/windows/win32/seccng/cng-portal */
/* https://docs.microsoft.com/en-us/windows/win32/seccng/creating-a-hash-with-cng */
#include <windows.h>
#include <bcrypt.h>

/* Configuration Defines */
/* #define CREATE_BINARY_FILE */

/* Variables */
static FILE *fp;

/* Declarations */
#ifdef CREATE_BINARY_FILE
void CreateBinaryFile(char *argv);
#endif
void cleanup();

/* Implementations */
#ifdef CREATE_BINARY_FILE
void CreateBinaryFile(char *argv)
{
    uint16_t KbCounter_ui16, ByteCounter_ui16;
    uint8_t Value2Write_ui08=0, MbCounter_ui08;
    fp = fopen(argv, "wb");
    if(fp == NULL)
    {
        perror("Failed to create file");
        exit(EXIT_FAILURE);
    }
    /* Write 4MB byte by byte -> just do somw junk way not useful code*/
    for(MbCounter_ui08=0; MbCounter_ui08<4; MbCounter_ui08++)
    {
        /* Write 1 MB */
        for(KbCounter_ui16=0; KbCounter_ui16<1024; KbCounter_ui16++)
        {
            /* Write 1KB */
            for(ByteCounter_ui16=0; ByteCounter_ui16<1024; ByteCounter_ui16++)
            {
                fprintf(fp, "%d", Value2Write_ui08);
                if(Value2Write_ui08!=9)
                {
                    Value2Write_ui08++;
                }
                else
                {
                    Value2Write_ui08=0;
                }
            }
        }
    }
    if(0 != fclose(fp))
    {
        exit(EXIT_FAILURE);
    }
}    
#endif

void CalculateSHA256()
{
    BCRYPT_ALG_HANDLE       hAlg            = NULL;
    BCRYPT_HASH_HANDLE      hHash           = NULL;
    NTSTATUS                status          = STATUS_UNSUCCESSFUL;
    DWORD                   cbData          = 0,
                            cbHash          = 0,
                            cbHashObject    = 0;
    PBYTE                   pbHashObject    = NULL;
    PBYTE                   pbHash          = NULL;

    //open an algorithm handle
    if(!NT_SUCCESS(status = BCryptOpenAlgorithmProvider(
                                                &hAlg,
                                                BCRYPT_SHA256_ALGORITHM,
                                                NULL,
                                                0)))
    {
        wprintf(L"**** Error 0x%x returned by BCryptOpenAlgorithmProvider\n", status);
        goto Cleanup;
    }

    //calculate the size of the buffer to hold the hash object
    if(!NT_SUCCESS(status = BCryptGetProperty(
                                        hAlg, 
                                        BCRYPT_OBJECT_LENGTH, 
                                        (PBYTE)&cbHashObject, 
                                        sizeof(DWORD), 
                                        &cbData, 
                                        0)))
    {
        wprintf(L"**** Error 0x%x returned by BCryptGetProperty\n", status);
        goto Cleanup;
    }

    //allocate the hash object on the heap
    pbHashObject = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbHashObject);
    if(NULL == pbHashObject)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;
    }

   //calculate the length of the hash
    if(!NT_SUCCESS(status = BCryptGetProperty(
                                        hAlg, 
                                        BCRYPT_HASH_LENGTH, 
                                        (PBYTE)&cbHash, 
                                        sizeof(DWORD), 
                                        &cbData, 
                                        0)))
    {
        wprintf(L"**** Error 0x%x returned by BCryptGetProperty\n", status);
        goto Cleanup;
    }

    //allocate the hash buffer on the heap
    pbHash = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbHash);
    if(NULL == pbHash)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;
    }

    //create a hash
    if(!NT_SUCCESS(status = BCryptCreateHash(
                                        hAlg, 
                                        &hHash, 
                                        pbHashObject, 
                                        cbHashObject, 
                                        NULL, 
                                        0, 
                                        0)))
    {
        wprintf(L"**** Error 0x%x returned by BCryptCreateHash\n", status);
        goto Cleanup;
    }
    

    //hash some data
    if(!NT_SUCCESS(status = BCryptHashData(
                                        hHash,
                                        (PBYTE)rgbMsg,
                                        sizeof(rgbMsg),
                                        0)))
    {
        wprintf(L"**** Error 0x%x returned by BCryptHashData\n", status);
        goto Cleanup;
    }
    
    //close the hash
    if(!NT_SUCCESS(status = BCryptFinishHash(
                                        hHash, 
                                        pbHash, 
                                        cbHash, 
                                        0)))
    {
        wprintf(L"**** Error 0x%x returned by BCryptFinishHash\n", status);
        goto Cleanup;
    }

    wprintf(L"Success!\n");

Cleanup:

    if(hAlg)
    {
        BCryptCloseAlgorithmProvider(hAlg,0);
    }

    if (hHash)    
    {
        BCryptDestroyHash(hHash);
    }

    if(pbHashObject)
    {
        HeapFree(GetProcessHeap(), 0, pbHashObject);
    }

    if(pbHash)
    {
        HeapFree(GetProcessHeap(), 0, pbHash);
    }

}

void cleanup()
{
    if(0 != fclose(fp))
    {
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char**argv)
{
    uint8_t MbCounter_ui08, NumberOf256bytesChunk_ui08;
    uint16_t KbCounter_ui16;
    int RetVal_i=1;
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
    
    for(MbCounter_ui08=0; MbCounter_ui08<4; MbCounter_ui08++)
    {
        /* Run over 1k*1k = 1M */
        for(KbCounter_ui16=0;KbCounter_ui16<1024;KbCounter_ui16++)
        {
            /* Run over 256 * 4 bytes = 1k */
            for(NumberOf256bytesChunk_ui08=0; NumberOf256bytesChunk_ui08<4; NumberOf256bytesChunk_ui08++)
            {
                /* fgets(a, 256, fp);
                Hash256Bytes(a, md_value_global[counter], 256);
                counter++;
                printf("Current Counter Value is: %ld\n", counter); */
            }
        }
    }
    return EXIT_SUCCESS;
}