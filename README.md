# Document Management System

A C++ application for managing documents with MySQL database integration. This system allows users to create, view, search, and manage documents with expiration dates.

## Features

- **Document Creation**: Add new documents with title, category, tags, file path, and retention period
- **Document Viewing**: Browse all documents stored in the database
- **Document Searching**: Search for documents by title, category, tags, or upload date
- **Automatic Expiration**: Track document expiration dates based on retention periods
- **Expired Document Management**: Review and delete expired documents

## Prerequisites

- C++ compiler
- MySQL server
- MySQL Connector/C++ library

## Installation

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/document-management-system.git
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

Run the compiled program:
```
./document_manager
```

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

## License

[Add your license information here]

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.
