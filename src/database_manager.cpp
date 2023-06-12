#include <string>
#include <iostream>
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

bool DatabaseManager::error_handler(int rc){
    if (rc) {
        std::cout<<"Cannot execute operation, "<<sqlite3_errmsg(db)<<std::endl;
        return false;
    } else {
        std::cout<<"Operation successful"<<std::endl;
        return true;
    }
}

bool DatabaseManager::init_userpw_table(){
    std::string query = "CREATE TABLE user_pw (entry_id INT NOT NULL AUTO_INCREMENT, service_name text NOT NULL, username text NOT NULL, user_hash text NOT NULL, created_at int, expiration_date int, updated_at int)";
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);
    return error_handler(rc);
}

bool DatabaseManager::insert_entry(std::string service, std::string username, std::string hash, int created_at, int expiration_date, int updated_at) {
    std::string query = "INSERT INTO user_pw (service_name, username, user_hash, created_at, expiration_date, updated_at) VALUES (" + service + ", " + username + ", " + hash + ");";
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);
    return error_handler(rc);
}

bool DatabaseManager::delete_entry(int id) {

}

bool DatabaseManager::update_entry(int id) {
    
}