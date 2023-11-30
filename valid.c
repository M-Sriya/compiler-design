#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Token types
typedef enum {
    IDENTIFIER,
    INVALID_IDENTIFIER,
    END_OF_FILE
} TokenType;

// Structure to represent a token
typedef struct {
    TokenType type;
    char value[30]; // Assuming a maximum length for the identifier
} Token;

// Function to check if a character is a valid starting character for an identifier
int isValidIdentifierStart(char ch) {
    return isalpha(ch) || ch == '_';
}

// Function to check if a character is a valid subsequent character for an identifier
int isValidIdentifierChar(char ch) {
    return isalnum(ch) || ch == '_';
}

// Function to analyze the input and identify identifiers
Token getNextToken(FILE *fp) {
    Token token;
    int ch;
    int index = 0;

    // Ignore spaces, tabs, and new lines
    while ((ch = fgetc(fp)) == ' ' || ch == '\t' || ch == '\n') {}

    // Check if it's a valid starting character for an identifier
    if (!isValidIdentifierStart(ch)) {
        token.type = INVALID_IDENTIFIER;
        strcpy(token.value, "Invalid identifier");
        return token;
    }

    // Read the identifier
    do {
        if (index < sizeof(token.value) - 1) {
            token.value[index++] = (char) ch;
        }
        ch = fgetc(fp);
    } while (isValidIdentifierChar(ch));

    token.value[index] = '\0';

    // If none of the above, return as end of file token
    token.type = IDENTIFIER;
    ungetc(ch, fp); // Return the non-alphanumeric character to the input stream
    return token;
}

int main() {
    FILE *fp;
    Token token;

    // Open the input file (replace "input.txt" with your file name)
    fp = fopen("input.txt", "r");

    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Loop to get and print identifiers until the end of file is reached
    do {
        token = getNextToken(fp);
        switch (token.type) {
            case IDENTIFIER:
                printf("Valid Identifier: %s\n", token.value);
                break;
            case INVALID_IDENTIFIER:
                printf("Invalid Identifier: %s\n", token.value);
                break;
        }
    } while (token.type != END_OF_FILE);

    // Close the file
    fclose(fp);

    return 0;
}
