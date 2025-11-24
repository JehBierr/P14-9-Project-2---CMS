#include "operations.h"
#include <stdio.h>
#include <string.h>

int findStudent(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

void searchRecord(char *command) {
    int id;
    sscanf(command, "%d", &id);
    int index = findStudent(id);
    
    if (index == -1) {
        printf(RED "Record with ID %d not found.\n" RESET, id);
        return;
    }
    
    Student *s = &students[index];
    printf("Record Found: ID: %d, Name: %s, Programme: %s, Mark: %.2f\n", s->id, s->name, s->programme, s->mark);
}

int insertRecord(char *command) {
    Student newStudent;

    // Parse comma-separated input: ID,Name,Programme,Mark
    int fields = sscanf(command, "%d,%49[^,],%49[^,],%f",
                        &newStudent.id,
                        newStudent.name,
                        newStudent.programme,
                        &newStudent.mark);

    if (fields != 4) {
        printf(RED "Invalid format. Please enter: \"ID,Name,Programme,Mark\"\n" RESET);
        return -1;
    }

    // Validate mark
    if (newStudent.mark < 0 || newStudent.mark > 100) {
        printf(RED "Invalid mark. Must be between 0 and 100.\n" RESET);
        return -1;
    }

    // Check for duplicate ID
    if (findStudent(newStudent.id) != -1) {
        printf("Record with ID %d already exists.\n", newStudent.id);
        return -1;
    }

    // Check capacity
    if (studentCount >= MAX_STUDENTS) {
        printf("Cannot add more records. Maximum limit reached.\n");
        return -1;
    }

    // Find correct position based on first letter of name
    int insertPos = 0;
    while (insertPos < studentCount && toupper(newStudent.name[0]) > toupper(students[insertPos].name[0])) {
        insertPos++;
    }

    // Shift records to make space
    for (int i = studentCount; i > insertPos; i--) {
        students[i] = students[i - 1];
    }

    // Insert new student
    students[insertPos] = newStudent;
    studentCount++;

    printf("Record with ID: %d added successfully at position %d.\n", newStudent.id, insertPos);
    return 0;
}

void deleteRecord(char *command) {
    int id;
    sscanf(command, "%d", &id);
    if (sscanf(command, "%d", &id) != 1) {
        printf("CMS: Invalid delete command format. Use DELETE <ID>\n");
        return;
    }
    int index = findStudent(id);
    
    if (index == -1) {
        printf("CMS: The record with ID=%d does not exist.\n", id);
        return;
    }
    
    printf("CMS: Are you sure you want to delete record with ID=%d? Type \"Y\" to Confirm or type any other key to cancel.\n", id);
    
    char confirm[10];
    printf("CONFIRM? ");
    fgets(confirm, sizeof(confirm), stdin);
    confirm[strcspn(confirm, "\n")] = 0;
    
    if (strcmp(confirm, "Y") == 0 || strcmp(confirm, "y") == 0) {
        for (int i = index; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;
        printf(GREEN "CMS: The record with ID=%d is successfully deleted.\n" RESET, id);
    } else {
        printf("CMS: The deletion is cancelled.\n");
    }
}

void updateRecord(char *command)
{
    int id;
    if(sscanf(command, "%d", &id)!=1){
        printf(RED "Invalid format. Use: UPDATE <ID>\n" RESET);
        return;
    }
    int index = findStudent(id);
    if (index == -1) {
        printf("Record with ID %d not found.\n", id);
        return;
    }

    Student *s = &students[index];
    printf("Current Record:\nID: %d, Name: %s, Programme: %s, Mark: %.2f\n", s->id, s->name, s->programme, s->mark);

    printf("\nWhat would you like to update?\n");
    printf("Options: NAME, PROGRAMME, MARK, ALL\n");

    char choice[20];
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = 0;

    for (int i = 0; choice[i]; i++) {
        choice[i] = toupper(choice[i]);
    }

    // Temporary variables to hold new values
    char newName[50], newProgramme[50];
    float newMark = s->mark; // default to current mark

    if (strcmp(choice, "NAME") == 0) {
        printf("Enter new name: ");
        fgets(newName, sizeof(newName), stdin);
        newName[strcspn(newName, "\n")] = 0;

        printf("Proposed Update:\nName: %s -> %s\n", s->name, newName);
        } else if (strcmp(choice, "PROGRAMME") == 0) {
        printf("Enter new programme: ");
        fgets(newProgramme, sizeof(newProgramme), stdin);
        newProgramme[strcspn(newProgramme, "\n")] = 0;

        printf("Proposed Update:\nProgramme: %s -> %s\n", s->programme, newProgramme);

    } else if (strcmp(choice, "MARK") == 0) {
        printf("Enter new mark: ");
        if (scanf("%f", &newMark) != 1 || newMark < 0 || newMark > 100) {
            printf(RED "Invalid mark. Must be between 0 and 100.\n" RESET);
            while (getchar() != '\n'); // clear buffer
            return;
        }
        while (getchar() != '\n'); // clear buffer

        printf("Proposed Update:\nMark: %.2f -> %.2f\n", s->mark, newMark);

    } else if (strcmp(choice, "ALL") == 0) {
        printf("Enter new name: ");
        fgets(newName, sizeof(newName), stdin);
        newName[strcspn(newName, "\n")] = 0;

        printf("Enter new programme: ");
        fgets(newProgramme, sizeof(newProgramme), stdin);
        newProgramme[strcspn(newProgramme, "\n")] = 0;

        printf("Enter new mark: ");
        if (scanf("%f", &newMark) != 1 || newMark < 0 || newMark > 100) {
            printf(RED "Invalid mark. Must be between 0 and 100.\n" RESET);
            while (getchar() != '\n'); // clear buffer
            return;
        }
         while (getchar() != '\n'); // clear buffer

        printf("Proposed Update:\nName: %s -> %s\nProgramme: %s -> %s\nMark: %.2f -> %.2f\n", s->name, newName, s->programme, newProgramme, s->mark, newMark);

    } else {
        printf(RED "Unknown option: %s. Valid options are NAME, PROGRAMME, MARK, ALL.\n" RESET, choice);
        return;
    }

    // Confirmation step
    char confirm[10];
    printf("Confirm update? Type \"Y\" to confirm or any other key to cancel: ");
    fgets(confirm, sizeof(confirm), stdin);
    confirm[strcspn(confirm, "\n")] = 0;

    if (strcmp(confirm, "Y") == 0 || strcmp(confirm, "y") == 0) {
        if (strcmp(choice, "NAME") == 0) {
            strncpy(s->name, newName, sizeof(s->name) - 1);
        } else if (strcmp(choice, "PROGRAMME") == 0) {
            strncpy(s->programme, newProgramme, sizeof(s->programme) - 1);
        } else if (strcmp(choice, "MARK") == 0) {
            s->mark = newMark;
        } else if (strcmp(choice, "ALL") == 0) {
            strncpy(s->name, newName, sizeof(s->name) - 1);
            strncpy(s->programme, newProgramme, sizeof(s->programme) - 1);
            s->mark = newMark;
        }
        printf(GREEN "Record with ID %d added successfully.\n" RESET, id);
    } else {
        printf(RED "Update cancelled.\n" RESET);
    }
}