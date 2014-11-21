/**
* Class that simulates the neuron
* Author: Inaciane Monteiro
*/

#ifndef MLP_H
#define MLP_H

#include "matrix.h"

class MLP
{
public:

    /* ==========================================================
                             Constructors
    ========================================================== */
    MLP(Matrix X, Matrix Y);

    /* ==========================================================
                                 Sets
    ========================================================== */
    void setMartrixX(Matrix X);
    void setMartrixY(Matrix Y);

    void setMartrixM(Matrix M);
    void setMartrixW(Matrix W);

    void setMartrixU(Matrix U);
    void setMartrixZ(Matrix Z);   
    /* ==========================================================
                                 Gets
    ========================================================== */
    Matrix getX();
    Matrix getY();

    Matrix getM();
    Matrix getW();

    Matrix getU();
    Matrix getZ();
    /* ==========================================================
                                 Run
    ========================================================== */
    bool run();

    // Initialize W's matrix with values between [0, 0.1]
    void initializeW();

    void initializeXT();
    void initializeYT();

private:

    Matrix X;             // The total X's Matrix
    Matrix Y;             // The total Y's Matrix

    Matrix XT;             // The X's Matrix for training
    Matrix YT;             // The Y's Matrix for training

    Matrix W;             // The W's Matrix, for the first layer.
    Matrix M;             // The Y's Matrix, for the second layer.

    Matrix U;             //
    Matrix Z;             //

};

#endif //MLP_H