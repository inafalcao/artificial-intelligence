/**
* Class that simulates the neuron
* Author: Inaciane Monteiro
*/

#ifndef NEURON_H
#define NEURON_H

#include "matrix.h"

class Neuron
{
public:

    /* ==========================================================
                             Constructors
    ========================================================== */
    Neuron(Matrix X, Matrix Y);

    /* ==========================================================
                                 Sets
    ========================================================== */
    void setMartrixX(Matrix X);
    void setMartrixY(Matrix Y);
   
    /* ==========================================================
                                 Gets
    ========================================================== */
    Matrix getX();
    Matrix getY();

    /* ==========================================================
                                 Run
    ========================================================== */
    bool run();


private:

    Matrix X;             // The X's Matrix
    Matrix Y;             // The Y's Matrix

};

#endif //NEURON_H