# Automated Document Management System (DMS)

## Description
The Automated Document Management System (DMS) is designed to help individuals manage their documents efficiently by automatically categorizing, tagging, and storing them based on their content. The system offers powerful search and indexing capabilities for easy document retrieval, alongside lifecycle management features to ensure proper archiving and deletion of documents over time.

## Key Features
- **Document Categorization and Tagging**: Automatically categorizes documents (e.g., legal, financial) and tags them based on their content.
- **Document Search and Indexing**: 
  - Full-Text Search: Allows searching through the entire content of documents.
  - Advanced Filters: Filter documents by type, category, tags, or creation date.
  - Search Suggestions: Real-time suggestions and auto-complete as you search.
  - Metadata Search: Search documents based on metadata like author or creation date.
- **Document Lifecycle Management**: 
  - Archiving: Automatically archives documents based on their age or category.
  - Retention Policies: Define rules for how long documents are kept (e.g., financial records for 7 years).
  - Automatic Deletion: Automatically deletes documents when they reach the end of their lifecycle.
  - Reminders: Sends reminders to review documents before deletion or archiving.
- **Document Upload & OCR**: Users can upload documents, and the system automatically categorizes them. OCR scans and extracts text from scanned documents for easy searchability.

## Tech Stack
- **C++ (OOP)**: For implementing the core application logic, including file handling, categorization, and interactions with the database.
- **MySQL**: For storing document metadata (e.g., title, tags, date) and other related information in a structured manner.
- **SQL**: For querying and manipulating data within the MySQL database.
- **Boost Libraries**: For file handling and string manipulations in C++ (optional but useful).
- **C++ MySQL Connector**: A library (e.g., MySQL Connector/C++) to connect C++ with MySQL for database operations.

## Installation Instructions
1. **Set Up Development Environment**:
   - Install a C++ compiler (e.g., GCC for Linux, MinGW for Windows).
   - Install MySQL (Community Edition).
   - Install MySQL C++ Connector to enable C++ to interact with MySQL.
   - Use an IDE like Visual Studio, Code::Blocks, or CLion for easier development.

2. **Clone the Repository**:
   ```bash
   git clone https://github.com/ChauhanSaumya/document-management-system.git
   cd document-management-system
