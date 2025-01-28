#ifndef DATABASE_H
#define DATABASE_H

#include <mysql.h>
#include <mysqld_error.h>
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

// Database class handles MySQL database connection and basic operations
class Database {
public:
    MYSQL* conn; // MySQL connection pointer
private: 
    string host, user, password, dbName; // Database connection parameters

public:
    // Constructor with default parameters
    Database(const string& h = "localhost", const string& u = "dms_user", const string& p = "secure_password", const string& db = "document_management")
        : host(h), user(u), password(p), dbName(db) {
        // Initialize MySQL connection
        conn = mysql_init(nullptr); // Use 'conn' instead of 'connection'

        // Attempt to establish connection to MySQL database
        if (!mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(), dbName.c_str(), 0, NULL, 0)) {
            // Throw runtime error if connection fails
            throw runtime_error("Database connection failed: " + string(mysql_error(conn))); // Use 'conn' here
        }
    }

    // Destructor to close MySQL connection
    ~Database() {
        if (conn) {
            mysql_close(conn); // Use 'conn' here
        }
    }

    // Execute SQL query
    // Throws an exception if the query fails
    bool executeQuery(const string& query) {
        if (mysql_query(conn, query.c_str())) { // Use 'conn' here
            throw runtime_error("Query execution failed: " + string(mysql_error(conn))); // Use 'conn' here
        }
        return true; // Query was successful
    }

    // Retrieve result set from last query
    MYSQL_RES* getResult() {
        return mysql_store_result(conn); // Use 'conn' here
    }
};

#endif // DATABASE_H