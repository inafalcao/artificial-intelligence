#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>               /* atof */
#include "sample-reader.h"

#define X_SAMPLES_LINES           150
#define X_SAMPLES_ROWS            4

using namespace std;


/* ==========================================================
                         Constructors
========================================================== */
SampleReader::SampleReader()
{ }

/* ==========================================================
                             Gets
========================================================== */
vector<Point> SampleReader::getPointList()
{ return this->pointList; }

/* ==========================================================
                             Sets
========================================================== */
void SampleReader::setPointList(vector<Point> list)
{ this->pointList = list; }


/* ==========================================================
                             Logic
========================================================== */
bool SampleReader::readSamplesFromFile(const char* filePath)
{
    ifstream sampleFile (filePath);

    /* +------------------------+ *
     * | Is the sample file ok? | *
     * +------------------------+ */

    // Yes
    if (sampleFile.good())
    {

        string id = "";
        string coma = "";
        double value = 0;
        double y = 0;


        
        // Reads the body (points)
        while (sampleFile)
        {

            
            string s;
            if (!getline( sampleFile, s )) break;

            istringstream ss( s );

            int count = 0;
            Point *p = new Point();
            while (ss)
            {
                string s;
                if (!getline( ss, s, ',' )) break;
                 
                count++;
                value = atof(s.c_str());

                if(count == 1)
                  p->setX(value);
                if(count == 2)
                    p->setY(value);
                if(count == 3)
                    p->setZ(value);
                if(count == 4)
                    p->setW(value);

            }
            pointList.push_back(*p);
            //p->printPoint();
        }

    }
    else
    {
        cout << "Could not read the file." << endl;
        return false;
    }

    return true;
}
