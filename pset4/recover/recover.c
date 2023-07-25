#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        return 1;
    }

    BYTE buffer[512];
    int name = -1;
    char output[8];
    FILE *image;

    while (fread(buffer, 1, 512, file) == 512)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (name != -1)
            {
                fclose(image);
            }
            name++;

            sprintf(output, "%03i.jpg", name);
            image = fopen(output, "w");

            fwrite(buffer, 1, 512, image);
        }
        else if (name > -1)
        {
            fwrite(buffer, 1, 512, image);
        }
    }
    fclose(image);
    fclose(file);
}