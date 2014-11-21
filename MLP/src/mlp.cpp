#include "mlp.h"
#include <cmath>
#include <cstdio>
#include <iostream>

#define M_PI           		3.14159265358979323846  /* pi */

#define HIDDEN_LAYERS  		2
#define W_INITIAL_VALUE  	0.1

using namespace std;

/* ==========================================================
                         Constructors
========================================================== */
MLP::MLP(Matrix X, Matrix Y)
    : X(X), Y(Y)
{
	initializeW();
	initializeXT();
	initializeYT();
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
	this->W.resize(this->X.rows() + 1, HIDDEN_LAYERS + 1);

	int elementCount = (this->X.rows() + 1) * (HIDDEN_LAYERS + 1);
	for(elementCount; elementCount > 0; elementCount--) {
		W >> W_INITIAL_VALUE;
	}

	//cout << this->W;
}

void MLP::initializeXT() {
	// Get 70% of the X
	int XTLines = this->X.lines() * 0.7;

	// XT has 70% of the lines of X, and the same rows
	this->XT.resize(XTLines, this->X.rows());

	int lines = 0;
	for(lines; lines < XTLines; lines++) {
		int rows = 0;
		for(rows; rows < this->X.rows(); rows++) {
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

	int lines = 0;
	for(lines; lines < YTLines; lines++) {
		int rows = 0;
		XT >> this->X.get(lines, this->Y.rows()-1);
	}

	//cout << this->YT;
}
