#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <iomanip>
#include <fstream>

#include "sample-reader.h"
#include "mlp.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Read samples from file and store them
    SampleReader *sampleReader = new SampleReader();
    sampleReader->readSamplesFromFile(argv[1]);

    MLP mlp (sampleReader->getX(), sampleReader->getY());
    mlp.run();

    cout << endl << "Multilayer Perceptron" << endl;

    return 0;
}
