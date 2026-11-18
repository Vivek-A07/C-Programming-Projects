#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#include "common.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "rb");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "rb");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "wb");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}


Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo )
{
    if ((strstr(argv[2], ".bmp")) != NULL )
    {
        encInfo->src_image_fname = argv[2];
        
        if ((strstr(argv[3], ".txt")) != NULL )
        {
            encInfo->secret_fname = argv[3];

            if (argv[4] == NULL)
            {
                encInfo->stego_image_fname = "default.bmp";
            }
            else if((strstr(argv[4], ".bmp")) != NULL)
            {
                encInfo->stego_image_fname = argv[4];
            }
            else
            {
                return e_failure;
            }
        }
        else
        {
            return e_failure;
        }
        
    }
    else
    {
        return e_failure;
    }

    return e_success;
}


Status do_encoding(EncodeInfo *encInfo)
{
    //Encode part
    //Open file

    if ((open_files(encInfo)) == e_success)
    {
        printf("Open file Successful\n");

        if((check_capacity(encInfo)) == e_success)
        {
            printf("Check capacity Successful\n");
            if((copy_bmp_header(encInfo->fptr_src_image, encInfo->fptr_stego_image)) == e_success)
            {   
                printf("Copy bmp header Successfull\n");

                if ((encode_magic_string(MAGIC_STRING, encInfo)) == e_success)
                {
                    printf("Encoding magic string Successfully\n");

                   // Fetch the extension and store it in the extension structure member
                    char *extn = strrchr(encInfo->secret_fname, '.');

                    if (extn != NULL)
                    {
                        strcpy(encInfo->extn_secret_file, extn);
                        encInfo->extn_size = strlen(encInfo->extn_secret_file);
                    }
                    else
                    {
                        return e_failure;
                    }


                    // Encode the extension size
                    if ((encode_secret_file_extn_size(encInfo->extn_secret_file, encInfo)) == e_success)
                    {
                        printf("Encoded extn size successfully\n");
                    }
                    else
                    {
                        return e_failure;
                    }
                    
                    if (encode_secret_file_extn(encInfo->extn_secret_file, encInfo) == e_success)
                    {
                        printf("Encoded secret file extension successfully\n");
                    }
                    else
                    {
                        return e_failure;
                    }

                    if (encode_secret_file_size(encInfo->size_secret_file, encInfo) == e_success)
                    {
                        printf("Encoded secret file size successfully\n");
                    }
                    else
                    {
                        return e_failure;
                    }

                    if (encode_secret_file_data(encInfo) == e_success)
                    {
                        printf("Encoded secret file data successfully\n");
                    }
                    else
                    {
                        return e_failure;
                    }

                    if (copy_remaining_img_data(encInfo->fptr_src_image,
                            encInfo->fptr_stego_image) == e_success)
                    {
                        printf("Copied remaining image data successfully\n");
                    }
                    else
                    {
                        return e_failure;
                    }
                }
                
            }
            else
            {
                return e_failure;
            }
        }
        else
        {
            return e_failure;
        }
    }
    else
    {
        return e_failure;
    }
    
    return e_success;
    //check capacity
    //copy the bmp header
    //Encode magic string
    //encode len of extn

}


Status check_capacity(EncodeInfo *encInfo)
{
    encInfo->image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);
    encInfo->size_secret_file = get_file_size(encInfo->fptr_secret);

    // encInfo->extn_size = strlen(encInfo->extn_secret_file);

    printf("Image size : %d\n", encInfo->image_capacity);
    printf("Sec file size : %ld\n", encInfo->size_secret_file);
    //find the extn size and store it in extn_size variable
    if (encInfo->image_capacity > (16 + 32 + (encInfo->extn_size * 8) + 32 + (encInfo->size_secret_file * 8)))
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
    
}

uint get_file_size(FILE *fptr)
{
    // set your file offset 0th position
    //find the size of the file and return the size

    rewind(fptr);                 
    fseek(fptr, 0, SEEK_END);     
    long size = ftell(fptr);

    rewind(fptr);
    return size;
}


Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    char arr[54];

    fseek(fptr_src_image, 0, SEEK_SET);

    if (fread(arr, 1, 54, fptr_src_image) != 54)
    {
        return e_failure;
    }

    if (fwrite(arr, 1, 54, fptr_dest_image) != 54)
    {
        return e_failure;
    }

    return e_success;
}


