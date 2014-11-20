#include "neuron.h"
#include <cmath>
#include <cstdio>
#include <iostream>

#define M_PI           3.14159265358979323846  /* pi */

using namespace std;

/* ==========================================================
                         Constructors
========================================================== */
Neuron::Neuron(Matrix X, Matrix Y)
    : X(X), Y(Y)
{
}

/* ==========================================================
                             Sets
========================================================== */
void Neuron::setMartrixX(Matrix X)
{
    this->X = X;
}

void Neuron::setMartrixY(Matrix Y)
{
    this->Y = Y;
}

/* ==========================================================
                             Gets
========================================================== */
Matrix Neuron::getX() { return X; }

Matrix Neuron::getY() { return Y; }

/* ==========================================================
                             Run
========================================================== */
bool Neuron::run()
{
  return false;
}
