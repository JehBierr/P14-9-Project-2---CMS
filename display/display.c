#include "display.h"
#include <stdio.h>
#include <string.h>

void showAll() {
    if (studentCount == 0) {
        printf(RED "No records to display.\n" RESET);
        return;
    }
    // Compute dynamic widths
    int maxId = (int)strlen("ID");
    int maxName = (int)strlen("Name");
    int maxProg = (int)strlen("Programme");
    int maxMark = (int)strlen("Mark");
    char tmp[64];
    for (int i = 0; i < studentCount; ++i) {
        snprintf(tmp, sizeof(tmp), "%d", students[i].id);
        int l = (int)strlen(tmp); if (l > maxId) maxId = l;
        l = (int)strlen(students[i].name); if (l > maxName) maxName = l;
        l = (int)strlen(students[i].programme); if (l > maxProg) maxProg = l;
        snprintf(tmp, sizeof(tmp), "%.2f", students[i].mark);
        l = (int)strlen(tmp); if (l > maxMark) maxMark = l;
    }

printf(BLUE BOLD "\nAll Student Records:\n" RESET);
    printf(MAGENTA "%-*s     %-*s     %-*s     %-*s\n" RESET, maxId, "ID", maxName, "Name", maxProg, "Programme", maxMark, "Mark");
    for (int i = 0; i < studentCount; ++i) {
        snprintf(tmp, sizeof(tmp), "%.2f", students[i].mark);
        printf("%-*d     %-*s     %-*s     %-*s\n",
               maxId, students[i].id,
               maxName, students[i].name,
               maxProg, students[i].programme,
               maxMark, tmp);
    }
}


void showSummary() {
    if (studentCount == 0) {
        printf(RED "No records to summarize.\n" RESET);
        return;
    }
    else {}
    float total = 0, highest = students[0].mark, lowest = students[0].mark;
    int highestIdx = 0, lowestIdx = 0;
    for (int i = 0; i < studentCount; i++) {
        total += students[i].mark;
        if (students[i].mark > highest) {
            highest = students[i].mark;
            highestIdx = i;
        }
        else{}
        if (students[i].mark < lowest) {
            lowest = students[i].mark;
            lowestIdx = i;
        }
        else{}
    }
    
    printf(BLUE "\nCMS: Summary Statistics\n" RESET);
    printf("Total Students: %d\n", studentCount);
    printf("Average Mark: %.2f\n", total / studentCount);
    printf("Highest Mark: %.1f (%s)\n", highest, students[highestIdx].name);
    printf("Lowest Mark: %.1f (%s)\n", lowest, students[lowestIdx].name);
}

void sortBy() {
    if (studentCount == 0) {
        printf(RED "No records to sort.\n" RESET);
        return;
    }

    char field[20], order[20];
    
    printf("Sort by (ID / NAME / MARK): ");
    fgets(field, sizeof(field), stdin);
    field[strcspn(field, "\n")] = 0;

    printf("Order (ASC / DESC): ");
    fgets(order, sizeof(order), stdin);
    order[strcspn(order, "\n")] = 0;

    for (int i = 0; field[i]; i++) field[i] = toupper(field[i]);
    for (int i = 0; order[i]; i++) order[i] = toupper(order[i]);

    // sorting logic is here guys
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            int cmp = 0;

            if (strcmp(field, "ID") == 0) {
                cmp = students[i].id - students[j].id;
            } else if (strcmp(field, "NAME") == 0) {
                cmp = strcasecmp(students[i].name, students[j].name);
            } else if (strcmp(field, "MARK") == 0) {
                if (students[i].mark < students[j].mark) cmp = -1;
                else if (students[i].mark > students[j].mark) cmp = 1;
                else cmp = 0;
            } else {
                printf("Invalid field: %s. Use ID, NAME, or MARK.\n", field);
                return;
            }

            // Just swap based on asc or desc order.
            if ((strcmp(order, "ASC") == 0 && cmp > 0) ||
                (strcmp(order, "DESC") == 0 && cmp < 0)) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printf(GREEN "\nDatabase sorted by %s (%s).\n" RESET, field, order);
    showAll();
}