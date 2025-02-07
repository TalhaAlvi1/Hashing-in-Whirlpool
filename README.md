# Objective
Whirlpool is a cryptographic hash function designed to produce a 512-bit fixed-length hash value for any input message. It is based on a modified Advanced Encryption Standard (AES) block cipher and ensures high security and efficiency for data integrity and authentication.

# Algorithm: 
Preprocessing
1. Divide the Input Message:
- Split the input into 512-bit (64-byte) blocks.
- If the last block is incomplete, apply padding using the Merkle-Damgård scheme (add a "1" bit followed by "0" bits until the block is complete, then append the message length as a 256-bit value).
2. Initialization:
- Set the initial state to a predefined 512-bit value (Initialization Vector or IV).
  
Hash Computation for Each Block
1. State Update:
- XOR the current message block with the current hash state.
2. Apply Whirlpool Transformation:
- Perform 10 rounds of the following transformations on the state:
  - SubBytes: Substitute each byte using a fixed substitution table (S-Box).
  - ShiftColumns: Rotate bytes in each column by predetermined offsets.
  - MixRows: Multiply bytes in each row with a fixed matrix over a Galois field (GF(2^8)).
  - AddRoundKey: XOR the round key with the current state. The round key is derived from the input block and state.
3. Finalize the State:
- After processing all blocks, the resulting state is the Whirlpool hash of the input.
  
