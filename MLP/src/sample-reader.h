/**
* Class used for read the samples from file and build initial matrices
* Author: Inaciane Monteiro
*/

#ifndef SAMPLE_READER_H
#define SAMPLE_READER_H

#include "matrix.h"
#include <vector>

using namespace std;

class SampleReader
{

public:

    /* ==========================================================
                             Constructors
    ========================================================== */
    SampleReader();

    /* ==========================================================
                                 Gets
    ========================================================== */
    Matrix getX();

    Matrix getY();

    /* ==========================================================
                                 Sets
    ========================================================== */

    /* ==========================================================
                                 Logic
    ========================================================== */
    bool readSamplesFromFile(const char* filePath);

private:

    /**
     *   X's matrix.
     *   The x's are positioned as folows:
     *
     *   1|x11 x12 x13 ...  x10|
     *   2|x21 x22 x23 ...  x10|
     *    |...                 |
     *   n|xn1 xn2 xn3 ... xn10|
     *
    */
    Matrix X;

    /**
     *   Y's matrix.
     *   Y can be 2 or 4
     *   (2 for benign, 4 for malignant)
    */
    Matrix Y;

};

#endif //SAMPLE_READER_H
