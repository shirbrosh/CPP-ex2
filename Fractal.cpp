#include "Fractal.h"
#include <cmath>
#include <iostream>

#define SPACE " "
#define HASHTAG "#"
#define SIERPINSKI_CARPET 1
#define SIERPINSKI_TRIANGLE 2

/**
 * Constructor for Fractal class
 * @param base - the base size for the Fractal shape
 * @param dim - the number of iterations
 */
Fractal::Fractal(int base, int dim) : dims((int) pow(base, dim))
{}

/**
 * This function fills the fractal's board
 */
void Fractal::fillBoard()
{
    for (int i = 0; i < this->dims; i++)
    {
        for (int j = 0; j < this->dims; j++)
        {
            this->board.push_back(fillPixel(i, j));
        }
    }
}

/**
 * This function prints the fractal's board with the symbol "#"
 */
void Fractal::draw()
{
    for (int i = 0; i < this->dims; i++)
    {
        for (int j = 0; j < this->dims; j++)
        {
            if (this->board[(i * this->dims) + j] == 1)
            {
                std::cout << HASHTAG;
            }
            else
            {
                std::cout << SPACE;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/**
 * This function determent the value for a specific cell in the Sierpinski Carpet board
 * @param x- the row index in the board
 * @param y- the col index in the board
 * @return 1- if the cell need to be filled or 0 otherwise
 */
int SierpinskiCarpet::fillPixel(int x, int y)
{
    while (x > 0 || y > 0)
    {
        if (x % 3 == 1 && y % 3 == 1)
        {
            return 0;
        }
        x /= 3;
        y /= 3;
    }
    return 1;
}

/**
 * Constructor for SierpinskiCarpet class
 * @param dim- the number of iterations
 */
SierpinskiCarpet::SierpinskiCarpet(int dim) : Fractal(3, dim)
{
    fillBoard();
}

/**
* This function determent the value for a specific cell in the Sierpinski Triangle board
* @param x- the row index in the board
* @param y- the col index in the board
* @return 1- if the cell need to be filled or 0 otherwise
*/
int SierpinskiTriangle::fillPixel(int x, int y)
{
    while (x > 0 || y > 0)
    {
        if (x % 2 == 1 && y % 2 == 1)
        {
            return 0;
        }
        x /= 2;
        y /= 2;
    }
    return 1;
}

/**
 * Constructor for SierpinskiTriangle class
 * @param dim- the number of iterations
 */
SierpinskiTriangle::SierpinskiTriangle(int dim) : Fractal(2, dim)
{
    fillBoard();
}

/**
* This function determent the value for a specific cell in the Vicsek Fractal board
* @param x- the row index in the board
* @param y- the col index in the board
* @return 1- if the cell need to be filled or 0 otherwise
*/
int VicsekFractal::fillPixel(int x, int y)
{
    while (x > 0 || y > 0)
    {
        if ((x % 3 == 1) ^ (y % 3 == 1))
        {
            return 0;
        }
        x /= 3;
        y /= 3;
    }
    return 1;
}

/**
 * Constructor for VicsekFractal class
 * @param dim- the number of iterations
 */
VicsekFractal::VicsekFractal(int dim) : Fractal(3, dim)
{
    fillBoard();
}


/**
 * The factory for creating Fractal objects
 * @param num- the Fractal type number representing the specific fractal to build
 * @param dim- the number of iterations
 * @return pointer to the Fractal Object of the given type:
 *          1= SierpinskiCarpet
 *          2= SierpinskiTriangle
 *          3= VicsekFractal
 */
Fractal *FractalFactory::createFractal(int type, int dim)
{
    switch (type)
    {
        case SIERPINSKI_CARPET:
            return new SierpinskiCarpet(dim);
        case SIERPINSKI_TRIANGLE:
            return new SierpinskiTriangle(dim);
        default:
            return new VicsekFractal(dim);

    }
}
