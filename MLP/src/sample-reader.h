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
     *   1|x11 x12 x13 ...  x9|
     *   2|x21 x22 x23 ...  x9|
     *    |...                |
     *   n|xn1 xn2 xn3 ... xn9|
     *
    */
    Matrix X;

    /**
     *   Y's matrix.
     *   Y can be 1 or 0
     *   (0 for benign, 1 for malignant)
    */
    Matrix Y;

};

#endif //SAMPLE_READER_H
