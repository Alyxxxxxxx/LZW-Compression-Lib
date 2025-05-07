# LZW-Compression-Lib
C library for file compression using the LZW algorithm, optimized with radix tree structures for efficient pattern management. Designed for Linux environments.

## Table of Contents
1. [Overview](#overview)
2. [Features](#features)
3. [Requirements](#requirements)
4. [Installation](#installation)
5. [Usage](#usage)
6. [Implementation Details](#implementation-details)
   - [LZW Compression Algorithm](#lzw-compression-algorithm)
   - [Radix Tree Dictionary](#radix-tree-dictionary)
   - [Bit-to-Byte Conversion](#bit-to-byte-conversion)
   - [Dictionary Reset](#dictionary-reset)
   - [Null Character Handling](#null-character-handling)
7. [Code Structure](#code-structure)
   - [Key Functions](#key-functions)
8. [Limitations](#limitations)
9. [Potential Improvements](#potential-improvements)
10. [Contributing](#contributing)
11. [License](#license)

## Overview
The LZW Compression Library is a high-performance C library designed for compressing text and image files in a Linux environment using the Lempel-Ziv-Welch (LZW) algorithm. By leveraging a radix tree for dictionary management, the library achieves efficient pattern storage and retrieval, enabling significant file size reduction. The implementation uses a 12-bit dictionary, supporting up to 4096 patterns, and is optimized for UTF-8 encoded files. This library is ideal for applications requiring robust and scalable file compression.

## Features
- **Efficient LZW Compression**: Reduces file sizes by encoding repetitive patterns using the LZW algorithm.
- **Radix Tree Implementation**: Enables logarithmic-time operations for pattern insertion, search, and deletion.
- **12-bit Dictionary**: Supports 4096 patterns, including the 256 ASCII extended characters.
- **Binary File I/O**: Ensures accurate reading and writing of binary data.
- **Buffer Management**: Seamlessly converts 12-bit codes to 8-bit bytes with overflow handling.
- **Dictionary Reset**: Automatically reinitializes the dictionary upon reaching the 4096-pattern limit.
- **Null Character Handling**: Replaces null characters with the string "cero" to maintain data integrity.

## Requirements
- **Operating System**: Linux
- **Compiler**: GCC or any C99-compliant compiler
- **Dependencies**: Standard C libraries (`stdio.h`, `stdlib.h`, `string.h`)

## Installation
To install the library, follow these steps:
1. Clone the repository:
   ```bash
   git clone https://github.com/username/lzw-compression.git
   ```
2. Navigate to the project directory:
   ```bash
   cd lzw-compression
   ```
3. Compile the source code:
   ```bash
   make
   ```
   This generates the executable `lzw_compression`.

## Usage
To compress a file, execute the program with the input file specified in the source code:
1. Open the `main.c` file and manually update the input file name in the `main` function:
   ```c
   char *inputFile = "your_file_name_here"; // e.g., "image.bmp" or "text.txt"
   ```
2. Recompile the program:
   ```bash
   make
   ```
3. Run the program:
   ```bash
   ./lzw_compression
   ```
- **Output**: A compressed file named `compressed.lzw` will be generated in the project directory.
- **Note**: The input file name must be manually set in the source code before compilation, as the program does not currently accept command-line arguments for file input.

**Example**:
To compress `image.bmp`, modify `main.c` to:
```c
char *inputFile = "image.bmp";
```
Then compile and run:
```bash
make
./lzw_compression
```

## Implementation Details
### LZW Compression Algorithm
The LZW algorithm initializes a dictionary with single-character patterns (ASCII 0–255) and processes the input as follows:
1. Constructs a string by appending characters.
2. If the current string exists in the dictionary, it reads the next character.
3. If the string is not found:
   - Outputs the code for the last known string.
   - Adds the new string to the dictionary with a code from 256 to 4095.
4. Continues until all input is processed, outputting the final string’s code.

### Radix Tree Dictionary
The dictionary is implemented as a radix tree, which:
- Compresses common prefixes to minimize redundancy.
- Supports efficient insertion and search in logarithmic time.
- Uses a 12-bit `BitField` to ensure codes stay within the dictionary’s limit.

**Key Structures**:
- **RadixTree**: Stores the root node, next pattern identifier, and a flag for dictionary fullness.
- **RadixNode**: Represents a node with a boolean for pattern end, a pattern code, and child edges.
- **RadixEdge**: Connects nodes with a pattern string and a pointer to the next node.

### Bit-to-Byte Conversion
The library adheres to a 12-bit dictionary standard with the following process:
1. **Decimal to Binary**: Converts pattern codes to 12-bit binary strings.
2. **Buffer Management**: Combines buffered bits (if any) with the 12-bit code to form 8-bit bytes.
3. **Byte Writing**: Writes complete 8-bit bytes to the output file, storing excess bits in the buffer.
4. **Finalization**: Pads the buffer with zeros if less than 8 bits remain and writes the final byte.

### Dictionary Reset
Upon reaching the 4096-pattern limit:
1. Adds the last pattern (code 4095).
2. Writes the previous pattern to the output.
3. Resets the dictionary, reinitializing with ASCII characters (0–255).

### Null Character Handling
Null characters (`\0`) are replaced with the string `"cero"` to prevent premature termination of pattern reading. This approach ensures continuous processing but may increase the compressed file size for files with frequent null characters.

## Code Structure
The library is modular, with separate files for different functionalities:

- **`LZWCompression.h/c`**: Implements the core LZW compression logic and dictionary initialization.
- **`RadixTree.h/c`**: Manages the radix tree for dictionary storage and operations.
- **`RadixNode.h/c`**: Defines the node structure and related functions.
- **`RadixEdge.h/c`**: Handles edge connections between nodes.
- **`ByteManagement.h/c`**: Provides bit-to-byte conversion and buffer management.
- **`FileManagement.h/c`**: Facilitates binary file reading schrijven.

### Key Functions
- **Compression**:
  - `compressLZW`: Orchestrates the compression process.
  lindo
  - `initializeDictionary`: Populates the dictionary with ASCII characters.
- **Radix Tree**:
  - `createRadixTree`: Initializes a new radix tree.
  - `insertPattern`: Adds a pattern to the tree.
  - `searchPattern`: Locates a pattern in the tree.
  - `resetRadixTree`: Clears and reinitializes the dictionary.
- **Byte Management**:
  - `convertDecimalToBinary`: Converts decimal codes to 12-bit binary.
  - `binaryToUint`: Converts 8-bit binary strings to unsigned integers.
  - `writeByte`: Writes bytes to the output file with buffer handling.
  - `getBufferByte`: Writes remaining buffer data.
- **File Management**:
  - `createFileManagement`: Initializes a file handler.
  - `openFile`, `writeFile`, `closeFile`: Manage file operations.

## Limitations
- **Small Files**: LZW compression may increase file size for small inputs with few repetitive patterns due to dictionary overhead.
- **Null Characters**: Replacing nulls with `"cero"` can inflate compressed file sizes.
- **Manual File Input**: The input file name must be hardcoded in `main.c`, limiting usability.
- **Memory Usage**: The radix tree requires significant memory for large dictionaries.
- **Single-Threaded**: Compression is not optimized for parallel processing.
- **No Decompression**: The library currently supports only compression.

## Potential Improvements
The following enhancements could improve the library’s functionality and usability:
- **Decompression Support**: Implement a decompression function to restore `.lzw` files.
- **Command-Line Arguments**: Allow input file specification via command-line arguments instead of hardcoding.
- **Dynamic Dictionary Sizing**: Support configurable dictionary sizes (e.g., 10-bit or 14-bit) for flexibility.
- **Optimized Null Handling**: Develop a more compact representation for null characters.
- **Parallel Processing**: Introduce multi-threading to accelerate compression for large files.
- **Cross-Platform Compatibility**: Extend support to Windows and macOS.
- **Error Handling**: Enhance robustness with detailed error messages and recovery mechanisms.
- **Unit Tests**: Add comprehensive tests to ensure reliability and maintainability.

## Contributing
Contributions are highly encouraged to enhance the library’s functionality and performance. To contribute:
1. Fork the repository.
2. Create a feature branch:
   ```bash
   git checkout -b feature/your-feature
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add your feature"
   ```
4. Push to the branch:
   ```bash
   git push origin feature/your-feature
   ```
5. Open a pull request on GitHub.

**Contribution Ideas**:
- Implement decompression functionality.
- Add support for command-line file input.
- Optimize memory usage in the radix tree.
- Develop unit tests using a framework like Check or CUnit.
- Improve documentation with code comments and examples.

Please adhere to the existing code style, include relevant tests, and provide clear descriptions in pull requests.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

*This LZW Compression Library is designed for efficiency and scalability, offering a robust solution for file compression in Linux environments. Contributions to address limitations or add new features are warmly welcomed.*
