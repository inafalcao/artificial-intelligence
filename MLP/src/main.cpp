#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <iomanip>
#include <fstream>

#include "sample-reader.h"
#include "neuron.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Read samples from file and store them
    SampleReader *sampleReader = new SampleReader();
    sampleReader->readSamplesFromFile(argv[1]);

    Neuron neuron ( sampleReader->getX(), sampleReader->getY());
    neuron.run();

    cout << endl << "Multilayer Perceptron" << endl;

    return 0;
}
