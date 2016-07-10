#ifndef GNC_CONVERTER_H
#define GNC_CONVERTER_H

#include <string>

class GNC_CONVERTER
{
private:
    double safeZ = 0.25; // in inches
    double drillDepth = -0.1;
    double drillSpeed = 4.5;
    double moveSpeed = 15;
    bool mm = false; // flag true if in cm

public:
    GNC_CONVERTER();

    void inches2mm();

    void mm2inches();

    void convertGerber2GCode(std::string filename);

};


#endif // GNC_CONVERTER_H
