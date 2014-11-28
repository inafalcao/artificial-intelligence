#include "kmeans.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdlib.h>     		/* srand, rand */

#define MAX_K  			10
#define INITIAL_K  		2 	// começar sempre com 2 centróides


using namespace std;

/* ==========================================================
                         Constructors
========================================================== */
Kmeans::Kmeans(vector<Point> points)
    : points(points)
{

}

/* ==========================================================
                             Run
========================================================== */
bool Kmeans::run()
{

	int k = INITIAL_K;
	srand (time(NULL));

	// Calcula precisões para cada k
	for(k; k <= MAX_K; k++) {

		// seleciono k pontos aleatórios na matriz. eles serão os centroides iniciais.
		vector<Point> centroids; // Cada índice neste vetor, representa um grupo daquele centroide. Ex: indice 0, centroide do indice 0 é do grupo 0
		
		int i = 0;
		for(i; i < k; i++) {
			int randomCentroid = 0;
			//points.at(0).printPoint();
			randomCentroid = rand() % points.size(); // Gera um numero entre 0 e a quantidade de pontos.
		   	centroids.push_back(points.at(randomCentroid));
		}

		bool precisaIterar = true;
		// Enquanto houver ponto trocando de grupo, itera
		while(precisaIterar) {

			// Para todo ponto na lista de pontos, faça
			int p = 0;
			bool mudouGrupo = false;
			for(p; p < points.size(); p++) {
				double distancia = 0;
				mudouGrupo = false;
				int centroideEscolhido = 0;
				
				// calcula a sua distância para todos os centroides, decide qual é 
				// o mais próximo e coloca o ponto no grupo do mais próximo
				int m = 0;
				for(m; m < centroids.size(); m++) {
					double aux = calculateDistance(points.at(p), centroids.at(m));
					if(aux < distancia) {
						distancia = aux;
						centroideEscolhido = m;
					}
				}

				// Se mudou de grupo, seto o grupo no ponto
				if(points.at(p).getGroup() != centroideEscolhido) {
					mudouGrupo = true;
					points.at(p).setGroup(centroideEscolhido);
				}

			}

			precisaIterar = mudouGrupo;
			recalculateCentroids(centroids);

			// Imprime centroides
			/*for(int i = 0; i < centroids.size(); i++) {
				centroids.at(i).printPoint();
			}*/
		}

		cout << "Precisão com k = " << k << " -> " << getPrecision(centroids) << endl;
		resetGroups();

	}

	return false;
}

double Kmeans::calculateDistance(Point o, Point d) {
	double distance = sqrt(
							pow(o.getX() - d.getX(), 2) +
							pow(o.getY() - d.getY(), 2) + 
							pow(o.getZ() - d.getZ(), 2) + 
							pow(o.getW() - d.getW(), 2)
							);
	return distance;
}

void Kmeans::recalculateCentroids(vector<Point> centroids) {
	// Valores usados para médias
	double mx = 0;
	double my = 0;
	double mz = 0;
	double mw = 0;

	int contagemElementos = 0;

	int m = 0;

	// Para todos os centroides
	for(m; m < centroids.size(); m++) {
		
		// Devo recalcular as médias para este centroide
		mx = 0;
		my = 0;
		mz = 0;
		mw = 0;

		int i = 0;
		
		// Para todos os pontos
		for(i; i<points.size(); i++) {
			// Se grupo do ponto for o desse centróide, adiciono os valores das coordenadas para tirar a média
			if(points.at(i).getGroup() == m) {
				contagemElementos++;
				mx += points.at(i).getX();
				my += points.at(i).getY();
				mz += points.at(i).getZ();
				mw += points.at(i).getW();
			}
		}

		// Atualizo o centroide
		centroids.at(m).setX(mx/contagemElementos);
		centroids.at(m).setY(my/contagemElementos);
		centroids.at(m).setZ(mz/contagemElementos);
		centroids.at(m).setW(mw/contagemElementos);
	}

}

void Kmeans::resetGroups() {
	int j = 0;
	for(j; j < points.size(); j++) {
		points.at(j).setGroup(MAX_K + 1);
	}
}

double Kmeans::getPrecision(vector<Point> centroids) {
	double somatorio = 0;

	// para todo ponto da matriz, calcula a distância desse ponto ao seu centróide,
	// em seguida adiciona essa valor ao somatório de distâncias
	int i = 0;
	for(i; i<points.size(); i++) {
		somatorio += calculateDistance(points.at(i), 
									   centroids.at(points.at(i).getGroup())
									   );
	}

	return somatorio;
}