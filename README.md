# Automated Document Management System

## Overview

The **Automated Document Management System** is a C++ application designed to manage documents efficiently. This project utilizes Object-Oriented Programming (OOP) principles, including classes and objects, to create a robust system for document storage, retrieval, automated deletion and management. The system is linked to a MySQL database, allowing for persistent storage of documents and their metadata.

## Features

- **Create Documents**: Users can create new documents by providing details such as title, category, tags, file path, and retention period.
- **View Documents**: Users can view all stored documents along with their details.
- **Delete Expired Documents**: The system automatically identifies and allows users to delete documents that have expired based on their retention period.
- **Search Documents**: Users can search for documents based on various criteria, including title, category, tags, and upload date.
- **Database Integration**: The application is integrated with a MySQL database for persistent storage of documents.

## Technologies Used

- C++
- MySQL
- OOP Concepts (Classes, Objects, Inheritance, Encapsulation)

## Getting Started

### Prerequisites

- C++ compiler (e.g: DevC++, g++)
- MySQL server installed and running
- MySQL Connector/C++ library

### Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/ChauhanSaumya/document-management-system.git
   cd document-management-system

## Installation

1. Clone the repository:
   ```
   git clone https://github.com/ChauhanSaumya/document-management-system.git
   cd document-management-system
   ```

2. Set up the MySQL database:
   ```sql
   CREATE DATABASE document_management;
   USE document_management;
   
   CREATE TABLE documents (
     id INT AUTO_INCREMENT PRIMARY KEY,
     title VARCHAR(255) NOT NULL,
     category VARCHAR(100) NOT NULL,
     tags VARCHAR(255),
     upload_date DATETIME DEFAULT CURRENT_TIMESTAMP,
     expiration_date DATETIME NOT NULL,
     file_path VARCHAR(255) NOT NULL
   );
   ```

3. Update database connection details in `Database.h`:
   ```cpp
   conn = mysql_real_connect(conn, "localhost", "your_username", "your_password", "document_management", 3306, NULL, 0);
   ```

4. Compile the program:
   ```
   g++ -o document_manager main.cpp -lmysqlclient
   ```

## Usage
Create a Document: Select the option to create a document and provide the required details.
View Documents: Choose the option to view all documents stored in the database.
Delete Expired Documents: The system will prompt you to delete any documents that have expired.
Search Documents: Use the search functionality to find documents based on specific criteria.

The main menu provides the following options:
1. Create a Document
2. View Documents
3. Delete Expired Documents
4. Search Documents
5. Exit

## File Structure

- `main.cpp`: Main program logic and menu system
- `Database.h`: Database connection and query handling
- `Document.h`: Document class with methods for document operations

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.
