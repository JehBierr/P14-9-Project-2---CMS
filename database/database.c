#include "database.h"
#include <stdio.h>
#include <string.h>


void openDatabase(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No existing database found.\n");
        return;
    }

    studentCount = 0;
    char line[MAX_LINE];
    
    // Temporary buffers for fixed-width string extraction
    char temp_name[51] = {0};     // Max Name length 27, plus padding, plus null
    char temp_programme[51] = {0};// Max Programme length 28, plus padding, plus null

    // Skip header line
    fgets(line, sizeof(line), file);
    
    // Read each record
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0;
        
        // Skip short lines or empty lines
        if (strlen(line) < 68) continue;

        // 1. Extract ID and Mark (using sscanf for conversion)
        sscanf(line, "%d", &students[studentCount].id);
        sscanf(line + 68, "%f", &students[studentCount].mark);

        // 2. Extract Name (Fixed width: 25 characters starting at index 11)
        strncpy(temp_name, line + 11, 25);
        temp_name[25] = '\0'; // Null-terminate at the fixed width

        // 3. Extract Programme (Fixed width: 30 characters starting at index 37)
        strncpy(temp_programme, line + 37, 30);
        temp_programme[30] = '\0'; // Null-terminate at the fixed width


        // Trimming Name: remove leading/trailing spaces and store
        int start = 0;
        while (isspace((unsigned char)temp_name[start])) start++;
        int len = strlen(temp_name);
        while (len > start && isspace((unsigned char)temp_name[len - 1])) len--;
        
        // Copy trimmed string to struct
        if (len - start > 0) {
            strncpy(students[studentCount].name, temp_name + start, len - start);
            students[studentCount].name[len - start] = '\0'; // Ensure null termination
        } else {
            students[studentCount].name[0] = '\0'; // Empty string
        }

        // Trimming Programme: remove leading/trailing spaces and store
        start = 0;
        while (isspace((unsigned char)temp_programme[start])) start++;
        len = strlen(temp_programme);
        while (len > start && isspace((unsigned char)temp_programme[len - 1])) len--;

        // Copy trimmed string to struct
        if (len - start > 0) {
            strncpy(students[studentCount].programme, temp_programme + start, len - start);
            students[studentCount].programme[len - start] = '\0'; // Ensure null termination
        } else {
            students[studentCount].programme[0] = '\0'; // Empty string
        }
        
        studentCount++;
        if (studentCount >= MAX_STUDENTS){
            printf(RED "Maximum student limit reached while loading database.\n" RESET);
            break;
        } 
    }
    
    fclose(file);
    printf(GREEN "\nDatabase loaded from \"%s\" successfully with %d records.\n" RESET, filename, studentCount);
}

void saveDatabase(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf(RED "Error opening file \"%s\" for writing.\n" RESET, filename);
        return;
    }

    fprintf(file, "%-10s %-25s %-30s %-10s\n", "ID", "Name", "Programme", "Mark");

    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%-10d %-25s %-30s %-10.2f\n",
                students[i].id,
                students[i].name,
                students[i].programme,
                students[i].mark);
    }

    fclose(file);
    printf(GREEN "Database saved to \"%s\" successfully with %d records.\n" RESET, filename, studentCount);
}
