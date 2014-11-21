#include "mlp.h"
#include <cmath>
#include <cstdio>
#include <iostream>

#define M_PI           			3.14159265358979323846  /* pi */

#define NEURON_COUNT  			3
#define WEIGHTS_INITIAL_VALUE  	0.1

using namespace std;

/* ==========================================================
                         Constructors
========================================================== */
MLP::MLP(Matrix X, Matrix Y)
    : X(X), Y(Y)
{
	initializeW();
	initializeM();
	initializeXT();
	initializeYT();

	this->U.resize(NEURON_COUNT  , 1);
	this->Z.resize(NEURON_COUNT+1, 1);
}

/* ==========================================================
                             Sets
========================================================== */
void MLP::setMartrixX(Matrix X)
{
    this->X = X;
}

void MLP::setMartrixY(Matrix Y)
{
    this->Y = Y;
}

void MLP::setMartrixW(Matrix W)
{
    this->W = W;
}

void MLP::setMartrixM(Matrix M)
{
    this->M = M;
}

void MLP::setMartrixU(Matrix U)
{
    this->U = U;
}

void MLP::setMartrixZ(Matrix Z)
{
    this->Z = Z;
}
/* ==========================================================
                             Gets
========================================================== */
Matrix MLP::getX() { return X; }

Matrix MLP::getY() { return Y; }

Matrix MLP::getW() { return W; }

Matrix MLP::getM() { return M; }

Matrix MLP::getU() { return U; }

Matrix MLP::getZ() { return Z; }
/* ==========================================================
                             Run
========================================================== */
bool MLP::run()
{
  
	return false;
}

void MLP::initializeW() {
	this->W.resize(this->X.rows() + 1, NEURON_COUNT);

	int elementCount = (this->X.rows() + 1) * (NEURON_COUNT);
	for(elementCount; elementCount > 0; elementCount--) {
		W >> WEIGHTS_INITIAL_VALUE;
	}

	//cout << this->W;
}

void MLP::initializeM() {
	this->M.resize(this->X.rows() + 1, NEURON_COUNT);

	int elementCount = (this->X.rows() + 1) * (NEURON_COUNT);
	for(elementCount; elementCount > 0; elementCount--) {
		M >> WEIGHTS_INITIAL_VALUE;
	}

	//cout << this->M;
}

void MLP::initializeXT() {
	// Get 70% of the X
	int XTLines = this->X.lines() * 0.7;
	int XTRows = this->X.rows();

	// XT has 70% of the lines of X, and the same rows
	this->XT.resize(XTLines, XTRows);

	int lines = 1;
	int rows = 1;
	for(lines; lines <= XTLines; lines++) {
		rows = 1;
		for(rows; rows <= XTRows; rows++) {
			XT >> this->X.get(lines, rows);
		}
	}

	//cout << this->XT;
}

void MLP::initializeYT() {
	// Get 70% of the Y
	int YTLines = this->Y.lines() * 0.7;

	// YT has 70% of the lines of Y, and the same rows
	this->YT.resize(YTLines, this->Y.rows());

	int lines = 1;
	for(lines; lines <=YTLines; lines++) {
		YT >> this->Y.get(lines, this->Y.rows());
	}

	//cout << this->YT;
}
