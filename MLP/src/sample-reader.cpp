#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>               /* atof */
#include "sample-reader.h"

#define X_SAMPLES_LINES           699
#define X_SAMPLES_ROWS            9

using namespace std;


/* ==========================================================
                         Constructors
========================================================== */
SampleReader::SampleReader()
{ }

/* ==========================================================
                             Gets
========================================================== */
Matrix SampleReader::getX()
{ return this->X; }

Matrix SampleReader::getY()
{ return this->Y; }

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
        double x = 0;
        double y = 0;

        this->X.resize(X_SAMPLES_LINES, X_SAMPLES_ROWS);
        this->Y.resize(X_SAMPLES_LINES, 1);

        vector <double>  data;
       

        // Reads the body (points)
        while (sampleFile)
        {

            
            string s;
            if (!getline( sampleFile, s )) break;

            istringstream ss( s );

            int count = 0;
            while (ss)
            {
              string s;
              if (!getline( ss, s, ',' )) break;
              
              x = atof(s.c_str());

              count++;

              cout << count << "-";
              if(count > 1 && count < 10) {
                X >> x;
              }

              if(count == 10) {
                Y >> x;
                count = 0;
              }
                

              //cout << x << " - ";
            }

            
            data.empty();

            
            // Reading 10 values of x.
            /*for(int i = 1; i <= 9; i++) {
                sampleFile >> x;
                
                X >> x;
                sampleFile >> coma;
            }*/

            // Reading y
            //sampleFile >> y;
            //Y >> y;
        }

        // Feedback
        cout << endl
             << ""
             << "===============================================" << endl
             << "X matrix"                                        << endl
             //<< std::setw(2) <<  X                                << endl << endl
             << "===============================================" << endl
             << "Y matrix"                                        << endl
             << "===============================================" << endl;
    }
    else
    {
        cout << "Could not read the file." << endl;
        return false;
    }

    return true;
}
