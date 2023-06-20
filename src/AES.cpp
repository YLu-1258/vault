#include "AES.h"
#include <iostream>


unsigned char* AES::generate_AES_Key() {
    unsigned char* key = new unsigned char[KEY_LENGTH];         // Specify character array for key
    if (RAND_bytes(key, KEY_LENGTH) != 1) {                     // Try to generate key
        throw std::runtime_error("Failed to generate AES key"); // Key generation failed
    }
    return key;
}

void AES::sub_bytes(){
    unsigned char row, column;
    for (int i = 0; i < STATE_SIZE; i++) {
        for (int j = 0; j < STATE_SIZE; j++) {
            std::tie(row, column) = extract_nibble(&state[i][j]);
            state[i][j] = s_box[row][column];
        }
    }
}

void AES::inv_sub_bytes(){
    unsigned char row, column;
    for (int i = 0; i < STATE_SIZE; i++) {
        for (int j = 0; j < STATE_SIZE; j++) {
            std::tie(row, column) = extract_nibble(&state[i][j]);
            state[i][j] = inv_s_box[row][column];
        }
    }
}

void AES::rot_word_left(int row, int rotation){
    // we want to calculate new indexes
    byte word[STATE_SIZE];
    for (int i = 0; i < STATE_SIZE; i++) {
        word[i] = state[row][i];
    }
    for (int j = 0; j < STATE_SIZE; j++) {
        int new_index = calculate_new_rotation_index(j-rotation);
        state[row][new_index] = word[j];
    }
}

int AES::calculate_new_rotation_index(int idx){
    return (idx < 0) ? 3-(abs(idx)-1) : idx;
}

void AES::shift_rows(){
    for (int i = 0; i < STATE_SIZE; i++) {
        rot_word_left(i, i);
    }
}

std::tuple<byte, byte> AES::extract_nibble(byte* source) {
    const int first_nibble = (*source & 0xF0) >> 4;
	const int second_nibble = (*source & 0xF) >> 0;

    return {first_nibble, second_nibble};
}

byte* AES::get_state() {
    return &state[0][0];
}