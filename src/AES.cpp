#include "AES.h"
#include <iostream>

byte* AES::get_state() {
    return &state[0][0];
}

std::tuple<byte, byte> AES::extract_nibble(byte* source) {
    const int first_nibble = (*source & 0xF0) >> 4;
	const int second_nibble = (*source & 0xF) >> 0;

    return {first_nibble, second_nibble};
}

unsigned char* AES::generate_AES_Key() {
    unsigned char* key = new unsigned char[KEY_LENGTH];         // Specify character array for key
    if (RAND_bytes(key, KEY_LENGTH) != 1) {                     // Try to generate key
        throw std::runtime_error("Failed to generate AES key"); // Key generation failed
    }
    return key;
}

void AES::add_round_key(){
    unsigned char* key = generate_AES_Key()
    
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
        int new_index = calculate_new_left_rotation_index(j-rotation);
        state[row][new_index] = word[j];
    }
}

void AES::rot_word_right(int row, int rotation){
    // we want to calculate new indexes
    byte word[STATE_SIZE];
    for (int i = 0; i < STATE_SIZE; i++) {
        word[i] = state[row][i];
    }
    for (int j = 0; j < STATE_SIZE; j++) {
        int new_index = calculate_new_right_rotation_index(j+rotation);
        state[row][new_index] = word[j];
    }
}

int AES::calculate_new_left_rotation_index(int idx){
    return (idx < 0) ? 3-(abs(idx)-1) : idx;
}

int AES::calculate_new_right_rotation_index(int idx){
    return idx%4;
}

void AES::shift_rows(){
    for (int i = 0; i < STATE_SIZE; i++) {
        rot_word_left(i, i);
    }
}

void AES::inv_shift_rows(){
    for (int i = 0; i < STATE_SIZE; i++) {
        rot_word_right(i, i);
    }
}

byte AES::galois_field_multiply(byte a, byte b) {
    byte result = 0;
    byte carry;
    for (int i = 0; i < 8; i++) {
        if (b & 1) {
            result ^= a;
        }
        carry = (a & 0x80) ? 0x1b : 0x00;
        a = (a << 1) ^ carry;
        b >>= 1;
    }
    return result;
}

void AES::mix_column_at_idx(int idx) {
    byte original[STATE_SIZE];
    for (int i = 0; i < STATE_SIZE; i++) {
        original[i] = state[i][idx];
    }
    state[0][idx] = galois_field_multiply(mix_col[0][0],original[0]) ^ galois_field_multiply(mix_col[0][1],original[1]) ^ galois_field_multiply(mix_col[0][2],original[2]) ^  galois_field_multiply(mix_col[0][3],original[3]);
    state[1][idx] = galois_field_multiply(mix_col[1][0],original[0]) ^ galois_field_multiply(mix_col[1][1],original[1]) ^ galois_field_multiply(mix_col[1][2],original[2]) ^  galois_field_multiply(mix_col[1][3],original[3]);
    state[2][idx] = galois_field_multiply(mix_col[2][0],original[0]) ^ galois_field_multiply(mix_col[2][1],original[1]) ^ galois_field_multiply(mix_col[2][2],original[2]) ^  galois_field_multiply(mix_col[2][3],original[3]);
    state[3][idx] = galois_field_multiply(mix_col[3][0],original[0]) ^ galois_field_multiply(mix_col[3][1],original[1]) ^ galois_field_multiply(mix_col[3][2],original[2]) ^  galois_field_multiply(mix_col[3][3],original[3]);
}

void AES::inv_mix_column_at_idx(int idx) {
    byte original[STATE_SIZE];
    for (int i = 0; i < STATE_SIZE; i++) {
        original[i] = state[i][idx];
    }
    state[0][idx] = galois_field_multiply(inv_mix_col[0][0],original[0]) ^ galois_field_multiply(inv_mix_col[0][1],original[1]) ^ galois_field_multiply(inv_mix_col[0][2],original[2]) ^  galois_field_multiply(inv_mix_col[0][3],original[3]);
    state[1][idx] = galois_field_multiply(inv_mix_col[1][0],original[0]) ^ galois_field_multiply(inv_mix_col[1][1],original[1]) ^ galois_field_multiply(inv_mix_col[1][2],original[2]) ^  galois_field_multiply(inv_mix_col[1][3],original[3]);
    state[2][idx] = galois_field_multiply(inv_mix_col[2][0],original[0]) ^ galois_field_multiply(inv_mix_col[2][1],original[1]) ^ galois_field_multiply(inv_mix_col[2][2],original[2]) ^  galois_field_multiply(inv_mix_col[2][3],original[3]);
    state[3][idx] = galois_field_multiply(inv_mix_col[3][0],original[0]) ^ galois_field_multiply(inv_mix_col[3][1],original[1]) ^ galois_field_multiply(inv_mix_col[3][2],original[2]) ^  galois_field_multiply(inv_mix_col[3][3],original[3]);
}

void AES::mix_columns(){
    for (int i = 0; i < STATE_SIZE; i++) {
        mix_column_at_idx(i);
    }
}

void AES::inv_mix_columns() {
    for (int i = 0; i < STATE_SIZE; i++) {
        inv_mix_column_at_idx(i);
    } 
}