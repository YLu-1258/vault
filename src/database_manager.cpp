#include <string>
#include <iostream>
#include <ctime>
#include "database_manager.hpp"

DatabaseManager::DatabaseManager(const char* db_name) {
    static sqlite3* db = nullptr;
    if (!db) {
        int rc = sqlite3_open(db_name, &db);

        if (rc != SQLITE_OK) {
            std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            db = nullptr;
        } else {
            std::cout << "Database opened successfully at " << db_name << std::endl;
        }
    }
}

DatabaseManager::~DatabaseManager() {
    if (db) {
        sqlite3_close(db);
        std::cout << "Database connection closed." << std::endl;
    }
}

bool DatabaseManager::error_handler(int rc, char* error_message){
    if (rc) {
        std::cout<<"Cannot execute operation, "<<error_message<<std::endl;
        return false;
    } else {
        std::cout<<"Operation successful"<<std::endl;
        return true;
    }
}

bool DatabaseManager::init_userpw_table(){
    std::string query = "CREATE TABLE user_records (entry_id INT NOT NULL AUTO_INCREMENT, service_name text NOT NULL, username text NOT NULL, user_hash text NOT NULL, created_at int, expiration_date int, updated_at int)";
    char* error_message;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &error_message);
    return error_handler(rc, error_message);
}

bool DatabaseManager::insert_entry(const std::string& table_name, const std::string& service, const std::string& username, const std::string& hash, std::time_t created_at, std::time_t expiration_date, std::time_t updated_at) {
    std::string query = "INSERT INTO user_records (service_name, username, user_hash, created_at, expiration_date, updated_at) VALUES (" + service + ", " + username + ", " + hash + ");";
    char* error_message;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &error_message);
    return error_handler(rc, error_message);
}

bool DatabaseManager::delete_entry(const std::string& table_name, const std::string& condition, const std::string& condition_column) {
    std::string query = "DELETE FROM " + table_name + "WHERE " + condition_column + " = " + condition + ";";
    char* error_message;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &error_message);
    return error_handler(rc, error_message);
}

bool DatabaseManager::update_entry(const std::string& table_name, const std::string& condition_column, const std::string& condition, const std::string& column_name, const std::string& new_value) {
    std::string query = "UPDATE " + table_name + " SET " + column_name + " = " + new_value + " WHERE " + condition_column + " = " + condition + ";";
    char* error_message;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &error_message);
    return error_handler(rc, error_message);
}