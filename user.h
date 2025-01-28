#ifndef USER_H
#define USER_H

#include <string>
#include <mysql.h>
#include <mysqld_error.h>
#include <iostream>

using namespace std;

// User class manages user authentication and registration
class User {
private:
    string username; // User's username
    string password; // User's password
    string preferences; // User's preferences

public:
    // Constructor with default parameters
    User(const string& uname = "", const string& pwd = "", const string& prefs = "")
        : username(uname), password(pwd), preferences(prefs) {}

    // Register a new user in the database
    // Returns true if registration is successful
    bool registerUser (Database& db) {
        // Check if the username already exists
        string checkQuery = "SELECT * FROM users WHERE username = '" + username + "'";
        if (db.executeQuery(checkQuery)) {
            MYSQL_RES* result = db.getResult();
            if (mysql_num_rows(result) > 0) {
                // Username already exists
                cout << "Error: Username '" << username << "' already exists." << endl;
                mysql_free_result(result); // Free the result set
                return false; // Indicate failure
            }
            mysql_free_result(result); // Free the result set
        }

        // If username does not exist, proceed to register the user
        string insertQuery = "INSERT INTO users (username, password, preferences) VALUES ('" +
                             username + "', '" + password + "', '" + preferences + "')";
        if (db.executeQuery(insertQuery)) {
            cout << "User  registered successfully!" << endl;
            return true; // Indicate success
        } else {
            cout << "Error registering user: " << mysql_error(db.conn) << endl;
            return false; // Indicate failure
        }
    }

    // Authenticate user credentials
    // Returns true if username and password match
    bool authenticate(Database& db) {
        string query = "SELECT * FROM users WHERE username = '" + username + "' AND password = '" + password + "'";
        if (db.executeQuery(query)) {
            MYSQL_RES* result = db.getResult();
            bool isValid = mysql_num_rows(result) > 0; // Check if any rows are returned (valid user)
            mysql_free_result(result);
            return isValid;
        }
        return false; // Return false if query fails
    }
};

#endif // USER_H