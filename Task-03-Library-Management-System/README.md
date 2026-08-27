# Library Management System

A console-based **Library Management System** developed in C++ as part of the **Thiranex C++ Internship**.

The application manages books, library members, book issuing, book returns, searching, and persistent data storage using text files.

---

## Project Objective

The objective of this project is to build a simple and efficient Library Management System using C++ and Object-Oriented Programming concepts.

The system allows users to:

- Add books
- Add members
- Display books
- Search for books
- Issue books
- Return books
- Store records permanently using text files

---

## Features

### Book Management

- Add new books
- Store Book ID
- Store book title
- Store author name
- Track book availability
- Display stored books

### Member Management

- Add new library members
- Store Member ID
- Store member name

### Search Functionality

Books can be searched using:

- Book title
- Author name

### Book Issue System

- Issue a book to a registered member
- Verify that the book exists
- Verify that the member exists
- Prevent an unavailable book from being issued again
- Update book availability after issue

### Book Return System

- Return an issued book
- Update book availability after return
- Make the returned book available for future borrowing

### File Handling

The application stores book and member information in text files.

This allows the data to remain available even after the program is closed and started again.

---

## Technologies Used

- C++
- Object-Oriented Programming
- File Handling
- Standard Template Library
- GCC / G++
- Visual Studio Code
- Git
- GitHub

---

## C++ Concepts Used

This project demonstrates the use of:

- Classes and Objects
- Functions
- Constructors
- File Input and Output
- Conditional Statements
- Loops
- Strings
- Searching Records
- Data Validation
- Object-Oriented Programming
- Persistent Data Storage

---

## Project Structure

    Task-03-Library-Management-System/
    |
    |-- main.cpp
    |-- books.txt
    |-- members.txt
    |-- .gitignore
    |-- README.md
    |
    `-- screenshots/
        |-- main-menu.png
        |-- add-book.png
        |-- add-member.png
        |-- search-book.png
        |-- issue-book.png
        `-- return-book.png

---

## How to Compile

Open the terminal inside the project directory and run:

    g++ main.cpp -o library

This will generate the executable file:

    library.exe

on Windows.

---

## How to Run

After compilation, run:

    .\library.exe

or:

    library.exe

---

## Sample Book Record

    Book ID : 101
    Title   : The Alchemist
    Author  : Paulo Coelho
    Status  : Available

---

## Sample Member Record

    Member ID   : 201
    Member Name : Rahul Sharma

---

## Example Workflow

A typical workflow of the application is:

1. Start the Library Management System.
2. Add a new book.
3. Add a new library member.
4. Search for the book using its title or author.
5. Issue the book to the registered member.
6. Return the issued book.
7. Exit the program.
8. Restart the application.
9. Search for the saved book again to verify data persistence.

---

## Data Persistence

The application uses text files to save information permanently.

### books.txt

Stores book information such as:

- Book ID
- Book title
- Author name
- Availability status

### members.txt

Stores member information such as:

- Member ID
- Member name

The stored information remains available even after the program is closed.

---

## Screenshots

The `screenshots` folder contains screenshots demonstrating the major functions of the application.

### Main Menu

Shows the main options available in the Library Management System.

### Add Book

Shows the process of adding a new book.

### Add Member

Shows the process of registering a new library member.

### Search Book

Shows a successful book search using the title or author.

### Issue Book

Shows a book being successfully issued to a registered member.

### Return Book

Shows an issued book being successfully returned.

---

## Git Ignore

Compiled executable and object files are excluded from the Git repository using the `.gitignore` file.

The `.gitignore` contains:

    *.exe
    *.o

This prevents generated compilation files from being uploaded to GitHub.

---

## Expected Outcome

The completed application provides a functional Library Management System capable of:

- Managing books
- Managing library members
- Searching for books
- Issuing books
- Returning books
- Tracking book availability
- Storing data using files
- Retaining stored data after restarting the program

---

## Learning Outcomes

Through this project, I practiced:

- C++ programming
- Object-Oriented Programming
- Classes and objects
- File handling
- Data persistence
- Searching records
- Updating stored records
- Application flow management
- Organizing a C++ project
- Using Git and GitHub for version control

---

## Task

**Task 03 - Library Management System**

Developed as part of the **Thiranex C++ Internship Program**.