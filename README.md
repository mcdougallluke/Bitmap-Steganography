# CS 241 Data Organization using C

# Lab 8: Bitmap Steganography

### Brooke Chenoweth

### Fall 2021

## 1 Steganography

Steganography^1 is the practice of concealing a secret message within another message. In
this assignment, you will hide a secret message text in the pixels of a bitmap image.

## 2 BMP File Format

The image files used in this assignment will use 24 bits/pixel encoding with a 54 byte header.^2
The secret message will be hidden in the lowest two bits of each byte in the pixel data.
I have provided you with a couple of example programs to read and write the BMP file
format. You will likely find these useful, in particular for an example of extracting the pixel
data size from the file header.

## 3 Program Requirements

For this assignment, you will write two programs, one to hide a message text in the pixels
of a bitmap file and one to extract the secret text from a bitmap generated in this manner.

### 3.1 Hiding the message

A character of the secret message will be hidden in the lowest two bits of four consecutive
bytes of the pixel data. (These bytes will include both RGB values and row padding bytes.)
If the bits of a single character of the secret message areABCDEFGH, where H is the least
significant bit, the bytes of the image pixels will be modified as follows.
Original Bytes: abcdefgh ijklmnop qrstuvwx yz
Modified Bytes: abcdefAB ijklmnCD qrstuvEF yz0123GH
This will result in the colors of the pixels to be slightly changed, but not enough to be
noticable to the eye.

(^1) Seehttps://en.wikipedia.org/wiki/Steganography
(^2) See Example 1 athttps://en.wikipedia.org/wiki/BMP_file_format


### 3.2 steg

The program insteg.cwill take two command line arguments, the first specifies the input
image file name and second is the name of the file to generate. The secret message text will
be read from standard input.
The output file’s header will be identical to the input file’s header, since the size of the
image will be the same.
Each character of the secret message will be hidden the lowest two bits of four consecutive
bytes of the pixel data. (These bytes will include both RGB values and row padding bytes.)
After the last character from the message, encode a null character. (That is, encode a zero
byte rather than an EOF value). If you have processed the entire secret message before
reaching the end of the pixel data, copy the remaining bytes to the output file unchanged.

### 3.3 desteg

The program indesteg.ctakes one command line argument, the filename of the image file
containing the hidden message. It will print the message to standard output.
Each character of the secret message will be hidden the lowest two bits of four consecutive
bytes of the pixel data. (These bytes will include both RGB values and row padding bytes.)
As you extract each hidden character, print it to standard output. When you decode a null
character, you have reached the end of the secret message and should not continue extracting
characters past that point.

## 4 Turning in your assignment

Submit yoursteg.canddesteg.cto UNM Learn.

## 5 Grading Rubric (total of 30 points)

-5 point : The programs do not start with a comment stating the students first and last
name and/or the source files are not named correctly.

-5 points: Programs compile with warnings on moons.cs.unm.edu using/usr/bin/gccwith
the-Wall -ansi -pedanticoptions.

5 points: Follows CS-241 Coding Standard: including quality, quantity and neatness of
comments, no dead code, and Best Practices (functions not being too long, nestings
not needlessly deep, and avoidance of duplicate code).

10 points:Bitmap image file created bystegmatches expected output for each the follow-

```
ing tests. (5 points each)
./steg ralph.bmp myout.bmp < catpoem.txt
./steg stego.bmp myout.bmp < lostworld.txt
```
10 points:Extracted secret message found bydestegmatches expected output for each

```
the following tests. (5 points each)
```
```
./desteg ralph-poem.bmp > myout.txt
./desteg stego-book.bmp > myout.txt
```

5 points: Extracted message found bydestegmatches expected secret message hidden in
mystery.bmp


