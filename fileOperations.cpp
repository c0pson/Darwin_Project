/**
 * @file fileOperations.cpp
 * @brief Implementation of file-related operations.
 */

#include "fileOperations.h"
#include "messages.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

/**
 * @brief Reads a matrix from a file and performs error checking.
 *
 * This function reads a matrix from the specified file and performs error checking during the process.
 * It ensures that the file is opened successfully, reads each line, validates the characters, and builds the matrix.
 * If any error is encountered, the function prints an error message and exits the program.
 *
 * @param filename The path to the file containing the matrix data.
 * @return A structure containing the read matrix, line number of error (if any), and the wrong character (if any).
 *
 * The function uses the following structure for the result:
 *   - `matrix`: 2D vector representing the read matrix.
 *   - `lineNumber`: Line number where an error occurred (if any).
 *   - `wrongChar`: Wrong character found in the file (if any).
 *
 * If a non-integer character is encountered in the file, an error message is printed, and the program exits.
 * If the file cannot be opened, an error message is printed, and the program exits.
 */

MatrixResult readMatrixFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    MatrixResult result;
    result.wrongChar = '\0'; // Initialize with null character
    result.lineNumber = 0;

    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            ++result.lineNumber; // Increment line number for each new line
            std::vector<int> row;
            std::istringstream iss(line);

            char c;
            while (iss >> c)
            {
                if (!std::isdigit(c) && c != '-' && c != '+')
                {
                    // If the character is not a digit, '-', or '+', it's a non-integer character
                    result.wrongChar = c;
                    printStartMessage();
                    std::cerr << RED BOLD << "Error: Non-integer value found in file: " << filename
                              << " (Character: " << c << " at line " << result.lineNumber << ")" << RESET << std::endl;
                    printInstructionForWrongFile();
                    exit(EXIT_FAILURE);
                }

                iss.putback(c); // Put the character back into the stream
                int num;
                if (iss >> num)
                {
                    row.push_back(num);
                }
            }

            result.matrix.push_back(row);
        }

        file.close();
    }
    else
    {
        std::cerr << RED BOLD << "Error: Unable to open file: " << filename << "\n\nPress 'enter' to exit..." << RESET;
        std::cin.get();
        exit(EXIT_FAILURE);
    }

    return result;
}

/**
 * @brief Writes a matrix of integers to a file.
 *
 * Writes the specified matrix to the specified file. Each row of the matrix is written as a line in the file,
 * and integers are separated by spaces.
 *
 * @param matrix The matrix to write to the file.
 * @param filename The name of the file to write.
 */

void writeMatrixToFile(const std::vector<std::vector<int>>& matrix, const std::string& filename, double accuracy, int perfectFits)
{
    if (std::isnan(accuracy))
    {
        accuracy = 0;
    }

    std::ofstream file(filename);
    if (file.is_open())
    {
        file << "Accuracy: " << accuracy * 100 << "%" << std::endl;
        file << "Perfect fits: " << perfectFits << std::endl;

        for (const auto& row : matrix)
        {
            if (!row.empty())
            {
                for (int num : row)
                {
                    file << num << ' ';
                }
                file << '\n';
            }
        }

        file.close();
    }
}