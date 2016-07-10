#ifndef GNC_CONVERTER_H
#define GNC_CONVERTER_H

#include <string>

class GNC_CONVERTER
{
private:
    double safeZ = 0.25;
    double drillDepth = -0.1;
    double drillSpeed = 4.5;
    double moveSpeed = 15;
    bool cm = false;

public:
    GNC_CONVERTER();
    void convertGerber2GCode(std::string filename);
};


#endif // GNC_CONVERTER_H
