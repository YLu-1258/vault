#include <string> 
#include <iostream>
#include <sqlite3.h>
#include <project_path.h>


sqlite3* open_database(const char* db_name) {
    sqlite3 *db;
    int rc = sqlite3_open(db_name, &db);
    
    if (rc) {
        std::cout<<"Can't open database:"<<sqlite3_errmsg(db)<<std::endl;
    } else {
        std::cout<<"Database opened succesfully at "<<db_name<<std::endl;
    }
    return db;
}

int add_entry(sqlite3 *db) {
    
}


int main(int argc, char* argv[]) {
    sqlite3 *db = open_database(DB_PATH);
    return 0;
}