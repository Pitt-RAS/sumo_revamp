#ifndef LINE_SENSE_H 
#define LINE_SENSE_H

class LineSense
{

	private:
	  int FL_PIN;
      int FR_PIN;
      int BL_PIN;
      int BR_PIN;
    public: 
        LineSense(int fl_pin, int fr_pin, int bl_pin, int br_pin);
    
            void update();
               
            bool isWhiteFL;
            bool isWhiteFR;
            bool isWhiteBL;
            bool isWhiteBR;
};

#endif
