#include <iostream>
#include <string>
#include <vector>
#include "database.h"   // Include your Database class
#include "document.h"   // Include your Document class
#include "category.h"   // Include your Category class
#include "user.h"       // Include your User class

using namespace std; // Use the standard namespace

int main() {
    Database db; // Create a database connection
    int choice;

    do {
        cout << "--- Document Management System ---\n";
        cout << "1. Register User\n";
        cout << "2. Login\n";
        cout << "3. Add Document\n";
        cout << "4. Search Documents\n";
        cout << "5. Create Category\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string username, password, preferences;
                cout << "Username: ";
                cin.ignore(); 
   			    getline(cin, username);
                cout << "Password: ";
                cin >> password;
                cout << "Preferences (e.g., legal, financial, personal): ";
    			cin.ignore(); // Clear the input buffer
   			    getline(cin, preferences); // Use getline to allow spaces in preferences

                User newUser (username, password, preferences);
                if (newUser .registerUser (db)) {
                    cout << "User  registration successful!\n";
                } else {
                    cout << "Error registering user.\n";
                }
                break;
            }
            case 2: {
                string username, password;
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;

                User loginUser (username, password);
                if (loginUser .authenticate(db)) {
                    cout << "Login successful!\n";
                    // You can add additional functionality here for logged-in users
                } else {
                    cout << "Invalid username or password.\n";
                }
                break;
            }
            case 3: {
   				 string title, type, tags, filePath;
   				 cout << "Document Title: ";
    			 cin.ignore(); 
    			 getline(cin, title); 
    			 cout << "Document Type (e.g., PDF, DOCX): ";
    			 getline(cin, type); 
    			 cout << "Tags (e.g., legal, contract): ";
                 getline(cin, tags); 
                 cout << "File Path (e.g., /path/to/document.pdf): ";
                 getline(cin, filePath); 

    Document doc(title, type, tags, filePath);
    if (doc.saveToDatabase(db.conn)) { // Ensure this matches the method name
        cout << "Document added successfully!\n";
    } else {
        cout << "Error adding document.\n";
    }
    break;
}
            case 4: {
                string keyword;
                cout << "Enter Search Keyword (title, tags, or category): ";
   			    cin.ignore(); // Clear the input buffer
  			    getline(cin, keyword); // Use getline to allow spaces in the keyword
                
                auto results = Document::search(db, keyword);
                cout << "Search Results:\n";
                for (const auto& result : results) {
                    cout << result.getTitle() << " (" << result.getCategory() << ")\n";
                    cout << "   - Tags: " << result.getTags() << "\n";
                    cout << "   - Upload Date: " << result.getUploadDate() << "\n";
                    cout << "   - File Path: " << result.getFilePath() << "\n";
                }
                cout << "Total Documents Found: " << results.size() << "\n";
                break;
            }
            case 5: {
                string categoryName;
                cout << "Enter Category Name: ";
                cin >> categoryName;

                Category newCategory(categoryName);
                if (newCategory.saveCategory(db)) {
                    cout << "Category created successfully!\n";
                } else {
                    cout << "Error creating category.\n";
                }
                break;
            }
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

        cout << "Press Enter to continue...";
        cin.ignore(); // Clear the newline character from the input buffer
        cin.get(); // Wait for user to press Enter

    } while (choice != 6);

    return 0;
}
