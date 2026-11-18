# LSB Image Steganography

## Overview

A C-based image steganography project that hides secret text files inside BMP images using the Least Significant Bit (LSB) technique. The project supports both encoding secret data into an image and decoding the embedded data back into a file.

The program stores information such as a magic string, secret file extension, file size, and secret file contents within the image data, allowing the embedded message to be recovered during decoding.

## Features

- Encode secret files into BMP images using LSB encoding
- Decode and recover hidden file contents from stego images
- Embed and verify a magic string
- Store the secret file extension
- Store the secret file size
- Check image capacity before encoding
- Preserve and copy the BMP image header
- Support optional output filenames
- Command-line interface for encoding and decoding

## Technologies Used

- C Programming
- File Handling
- Bitwise Operations
- Structures
- Command-Line Arguments
- BMP Image File Handling

## Project Structure

```text
LSB-Image-Steganography/
├── encode.c
├── encode.h
├── decode.c
├── decode.h
├── common.h
├── types.h
├── test_encode.c
├── beautiful.bmp
├── default.bmp
├── secret.txt
└── decoded.txt
```

## Compilation

Compile all C source files using GCC:

```bash
gcc *.c -o lsb_steg
```

## Running the Project

### 1. Encoding

Encode the secret file into the source BMP image:

```bash
./lsb_steg -e beautiful.bmp secret.txt default.bmp
```

- `beautiful.bmp` – source image
- `secret.txt` – secret file to hide
- `default.bmp` – output stego image

### 2. Decoding

Extract the hidden data from the stego image:

```bash
./lsb_steg -d default.bmp decoded.txt
```

- `default.bmp` – image containing hidden data
- `decoded.txt` – output file containing recovered data

### 3. View the Decoded File

```bash
cat decoded.txt
```

### 4. Verify Encoding and Decoding

Compare the original secret file and decoded file:

```bash
cmp secret.txt decoded.txt
```

If the command produces no output, the files are identical, confirming successful encoding and decoding.

### 5. Check File Sizes

```bash
wc -c secret.txt decoded.txt
```

This displays the byte count of both files for comparison.

## Complete Testing Workflow

Run the following commands in sequence:

```bash
gcc *.c -o lsb_steg

./lsb_steg -e beautiful.bmp secret.txt default.bmp

./lsb_steg -d default.bmp decoded.txt

cat decoded.txt

cmp secret.txt decoded.txt

wc -c secret.txt decoded.txt
```

## How It Works

### Encoding Process

1. Open the source BMP image and secret file.
2. Check the available image capacity.
3. Copy the BMP header to the output image.
4. Encode the magic string.
5. Encode the secret file extension.
6. Encode the secret file size.
7. Encode the secret file data into image bits.
8. Copy the remaining image data to complete the stego image.

### Decoding Process

1. Open the stego image and output file.
2. Read and verify the embedded magic string.
3. Decode the secret file extension size.
4. Recover the secret file extension.
5. Recover the secret file size.
6. Extract the secret file data.
7. Write the recovered data to the output file.

## Learning Outcomes

- Understanding bitwise operations and LSB manipulation
- Practicing binary file handling in C
- Working with BMP image data
- Implementing file encoding and decoding
- Using structures to organize program data
- Handling command-line arguments
- Managing file operations and validation

## Author

**Vivek**

Embedded Systems | C Programming | Firmware Development
