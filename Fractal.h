#include <vector>
#include <string>

#ifndef CPP_EX2_FRACTAL_H
#define CPP_EX2_FRACTAL_H

#endif //CPP_EX2_FRACTAL_H

/**
 * A Fractal object class
 */
class Fractal
{
public:
    /**
    * This function prints the fractal's board with the symbol "#"
    */
    virtual void draw();

protected:
    std::vector<int> board;
    int dims;

    /**
    * Constructor for Fractal class
    * @param base - the base size for the Fractal shape
    * @param dim - the number of iterations
    */
    explicit Fractal(int base, int dim);

    /**
    * This function determent the value for a specific cell in the fractal board
    * @param x- the row index in the board
    * @param y- the col index in the board
    * @return 1- if the cell need to be filled or 0 otherwise
    */
    virtual int fillPixel(int x, int y) = 0;

    /**
    * This function fills the fractal's board
    */
    virtual void fillBoard();

public:
    /**
    * The destructor for Fractal class
    */
    virtual ~Fractal() = default;
};

/**
 * A SierpinskiCarpet object class
 */
class SierpinskiCarpet : public Fractal
{
public:
    /**
    * Constructor for SierpinskiCarpet class
    * @param dim- the number of iterations
    */
    explicit SierpinskiCarpet(int dim);

protected:
    /**
    * This function determent the value for a specific cell in the Sierpinski Carpet board
    * @param x- the row index in the board
    * @param y- the col index in the board
    * @return 1- if the cell need to be filled or 0 otherwise
    */
    int fillPixel(int x, int y) override;
};

/**
 * A SierpinskiTriangle object class
 */
class SierpinskiTriangle : public Fractal
{
public:
    /**
    * Constructor for SierpinskiTriangle class
    * @param dim- the number of iterations
    */
    explicit SierpinskiTriangle(int dim);

protected:
    /**
    * This function determent the value for a specific cell in the Sierpinski Triangle board
    * @param x- the row index in the board
    * @param y- the col index in the board
    * @return 1- if the cell need to be filled or 0 otherwise
    */
    int fillPixel(int x, int y) override;
};

/**
 * A VicsekFractal object class
 */
class VicsekFractal : public Fractal
{
public:
    /**
    * Constructor for VicsekFractal class
    * @param dim- the number of iterations
    */
    explicit VicsekFractal(int dim);

protected:
    /**
    * This function determent the value for a specific cell in the Vicsek Fractal board
    * @param x- the row index in the board
    * @param y- the col index in the board
    * @return 1- if the cell need to be filled or 0 otherwise
    */
    int fillPixel(int x, int y) override;
};

/**
 * A FractalFactory object class
 */
class FractalFactory
{
public:
    /**
     * The factory for creating Fractal objects
     * @param num- the Fractal type number representing the specific fractal to build
     * @param dim- the number of iterations
     * @return pointer to the Fractal Object of the given type:
     *          1= SierpinskiCarpet
     *          2= SierpinskiTriangle
     *          3= VicsekFractal
     */
    static Fractal *createFractal(int num, int dim);
};

