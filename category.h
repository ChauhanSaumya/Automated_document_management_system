#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <mysql.h>
#include <mysqld_error.h>
#include <iostream>
#include <vector>
#include "database.h" // Include the Database class header

using namespace std;

// Category class manages document categories (e.g., legal, financial, etc.)
class Category {
private:
    string name; // Category name

public:
    // Constructor with default parameter
    Category(const string& n = "") : name(n) {}

    // Save a new category in the database
    // Returns true if category creation is successful
    bool saveCategory(Database& db) {
        // Construct SQL INSERT query to add new category
        string query = "INSERT INTO categories (name) VALUES ('" + name + "')";
        try {
            db.executeQuery(query); // Use the executeQuery method from Database class
            cout << "Category created successfully!" << endl;
            return true; // Indicate success
        } catch (const runtime_error& e) {
            cout << "Error creating category: " << e.what() << endl;
            return false; // Indicate failure
        }
    }

    // Static method to retrieve all existing categories from the database
    static vector<Category> getAll(Database& db) {
        vector<Category> categories;
        string query = "SELECT * FROM categories";

        // Execute query to fetch all categories
        try {
            db.executeQuery(query); // Use the executeQuery method from Database class
            MYSQL_RES* result = db.getResult();
            MYSQL_ROW row;

            // Iterate through result set and create category objects
            while ((row = mysql_fetch_row(result))) {
                // Assuming row[1] is the category name
                Category cat(row[1]); // Adjust index based on your table structure
                categories.push_back(cat);
            }
            mysql_free_result(result);
        } catch (const runtime_error& e) {
            cout << "Error retrieving categories: " << e.what() << endl;
        }
        return categories; // Return the list of categories
    }

    // Getter for category name
    string getName() const { return name; }
};

#endif // CATEGORY_H