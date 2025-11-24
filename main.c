#include "common.h"
#include "database/database.h"
#include "display/display.h"
#include "operations/operations.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>


Student students[MAX_STUDENTS];
int studentCount = 0;
char currentFilename[100] = {0};
int fileOpen = 0; //file open status. if 0 means no if yes means 1 

void openFile() {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile("*.txt", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("No .txt files found in current directory.\n");
        exit(0);
    }

    // Collect filenames
    char availableFiles[100][256]; // up to 100 files
    int numFiles = 0;

    do {
        strcpy(availableFiles[numFiles++], findFileData.cFileName);
    } while (FindNextFile(hFind, &findFileData) && numFiles < 100);

    FindClose(hFind);

    printf(MAGENTA "\nSelect a database file to open:\n" RESET);
    printf("  0 -> Exit CMS\n");

    for (int i = 0; i < numFiles; i++) {
        printf("  %d -> %s\n", i + 1, availableFiles[i]);
    }

    // Get choice
    int fileChoice;
    printf("Enter your choice (1-%d): ", numFiles);
    scanf("%d", &fileChoice);
    getchar(); // consume newline

    if (fileChoice == 0) {
        exit(0);
    }
    else if (fileChoice < 1 || fileChoice > numFiles) {
        printf(RED "Invalid choice.\n" RESET);
        startupPrompt();
    }



    strcpy(currentFilename, availableFiles[fileChoice - 1]);
    openDatabase(currentFilename);   // your existing function
    fileOpen = 1;
    printf(GREEN "Opened database: %s\n" RESET, currentFilename);
}

int main() {

    printf(YELLOW "welcome to CMS" RESET);
    openFile();

    char command[MAX_LINE];

    while (1) {
        printf("\nEnter command: \n");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;  // Remove newline

        for (int i = 0; command[i]; i++) {
            command[i] = toupper(command[i]);
        }

        if (strcmp(command, "OPEN") == 0) {
            if (fileOpen) {
                char choice;
                printf(YELLOW "You currently have \"%s\" open. Save before opening another file? (Y/N): " RESET, currentFilename);
                choice = getchar();
                getchar(); // consume newline

                if (choice == 'Y' || choice == 'y') {
                    printf(GREEN "Changes Saved into \"%s\".\n" RESET, currentFilename);
                    saveDatabase(currentFilename);
                } 
                else {
                    printf(RED "Changes discarded for \"%s\".\n" RESET, currentFilename);
                }
            }
            openFile(); 
        } else if (strcmp(command, "SAVE") == 0) {
            saveDatabase(currentFilename);
        } else if (strncmp(command, "INSERT", 6) == 0) {
            insertRecord(command + 7);
        } else if (strncmp(command, "QUERY", 5) == 0) {
            searchRecord(command + 6);
        } else if (strncmp(command, "DELETE", 6) == 0) {
            deleteRecord(command + 7);
        } else if (strcmp(command, "SHOW ALL") == 0) {
            showAll();
        } else if (strcmp(command, "SHOW SUMMARY") == 0) {
            showSummary();
        } else if (strncmp(command, "UPDATE", 6) == 0) {
            updateRecord(command + 7); 
        } else if (strcmp(command, "SORT BY") == 0) {
            sortBy();
        }  


        else if (strcmp(command, "HELP") == 0) {
            printf("Available commands:\n");
            printf("OPEN - Open the database file\n");
            printf("SAVE - Save the database file\n");
            printf("INSERT <ID>,<Name>,<Programme>,<Mark> - Insert a new student record\n");
            printf("QUERY <ID> - Search for a student record by ID\n");
            printf("DELETE <ID> - Delete a student record by ID\n");
            printf("UPDATE <ID> - Update a student record by ID (choose field or update all)\n");
            printf("SHOW ALL - Display all student records\n");
            printf("SORT BY - Sort records by ID, Name, or Mark (ASC/DESC)\n");
            printf("SHOW SUMMARY - Display summary statistics of student records\n");
            printf("EXIT - Exit the program\n");
        } else if (strcmp(command, "EXIT") == 0) {
            break;
        } else {
            printf("Unknown command: %s\n", command);
            printf("To show available command, type HELP.\n");
        }
    }
}