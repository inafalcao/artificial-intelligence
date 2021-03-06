#include "mlp.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdlib.h>     		/* srand, rand */

#define NEURON_COUNT  			3
#define NEURON_COUNT_O  		1
#define WEIGHTS_INITIAL_VALUE  	0.1
#define EPOCA					10
#define ALPHA					0.2
#define TOTAL					699

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
	this->result.resize(NEURON_COUNT_O , 1);
	this->Uoculta.resize(NEURON_COUNT_O , 1);

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

void MLP::setMartrixResult(Matrix R) {
	this->result = R;
}

void MLP::setMartrixUoculta(Matrix Uo) {
	this->Uoculta = Uo;
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

Matrix MLP::getUoculta() { return Uoculta; }

Matrix MLP::getResult() { return result; }
/* ==========================================================
                             Run
========================================================== */
bool MLP::run()
{
	int acertou = 0;
    //cout << X << endl;
    //cout << XT << endl;
	for(int i = 1; i <= EPOCA; i++) {
		randomizeTraining();
		for(int j = 1; j <=this->X.lines() * 0.7; j++) {
		
		    //cout << YT << endl;
		    //cout << "Antes do calculateU" << endl;
			calculateU(j);
			//cout << "Antes do calculateZ" << endl;
			calculateZ();
			//cout << "Antes do calculateUoculta" << endl;
			calculateUoculta();
			//cout << "Antes do calculateResult" << endl;
			calculateResult();
			//cout << "Antes do updateM" << endl;
			updateM(j);
			//cout << "Antes do updateW" << endl;
			updateW(j);
		}
	}
	
	cout << endl << "Matriz W final: " << endl << W << endl << endl;
	cout << endl << "Matriz M final: " << endl << M << endl << endl;

	for(int j = 1; j <=this->X.lines(); j++) {
		calculateU2(j);								//NÃO É MAIS TREINAMENTO
		calculateZ();
		calculateUoculta();
		calculateResultFinal();

		if(getResult().get(1,1) == getY().get(j,1)) {
			acertou++;
		}
	}

	cout << "Acertou: " << acertou << " de " << TOTAL << endl;

	return false;
}

void MLP::initializeW() {
	this->W.resize(this->X.rows() + 1, NEURON_COUNT);

	int elementCount = (this->X.rows()+1) * (NEURON_COUNT);
	for(elementCount; elementCount > 0; elementCount--) {
		W >> WEIGHTS_INITIAL_VALUE;
	}

	//cout << this->W;
}

void MLP::initializeM() {
	this->M.resize(NEURON_COUNT+1, NEURON_COUNT_O);

	int elementCount = (NEURON_COUNT+1) * (NEURON_COUNT_O);			//Essa Matriz ta errada VER DEPOIS (CORRIGIDA?)
	for(elementCount; elementCount > 0; elementCount--) {
		M >> WEIGHTS_INITIAL_VALUE;
	}

	//cout << this->M;
}

void MLP::initializeXT() {
	// Get 70% of the X
	int XTLines = this->X.lines() * 0.7 + 1;            //TESTANDO O +1
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

void MLP::initializeYT() {						//TRANSFORMAR DE 2 e 4 PRA 0 e 1 ?
	// Get 70% of the Y
	int YTLines = this->Y.lines() * 0.7 + 1;

	// YT has 70% of the lines of Y, and the same rows
	this->YT.resize(YTLines, this->Y.rows());

	int lines = 1;
	for(lines; lines <=YTLines; lines++) {
		YT >> this->Y.get(lines, this->Y.rows());
	}

	//cout << this->YT;
}

void MLP::randomizeTraining() {
  	srand (time(NULL)); // initialize random seed.
	int lineCount = this->X.lines() * 0.7;

	// Lines to switch
	int line1 = 0;
	int line2 = 0;

	// Switch lines 70% times
	int switchNumber = lineCount;
	for(switchNumber; switchNumber > 0; switchNumber--) {
		// Choose lines to switch
		line1 = rand() % lineCount + 1;
		line2 = line1;
		while(line1 == line2) {
			line2 = rand() % lineCount + 1;
		}

		// Switch in XT
		int xRowCount = this->X.rows();
		for (xRowCount; xRowCount > 0; xRowCount--)
		{
			// Switch row by row elements of the lines
			double aux;
			aux = this->XT.get(line1, xRowCount);
			this->XT.put(this->XT.get(line2, xRowCount), line1, xRowCount);
			this->XT.put(aux, line2, xRowCount);
		}

		// Switch in YT
		double aux;
		aux = this->YT.get(line1, 1);
		this->YT.put(this->YT.get(line2, 1), line1, 1);
		this->YT.put(aux, line2, 1);

	}

	//cout << this->YT;

}

void MLP::calculateU(int i) {
	Matrix mtx (10, 2);
	mtx >> -1;
	for(int j = 1; j < 10; j++) {		//Depois olhar aqui
		mtx >> this->XT.get(i,j);
	}

	this->U = this->W.transpose()*mtx;
}

void MLP::calculateU2(int i) {
	Matrix mtx (10, 2);
	mtx >> -1;
	for(int j = 1; j < 10; j++) {		//Depois olhar aqui
		mtx >> this->X.get(i,j);
	}

	this->U = this->W.transpose()*mtx;
}

void MLP::calculateZ() {
	this->Z >> -1;
	this->Z >> 1/(1 + exp(-(this->U.get(1,1))));
	this->Z >> 1/(1 + exp(-(this->U.get(2,1))));
	this->Z >> 1/(1 + exp(-(this->U.get(3,1))));
}

void MLP::calculateUoculta() {
	this->Uoculta = this->M.transpose()*this->Z;
}

void MLP::calculateResult() {
	this->result >> 1/(1 + exp(-(this->Uoculta.get(1,1))));
}

void MLP::calculateResultFinal() {
	this->result >> 1/(1 + exp(-(this->Uoculta.get(1,1))));
	if(this->result.get(1,1) < 0.5) {
	    this->result.put(0, 1, 1);
	}
	
	else this->result.put(1, 1, 1);
}

void MLP::updateM(int i) {
	double erro = this->YT.get(i,1) - this->result.get(1,1);
	double Gk = erro*getResult().get(1,1);
	double aux;
	

	for(int j = 1; j<=4; j++) {
	    if(j == 1) {
	        aux = this->M.get(j,1) + ALPHA*Gk*(-1);
	    }
		aux = this->M.get(j,1) + ALPHA*Gk*this->Z.get(j,1);
		this->M.put( aux, j, 1);
		
	}
}

void MLP::updateW(int i) {
	double erro = this->YT.get(i,1) - this->result.get(1,1);
	double Gk = erro*getResult().get(1,1);
	double Gi;
	double aux;

	for(int j = 1; j<=3; j++) {
	    Gi = this->Z.get(j,1)*Gk*this->M.get(j,1);
		for(int k = 1; k<=10; k++) {
		    
			if(k == 1) {
			    aux = this->W.get(k,j) + ALPHA*Gi*(-1);
			}
			else aux = this->W.get(k,j) + ALPHA*Gi*this->XT.get(i, k - 1);
			this->W.put( aux, k, j);

		}
	}
}

void MLP::normalizarX() {

	double gambiarra;
	double maximo = 0;
	double minimo = 100;

    for(int i = 1; i <= 699; i++) {
       for(int j = 1; j<=9; j++) {
	        if(this->X.get(i,j) < minimo) {
	            minimo = this->X.get(i,j);
	        }
	        if(this->X.get(i,j) > maximo) {
	            maximo = this->X.get(i,j);
	        }       
       } 
    }
    
    for(int i = 1; i <= 699; i++) {
       for(int j = 1; j<=9; j++) {
            gambiarra = (this->X.get(i,j) - minimo)/(maximo - minimo);
            this->X.put(gambiarra, i, j);
       }
    }
    
}
