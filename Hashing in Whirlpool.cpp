#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int BLOCK_SIZE = 64; // 512 bits
const int ROUNDS = 10;    // Whirlpool transformation rounds

const unsigned char S_BOX[256] = {
    0x18, 0x23, 0xC6, 0xE8, 0x87, 0xB8, 0x01, 0x4F, 0x36, 0xA6, 0xD2, 0xF5, 0x79, 0x6F, 0x91, 0x52,
    // Fill the rest of the 256 values as per the Whirlpool specification.
};

void SubBytes(vector<unsigned char>& state) {
    for (size_t i = 0; i < state.size(); ++i) {
        state[i] = S_BOX[state[i]];
    }
}

void ShiftColumns(vector<unsigned char>& state) {

    vector<unsigned char> temp = state;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            state[i * 8 + j] = temp[i * 8 + ((j + i) % 8)];
        }
    }
}

void MixRows(vector<unsigned char>& state) {
}

void AddRoundKey(vector<unsigned char>& state, const vector<unsigned char>& roundKey) {
    for (size_t i = 0; i < state.size(); ++i) {
        state[i] ^= roundKey[i];
    }
}

void WhirlpoolHash(const string& input) {
    vector<unsigned char> state(BLOCK_SIZE, 0); // Initialize state
    vector<unsigned char> paddedInput(input.begin(), input.end());

    paddedInput.push_back(0x80); // Append "1" bit
    while (paddedInput.size() % BLOCK_SIZE != 56) {
        paddedInput.push_back(0x00); // Append "0" bits
    }
    for (int i = 0; i < 8; ++i) {
        paddedInput.push_back(0x00);
    }
    for (size_t i = 0; i < paddedInput.size(); i += BLOCK_SIZE) {
        vector<unsigned char> block(paddedInput.begin() + i, paddedInput.begin() + i + BLOCK_SIZE);

        for (size_t j = 0; j < BLOCK_SIZE; ++j) {
            state[j] ^= block[j];
        }

        for (int round = 0; round < ROUNDS; ++round) {
            SubBytes(state);
            ShiftColumns(state);
            MixRows(state);
            AddRoundKey(state, block);
        }
    }

    cout << "Whirlpool Hash: ";
    for (unsigned char byte : state) {
        cout << hex << setw(2) << setfill('0') << (int)byte;
    }
    cout << endl;
}

int main() {
    string input;
    cout << "Enter input: ";
    getline(cin, input);

    WhirlpoolHash(input);
    return 0;
}