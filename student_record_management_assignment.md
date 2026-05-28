# Console-Based Student Record Management System in C

## Objective

The objective of this project is to design and implement a small console-based database management system using the C programming language. The project is intended to help students practice fundamental and intermediate C programming concepts, particularly:

- Structures
- Linked Lists
- Pointers
- Dynamic Memory Allocation
- File Handling
- Modular Programming
- Console User Interface Design

Students are expected to build a fully functional interactive application that manages student records dynamically during program execution.

---

## Project Description

You are required to develop a **Student Record Management System** for a small educational institution.

The application shall maintain student records in memory using a **singly linked list** and shall store records permanently in a file.

The system must provide an interactive console dashboard that continuously displays the current student database after every operation performed by the user.

The dashboard should automatically refresh whenever:
- A student is added
- A student is deleted
- A student record is updated

The program must continue running until the user chooses to exit.

---

## Student Record Information

Each student record shall contain the following fields:

| Field       | Type    |
|-------------|---------|
| Student ID  | Integer |
| Name        | String  |
| Age         | Integer |
| Department  | String  |
| GPA         | Float   |

---

## Functional Requirements

### 1. Add Student
The user shall be able to add a new student record dynamically into the linked list.

**Requirements:**
- Memory must be allocated dynamically using `malloc()`
- Duplicate student IDs should not be allowed

### 2. Display Students
The application shall display all student records in a well-formatted table. 

### 3. Search Student
The user shall be able to search for a student using the student ID. (but this one will be easy don't mind me lol)

### 4. Update Student
The user shall be able to modify an existing student record.

### 5. Delete Student
The user shall be able to remove a student record from the linked list.

**Requirements:**
- Correct pointer manipulation must be used
- Dynamically allocated memory must be released using `free()`

### 6. Save Data to File
The application shall save all student records into a file before program termination or after every modification. Students may use either:
- Text files (`students.txt`)
- Binary files (`students.dat`)

### 7. Load Data from File
When the program starts, it shall automatically load previously saved records from the file into the linked list.

---

## Dashboard Requirement

The program must implement a **continuously refreshing console dashboard**. After every operation, the database table shall automatically be redisplayed on the screen.

---

## Technical Requirements

Students must demonstrate proper use of the following concepts (as listed in the Functional Requirements above).

---

## Additional Requirements

### Input Validation
The program should handle invalid user input gracefully. Examples:
- Negative age
- GPA outside valid range
- Duplicate IDs

### Memory Management
Students must ensure:
- No memory leaks
- Proper use of `free()`
- Safe pointer handling

---

## Deliverables

Students shall submit:
1. Complete C source code
2. Sample database file
3. Short report containing:
   - Program description
   - Data structure used
   - Challenges encountered
   - Screenshots of execution

---

## Bonus Features *(Optional)*

Students may earn bonus marks for implementing:
- Sorting records
- GPA statistics
- Colored console output
- Password protection
- Pagination
- Doubly linked lists
- Search by name
( our teacher is not nice ya its final)
---

## Learning Outcomes

Upon completion of this assignment, students should be able to:
- Build dynamic data structures in C
- Manage memory safely
- Manipulate files for persistent storage
- Design modular console applications
- Apply pointers effectively in real-world programming tasks

---

## Assessment Criteria

| Component                        | Marks |
|----------------------------------|-------|
| Correct use of structures        | 10    |
| Linked list implementation       | 20    |
| Dynamic memory management        | 15    |
| File handling                    | 15    |
| Dashboard functionality          | 15    |
| Program correctness              | 15    |
| Code organization and readability| 10    |
| **Total**                        | **100** |
