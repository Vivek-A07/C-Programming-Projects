#include <stdio.h>
#include <string.h>
#include "decode.h"
#include "common.h"

Status do_decoding(DecodeInfo *decInfo)
{
    printf("Selected Decoding\n");

    if (open_decode_files(decInfo) == e_failure)
    {
        printf("Failed to open files\n");
        return e_failure;
    }

    printf("Files opened successfully\n");

    if (decode_magic_string(decInfo) == e_failure)
    {
        printf("Magic string decoding failed\n");
        return e_failure;
    }

    printf("Magic string decoded successfully\n");

    if (decode_secret_file_extn_size(decInfo) == e_failure)
    {
        printf("Extension size decoding failed\n");
        return e_failure;
    }

    printf("Extension size decoded successfully\n");

 
    if (decode_secret_file_extn(decInfo) == e_failure)
    {
        printf("Extension decoding failed\n");
        return e_failure;
    }

    printf("Extension decoded successfully\n");
    
    
    if (decode_secret_file_size(decInfo) == e_failure)
    {
        printf("Secret file size decoding failed\n");
        return e_failure;
    }

    printf("Secret file size decoded successfully\n");

 
    if (decode_secret_file_data(decInfo) == e_failure)
    {
        printf("Secret file data decoding failed\n");
        return e_failure;
    }

    printf("Secret file data decoded successfully\n");
    

    return e_success;
}


Status open_decode_files(DecodeInfo *decInfo)
{
    decInfo->fptr_stego_image = fopen(decInfo->stego_image_fname, "rb");

    if (decInfo->fptr_stego_image == NULL)
    {
        perror("fopen stego image");
        return e_failure;
    }

    decInfo->fptr_output = fopen(decInfo->output_fname, "wb");

    if (decInfo->fptr_output == NULL)
    {
        perror("fopen output file");
        fclose(decInfo->fptr_stego_image);
        decInfo->fptr_stego_image = NULL;
        return e_failure;
    }

    return e_success;
}

Status decode_byte_from_lsb(char *image_buffer, char *data)
{
    *data = 0;

    for (int i = 0; i < 8; i++)
    {
        *data |= (image_buffer[i] & 1) << i;
    }

    return e_success;
}

Status decode_int_from_lsb(char *image_buffer, int *data)
{
    unsigned int value = 0;

    for (int i = 0; i < 32; i++)
    {
        value |= (unsigned int)(image_buffer[i] & 1) << i;
    }

    *data = (int)value;

    return e_success;
}

Status decode_magic_string(DecodeInfo *decInfo)
{
    char image_buffer[8];
    char decoded_char;

     
    fseek(decInfo->fptr_stego_image, 54, SEEK_SET);

    for (size_t i = 0; i < strlen(MAGIC_STRING); i++)
    {
        if (fread(image_buffer, 1, 8, decInfo->fptr_stego_image) != 8)
        {
            return e_failure;
        }

        decode_byte_from_lsb(image_buffer, &decoded_char);

        if (decoded_char != MAGIC_STRING[i])
        {
            return e_failure;
        }
    }
    printf("Magic string decoded successfully!\n");
    return e_success;
}


Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)
{
    
    decInfo->stego_image_fname = argv[2];

     
    if (argv[3] != NULL)
    {
        decInfo->output_fname = argv[3];
    }
    else
    {
        decInfo->output_fname = "decoded.txt";
    }

    return e_success;
}


Status decode_secret_file_extn_size(DecodeInfo *decInfo)
{
    char image_buffer[32];
    int extn_size;

    if (fread(image_buffer, 1, 32, decInfo->fptr_stego_image) != 32)
    {
        return e_failure;
    }

    if (decode_int_from_lsb(image_buffer, &extn_size) == e_failure)
    {
        return e_failure;
    }

    decInfo->extn_size = extn_size;

    printf("Decoded extension size: %u\n", decInfo->extn_size);

    return e_success;
}


Status decode_secret_file_extn(DecodeInfo *decInfo)
{
    char image_buffer[8];
    char decoded_char;

    for (int i = 0; i < decInfo->extn_size; i++)
    {
        if (fread(image_buffer, 1, 8, decInfo->fptr_stego_image) != 8)
        {
            return e_failure;
        }

        if (decode_byte_from_lsb(image_buffer, &decoded_char) == e_failure)
        {
            return e_failure;
        }

        decInfo->extn_secret_file[i] = decoded_char;
    }

    decInfo->extn_secret_file[decInfo->extn_size] = '\0';

    printf("Decoded extension: %s\n", decInfo->extn_secret_file);

    return e_success;
}


 
Status decode_secret_file_size(DecodeInfo *decInfo)
{
    char image_buffer[32];
    int file_size;

    if (fread(image_buffer, 1, 32, decInfo->fptr_stego_image) != 32)
    {
        return e_failure;
    }

    if (decode_int_from_lsb(image_buffer, &file_size) == e_failure)
    {
        return e_failure;
    }

    decInfo->size_secret_file = file_size;

    printf("Decoded secret file size: %ld bytes\n",decInfo->size_secret_file);

    return e_success;
}
 


Status decode_secret_file_data(DecodeInfo *decInfo)
{
    char image_buffer[8];
    char decoded_char;

    for (long i = 0; i < decInfo->size_secret_file; i++)
    {
        if (fread(image_buffer, 1, 8, decInfo->fptr_stego_image) != 8)
        {
            return e_failure;
        }

        if (decode_byte_from_lsb(image_buffer, &decoded_char) == e_failure)
        {
            return e_failure;
        }

        if (fwrite(&decoded_char, 1, 1, decInfo->fptr_output) != 1)
        {
            return e_failure;
        }
    }

    return e_success;
}
