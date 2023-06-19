#include "AES.h"
#include <iostream>

unsigned char* AES::generate_AES_Key() {
    unsigned char* key = new unsigned char[KEY_LENGTH];         // Specify character array for key
    if (RAND_bytes(key, KEY_LENGTH) != 1) {                     // Try to generate key
        throw std::runtime_error("Failed to generate AES key"); // Key generation failed
    }
    return key;
}