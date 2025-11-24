#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "../common.h"

int insertRecord(char *command);
void searchRecord(char *command);
void updateRecord(char *command);
void deleteRecord(char *command);
int findStudent(int id);

#endif