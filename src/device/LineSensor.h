#include "../config.h"
#include <Arduino.h>

class LineSensor
{
    public: 
        LineSensor();
    
        void update();
           
        bool isWhiteFL;
        bool isWhiteFR;
        bool isWhiteBL;
        bool isWhiteBR;
};