Status encode_byte_to_lsb(char data, char *image_buffer)
{
    unsigned char byte = (unsigned char)data;

    for (int i = 0; i < 8; i++)
    {
        if (byte & (1u << i))
        {
            image_buffer[i] = (image_buffer[i] & 0xFE) | 1;
        }
        else
        {
            image_buffer[i] = (image_buffer[i] & 0xFE) | 0;
        }
    }

    return e_success;
}

Status encode_int_to_lsb(int data, char *image_buffer)
{
    unsigned int value = (unsigned int)data;

    for (int i = 0; i < 32; i++)
    {
        if (value & (1u << i))
        {
            image_buffer[i] = (image_buffer[i] & 0xFE) | 1;
        }
        else
        {
            image_buffer[i] = (image_buffer[i] & 0xFE) | 0;
        }
    }

    return e_success;
}


Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    if ((encode_data_to_image(magic_string, strlen(magic_string),encInfo->fptr_src_image, encInfo->fptr_stego_image)) == e_success)
    {
        return e_success;
    }

    return e_failure;
}


Status encode_data_to_image(const char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image)
{
    char buffer[8];

    for (int i = 0; i < size; i++)
    {
        if (fread(buffer, 1, 8, fptr_src_image) != 8)
        {
            return e_failure;
        }

        if (encode_byte_to_lsb(data[i], buffer) != e_success)
        {
            return e_failure;
        }

        if (fwrite(buffer, 1, 8, fptr_stego_image) != 8)
        {
            return e_failure;
        }
    }
    return e_success;
}


Status encode_secret_file_extn_size(const char *file_extn, EncodeInfo *encInfo)
{
    // Find the length of the extension
    encInfo->extn_size = strlen(file_extn);

    // Declare a buffer of 32 bytes
    char buffer[32];

    // Read 32 bytes from source image
    if (fread(buffer, 32, 1, encInfo->fptr_src_image) != 1)
    {
        return e_failure;
    }

    // Encode extension size into the LSBs
    encode_int_to_lsb(encInfo->extn_size, buffer);

    // Write 32 bytes into the stego image
    if (fwrite(buffer, 32, 1, encInfo->fptr_stego_image) != 1)
    {
        return e_failure;
    }

    return e_success;
}

Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    if (encode_data_to_image(file_extn, strlen(file_extn),encInfo->fptr_src_image,encInfo->fptr_stego_image) == e_success)
    {
        return e_success;
    }

    return e_failure;
}

Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    char buffer[32];

    if (fread(buffer, 1, 32, encInfo->fptr_src_image) != 32)
    {
        return e_failure;
    }

    encode_int_to_lsb((int)file_size, buffer);

    if (fwrite(buffer, 1, 32, encInfo->fptr_stego_image) != 32)
    {
        return e_failure;
    }

    return e_success;
}



Status encode_secret_file_data(EncodeInfo *encInfo)
{
    char buffer[MAX_IMAGE_BUF_SIZE];

    for (long i = 0; i < encInfo->size_secret_file; i++)
    {
        char data;

        if (fread(&data, 1, 1, encInfo->fptr_secret) != 1)
        {
            printf("Failed to read secret file at byte %ld\n", i);
            return e_failure;
        }

        if (fread(buffer, 1, 8, encInfo->fptr_src_image) != 8)
        {
            printf("Failed to read source image at byte %ld\n", i);
            return e_failure;
        }

        if (encode_byte_to_lsb(data, buffer) != e_success)
        {
            printf("Failed to encode byte %ld\n", i);
            return e_failure;
        }

        if (fwrite(buffer, 1, 8, encInfo->fptr_stego_image) != 8)
        {
            printf("Failed to write stego image at byte %ld\n", i);
            return e_failure;
        }
    }

    return e_success;
}


Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    char ch;

    while (fread(&ch, 1, 1, fptr_src) == 1)
    {
        if (fwrite(&ch, 1, 1, fptr_dest) != 1)
        {
            return e_failure;
        }
    }

    if (ferror(fptr_src))
    {
        return e_failure;
    }

    return e_success;
}