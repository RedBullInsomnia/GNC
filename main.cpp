#include <gnc_converter.h>

int main(int argc, char *argv[])
{
    GNC_CONVERTER converter;

    converter.convertGerber2GCode("drill.txt");

    return 0;
}

