#include <string> 
#include <iostream>
#include <ctime>
#include <sqlite3.h>
#include "project_path.hpp"
#include "database_manager.h"
#include "AES.h"

int main(int argc, char* argv[]) {
    DatabaseManager DB_manager(DB_PATH);
    AES AES_manager;
    DB_manager.init_userpw_table();
    return 0;
}