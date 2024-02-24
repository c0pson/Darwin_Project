#include <iostream>
#include <string>
#include "messages.h"
#include "commands.h"

/**
 * @brief Prints error message for incorrect input.
 */

void printError()
{
    printStartMessage();
    std::cerr << "Execution error: Incorrect input." << std::endl;
    printInstructionForWrongInput();
    std::cout << CYAN << "Press 'Enter' to continue" << std::endl;
    std::cin.get();
    exit(EXIT_FAILURE);
}

/**
 * @brief Clears terminal, command is specified by system installed on machine.
 */

void clear()
{
    #ifdef WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * @brief Prints Instruction if users give wrong input.
 */

void printInstructionForWrongInput()
{
    Parameters parameter;
    std::cout << "\n" << YELLOW BOLD << "Short instruction of usage: \n" << RESET
              << "The command should look like this: \n"
              << RED BOLD <<" \\Darwin_v3.exe -i \'your\\path\\to\\file.txt\' -o \'your\\path\\to\\output\\file.txt\' -w \'number from 0 to"
                 " 1\' -r \'number from 0 to 1\' -p \'random integer\' -k \'random integer\' \n" << RESET
              << "   -i - input file with a population \n"
              << "   -o - output file with mutated population \n"
              << "   -w - extinction threshold - w belongs to set [0,1] \n"
              << "   -r - proliferation threshold - r belongs to set [0,1] \n"
              << "   -p - number of generations \n"
              << "   -k - number k of pair to cross-over (its recommended to use number lower than the number of organisms)\n\n";
}

/**
 * @brief Prints instruction if users give file with incorrect data.
 */

void printInstructionForWrongFile()
{
    std::cout <<"\nShort instruction of usage: \n" << YELLOW BOLD
                " The file can only contain integers and not any other characters than <0,1,2,3,4,5,6,7,8,9>\n"
                " File can not have anything except integer values like shown below" << RESET;
    std::cout << R"(
      ______________________________
    / \                             \.
   |   | 27 26 30 41 42 99          |.
    \_ | 49 1 22 51 90 92 78 51 46  |.
       | 58 33 80 79 39 49 93       |.
       | 46 44 69 29 62 1           |.
       | 58 69                      |.
       | 42 28 71 1 48 97 44 33     |.
       | 93 35 29 48 44 614         |.
       | 93 35 29 48 44 614         |.
       | 59 78 15 12                |.
       | 98 26 93 35 29 48 44 614 1 |.
       | 58 97 10 57 47 85          |.
       | 5 27 16 57 41 13 51 28     |.
       | 13 69 51 31 71 97          |.
       |   _________________________|___
       |  /         input.txt          /.
       \_/____________________________/.)";
    std::cout << "\n\n" << "Press 'Enter' to exit...";
    std::cin.get();
}

/**
 * @brief Prints title and author of the project.
 */

void printStartMessage()
{
    clear();
    std::cout << GREEN BOLD << "\n" << R"(
 /$$$$$$$   /$$$$$$  /$$$$$$$  /$$      /$$ /$$$$$$ /$$   /$$
| $$__  $$ /$$__  $$| $$__  $$| $$  /$ | $$|_  $$_/| $$$ | $$
| $$  \ $$| $$  \ $$| $$  \ $$| $$ /$$$| $$  | $$  | $$$$| $$
| $$  | $$| $$$$$$$$| $$$$$$$/| $$/$$ $$ $$  | $$  | $$ $$ $$
| $$  | $$| $$__  $$| $$__  $$| $$$$_  $$$$  | $$  | $$  $$$$
| $$  | $$| $$  | $$| $$  \ $$| $$$/ \  $$$  | $$  | $$\  $$$
| $$$$$$$/| $$  | $$| $$  | $$| $$/   \  $$ /$$$$$$| $$ \  $$
|_______/ |__/  |__/|__/  |__/|__/     \__/|______/|__/  \__/
)" << MAGENTA << "\tby Piotr Copek" << RESET << "\n\n";
}

/**
 * @brief Prints parameters given by user.
 */

void printParameters(const std::string& input, const std::string& output, double w, double r, int p, int k)
{
    std::cout << YELLOW << "User input: \n"
              << BOLD << " - Input file: \'" << input << "\'\n"
              << " - Output file: \'" << output << "\'\n"
              << " - extinction threshold \'" << w << "\'\n"
              << " - Proliferation threshold: \'" << r << "\'\n"
              << " - Number of generations: \'" << p << "\'\n"
              << " - number of pair to cross-over \'" << k << "\'\n"
              << CYAN << "\nExecuting program..." << RESET << "\n";
}

/**
 * @brief Prints message if program was executed correctly.
 */

void printEndMessage()
{
    std::cout << CYAN << "\nProgram executed correctly. Press \'enter\' to exit...\n" << RESET;
    std::cin.get();
}
