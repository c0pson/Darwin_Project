#include "evolutionProcess.h"
#include "fileOperations.h"
#include "commands.h"
#include "messages.h"

/**
 * @file main.cpp
 * @author Piotr Copek
 * @brief Main function.
 * @param argc The number of cmd arguments.
 * @param argv The number of cmd arguments.
 * @return 0 on success
 *
 * @brief Program simulating process of evolution
 *
 * @details Program reads users organism saved in .txt file
 * Example of file with 3 organisms
 * 12 645 24 1 37 21
 * 95 30 15 1 283 12
 * 1 23 481 1
 * Program reads all lines, select given amount of organisms and mix them (mutate).
 * After mutation of some creatures their capability to survive is checked by mathematical function.
 * Program repeats itself x times given by user in parameter.
 * After all processes of evolution matrix is saved to file in save template as users input file should look like.
 * At the end of the process function writes information that the program executed correctly if it did not error is printed.
 * Program also offers help for new users as well for users not used to parameters in command line.
 * Given input might be slightly imperfect.
 * For windows users its possible to open ready file in notepad
 * The program may be familiar to you under the name "Game of life".
*/

int main(int argc, char **argv)
{
    printStartMessage();
    Parameters p = user_input(argc, argv);
    printParameters(p.inputFile, p.outputFile, p.extinctionThreshold, p.proliferationThreshold, p.generations, p.pairsToCrossover);
    MatrixResult matrixResult = readMatrixFromFile(p.inputFile);
    std::vector<std::vector<int>> originalMatrix = matrixResult.matrix;

    for (int i = 0; i < p.generations; ++i)
    {
        std::vector<std::vector<int>> pairsToCrossover = selectOrganism(originalMatrix, p.pairsToCrossover);
        std::vector<std::vector<int>> pairsMutated = pairsForMutation(pairsToCrossover);
        std::vector<std::vector<int>> mutationProcess = mutation(pairsMutated);
        std::vector<std::vector<int>> connectedVectorOfOrganism = connectVectors(originalMatrix, mutationProcess);
        std::vector<std::vector<int>> OrganismsAfterEvolution = fittedPopulation(connectedVectorOfOrganism, p.proliferationThreshold, p.extinctionThreshold, i);
        originalMatrix = OrganismsAfterEvolution;
    }
    Results result = calculateAverageCosine(originalMatrix, p.proliferationThreshold);
    writeMatrixToFile(originalMatrix, p.outputFile, result.accuracy, result.perfectFits);
    printEndMessage();
    return 0;
}
