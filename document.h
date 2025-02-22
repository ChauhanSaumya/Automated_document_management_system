#ifndef DOCUMENT_H
#define DOCUMENT_H

// Include necessary headers
#include <string>
#include <vector>
#include <mysql.h>
#include <mysqld_error.h>
#include <iostream>
#include <ctime> // Include ctime for time functions

using namespace std;

// Document class definition
class Document {
private:
    int id; // Unique document identifier
    string title; // Document title
    string category; // Document category
    string tags; // Document tags for searching
    string upload_date; // Date and time of document upload
    string file_path; // Path to the physical document file

public:
    Document(string t, string c, string tg, string fp)
        : title(t), category(c), tags(tg), file_path(fp) {
        // Initialize upload_date to the current time
        time_t now = time(0);
        char* dt = ctime(&now);
        upload_date = dt; // Store formatted date
    }

    // Method to save the document to the database
    bool saveToDatabase(MYSQL* conn) {
        string query = "INSERT INTO documents (title, category_id, tags, upload_date, file_path) VALUES ('" +
                       title + "', (SELECT id FROM categories WHERE name='" + category + "'), '" +
                       tags + "', NOW(), '" + file_path + "')";
        if (mysql_query(conn, query.c_str())) {
            cerr << "Error inserting document: " << mysql_error(conn) << endl;
            return false; // Indicate failure
        } else {
            return true; // Indicate success
        }
    }

    // Static method to search documents by keyword
    static vector<Document> search(Database& db, const string& keyword) {
        vector<Document> results;
        string query = "SELECT * FROM documents WHERE title LIKE '%" + keyword + "%'";

        if (mysql_query(db.conn, query.c_str())) {
            cerr << "Error executing search query: " << mysql_error(db.conn) << endl;
            return results; // Return empty results on error
        }

        MYSQL_RES* result = mysql_store_result(db.conn);
        if (result) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                // Assuming the columns are in the order: id, title, category_id, tags, upload_date, file_path
                Document doc(row[1], "", row[3], row[5]); // Adjust based on your table structure
                results.push_back(doc);
            }
            mysql_free_result(result);
        }
        return results;
    }

    // Getter methods to access document properties
    string getTitle() const { return title; }
    string getCategory() const { return category; }
    string getTags() const { return tags; }
    string getUploadDate() const { return upload_date; }
    string getFilePath() const { return file_path; }
};

#endif // DOCUMENT_H
