#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "sample-reader.h"
#include "kmeans.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Read samples from file and store them
    SampleReader *sampleReader = new SampleReader();
    sampleReader->readSamplesFromFile(argv[1]);

    Kmeans kmeans (sampleReader->getPointList());
    kmeans.run();

    cout << endl << "K-Means" << endl;

    return 0;
}
