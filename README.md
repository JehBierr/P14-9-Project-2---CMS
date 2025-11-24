# INF1002, P14_9
- Liew Hui Zhong 2502222
- Charissa Koh Yi En 2501810
- Ong Si Kai 2501225
- Javier Soh Jie En 2500119

#Course Management System
- Add, update, query, and delete student records
- File operations (open, save, show all)
- Commands for sorting and statistics
- Command-line interface (CLI)
- Robust error handling and input validation
- Maximum configurable limits for records and command input
- Help and usage guidance

#Data Structure
typedef struct {
    int id;
    char name[50];
    char programme[50];
    float mark;
} Student;

#Usage
1. Open the datavase: OPEN <filename>
2. Show records: SHOW ALL
3. Insert a new record: INSERT ID Name Programme Mark
4. Update a record: UPDATE ID [Name/Programme/Mark] <new_value>
5. Delete a record: DELETE ID
6. Query a record: QUERY ID
7. Save database: SAVE
8. Display help: HELP
9. Exit program: EXIT

#Limits
- Maximum student:1100
- Maximum inpuit line length: 256 characters

#compilation
gcc main.c database.c operations.c display.c -o cms

#Running the program
./cms

#File Format
Student data files must use tabular text with fields: ID, Name, Programme, Mark.
