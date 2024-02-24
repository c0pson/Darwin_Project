#ifndef DARWIN_V2_COMMANDS_H
#define DARWIN_V2_COMMANDS_H

#include <string>

/**
 * @file darwin_v2_commands.h
 * @brief Defines the structure and function for handling user input in Darwin V2.
 */

/**
 * @struct Parameters
 * @brief A structure to hold user input parameters for the Darwin V2 simulation.
 */
struct Parameters {
    std::string inputFile;          ///< Path to the input file.
    std::string outputFile;         ///< Path to the output file.
    double extinctionThreshold;     ///< Extinction threshold for the simulation.
    double proliferationThreshold;  ///< Proliferation threshold for the simulation.
    int generations;                ///< Number of generations for the simulation.
    int pairsToCrossover;           ///< Number of pairs to perform crossover in the simulation.
};

/**
 * @brief Parses command-line arguments to extract user input parameters.
 *
 * This function takes command-line arguments, extracts relevant information,
 * and returns a Parameters structure with the parsed values.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return A Parameters structure with parsed input values.
 */
Parameters user_input(int argc, char* argv[]);

#endif // DARWIN_V2_COMMANDS_H
