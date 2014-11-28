/**
* Class used for read the samples from file and build initial matrices
* Author: Inaciane Monteiro
*/

#ifndef SAMPLE_READER_H
#define SAMPLE_READER_H

#include <vector>
#include "point.h"

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
    vector<Point> getPointList();

    /* ==========================================================
                                 Sets
    ========================================================== */
    void setPointList(vector<Point> points);

    /* ==========================================================
                                 Logic
    ========================================================== */
    bool readSamplesFromFile(const char* filePath);

private:
    vector<Point> pointList;
};

#endif //SAMPLE_READER_H
