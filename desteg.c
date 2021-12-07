#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  char* infilename = argv[1];

  unsigned char header[54];
  unsigned char output = 'a';

  FILE* in = fopen(infilename, "rb");

  fread(header, 1, 54, in);

  while (output != 0)
  {
    unsigned char bytes[4];

    fread(bytes, 1, 4, in);

    bytes[0] = (bytes[0] << 6) & 0xC0;
    bytes[1] = (bytes[1] << 4) & 0x30;
    bytes[2] = (bytes[2] << 2) & 0xC;
    bytes[3] = bytes[3] & 0x3;

    output = bytes[0] | bytes[1] | bytes[2] | bytes[3];

    if (output==0);
    else printf("%c",output);
  }

  fclose(in);
  return 0;
}