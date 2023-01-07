#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //check if there is one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./image.raw\n");
        return 1;
    }

    //open files and raises error if can't be opened
    char *raw_file_name = argv[1];
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Could not open %s.\n", raw_file_name);
        return 1;
    }

    //variables to read raw file and create new jpg files
    typedef uint8_t BYTE;
    int block_size = sizeof(BYTE) * 512;
    BYTE buffer[block_size];
    char jpg_file_to_write_name[8];
    FILE *jpg_file_to_write;
    int jpgs_found = -1;

    while (fread(buffer, 1, block_size, raw_file) == block_size)
    {
        //bytes that show a new jpg is starting
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            jpgs_found += 1;

            //first jpeg found just create a new file to write
            if (jpgs_found == 0)
            {
                sprintf(jpg_file_to_write_name, "%03i.jpg", jpgs_found);
                jpg_file_to_write = fopen(jpg_file_to_write_name, "w");
            }

            //subsequent jpegs found closes last file and creates new files
            else if (jpgs_found > 0)
            {
                fclose(jpg_file_to_write);
                sprintf(jpg_file_to_write_name, "%03i.jpg", jpgs_found);
                jpg_file_to_write = fopen(jpg_file_to_write_name, "w");
            }
        }

        //if at least 1 jpeg was found start writing
        //there is no need to stop write because jpgs are contiguous in file with padded 0 between then
        if (jpgs_found >= 0)
        {
            fwrite(buffer, 1, block_size, jpg_file_to_write);
        }
    }

    //if jpgs were found close last file
    if (jpgs_found >= 0)
    {
        fclose(jpg_file_to_write);
    }
    //close raw file
    fclose(raw_file);
}