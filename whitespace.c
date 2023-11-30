#include <stdio.h>

int main() {
    FILE *fp;
    int whitespaceCount = 0;
    int newlineCount = 0;
    int ch;

    // Open the input file (replace "input.txt" with your file name)
    fp = fopen("input.txt", "r");

    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Loop through the file to count whitespaces and newline characters
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == ' ' || ch == '\t') {
            // Increment whitespace count for space or tab
            whitespaceCount++;
        } else if (ch == '\n') {
            // Increment newline count
            newlineCount++;
        }
    }

    // Print the results
    printf("Number of whitespaces: %d\n", whitespaceCount);
    printf("Number of newline characters: %d\n", newlineCount);

    // Close the file
    fclose(fp);

    return 0;
}
