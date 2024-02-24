/**
 * @file evolutionProcess.cpp
 * @brief Functions responsible for all evolution processes
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <limits>
#include <numeric>
#include "evolutionProcess.h"

/**
 * @brief Initializes a random number generator using the current high-resolution clock time as the seed.
 *
 * This function uses std::chrono::high_resolution_clock::now().time_since_epoch().count()
 * to generate a seed for std::mt19937 random number generator.
 *
 * @return A std::mt19937 random number generator with the initialized seed.
 */

// might be a singleton but it works just fine

auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 gen(seed);

/**
 *
 * @param matrix
 */

void removeEmptyLines(std::vector<std::vector<int>>& matrix) {
    matrix.erase(std::remove_if(matrix.begin(), matrix.end(),
                                [](const std::vector<int>& row) { return row.empty(); }),
                 matrix.end());
}

/**
 * @brief Chooses random pairs of organisms from the original matrix for crossover.
 *
 * Function that selects random lines from the original matrix containing all creatures from the user's file.
 * The chosen organisms are saved to a new matrix for further crossover operations.
 *
 * @param allOrganisms The original matrix containing all creatures from the user's file.
 * @param k Parameter representing the number of pairs to cross over.
 * @return The pairsVector if executed correctly; it contains the chosen creatures for crossover.
 *
 * @details The function reads the number of pairs (k) to be chosen from the original matrix. If it is not possible
 * to perform crossover as specified by the user, or if the population becomes too small, parameter k is automatically
 * resized until it is small enough. In a loop, organisms are randomly selected and checked to ensure they do not repeat,
 * and then the pairs are added to the new matrix. To avoid duplication, the selected organisms are also removed from
 * the original matrix.
 */

std::vector<std::vector<int>> selectOrganism(std::vector<std::vector<int>>& allOrganisms, int k)
{
    while (k > allOrganisms.size() / 2)
    {
        k = (int) allOrganisms.size() / 3;
    }

    std::vector<std::vector<int>> pairsVector;

    for (int i = 0; i < k; ++i)
    {
        std::uniform_int_distribution<> dis(0, (int) allOrganisms.size() - 1);

        int line1 = dis(gen);
        int line2;
        do
        {
            line2 = dis(gen);
        }
        while (line2 == line1); //ensure that line2 is not equal to line2

        pairsVector.push_back(allOrganisms[line1]); // Add the selected pairs to the new vector
        pairsVector.push_back(allOrganisms[line2]);

        allOrganisms.erase(allOrganisms.begin() + std::max(line1, line2)); // Remove the selected pairs from the original matrix
        allOrganisms.erase(allOrganisms.begin() + std::min(line1, line2));
    }
    return pairsVector;
}

/**
 * @brief Slices all organisms in half and puts them into a new matrix.
 *
 * Function that slices each organism in half and adds the halves to a new matrix. The resulting matrix is
 * two times longer, with each organism's chromosome split in half.
 *
 * @param organismsToMutate The matrix containing organisms to be sliced.
 * @return The resulting matrix with organisms sliced in half if executed correctly.
 *
 * @details The function starts by checking if the half-length of the chromosome is even or odd. If it is odd,
 * one is added to make the splitting process easier. Then, each organism's chromosome is divided into two halves,
 * and the halves are added to a new matrix. The resulting matrix is two times longer than the original matrix.
 */

std::vector<std::vector<int>> pairsForMutation(const std::vector<std::vector<int>>& organismsToMutate)
{
    std::vector<std::vector<int>> pairsToMutate;
    for (const auto &pair: organismsToMutate) //slices vector of selected organisms
    {
        std::size_t splitChromosome = pair.size();
        if(splitChromosome % 2 != 0)
        {
            splitChromosome = (splitChromosome + 1) / 2;
        }
        else
        {
            splitChromosome = splitChromosome / 2;
        }
        std::vector<int> firstHalfOfDNA(pair.begin(), pair.begin() + (int) splitChromosome);
        std::vector<int> secondHalfOfDNA(pair.begin() + (int) splitChromosome, pair.end());
        pairsToMutate.push_back(firstHalfOfDNA);
        pairsToMutate.push_back(secondHalfOfDNA);
    }
    return pairsToMutate;
}

/**
 * @brief The function randomly mixing rows from matrix to create full Organism.
 *
 * Function that takes random rows but not repetitively. Connect two rows and then put them in nwe matrix, so
 * later functions will be possible to implement.
 *
 * @param slicedPairs The matrix containing sliced in half pairs of chromosomes
 * @return The resulting matrix with connected rows (full organisms).
 *
 * @details The function starts by setting up a matrix for organisms after mixing them and initializes
 * a pseudo-random number generator using the current time as a seed. It then creates a shuffled index vector
 * to randomly select pairs of rows without repetition. The function loops through the shuffled indices,
 * connecting two rows at a time and adding the resulting merged row to the output matrix.
 */

std::vector<std::vector<int>> mutation(const std::vector<std::vector<int>>& slicedPairs)
{
    std::vector<std::vector<int>> crossOverProcess;

    std::vector<size_t> mixer(slicedPairs.size());
    std::iota(mixer.begin(), mixer.end(), 0);
    std::shuffle(mixer.begin(), mixer.end(), gen);

    for (size_t i = 0; i < mixer.size(); i += 2) {
        size_t index1 = mixer[i];
        size_t index2 = mixer[i + 1];

        std::vector<int> mixedLine;
        mixedLine.insert(mixedLine.end(), slicedPairs[index1].begin(), slicedPairs[index1].end());
        mixedLine.insert(mixedLine.end(), slicedPairs[index2].begin(), slicedPairs[index2].end());

        crossOverProcess.push_back(mixedLine);
    }

    return crossOverProcess;
}

