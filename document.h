#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <mysql.h>
#include <mysqld_error.h>
#include <ctime>
#include <string>
#include <iostream>
#include<sstream>
#include<iomanip>
#include "Database.h"  // Include Database class

using namespace std;

class Document {
private:
    int id;
    string title;
    string category;
    string tags;
    string upload_date;
    string file_path;
    int retention_period;  // Retention period in years
    string expiration_date;  // Calculated expiration date

public:
    Document(string t, string c, string tg, string fp, int retention)
        : title(t), category(c), tags(tg), file_path(fp), retention_period(retention) {

        // Set upload date to current date
        time_t now = time(0);
        char* dt = ctime(&now);
        upload_date = dt;

        // Calculate expiration date based on retention period
        struct tm tm;
        istringstream ss(dt);  // Use istringstream for date parsing
        ss >> get_time(&tm, "%a %b %d %H:%M:%S %Y");  // Parse date with std::get_time
        tm.tm_year += retention_period;  // Add retention years to the upload date
        mktime(&tm);  // Normalize the time structure

        // Convert to a formatted string
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
        expiration_date = string(buffer);  // Store expiration date
    }

    // Method to save document to the database
    bool saveToDatabase(MYSQL* conn) {
        string query = "INSERT INTO documents (title, category, tags, upload_date, expiration_date, file_path) "
                       "VALUES ('" + title + "', '" + category + "', '" + tags + "', NOW(), '" + expiration_date + "', '" + file_path + "')";
        if (mysql_query(conn, query.c_str())) {
            cerr << "Error inserting document: " << mysql_error(conn) << endl;
            return false;  // Indicate failure
        }
        return true;  // Indicate success
    }

    // Method to check whether a document should be archived or deleted based on expiration date
    bool archiveOrDelete(Database& db) {
        string query = "SELECT * FROM documents WHERE expiration_date <= NOW()";  // Check if expired

        if (mysql_query(db.conn, query.c_str())) {
            cerr << "Error executing archiving query: " << mysql_error(db.conn) << endl;
            return false;  // Error
        }

        MYSQL_RES* result = mysql_store_result(db.conn);
        if (result) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                // Archive or delete the document
                // For simplicity, let's assume we delete expired documents
                string deleteQuery = "DELETE FROM documents WHERE id = " + string(row[0]);
                if (mysql_query(db.conn, deleteQuery.c_str())) {
                    cerr << "Error deleting expired document: " << mysql_error(db.conn) << endl;
                    return false;  // Error
                }
            }
            mysql_free_result(result);
        }
        return true;
    }
};

#endif // DOCUMENT_H
