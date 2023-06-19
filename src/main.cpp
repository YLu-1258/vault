#include <string> 
#include <iostream>
#include <ctime>
#include <sqlite3.h>
#include "project_path.hpp"
#include "database_manager.h"

int main(int argc, char* argv[]) {
    DatabaseManager DB_manager(DB_PATH);
    DB_manager.init_userpw_table();
    return 0;
}