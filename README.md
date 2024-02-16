
# Visual Compiler

## Overview

The Visual Compiler is a C++ program designed to parse a text file containing variable declarations and assignments. It generates output files with information about these variables.

## Features

- Parses variable declarations and assignments from a text file.
- Generates output files with variable information.
- Distinguishes between variables without specified data types and those with assigned values.

## Usage

1. **Input File**: Prepare a text file named `text.txt` containing variable declarations and assignments. Each declaration should include its data type, and assignments should be separated by semicolons.

    ```plaintext
    int Integer; double Double; char Character; float Float; short Short; bool Boolean;
    unsigned int integerNumber = 10; Double; double doubleNumber = 3.14159; unsigned char character = 'A';
    unsigned float floatNumber = 2.71828f; unsigned short shortNumber = 1000; doubleNumber; unsigned bool boolean = true;
    long long int result; long int sum; const int constantValue = 11; constantValue; otherValue;
    ```

2. **Compile**. Build the program using CMake.

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3. **Run**: Execute the compiled program and specify the input file as a command-line argument.

    ```bash
    ./prog ../text.txt
    ```

4. **Output Files**: The program generates one output files:
   - `result.txt`: Contains a list of variables with their data types, values, names, row numbers, and column numbers. Variables without assigned values are labeled as `GARBAGE`.

## Code Structure

The program consists of the following classes:

- `InformationTypes`: Represents information about a variable, including its data type, value, name, row number, and column number.
- `Types`: Main class responsible for parsing the input file, processing each line, and generating output files.
