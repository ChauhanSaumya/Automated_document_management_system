#include <iostream>
#include <string>
#include "Database.h"
#include "Document.h"

using namespace std;

void createDocument(Database& db);
void viewDocuments(Database& db);
void deleteExpiredDocuments(Database& db);
void searchDocuments(Database& db);

int main() {
    try {
        Database db;  // Create a database connection
        int choice;  // User choice for the menu
        
        while (true) {
            cout << "\n----- Document Management System -----\n";
            cout << "1. Create a Document\n";
            cout << "2. View Documents\n";
            cout << "3. Delete Expired Documents\n";
            cout << "4. Search Documents\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();  // To clear the newline character after reading the integer
            
            switch (choice) {
                case 1:
                    createDocument(db);  // Create a new document
                    break;
                case 2:
                    viewDocuments(db);  // Display all documents
                    break;
                case 3:
                    deleteExpiredDocuments(db);  // Delete expired documents
                    break;
                case 4:
  					searchDocuments(db);  // Search for documents based on different criteria
    				break;
    		    case 5:
                    cout << "Exiting the program. Goodbye!" << endl;
                    return 0;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
        
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}

// Function to create a new document
void createDocument(Database& db) {
    string title, tags, filePath, categoryName;
    int retentionPeriod;
    
    cout << "\nEnter document title (e.g: Project Plan,Legal Agreement): ";
    getline(cin, title);
    
    // Ask for category details with an example
    cout << "Enter document category (e.g: personal,legal,financial): ";
    getline(cin, categoryName);
    
    cout << "Enter document tags (comma separated e.g: contract, important, legal): ";
    getline(cin, tags);
    
    cout << "Enter document file path (e.g: '/path/to/document.pdf'): ";
    getline(cin, filePath);
    
    cout << "Enter retention period (in years e.g:5): ";
    cin >> retentionPeriod;
    cin.ignore();  // To clear the newline character after reading the integer
    
    // Create Document object
    Document doc(title, categoryName , tags, filePath, retentionPeriod);
    
    // Save document to database
    if (doc.saveToDatabase(db.conn)) {
        cout << "Document saved successfully!" << endl;
    }
}

// Function to view all documents
void viewDocuments(Database& db) {
    string query = "SELECT * FROM documents";
    
    if (mysql_query(db.conn, query.c_str())) {
        cerr << "Error fetching documents: " << mysql_error(db.conn) << endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(db.conn);
    if (result) {
        MYSQL_ROW row;
        cout << "\n----- Documents -----\n";
        while ((row = mysql_fetch_row(result))) {
            cout << "ID: " << row[0] << ", Title: " << row[1] << ", Category: " << row[2]
                 << ", Tags: " << row[3] << ", Upload Date: " << row[4] << ", Expiration Date: " << row[5]
            
			   << ", File Path: " << row[6] << endl;
        }
        mysql_free_result(result);
    } else {
        cout << "No documents found." << endl;
    }
}
// Function to delete expired documents with user confirmation
void deleteExpiredDocuments(Database& db) {
    // Query to select expired documents
    string query = "SELECT * FROM documents WHERE expiration_date <= NOW()";  // Check if expired

    if (mysql_query(db.conn, query.c_str())) {
        cerr << "Error executing query: " << mysql_error(db.conn) << endl;
        return;  // Error
    }

    MYSQL_RES* result = mysql_store_result(db.conn);
    if (result) {
        int num_rows = mysql_num_rows(result);
        if (num_rows == 0) {
            cout << "No expired documents found." << endl;
        }
        
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            // Display document details to the user
            cout << "\nExpired Document ID: " << row[0] << endl;
            cout << "Title: " << row[1] << endl;
            cout << "Category: " << row[2] << endl;
            cout << "Tags: " << row[3] << endl;
            cout << "Upload Date: " << row[4] << endl;
            cout << "Expiration Date: " << row[5] << endl;
            cout << "File Path: " << row[6] << endl;

            // Ask for user confirmation to delete the document
            char confirmation;
            cout << "\nDo you want to delete this document? (y/n): ";
            cin >> confirmation;
            cin.ignore();  // To clear the newline character after reading the character

            if (confirmation == 'y' || confirmation == 'Y') {
                string deleteQuery = "DELETE FROM documents WHERE id = " + string(row[0]);
                if (mysql_query(db.conn, deleteQuery.c_str())) {
                    cerr << "Error deleting expired document: " << mysql_error(db.conn) << endl;
                } else {
                    cout << "Document deleted successfully!" << endl;
                }
            } else {
                cout << "Document not deleted." << endl;
            }
        }
        mysql_free_result(result);
    } else {
        cerr << "Error fetching result: " << mysql_error(db.conn) << endl;
    }
}

// Function to search documents
void searchDocuments(Database& db) {
    int searchChoice;
    cout << "\nSearch by:\n";
    cout << "1. Title\n";
    cout << "2. Category\n";
    cout << "3. Tags\n";
    cout << "4. Upload Date\n";
    cout << "Enter your choice: ";
    cin >> searchChoice;
    cin.ignore();  // To clear the newline character

    string searchTerm;
    string query;

    switch (searchChoice) {
        case 1:
            cout << "Enter title to search: ";
            getline(cin, searchTerm);
            query = "SELECT * FROM documents WHERE title LIKE '%" + searchTerm + "%'";
            break;
        case 2:
            cout << "Enter category to search: ";
            getline(cin, searchTerm);
            query = "SELECT * FROM documents WHERE category LIKE '%" + searchTerm + "%'";
            break;
        case 3:
            cout << "Enter tags to search: ";
            getline(cin, searchTerm);
            query = "SELECT * FROM documents WHERE tags LIKE '%" + searchTerm + "%'";
            break;
        case 4:
            cout << "Enter upload date to search (YYYY-MM-DD): ";
            getline(cin, searchTerm);
            query = "SELECT * FROM documents WHERE upload_date LIKE '" + searchTerm + "%'";
            break;
        default:
            cout << "Invalid choice.\n";
            return;
    }

    if (mysql_query(db.conn, query.c_str())) {
        cerr << "Error executing search query: " << mysql_error(db.conn) << endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(db.conn);
    if (result) {
        MYSQL_ROW row;
        cout << "\n----- Search Results -----\n";
        while ((row = mysql_fetch_row(result))) {
            cout << "ID: " << row[0] << ", Title: " << row[1] << ", Category: " << row[2]
                 << ", Tags: " << row[3] << ", Upload Date: " << row[4] << ", Expiration Date: " << row[5]
                 << ", File Path: " << row[6] << endl;
        }
        mysql_free_result(result);
    } else {
        cout << "No documents found matching the search criteria." << endl;
    }
}