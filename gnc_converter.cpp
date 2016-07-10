#include "gnc_converter.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

GNC_CONVERTER::GNC_CONVERTER(void)
{

}

void GNC_CONVERTER::convertGerber2GCode(string filename)
{
    ifstream file;
    file.open(filename);

    ofstream ngc_file;
    ngc_file.open("cnc_code.ngc");

    // Parse header


    // Print standard header in ngc_file
    ngc_file << "G20 (Use Inches)" << endl;
    ngc_file << "G90 (Set Absolute Coordinates)" << endl;
    ngc_file << "G17 (G0 XY plane selection)" << endl;
    ngc_file << "G0 Z" << this->safeZ << endl;
    ngc_file << "G0 X0 Y0" << endl;
    ngc_file << "M03 (Start spindle)\n\n";

    string line;
    while (getline(file, line))
    {
        if(line.at(0) == 'X')
        {
            ngc_file << "G1 X";
            string x = line.substr(1, line.find_first_of('Y') - 1);
            cout << x << endl;
            double x_int = stod(x)/10000;
            ngc_file << x_int << " Y";
            string y = line.substr(line.find_first_of('Y') + 1, line.length());
            cout << y << endl;
            double y_int = stod(y)/10000;
            ngc_file << y_int << " F" << this->moveSpeed << endl;

            // Drill
            ngc_file << "G1 Z" << this->drillDepth << "F" << this->drillSpeed << endl;
            ngc_file << "G0 Z"<< this->safeZ << endl << endl;
        }
    }

    // Print standard footer
    ngc_file << "M05 (Stop spindle)\n";
    ngc_file << "M02 (Program End)\n";

    file.close();
    ngc_file.close();
}
