#include "point.h"
#include <iostream>

using namespace std;

/* ==========================================================
                         Constructors
========================================================== */
Point::Point()
{ this->group = -1;}

/* ==========================================================
                             Gets
========================================================== */
double Point::getX()
{ return this->x; }

double Point::getY()
{ return this->y; }

double Point::getZ()
{ return this->z; }

double Point::getW()
{ return this->w; }

double Point::getGroup()
{ return this->group; }

/* ==========================================================
                             Sets
========================================================== */
void Point::setX(double x) {
    this->x = x;
}
void Point::setY(double y) {
    this->y = y;
}

void Point::setZ(double z) {
    this->z = z;
}

void Point::setW(double w) {
    this->w = w;
}

void Point::setGroup(double group) {
    this->group = group;
}

/* ==========================================================
                             Logic
========================================================== */

// Prints the point coordinates
void Point::printPoint() {
    cout << "[" << x << ", " << y << ", " << z << ", " << w << "]" << "[" << group << "]" << endl; 
}