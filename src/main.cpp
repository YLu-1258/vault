#include <string> 
#include <iostream>
#include <ctime>
#include <sqlite3.h>
#include <project_path.h>


sqlite3* connect_to_database(const char* db_name) {
    sqlite3 *db;
    int rc = sqlite3_open(db_name, &db);
    
    if (rc) {
        std::cout<<"Can't open database:"<<sqlite3_errmsg(db)<<std::endl;
    } else {
        std::cout<<"Database opened succesfully at "<<db_name<<std::endl;
    }
    return db;
}

void print_error_msg(sqlite3 *db, int rc){
    if (rc) {
        std::cout<<"Cannot execute operation, "<<sqlite3_errmsg(db)<<std::endl;
    } else {
        std::cout<<"Operation successful"<<std::endl;
    }
}

bool check_table_existence(sqlite3 *db, std::string table_name) {
    std::string query = "";
    
}

int get_posix_time() {
    return static_cast<int>(std::time(nullptr));
}



void init_userpw_table(sqlite3 *db) {
    std::string query = "CREATE TABLE user_pw (entry_id INT NOT NULL AUTO_INCREMENT, service_name text NOT NULL, username text NOT NULL, user_hash text NOT NULL, created_at int, expiration_date int, updated_at int)";
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);
    print_error_msg(db, rc);
}

void add_entry(sqlite3 *db, std::string service, std::string username, std::string hash) {
    std::string query = "INSERT INTO user_pw (service_name, username, user_hash, created_at) VALUES (" + service + ", " + username + ", " + hash + ");";
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);
    print_error_msg(db, rc);
}


int main(int argc, char* argv[]) {
    sqlite3 *db = connect_to_database(DB_PATH);
    add_entry(db, "test", "test", "test");
    std::cout<<get_posix_time()<<std::endl;
    return 0;
}