#LUTGen.py
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes


def generate_aes_lut(output_bytes, lut_size, filename):
    """
    Generates an AES lookup table and saves it to a file.

    :param output_bytes: The number of output bytes to save per lookup table entry (max 16)
    :param lut_size: The size of the lookup table (i.e., how many distinct input values)
    :param filename: The filename to save the lookup table
    """
    if output_bytes > 16:
        raise ValueError("output_bytes cannot be greater than 16")

    key = get_random_bytes(16)
    cipher = AES.new(key, AES.MODE_ECB)

    with open(filename, 'wb') as lut_file:
        for i in range(lut_size):
            # Create a full AES block where the first N bytes are our input of interest (N <= 8), and the rest are padding
            input_block = i.to_bytes(min(8, lut_size.bit_length()), 'big') + b'\x00' * (
                        16 - min(8, lut_size.bit_length()))

            # Encrypt the full block
            encrypted = cipher.encrypt(input_block)

            # Extract the first output_bytes of the encrypted result and write it to the file
            lut_file.write(encrypted[:output_bytes])
