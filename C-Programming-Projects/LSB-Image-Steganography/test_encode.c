#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#include "decode.h"

int main(int argc, char *argv[])
{
    EncodeInfo encode;
    DecodeInfo decode;

    int ret = check_operation_type(argv);

    if (ret == e_encode)
    {
        if (argc < 4 || argc > 5)
        {
            printf("Usage: ./lsb_steg -e source.bmp secret.txt [output.bmp]\n");
            return 1;
        }

        printf("Selected Encoding\n");

        if (read_and_validate_encode_args(argv, &encode) == e_success)
        {
            printf("Read and Validate Success\n");

            if (do_encoding(&encode) == e_success)
                printf("Encoding Successful\n");
            else
                printf("Encoding Failed\n");
        }
        else
        {
            printf("Read and Validate Failure\n");
            return 1;
        }
    }
    else if (ret == e_decode)
    {
        if (argc != 3 && argc != 4)
        {
            printf("Usage: ./lsb_steg -d stego.bmp [output.txt]\n");
            return 1;
        }

        printf("Selected Decoding\n");

        if (read_and_validate_decode_args(argv, &decode) == e_success)
        {
            if (do_decoding(&decode) == e_success)
                printf("Decoding Successful\n");
            else
                printf("Decoding Failed\n");
        }
        else
        {
            printf("Decode argument validation failed\n");
            return 1;
        }
    }
    else
    {
        printf("Invalid option\n");
        return 1;
    }

   
   return 0;
}

OperationType check_operation_type(char *argv[])
{
    if ((strcmp(argv[1],"-e")) == 0 )
    {
        return e_encode;
    }
    else if ((strcmp(argv[1],"-d")) == 0)
    {
        return e_decode;
    }

    return e_unsupported;
    
}
