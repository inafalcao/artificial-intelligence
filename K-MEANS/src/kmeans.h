#ifndef KMEANS_H
#define KMEANS_H

#include "kmeans.h"
#include <vector>
#include "point.h"

class Kmeans
{
public:

    /* ==========================================================
                             Constructors
    ========================================================== */
    Kmeans(vector<Point> points);

    /* ==========================================================
                                 Sets
    ========================================================== */
   
    /* ==========================================================
                                 Gets
    ========================================================== */

    /* ==========================================================
                                 Run
    ========================================================== */
    bool run();

    // Calcula distancia de um ponto origem a um ponto destino
    double calculateDistance(Point o, Point d);
    // Recalcula centroides
    void recalculateCentroids(vector<Point> centroids);
    // Seta o grupo de todos os pontos pra -1
    void resetGroups();
    // Retorna o quão bom foi a divisão com um certo k.
    double getPrecision(vector<Point> centroids);

private:

    vector<Point> points;

};

#endif //KMEANS_H
