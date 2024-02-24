#include <map>
#include <string>
#include <stdexcept>
#include "commands.h"
#include "messages.h"

/**
 * @brief Parses command line arguments and extracts parameters for the program.
 *
 * This function takes command line arguments and extracts specific parameters needed for the program.
 * It supports various command line options such as input file, output file, thresholds, and others.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line argument strings.
 * @return A structure containing the extracted parameters.
 *
 * The function uses the following command line options:
 *   - "-i": Input file path.
 *   - "-o": Output file path.
 *   - "-w": Extinction threshold (double).
 *   - "-r": Proliferation threshold (double).
 *   - "-p": Number of generations (integer).
 *   - "-k": Number of pairs for crossover (integer).
 *
 * Example usage:
 * @code
 *   Parameters params = user_input(argc, argv);
 * @endcode
 */

Parameters user_input(int argc, char* argv[])
{
    Parameters params;

    for (int i = 1; i < argc; i += 2) {
        std::string arg = argv[i];

        if (arg == "-i") {
            params.inputFile = argv[i + 1];
        } else if (arg == "-o") {
            params.outputFile = argv[i + 1];
        } else if (arg == "-w") {
            try {
                params.extinctionThreshold = std::stod(argv[i + 1]);
            } catch (const std::invalid_argument& e) {
                printError();
            }
        } else if (arg == "-r") {
            try {
                params.proliferationThreshold = std::stod(argv[i + 1]);
            } catch (const std::invalid_argument& e) {
                printError();
            }
        } else if (arg == "-p") {
            try {
                params.generations = std::stoi(argv[i + 1]);
            } catch (const std::invalid_argument& e) {
                printError();
            }
        } else if (arg == "-k") {
            try {
                params.pairsToCrossover = std::stoi(argv[i + 1]);
            } catch (const std::invalid_argument& e) {
                printError();
            }
        } else {
            printError();
        }
    }

    // Check if any required parameter is missing
    if (params.inputFile.empty() || params.outputFile.empty() || params.extinctionThreshold == 0.0 ||
        params.proliferationThreshold == 0.0 || params.generations == 0 || params.pairsToCrossover == 0) {
        printError();
    }

    return params;
}