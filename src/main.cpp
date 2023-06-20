#include <string> 
#include <sstream>
#include <iostream>
#include <iomanip>
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

std::string print_words(word* arr){
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < sizeof(arr[i]); j++) {
            ss<<std::hex<<static_cast<int>(arr[i][j])<<" ";
        }
        ss<<std::endl;
        
    }
    std::cout<<ss.str()<<std::endl;
}

void printKeys(word* round_keys, int num_keys) {
    for (int i = 0; i < num_keys; i++) {
        std::cout << "word " << i << ": ";
        for (int j = 0; j < 4; j++) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(round_keys[i][j]) << std::dec;
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // DatabaseManager DB_manager(DB_PATH);
    // DB_manager.init_userpw_table();
    AES AES_cipher;
    unsigned char* key = AES_cipher.generate_AES_Key();
    word* expanded_keys = AES_cipher.key_expansion(key);
    int num_keys = Nb * (Nr + 1);
    printKeys(expanded_keys, num_keys);

    return 0;
}