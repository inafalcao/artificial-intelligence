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

    void setMartrixResult(Matrix R);
    void setMartrixUoculta(Matrix Uo);
    /* ==========================================================
                                 Gets
    ========================================================== */
    Matrix getX();
    Matrix getY();

    Matrix getM();
    Matrix getW();

    Matrix getU();
    Matrix getZ();

    Matrix getUoculta();
    Matrix getResult();
    /* ==========================================================
                                 Run
    ========================================================== */
    bool run();

    // Initialize W's and M's weights matrices with values between [0, 0.1]
    void initializeW();
    void initializeM();

    // Initialize training matrices
    void initializeXT();
    void initializeYT();

    void randomizeTraining();

    void calculateU(int i);
    void calculateU2(int i);

    void calculateZ();

    void calculateUoculta();
    void calculateResult();
    void calculateResultFinal();

    void updateM(int i);
    void updateW(int i);
    
    void normalizarX();

private:

    Matrix X;             // The total X's Matrix
    Matrix Y;             // The total Y's Matrix

    Matrix XT;             // The X's Matrix for training
    Matrix YT;             // The Y's Matrix for training

    Matrix W;             // The W's Matrix, for the first layer.
    Matrix M;             // The Y's Matrix, for the second layer.

    Matrix U;             //
    Matrix Z;             //

    Matrix Uoculta;
    Matrix result;

};

#endif //MLP_H
