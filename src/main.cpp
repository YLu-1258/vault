#include <string> 
#include <sstream>
#include <iostream>
#include <ctime>
#include <sqlite3.h>
#include "project_path.hpp"
#include "database_manager.h"
#include "AES.h"

std::string print_array(unsigned char* arr) {
    std::stringstream ss;
    int cols = 4;
    int rows = 4;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            ss<<std::hex<<static_cast<int>(arr[i*rows + j])<<" ";
        } 
        ss<<"\n";
    }
    return ss.str();
}

int main(int argc, char* argv[]) {
    // DatabaseManager DB_manager(DB_PATH);
    // DB_manager.init_userpw_table();
    AES AES_manager;
    std::cout<<"Original State: "<< "\n" <<print_array(AES_manager.get_state())<<std::endl;
    AES_manager.sub_bytes();
    std::cout<<"Subbed State: "<< "\n" <<print_array(AES_manager.get_state())<<std::endl;
    AES_manager.inv_sub_bytes();
    std::cout<<"Inverse Subbed State: "<< "\n" <<print_array(AES_manager.get_state())<<std::endl;
    AES_manager.shift_rows();
    std::cout<<"Shifted Rows"<< "\n" <<print_array(AES_manager.get_state())<<std::endl;
    AES_manager.inv_shift_rows();
    std::cout<<"Inverse Shifted Rows"<< "\n" <<print_array(AES_manager.get_state())<<std::endl;
    return 0;
}