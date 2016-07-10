#include <gnc_converter.h>

int main(int argc, char *argv[])
{
    GNC_CONVERTER converter;

    converter.convert2GCode("drill.txt");

    return 0;
}

