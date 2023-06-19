#include <string>
#include <iostream>
#include <ctime>
#include "database_manager.h"


DatabaseManager::DatabaseManager(const char* db_name) {
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

bool DatabaseManager::error_handler(int rc){
    if (rc) {
        std::cout<<"Cannot execute operation, "<<sqlite3_errmsg(db)<<std::endl;
        return false;
    } else {
        std::cout<<"Operation successful"<<std::endl;
        return true;
    }
}

bool DatabaseManager::check_table_existence(const std::string& table_name){
    std::string query = "SELECT name FROM sqlite_master WHERE type = 'table' AND name = '" + table_name + "';";
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);
    return rc == SQLITE_OK;
}

void DatabaseManager::create_user_pw_table_if_not_exist(const std::string& table_name) {
    bool existence = check_table_existence(table_name);
    if (!existence) {
        init_userpw_table();
        return;
    }
    else {
        return;
    }
}

std::time_t DatabaseManager::get_posix_time(){
    return std::time(nullptr);
}

bool DatabaseManager::init_userpw_table(){
    std::string query = "CREATE TABLE user_records (entry_id INTEGER PRIMARY KEY AUTOINCREMENT, service_name TEXT NOT NULL, username TEXT NOT NULL, user_hash TEXT NOT NULL, created_at INT, expiration_date INT, updated_at INT);";
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);
    return error_handler(rc);
}

bool DatabaseManager::insert_entry(const std::string& table_name, const std::string& service, const std::string& username, const std::string& hash, std::time_t created_at, std::time_t expiration_date, std::time_t updated_at) {
    std::string query = "INSERT INTO user_records (service_name, username, user_hash, created_at, expiration_date, updated_at) VALUES (" + service + ", " + username + ", " + hash + ");";
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);
    return error_handler(rc);
}

bool DatabaseManager::delete_entry(const std::string& table_name, const std::string& condition, const std::string& condition_column) {
    std::string query = "DELETE FROM " + table_name + "WHERE " + condition_column + " = " + condition + ";";
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);
    return error_handler(rc);
}

bool DatabaseManager::update_entry(const std::string& table_name, const std::string& condition_column, const std::string& condition, const std::string& column_name, const std::string& new_value) {
    std::string query = "UPDATE " + table_name + " SET " + column_name + " = " + new_value + " WHERE " + condition_column + " = " + condition + ";";
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);
    return error_handler(rc);
}
