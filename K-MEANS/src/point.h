/**
* Class used for the points
*/

#ifndef POINT_H
#define POINT_H

using namespace std;

class Point
{

public:

    /* ==========================================================
                             Constructors
    ========================================================== */
    Point();

    /* ==========================================================
                                 Gets
    ========================================================== */
    double getX();
    double getY();
    double getZ();
    double getW();
    double getGroup();

    /* ==========================================================
                                 Sets
    ========================================================== */
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setW(double w);
    void setGroup(double g);

    void printPoint();

private:
    // Coordinates
    double x;
    double y;
    double z;
    double w;

    // The point belongs to this group. It's a index of the centroids vector.
    double group;
};

#endif //POINT_H
