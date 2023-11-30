#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_IDENTIFIER_LENGTH 30
#define MAX_COMMENT_LENGTH 100

// Token types
typedef enum {
    IDENTIFIER,
    CONSTANT,
    OPERATOR,
    COMMENT
} TokenType;

// Structure to represent a token
typedef struct {
    TokenType type;
    char value[MAX_IDENTIFIER_LENGTH];
} Token;

// Function to check if a character is an operator
int isOperator(char ch) {
    char operators[] = {'+', '-', '*', '/', '=', '<', '>', '!', '&', '|'};
    for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); ++i) {
        if (ch == operators[i]) {
            return 1;
        }
    }
    return 0;
}

// Function to analyze the input and identify tokens
Token getNextToken(FILE *fp) {
    Token token;
    int ch;
    int index = 0;

    // Ignore spaces, tabs, and new lines
    while ((ch = fgetc(fp)) == ' ' || ch == '\t' || ch == '\n') {}

    // Ignore comments
    if (ch == '/') {
        if ((ch = fgetc(fp)) == '/') {
            while ((ch = fgetc(fp)) != '\n' && ch != EOF) {}
            token.type = COMMENT;
            return token;
        } else {
            ungetc(ch, fp); // Return the character to the input stream
            ch = '/';
        }
    }

    // Identify identifiers
    if (isalpha(ch) || ch == '_') {
        do {
            if (index < MAX_IDENTIFIER_LENGTH - 1) {
                token.value[index++] = (char) ch;
            }
            ch = fgetc(fp);
        } while (isalnum(ch) || ch == '_');

        token.value[index] = '\0';
        token.type = IDENTIFIER;
        ungetc(ch, fp); // Return the non-alphanumeric character to the input stream
        return token;
    }

    // Identify constants
    if (isdigit(ch)) {
        do {
            if (index < MAX_IDENTIFIER_LENGTH - 1) {
                token.value[index++] = (char) ch;
            }
            ch = fgetc(fp);
        } while (isdigit(ch));

        token.value[index] = '\0';
        token.type = CONSTANT;
        ungetc(ch, fp); // Return the non-digit character to the input stream
        return token;
    }

    // Identify operators
    if (isOperator(ch)) {
        token.type = OPERATOR;
        token.value[0] = (char) ch;
        token.value[1] = '\0';
        return token;
    }

    // If none of the above, return as an unknown token
    token.type = -1;
    token.value[0] = (char) ch;
    token.value[1] = '\0';
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

    // Loop to get and print tokens until the end of file is reached
    do {
        token = getNextToken(fp);
        switch (token.type) {
            case IDENTIFIER:
                printf("Identifier: %s\n", token.value);
                break;
            case CONSTANT:
                printf("Constant: %s\n", token.value);
                break;
            case OPERATOR:
                printf("Operator: %s\n", token.value);
                break;
            case COMMENT:
                printf("Comment\n");
                break;
            default:
                if (token.value[0] != EOF) {
                    printf("Unknown: %s\n", token.value);
                }
        }
    } while (token.value[0] != EOF);

    // Close the file
    fclose(fp);

    return 0;
}
