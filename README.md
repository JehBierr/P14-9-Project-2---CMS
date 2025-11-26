# 👨‍💻 INF1002, P14_9
- Charissa Koh Yi En 2501810
- Javier Soh Jie En 2500119
- Liew Hui Zhong 2502222
- Ong Si Kai 2501225

## 🗂️ Course Management System
- Add, update, query, and delete student records
- File operations (open, save, show all)
- Commands for sorting and statistics
- Command-line interface (CLI)
- Robust error handling and input validation
- Maximum configurable limits for records and command input
- Help and usage guidance

## 🏗️ Data Structure
- id: Holds the unique student identifier as an integer.
- name: Stores the student's name as a string with a maximum length of 50 characters.
- programme: Contains the academic programme or course, also as a string up to 50 characters.
- mark: Records the student's mark as a floating-point number.

## ✨ Usage
1. Open the datavase: OPEN <filename>
2. Show records: SHOW ALL
3. Insert a new record: INSERT [ID],[Name],[Programme],[Mark]
4. Update a record: UPDATE [ID]
   [Name/Programme/Mark/All] <new_value>
6. Delete a record: DELETE [ID]
8. Query a record: QUERY [ID]
9. Save database: SAVE
10. Display help: HELP
11. Exit program: EXIT

## ⚠️ Limits
- Maximum student: 100
- Maximum inpuit line length: 256 characters

## 🛠️ compilation
gcc main.c database/database.c operations/operations.c display/display.c -o main.exe

## 🟢 Running the program
### </>>_ Integrated terminal
./main.exe
### 🔳⚙️ Open exe
double click main.exe

## 📝 File Format
Student data files must use tabular text with fields: ID, Name, Programme, Mark.
