#include <stddef.h>
#include <stdio.h>

int countlines(int *lines, char* filename)
{
    // Open the file in read mode
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    char buf[65536];  // Buffer to read chunks of the file
    for (;;) {
        size_t res = fread(buf, 1, sizeof(buf), file);
        if (ferror(file)) {
            printf("Error: Reading error in file %s\n", filename);
            fclose(file);
            return 1;
        }

        // Count newlines in the buffer
        for (size_t i = 0; i < res; i++) {
            if (buf[i] == '\n') {
                (*lines)++;
            }
        }

        // Break loop if end of file
        if (feof(file))
            break;
    }

    // Close the file after reading
    fclose(file);

    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Error: no files provided\n");
        return 1;
    }

    int lines = 0;

    // Loop through each file argument
    for (int i = 1; i < argc; i++) {
        if (countlines(&lines, argv[i]) != 0) {
            printf("Failed to count lines for file: %s\n", argv[i]);
        }
    }

    printf("Total lines: %d\n", lines);

    return 0;
}

