# INF1002, Project P14_9
# 📚 Course Management System (CMS)

A command-line interface application for managing student records with support for CRUD operations, sorting, and statistical analysis.

## 👥 Team Members
- Charissa Koh Yi En (2501810)
- Javier Soh Jie En (2500119)
- Liew Hui Zhong (2502222)
- Ong Si Kai (2501225)



---

## 🎯 Features

### Core Operations
- **CRUD Operations**: Create, Read, Update, and Delete student records
- **File Management**: Open, save, and manage multiple database files
- **Search & Query**: Find specific student records by ID
- **Sorting**: Sort records by ID, Name, or Mark (ascending/descending)
- **Statistics**: Display summary statistics including averages and extremes
- **Data Validation**: Input validation for marks (0-100) and duplicate ID prevention

### User Experience
- Color-coded terminal output for better readability
- Interactive confirmations for destructive operations
- Automatic alphabetical insertion by student name
- Help command for quick reference
- Multiple file selection on startup

---

## 🏗️ Project Structure

```
.
├── main.c                  # Main program entry and command processor
├── common.h               # Shared definitions and structures
├── database/
│   ├── database.h         # Database function declarations
│   └── database.c         # File I/O operations
├── operations/
│   ├── operations.h       # CRUD operation declarations
│   └── operations.c       # Insert, update, delete, search logic
├── display/
│   ├── display.h          # Display function declarations
│   └── display.c          # Show all, summary, and sort operations
└── *.txt                  # Database files
```

### Data Structure

The `Student` structure defined in [common.h](common.h):

```c
typedef struct {
    int id;              // Unique student identifier
    char name[50];       // Student name (max 50 chars)
    char programme[50];  // Academic programme (max 50 chars)
    float mark;          // Student mark (0.0 - 100.0)
} Student;
```

---

## 🚀 Getting Started

### Prerequisites
- GCC compiler (MinGW for Windows)
- Windows OS (uses Windows API for file listing)

### Compilation

```bash
gcc main.c database/database.c operations/operations.c display/display.c -o main.exe
```

Or use the provided VS Code task:
- Press `Ctrl+Shift+B` to build using the configured task in [.vscode/tasks.json](.vscode/tasks.json)

### Running the Program

**From Terminal:**
```bash
./main.exe
```

**From File Explorer:**
- Double-click `main.exe`

---

## 📖 Command Reference

### File Operations
| Command | Description | Example |
|---------|-------------|---------|
| `OPEN` | Open a database file from available .txt files | `OPEN` |
| `SAVE` | Save current database to file | `SAVE` |

### Record Operations
| Command | Description | Example |
|---------|-------------|---------|
| `INSERT` | Add a new student record | `INSERT 101,John Doe,Computer Science,85.5` |
| `QUERY` | Search for a record by ID | `QUERY 101` |
| `UPDATE` | Update a record's fields | `UPDATE 101` |
| `DELETE` | Remove a record by ID | `DELETE 101` |

### Display Operations
| Command | Description | Example |
|---------|-------------|---------|
| `SHOW ALL` | Display all student records | `SHOW ALL` |
| `SHOW SUMMARY` | Display statistics (total, average, highest, lowest) | `SHOW SUMMARY` |
| `SORT BY` | Sort records by ID, NAME, or MARK | `SORT BY` |

### Utility Commands
| Command | Description |
|---------|-------------|
| `HELP` | Display available commands |
| `EXIT` | Exit the program |

---

## 💡 Usage Examples

### 1. Starting the Program
```
welcome to CMS
Select a database file to open:
  0 -> Exit CMS
  1 -> P14_9-CMS.txt
  2 -> testfile1.txt
  3 -> testfile2.txt
  4 -> testfile3.txt
Enter your choice (1-4): 1
```

### 2. Inserting a Record
```
Enter command:
INSERT 105,Alice Tan,Information Security,92.0

Record with ID: 105 added successfully at position 0.
```

### 3. Updating a Record
```
Enter command:
UPDATE 105

Current Record:
ID: 105, Name: Alice Tan, Programme: Information Security, Mark: 92.00

What would you like to update?
Options: NAME, PROGRAMME, MARK, ALL
MARK
Enter new mark: 95.5

Proposed Update:
Mark: 92.00 -> 95.50
Confirm update? Type "Y" to confirm or any other key to cancel: Y
Record with ID 105 updated successfully.
```

### 4. Sorting Records
```
Enter command:
SORT BY
Sort by (ID / NAME / MARK): NAME
Order (ASC / DESC): ASC

Database sorted by NAME (ASC).
```

### 5. Viewing Summary
```
Enter command:
SHOW SUMMARY

CMS: Summary Statistics
Total Students: 5
Average Mark: 73.84
Highest Mark: 95.5 (Alice Tan)
Lowest Mark: 22.5 (Betty Goh)
```

---

## 📋 File Format

Database files must be plain text (.txt) with the following fixed-width format:

```
ID         Name                      Programme                      Mark      
101        JOHN DOE                  COMPUTER SCIENCE               85.50
```

**Column Widths:**
- ID: 10 characters (left-aligned)
- Name: 25 characters (left-aligned)
- Programme: 30 characters (left-aligned)
- Mark: 10 characters (left-aligned, 2 decimal places)

---

## ⚙️ Configuration

Constants defined in [common.h](common.h):

```c
#define MAX_STUDENTS 100    // Maximum number of student records
#define MAX_LINE 256        // Maximum input line length
```

### Color Codes
The system uses ANSI color codes for terminal output:
- **RED**: Errors and warnings
- **GREEN**: Success messages
- **YELLOW**: Prompts and important notices
- **BLUE**: Headers and section titles
- **MAGENTA**: Column headers

---

## 🔧 Technical Details

### Key Functions

**Database Module** ([database/database.c](database/database.c))
- [`openDatabase()`](database/database.c) - Load student records from file
- [`saveDatabase()`](database/database.c) - Save records to file

**Operations Module** ([operations/operations.c](operations/operations.c))
- [`insertRecord()`](operations/operations.c) - Add new student (sorted by name)
- [`searchRecord()`](operations/operations.c) - Find student by ID
- [`updateRecord()`](operations/operations.c) - Modify student fields
- [`deleteRecord()`](operations/operations.c) - Remove student record
- [`findStudent()`](operations/operations.c) - Helper function to locate student by ID

**Display Module** ([display/display.c](display/display.c))
- [`showAll()`](display/display.c) - Display all records with dynamic column widths
- [`showSummary()`](display/display.c) - Calculate and show statistics
- [`sortBy()`](display/display.c) - Sort records by various fields

### Input Validation
- Mark range: 0.0 to 100.0
- Duplicate ID prevention
- Format validation for INSERT command
- Confirmation prompts for destructive operations

---

## ⚠️ Known Limitations

- Maximum capacity: 100 student records (configurable in [common.h](common.h))
- Windows-specific file listing (uses `windows.h` API)
- Fixed-width file format required for parsing
- No support for concurrent file access

---

## 🐛 Error Handling

The system handles various error conditions:
- Invalid file access
- Duplicate student IDs
- Invalid mark values
- Malformed input commands
- Database capacity exceeded
- Missing or corrupted data files

---

## 📝 License

Academic project for INF1002 course at Singapore Institute of Technology.

---

## 🤝 Contributing

This is an academic project. For questions or issues, please contact the team members listed above.
