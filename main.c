#include "common.h"
#include "database/database.h"
#include "display/display.h"
#include "operations/operations.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


Student students[MAX_STUDENTS];
int studentCount = 0;

int main() {
    printf("DEBUG: Program started\n\n\n");
    
    char command[MAX_LINE];

    while (1) {
        printf("\nEnter command: \n");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;  // Remove newline

        for (int i = 0; command[i]; i++) {
            command[i] = toupper(command[i]);
        }

        if (strcmp(command, "OPEN") == 0) {
            openDatabase();
        } else if (strcmp(command, "SAVE") == 0) {
            saveDatabase();
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