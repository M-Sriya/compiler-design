#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RULES 10
#define MAX_RULE_LENGTH 50

// Structure to represent a production rule
typedef struct {
    char nonTerminal;
    char rule[MAX_RULE_LENGTH];
} ProductionRule;

// Function to eliminate left factoring from a set of production rules
void eliminateLeftFactoring(ProductionRule rules[], int *numRules) {
    for (int i = 0; i < *numRules; ++i) {
        char currentNonTerminal = rules[i].nonTerminal;

        // Find common prefix among alternative productions
        int commonPrefixLength = 0;
        while (rules[i].rule[commonPrefixLength] == rules[i + 1].rule[commonPrefixLength]) {
            ++commonPrefixLength;
        }

        // If common prefix exists, eliminate left factoring
        if (commonPrefixLength > 0) {
            // Create new non-terminal for the eliminated common prefix
            char newNonTerminal = currentNonTerminal + 1;

            // Modify the current rule
            char newRule[MAX_RULE_LENGTH];
            strcpy(newRule, rules[i].rule + commonPrefixLength);
            strcat(newRule, &newNonTerminal);
            rules[i].nonTerminal = currentNonTerminal;
            strcpy(rules[i].rule, newRule);

            // Add new rules to eliminate left factoring
            rules[*numRules].nonTerminal = newNonTerminal;
            strcpy(rules[*numRules].rule, rules[i].rule + commonPrefixLength);
            ++(*numRules);

            rules[*numRules].nonTerminal = newNonTerminal;
            strcpy(rules[*numRules].rule, rules[i + 1].rule + commonPrefixLength);
            ++(*numRules);
        }
    }
}

// Function to print the production rules
void printRules(ProductionRule rules[], int numRules) {
    for (int i = 0; i < numRules; ++i) {
        printf("%c -> %s\n", rules[i].nonTerminal, rules[i].rule);
    }
}

int main() {
    // Example production rules
    ProductionRule rules[MAX_RULES] = {
        {'A', "aX|aY|b"},
        {'B', "bX|bY|c"},
        {'C', "cX|cY|d"}
    };

    int numRules = sizeof(rules) / sizeof(rules[0]);

    printf("Original Grammar:\n");
    printRules(rules, numRules);

    eliminateLeftFactoring(rules, &numRules);

    printf("\nGrammar after Left Factoring Elimination:\n");
    printRules(rules, numRules);

    return 0;
}
