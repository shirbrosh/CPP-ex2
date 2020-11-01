#include <vector>
#include "Fractal.h"
#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>

#define NUM_OF_ARGS 2
#define FAIL 0
#define SEP ","
#define CSV ".csv"
#define NUM_OF_ARGS_MSG "Usage: FractalDrawer <file path>\n"
#define WRONG_FILE_MSG "Invalid input\n"

/**
 * This function is the file parser- reads the file and creates the matching Fractal
 * @param file- the file to read
 * @param fractalVec- the vector that will contain the Fractal objects created from the file
 */
void parser(std::ifstream &file, std::vector<Fractal *> &fractalVec)
{
    if (!file.is_open())
    {
        std::cerr << WRONG_FILE_MSG;
        exit(EXIT_FAILURE);
    }
    std::string line;
    std::vector<std::string> parameters;
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    boost::char_separator<char> sep{SEP};

    //reads one line at a time
    while (std::getline(file, line))
    {
        if (line[line.size() - 1] == ' ')
        {
            line = line.substr(0, line.size() - 1);
        }
        tokenizer tok{line, sep};
        parameters.assign(tok.begin(), tok.end());

        //check if the line contains exactly 2 arguments
        if (parameters.size() != NUM_OF_ARGS)
        {
            std::cerr << WRONG_FILE_MSG;
            exit(EXIT_FAILURE);
        }

        //check if the given arguments contain more than 1 char
        if (parameters[0].size() != 1 || parameters[1].size() != 1)
        {
            std::cerr << WRONG_FILE_MSG;
            exit(EXIT_FAILURE);
        }

        //check if the given chars are digits
        if (!isdigit(parameters[0][0]) || !isdigit(parameters[1][0]))
        {
            std::cerr << WRONG_FILE_MSG;
            exit(EXIT_FAILURE);
        }

        //convert the given arguments to int
        int type = std::stoi(parameters[0]);
        int dims = std::stoi(parameters[1]);

        //check if the given int arguments are within the given range
        if (type < 1 || type > 3 || dims < 1 || dims > 6)
        {
            std::cerr << WRONG_FILE_MSG;
            exit(EXIT_FAILURE);
        }

        //finally after validating all arguments, create the matching Fractal and add to the vector
        fractalVec.push_back(FractalFactory::createFractal(type, dims));
    }
}

/**
 * This function prints the Fractal objects from the given Fractal vector using the Fractal's
 * function draw()
 * @param fractalVec- the vector containing the Fractal objects to print
 */
void printFractal(std::vector<Fractal *> &fractalVec)
{
    for (int i = (int) fractalVec.size() - 1; i > -1; i--)
    {
        fractalVec[i]->draw();
        delete (fractalVec[i]);
    }
}


int main(int argc, char *argv[])
{
    if (argc != NUM_OF_ARGS)
    {
        std::cerr << NUM_OF_ARGS_MSG;
        exit(EXIT_FAILURE);
    }
    if (!boost::filesystem::exists(argv[1]) || boost::filesystem::extension(argv[1]) != CSV)
    {
        std::cerr << WRONG_FILE_MSG;
        exit(EXIT_FAILURE);
    }
    if (boost::filesystem::is_empty(argv[1]))
    {
        return FAIL;
    }

    std::vector<Fractal *> fractalVec;
    std::ifstream file(argv[1]);
    parser(file, fractalVec);
    printFractal(fractalVec);
    fractalVec.clear();
}