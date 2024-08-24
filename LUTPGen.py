import LUTGen
import math

def read_and_print_lut(filename, bytes_per_entry):
    """
    Reads an AES lookup table file and prints its contents.

    :param filename: The name of the lookup table file
    :param bytes_per_entry: The number of bytes per lookup table entry
    """
    with open(filename, 'rb') as lut_file:
        # Read the entire file content
        lut_content = lut_file.read()

        # Iterate through the file content, printing by the size of each lookup table entry
        for i in range(0, len(lut_content), bytes_per_entry):
            # Get the data for the current lookup table entry
            entry = lut_content[i:i + bytes_per_entry]

            # Convert the byte data to a hexadecimal string, removing the prefix 'b' and trailing '0x'
            hex_str = entry.hex()

            # Print the hexadecimal string, adding indices or other information as needed
            print(f"Entry {i // bytes_per_entry}: {hex_str}")


def generate_lut_pool(output_bytes, lut_size, num_luts):
    """
    Generates a series of AES lookup tables and saves them to files.

    :param output_bytes: The number of output bytes to save per lookup table entry (max 16)
    :param lut_size: The size of each lookup table (i.e., how many distinct input values)
    :param num_luts: The number of lookup tables to generate
    """
    if output_bytes > 16:
        raise ValueError("output_bytes cannot be greater than 16")

    for i in range(num_luts):
        # Construct the filename, e.g., lut0.bin, lut1.bin, ...
        filename = f"in{int(math.log2(lut_size))}_out{output_bytes*8}_lut{i}.bin"

        # Call the function from LUTGen.py to generate the lookup table
        LUTGen.generate_aes_lut(output_bytes, lut_size, filename)

        print(f"Generated LUT {i + 1}: {filename}")


if __name__ == "__main__":
    # User input (hardcoded here for demonstration, replace with input() functions for actual use)
    lut_size = 2**int(input("请输入查找表的输入长度（bits）："))  # 每个查找表的大小
    output_bytes = int(input("请输入查找表的输出长度（bits）："))//8  # 每个查找表项要保存的输出字节数
    num_luts = int(input("请输入查找表的数量："))  # 想要生成的查找表数量

    # Call the function to generate the lookup table pool
    generate_lut_pool(output_bytes, lut_size, num_luts)


    # Example call to the function, assuming each lookup table entry saves 8 bytes, filename is 'lut8.bin'
    # read_and_print_lut('lut8.bin', 8)