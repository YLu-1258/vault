#ifndef AES_H
#define AES_H
#define KEY_LENGTH 32
#include <openssl/rand.h>

class AES {
    public: // Methods for use
        
    private: // Algorithm logic
        unsigned char* generate_AES_Key();
};

#endif