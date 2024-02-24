#ifndef DARWIN_V3_MESSAGES_H
#define DARWIN_V3_MESSAGES_H

#include "commands.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

/**
 * @file darwin_v3_messages.h
 * @brief Declares functions for printing messages in a Darwin V3 simulation.
 */

/**
 * @brief Prints an error message.
 */
void printError();

/**
 * @brief Clears the console screen.
 */
void clear();

/**
 * @brief Prints instructions for handling incorrect input.
 */
void printInstructionForWrongInput();

/**
 * @brief Prints instructions for handling incorrect files.
 */
void printInstructionForWrongFile();

/**
 * @brief Prints the start message for the simulation.
 */
void printStartMessage();

/**
 * @brief Prints the simulation parameters.
 *
 * @param inputFile The input file name.
 * @param outputFile The output file name.
 * @param extinctionThreshold The extinction threshold.
 * @param proliferationThreshold The proliferation threshold.
 * @param generations The number of generations.
 * @param pairsToCrossOver The number of pairs for crossover.
 */
void printParameters(const std::string& inputFile, const std::string& outputFile, double extinctionThreshold, double proliferationThreshold, int generations, int pairsToCrossOver);

/**
 * @brief Prints the end message for the simulation.
 */
void printEndMessage();

#endif // DARWIN_V3_MESSAGES_H