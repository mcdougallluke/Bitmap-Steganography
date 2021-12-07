#include <stdio.h>
#include <stdlib.h>

/**********************************************************************/
/* Take 4 bytes from an unsigned char array and assemble them into an */
/* int where the first element of the array is the least significant  */
/* byte of the int.                                                   */
/**********************************************************************/
int getIntFromArray(unsigned char bytes[])
{
  int n =
    bytes[0] |
    bytes[1] << 8 |
    bytes[2] << 16 |
    bytes[3] << 24;
  return n;
}

int main(int argc, char** argv)
{
  char* infilename = argv[1];
  char* outfilename = argv[2];

  unsigned char header[54];
  unsigned char currentChar;

  FILE* in = fopen(infilename, "rb");
  FILE* out = fopen(outfilename, "wb");

  int pixelDataSize;
  int i;

  fread(header, 1, 54, in);
  pixelDataSize = getIntFromArray(&header[34]);
  currentChar = getchar();

  fwrite(header, 1, sizeof(header), out);

  for(i = 0; i < (pixelDataSize/4); i++)
  {
    unsigned char bytes[4];
    fread(bytes, 1, 4, in);

    if (currentChar == 0) fwrite(bytes, 1, 4, out);
    else
    {
      if (currentChar == 255) currentChar = 0;
      bytes[0] = ((currentChar >> 6) & 3) | ((bytes[0] >> 2) << 2);
      bytes[1] = ((currentChar >> 4) & 3) | ((bytes[1] >> 2) << 2);
      bytes[2] = ((currentChar >> 2) & 3) | ((bytes[2] >> 2) << 2);
      bytes[3] = (currentChar & 3) | ((bytes[3] >> 2) << 2);
      fwrite(bytes,1,4,out);
      currentChar = getchar();
    }
  }

  fclose(in);
  fclose(out);
  return 0;
}