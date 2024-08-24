This project is a prototype implementation of the RubikStone cryptographic algorithm.

This project has implemented lookup table generation algorithm, encryption algorithm, and compilation algorithm using Python and C language. Their specific contents are as follows:

- `LUTGen. py` calls AES algorithm to implement a lookup table generation algorithm
- `LUTPGen. py` implements the lookup table pool generation algorithm by calling `LUTGen. py`, which can generate a specified lookup table pool to a local folder based on the input length, output length, and number of lookup tables entered by the user.
  The lookup table files are stored in binary file format. The file naming convention is `in {lookup table input length} _out {lookup table output length} _1ut {lookup table index}. bin`

- `fast-lookup. c` is used to quickly search for table entries in a lookup table.
- `RubikStone_128_16_16_16_demo. c` implemented a demo of RubikStone-(128,16,16,16) (128 bits block, 16 bits lookup table input, 16 rounds , 16 lookup tables).
- `compiler_demo. c` implements a RubikStone encryption algorithm compiler. In this demo, it can directly output an executable file called `Compiler_output. exe`, which can encrypt the input plaintext using RubikStone-(128,16,16,16) and output the plaintext and ciphertext to the file `plaintext&ciphertext. txt`.

This project can help readers understand RubikStone's algorithm structure faster and provide an effective reference for RubikStone's application.
