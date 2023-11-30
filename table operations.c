#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 100

// Structure to represent a symbol entry in the symbol table
typedef struct {
    char name[30];
    int value;
} SymbolEntry;

// Structure to represent the symbol table
typedef struct {
    SymbolEntry entries[MAX_SYMBOLS];
    int size;
} SymbolTable;

// Function to initialize the symbol table
void initializeSymbolTable(SymbolTable *symbolTable) {
    symbolTable->size = 0;
}

// Function to insert a symbol into the symbol table
void insertSymbol(SymbolTable *symbolTable, const char *name, int value) {
    if (symbolTable->size < MAX_SYMBOLS) {
        SymbolEntry *entry = &symbolTable->entries[symbolTable->size];
        strncpy(entry->name, name, sizeof(entry->name) - 1);
        entry->name[sizeof(entry->name) - 1] = '\0';  // Ensure null-termination
        entry->value = value;
        symbolTable->size++;
        printf("Inserted: %s\n", name);
    } else {
        printf("Symbol table is full. Cannot insert %s\n", name);
    }
}

// Function to search for a symbol in the symbol table
int searchSymbol(SymbolTable *symbolTable, const char *name) {
    for (int i = 0; i < symbolTable->size; ++i) {
        if (strcmp(symbolTable->entries[i].name, name) == 0) {
            return symbolTable->entries[i].value;
        }
    }
    return -1; // Symbol not found
}

// Function to delete a symbol from the symbol table
void deleteSymbol(SymbolTable *symbolTable, const char *name) {
    for (int i = 0; i < symbolTable->size; ++i) {
        if (strcmp(symbolTable->entries[i].name, name) == 0) {
            printf("Deleted: %s\n", name);
            // Move the last entry to the deleted position
            symbolTable->entries[i] = symbolTable->entries[symbolTable->size - 1];
            symbolTable->size--;
            return;
        }
    }
    printf("Symbol not found: %s\n", name);
}

// Function to print the contents of the symbol table
void printSymbolTable(SymbolTable *symbolTable) {
    printf("Symbol Table:\n");
    for (int i = 0; i < symbolTable->size; ++i) {
        printf("%s: %d\n", symbolTable->entries[i].name, symbolTable->entries[i].value);
    }
    printf("\n");
}

int main() {
    SymbolTable symbolTable;

    // Initialize the symbol table
    initializeSymbolTable(&symbolTable);

    // Insert symbols
    insertSymbol(&symbolTable, "variable1", 10);
    insertSymbol(&symbolTable, "variable2", 20);
    insertSymbol(&symbolTable, "variable3", 30);

    // Print the symbol table
    printSymbolTable(&symbolTable);

    // Search for a symbol
    const char *searchName = "variable2";
    int searchResult = searchSymbol(&symbolTable, searchName);
    if (searchResult != -1) {
        printf("Found %s: %d\n", searchName, searchResult);
    } else {
        printf("%s not found in the symbol table\n", searchName);
    }

    // Delete a symbol
    const char *deleteName = "variable1";
    deleteSymbol(&symbolTable, deleteName);

    // Print the updated symbol table
    printSymbolTable(&symbolTable);

    return 0;
}