/**
 * @brief Function connecting two matrices containing both non-mutated and mutated organisms.
 *
 * @param unMutatedOrganisms Matrix containing non-mutated Organisms
 * @param mutatedOrganisms Matrix containing mutated organisms
 *
 * @return The resulting matrix containing all species from both params.
 *
 * @details The function starts by setting up empty matrix for all organisms from passed matrices, then in loop
 * all the rows from unMutatedOrganisms into connectedVectorOfAllOrganism using its constructor,
 * and then appends each row from mutatedOrganisms using push_back.
 */

std::vector<std::vector<int>> connectVectors(const std::vector<std::vector<int>>& unMutatedOrganisms, const std::vector<std::vector<int>>& mutatedOrganisms)
{
    std::vector<std::vector<int>> connectedVectorOfAllOrganism(unMutatedOrganisms);

    removeEmptyLines(connectedVectorOfAllOrganism);

    for (const auto& row : mutatedOrganisms)
    {
        connectedVectorOfAllOrganism.push_back(row);
    }
    return connectedVectorOfAllOrganism;
}

/**
 * @brief Function returning sum of row from matrix
 * @param row The line from matrix.
 * @return The sum of row. @code std::accumulate(row.begin(), row.end(), 0);
 *
 * @detailed Simple function returning just a sum of row using "std::accumulate".
 */

int calculateRowSum(const std::vector<int>& row)
{
    return std::accumulate(row.begin(), row.end(), 0);
}

/**
 * @brief Checks if organisms meets requirements given by user.
 *
 * Function that calculate sums of every row and put these sums into pro-life and extinction function to remove, leave
 * as it was or double the specie.
 *
 * @param mutatedOrganisms The matrix containing all organisms connected together (both mutated and not mutated).
 * @param ProLifeT The user defined parameter of doubling species in population.
 * @param ExtinT The user defined parameter of keeping if above or removing if below species in population.
 *
 * @return The resulting matrix containing organism after fitting process.
 *
 * @details The function starts by setting up matrix for organisms after fitting process and pseudo random number generator.
 * Then, for each row it is calculating a sum of all integers, and puts it to both pro-life and extinction functions, which is following
 * \n \a cos(random_double * sum_of_current_row) / 1.99 + 0.501
 * \n then after calculating this equation, requirements are checked for given parameters. If result is bigger than pro-life function
 * organism is duplicated, if result is bigger than extinction functions, but smaller than pro-life function, organism is just kept in matrix,
 * otherwise the organism is removed.
 */

std::vector<std::vector<int>> fittedPopulation(const std::vector<std::vector<int>>& mutatedOrganisms, double ProLifeT, double ExtinT, int generation)
{
    std::vector<std::vector<int>> organismsAfterEvolution;
    removeEmptyLines(organismsAfterEvolution);

    double(*fit_func)(double, double) = [](double factor, double rowSum){return factor * ((std::cos(rowSum) / 2) + 0.5);};

    std::uniform_real_distribution<double> randomEvolution((ExtinT - 0.04), 1.0);
    double factor = randomEvolution(gen);

    std::cout << "Generation: " << generation + 1 << "\n" << "Factor: " << factor << "\n\n";

    for (const auto& row : mutatedOrganisms)
    {
        int rowSum = calculateRowSum(row);

        double proLifeFunction = fit_func(factor, rowSum);
        double existFunction = fit_func(factor, rowSum);

        if (proLifeFunction > ProLifeT)
        {
            organismsAfterEvolution.push_back(row);
            organismsAfterEvolution.push_back(row);
        }
        else
        {
            if (existFunction < ExtinT)
            {
                continue;
            }
            else
            {
                organismsAfterEvolution.push_back(row);
            }
        }
    }
    return organismsAfterEvolution;
}

/**
 * @brief Calculates the average cosine value for each row in a matrix.
 *
 * This function takes a matrix and calculates the average cosine value for each row. 
 * This function aim to decide with what precision the output file was generated.
 *
 * If the input matrix is empty, the function returns quiet NaN to a avoid infinite loop for some reason.
 *
 * @param matrix A vector of all species.
 * @return The average cosine value for each row in the matrix, or quiet NaN if the matrix is empty.
 */

Results calculateAverageCosine(const std::vector<std::vector<int>>& matrix, double proLifeT)
{
    Results result;
    if (matrix.empty())
    {
        result.accuracy = std::numeric_limits<double>::quiet_NaN();
        result.perfectFits = 0;
        return result;
    }
    double sumCosines = 0.0;
    int counter_of_perfect_fits = 0;
    for (const auto& row : matrix) {
        int rowSum = calculateRowSum(row);
        double cosineValue = (std::cos(rowSum) / 2) + 0.5;
        sumCosines += cosineValue;
        if (rowSum > proLifeT)
        {
            counter_of_perfect_fits += 1;
        }
    }
    result.accuracy = sumCosines / matrix.size();
    result.perfectFits = counter_of_perfect_fits;
    return result;
}