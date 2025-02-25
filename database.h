#ifndef DATABASE_H
#define DATABASE_H

#include <mysql.h>
#include <mysqld_error.h>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Database {
public:
    MYSQL* conn;  // MySQL connection pointer

    // Constructor
    Database() {
        conn = mysql_init(0);  // Initialize MySQL connection
        if (!conn) {
            cerr << "MySQL initialization failed: " << mysql_error(conn) << endl;
            exit(1);  // Exit program if MySQL init fails
        }

        // Attempt to connect to the database
        conn = mysql_real_connect(conn, "localhost", "root", "matricesop0", "document_management", 3306, NULL, 0);
        
        if (!conn) {
            cerr << "Connection Failed: " << mysql_error(conn) << endl;
            exit(1);  // Exit program if connection fails
        } else {
            cout << "Successfully connected to the database!" << endl;
        }
    }

    // Destructor
    ~Database() {
        if (conn) {
            mysql_close(conn);
        }
    }

    // Execute SQL query
    bool executeQuery(const string& query) {
        if (mysql_query(conn, query.c_str())) {
            cerr << "Query execution failed: " << mysql_error(conn) << endl;
            return false;
        }
        return true;
    }

    // Retrieve result set from last query
    MYSQL_RES* getResult() {
        return mysql_store_result(conn);
    }
};

#endif