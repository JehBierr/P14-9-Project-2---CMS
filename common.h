#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define MAX_LINE 256
#define FILENAME "P14_9-CMS.txt"

#define RESET   "\033[0m"
#define BOLD    "\033[1m"

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"


typedef struct {
    int id;
    char name[50];
    char programme[50];
    float mark;
} Student;

extern Student students[MAX_STUDENTS];
extern int studentCount;

#endif