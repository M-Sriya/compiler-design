#include <stdio.h>
#include <ctype.h>

// Token types
typedef enum {
    OPERATOR,
    END_OF_FILE
} TokenType;

// Structure to represent a token
typedef struct {
    TokenType type;
    char value; // The operator itself
} Token;

// Function to check if a character is a valid operator
int isValidOperator(char ch) {
    char operators[] = {'+', '-', '*', '/'};
    for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); ++i) {
        if (ch == operators[i]) {
            return 1;
        }
    }
    return 0;
}

// Function to analyze the input and identify operators
Token getNextToken(FILE *fp) {
    Token token;
    int ch;

    // Ignore spaces, tabs, and new lines
    while ((ch = fgetc(fp)) == ' ' || ch == '\t' || ch == '\n') {}

    // Check if it's a valid operator
    if (isValidOperator(ch)) {
        token.type = OPERATOR;
        token.value = (char) ch;
        return token;
    }

    // If none of the above, return as end of file token
    token.type = END_OF_FILE;
    token.value = '\0';
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

    // Loop to get and print operators until the end of file is reached
    do {
        token = getNextToken(fp);
        switch (token.type) {
            case OPERATOR:
                printf("Operator: %c\n", token.value);
                break;
            case END_OF_FILE:
                printf("End of File\n");
                break;
        }
    } while (token.type != END_OF_FILE);

    // Close the file
    fclose(fp);

    return 0;
}
