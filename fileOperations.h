#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <string>
#include <vector>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"

/**
 * @file file_operations.h
 * @brief Declares functions for file operations in a Darwin V2 simulation.
 */

/**
 * @brief Reads a matrix from a file.
 *
 * @param filename The name of the file containing the matrix.
 * @return A matrix read from the file.
 */

struct MatrixResult
{
    char wrongChar;
    int lineNumber;
    std::vector<std::vector<int>> matrix;
};

MatrixResult readMatrixFromFile(const std::string& filename);

/**
 * @brief Writes a matrix to a file.
 *
 * @param matrix The matrix to be written to the file.
 * @param filename The name of the file to write the matrix to.
 */
void writeMatrixToFile(const std::vector<std::vector<int>>& matrix, const std::string& filename, double accuracy, int perfectFits);

/**
 * @brief Opens the Notepad application with the specified file.
 *
 * @param file The file to be opened with Notepad.
 */
void openNotepad(const std::string& file);

#endif // FILE_OPERATIONS_H
