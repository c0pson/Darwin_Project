#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include <vector>
#include <string>

struct Results {
    double accuracy;
    int perfectFits;
};

/**
 * @file matrix_operations.h
 * @brief Declares functions for matrix operations in a Darwin V2 simulation.
 */

/**
 * @brief Removes empty lines from the matrix.
 *
 * This function removes empty lines (rows) from the given matrix, modifying it in place.
 *
 * @param matrix The matrix from which empty lines will be removed.
 */

void removeEmptyLines(std::vector<std::vector<int>>& matrix);

/**
 * @brief Selects k organisms randomly from the provided set of organisms.
 *
 * @param allOrganisms The set of all organisms.
 * @param k The number of organisms to select.
 * @return A vector of k selected organisms.
 */
std::vector<std::vector<int>> selectOrganism(std::vector<std::vector<int>>& allOrganisms, int k);

/**
 * @brief Generates pairs of organisms for mutation.
 *
 * @param organismsToMutate The set of organisms to be mutated.
 * @return A vector of pairs for mutation.
 */
std::vector<std::vector<int>> pairsForMutation(const std::vector<std::vector<int>>& organismsToMutate);

/**
 * @brief Applies mutation to the given pairs of organisms.
 *
 * @param slicedPairs The pairs of organisms to be mutated.
 * @return A vector of mutated organisms.
 */
std::vector<std::vector<int>> mutation(const std::vector<std::vector<int>>& slicedPairs);

/**
 * @brief Connects vectors from two sets of organisms.
 *
 * @param unMutatedOrganisms The set of non mutated organisms.
 * @param mutatedOrganisms The set of mutated organisms.
 * @return A vector containing connected organisms.
 */
std::vector<std::vector<int>> connectVectors(const std::vector<std::vector<int>>& unMutatedOrganisms, const std::vector<std::vector<int>>& mutatedOrganisms);

/**
 * @brief Calculates the sum of elements in a row.
 *
 * @param row The row for which the sum is to be calculated.
 * @return The sum of elements in the row.
 */
int calculateRowSum(const std::vector<int>& row);

/**
 * @brief Filters the population based on proliferation and extinction thresholds.
 *
 * @param mutatedOrganisms The set of mutated organisms.
 * @param ProLifeT The proliferation threshold.
 * @param ExtinT The extinction threshold.
 * @return A vector of organisms that meet the specified thresholds.
 */
std::vector<std::vector<int>> fittedPopulation(const std::vector<std::vector<int>>& mutatedOrganisms, double ProLifeT, double ExtinT, int generation);

Results calculateAverageCosine(const std::vector<std::vector<int>>& matrix, double proLifeT);

#endif // MATRIX_OPERATIONS_H