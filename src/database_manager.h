#ifndef DATABASE_MANAGER_H
#define  DATABASE_MANAGER_H
#include <sqlite3.h>
#include <string>
#include <ctime>

class DatabaseManager {
public:
    DatabaseManager(const char* filename);

    ~DatabaseManager();

    bool error_handler(int rc);

    bool check_table_existence(const std::string& table_name);

    bool init_userpw_table();

    void create_user_pw_table_if_not_exist(const std::string& table_name);

    std::time_t get_posix_time();

    bool insert_entry(const std::string& table_name, const std::string& service, const std::string& username, const std::string& hash, std::time_t created_at, std::time_t expiration_date, std::time_t updated_at);

    bool delete_entry(const std::string& table_name, const std::string& condition, const std::string& condition_column);
    
    bool update_entry(const std::string& table_name, const std::string& condition_column, const std::string& condition, const std::string& column_name, const std::string& new_value);

private:
    sqlite3* db;
};


#endif