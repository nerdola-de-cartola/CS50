#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int SIZE_BLOCK = 512;

int main(int argc, char *argv[])
{
    //If missing arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    else
    {
        FILE *memoryCard = fopen(argv[1], "r");
        FILE *img;

        char *fileName = malloc(sizeof(BYTE) * 8);
        int fileCount = 0;
        BYTE buffer[SIZE_BLOCK];

        //While the current block is full of bytes
        while (fread(&buffer, sizeof(BYTE), SIZE_BLOCK, memoryCard))
        {
            //The current block is a new JPEG
            if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 && (buffer[3] & 240) == 224)
            {
                //It's the first JPEG
                if (fileCount == 0)
                {
                    //Update the file name
                    sprintf(fileName, "%03i.jpg", fileCount);

                    //Open a new JPEG
                    img = fopen(fileName, "w");

                    //Write into the new JPEG
                    fwrite(buffer, SIZE_BLOCK, 1, img);
                }
                //It's not the first JPEG
                else
                {
                    //Close the old JPEG
                    fclose(img);

                    //Update the file name
                    sprintf(fileName, "%03i.jpg", fileCount);

                    //Open a new JPEG
                    img = fopen(fileName, "w");

                    //Write into the new JPEG
                    fwrite(buffer, SIZE_BLOCK, 1, img);
                }

                //Update the file count
                fileCount++;
            }
            //The current block is part of the current JPEG
            else if (fileCount > 0)
            {
                //Keep writing into the current JPEG
                fwrite(buffer, SIZE_BLOCK, 1, img);
            }
        }

        //Free memory
        free(fileName);
        fclose(memoryCard);
        fclose(img);

        return 0;
    }
}