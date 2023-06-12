#ifndef DATABASE_MANAGER_HPP
#define  DATABASE_MANAGER_HPP
#include <sqlite3.h>
#include <string>

class DatabaseManager {
public:
    DatabaseManager(const char* filename);
    ~DatabaseManager();
    bool error_handler(int rc);
    bool init_userpw_table();
    bool insert_entry(std::string service, std::string username, std::string hash, int created_at, int expiration_date, int updated_at);
    bool delete_entry(int id);
    bool update_entry(int id);

private:
    sqlite3* db;
};

#endif