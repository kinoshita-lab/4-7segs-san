#include "TM1640.h"
using namespace kinoshita_lab;
TM1640 tm(11, 12);

void setup()
{    
    tm.init();
    tm.setDigit(0, 1);
    tm.setDigit(1, 2);
    tm.setDigit(2, 3);
    tm.setDigit(3, 4);    
}

void loop()
{
    tm.loop();
}