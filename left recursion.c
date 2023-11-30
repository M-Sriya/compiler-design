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

// Function to eliminate left recursion from a set of production rules
void eliminateLeftRecursion(ProductionRule rules[], int numRules) {
    for (int i = 0; i < numRules; ++i) {
        for (int j = 0; j < i; ++j) {
            char currentNonTerminal = rules[i].nonTerminal;
            char firstSymbol = rules[i].rule[0];

            // If there is left recursion, eliminate it
            if (firstSymbol == currentNonTerminal) {
                // Create new non-terminal for the eliminated recursion
                char newNonTerminal = currentNonTerminal + 1;

                // Modify the current rule
                char newRule[MAX_RULE_LENGTH];
                strcpy(newRule, rules[i].rule + 1);
                strcat(newRule, &newNonTerminal);
                rules[i].nonTerminal = newNonTerminal;
                strcpy(rules[i].rule, newRule);

                // Add new rules to eliminate left recursion
                strcpy(rules[numRules].rule, "epsilon"); // Rule for epsilon production
                rules[numRules].nonTerminal = newNonTerminal;
                ++numRules;

                strcpy(rules[numRules].rule, rules[j].rule);
                strcat(rules[numRules].rule, &newNonTerminal);
                rules[numRules].nonTerminal = currentNonTerminal;
                ++numRules;

                strcpy(rules[numRules].rule, rules[j].rule);
                strcat(rules[numRules].rule, &newNonTerminal);
                strcat(rules[numRules].rule, rules[i].rule + 1);
                rules[numRules].nonTerminal = currentNonTerminal;
                ++numRules;
            }
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
        {'A', "Aa|b"},
        {'B', "Ba|c"},
        {'C', "Cde|f"},
        {'D', "Dgh|i"}
    };

    int numRules = sizeof(rules) / sizeof(rules[0]);

    printf("Original Grammar:\n");
    printRules(rules, numRules);

    eliminateLeftRecursion(rules, numRules);

    printf("\nGrammar after Left Recursion Elimination:\n");
    printRules(rules, numRules);

    return 0;
}
