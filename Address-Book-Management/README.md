# Address Book Management System

A console-based Address Book Management System developed in C to store, search, modify, delete, and manage contact information using structures, arrays, functions, and file handling.

## Features

- Create new contacts
- Search contacts by name, phone number, or email
- Edit contact name, phone number, and email
- Delete contacts with confirmation
- Display all stored contacts
- Save contact records to a file
- Load saved contacts when the application starts
- Validate names, phone numbers, and email addresses
- Prevent duplicate phone numbers and email addresses
- Support up to 100 contacts

## Technologies Used

- C Programming
- Structures
- Arrays
- Functions
- String handling
- File handling
- Input validation

## Project Structure

```text
Address-Book-Management/
├── main.c
├── contact.c
├── contact.h
├── file.c
├── file.h
├── populate.c
├── populate.h
├── contacts.txt
└── README.md
```

## Compilation

Compile the project using GCC:

```bash
gcc -Wall -Wextra main.c contact.c file.c populate.c -o address_book
```

## Execution

Run the application:

```bash
./address_book
```

## Main Menu

```text
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save and Exit
```

## Contact Validation

- **Name:** Accepts alphabetic characters and spaces.
- **Phone number:** Requires a 10-digit numeric phone number.
- **Email:** Performs basic validation for permitted characters, digits, the `@` symbol, and dots.
- **Duplicate checking:** Prevents duplicate phone numbers and email addresses.

## File Storage

Contact records are stored in `contacts.txt`. The application loads saved records during initialization and saves contact data when exiting through the save-and-exit option.

## Learning Outcomes

- Working with structures and arrays in C
- Implementing CRUD operations (Create, Read, Update, Delete)
- Searching and modifying records
- String manipulation and validation
- File handling for persistent storage
- Organizing a multi-file C project

