#include "gnc_converter.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

GNC_CONVERTER::GNC_CONVERTER(void)
{

}

void GNC_CONVERTER::inches2mm()
{
    if (false == this->mm)
    {
        this->safeZ =  this->safeZ*25.4;
        this->drillDepth =  this->drillDepth*25.4;
        this->drillSpeed = this->drillSpeed*25.4;
        this->moveSpeed = this->moveSpeed*25.4;
        this->mm = true;
    }
}

void GNC_CONVERTER::mm2inches()
{
    if (true == this->mm)
    {
        this->safeZ =  this->safeZ/25.4;
        this->drillDepth =  this->drillDepth/25.4;
        this->drillSpeed = this->drillSpeed/25.4;
        this->moveSpeed = this->moveSpeed/25.4;
        this->mm = false;
    }
}

void GNC_CONVERTER::convertGerber2GCode(string filename)
{
    ifstream file;
    file.open(filename);

    ofstream ngc_file;
    ngc_file.open("cnc_code.ngc");

    string line;
    // Parse header
    getline(file, line);
    if (line.compare("G20 (Uses Inches)"))
    {
        ngc_file << "G20 (Use Inches)" << endl;
        this->mm = false;
    }
    else
    {
        ngc_file << "G21 (Use mm)" << endl;
        this->inches2mm();
    }

    // Print standard header in ngc_file
    ngc_file << "G90 (Set Absolute Coordinates)" << endl;
    ngc_file << "G17 (G0 XY plane selection)" << endl;
    ngc_file << "G0 Z" << this->safeZ << endl;
    ngc_file << "G0 X0 Y0" << endl;
    ngc_file << "M03 (Start spindle)\n\n";

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
            ngc_file << "G1 Z" << this->drillDepth << " F" << this->drillSpeed << endl;
            ngc_file << "G0 Z"<< this->safeZ << endl << endl;
        }
    }

    // Print standard footer
    ngc_file << "M05 (Stop spindle)\n";
    ngc_file << "M02 (Program End)\n";

    file.close();
    ngc_file.close();
}
