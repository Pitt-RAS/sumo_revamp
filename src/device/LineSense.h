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
        LineSense(int fl_pin, int fr_pin, int bl_pin, int br_pin) :
          FL_PIN(fl_pin),
          FR_PIN(fr_pin),
          BL_PIN(bl_pin),
          BR_PIN(br_pin) {
              pinMode(FL_PIN, INPUT);
              pinMode(FR_PIN, INPUT);
              pinMode(BL_PIN, INPUT);
              pinMode(BR_PIN, INPUT);
              
              update();
          }
    
            void update();

            bool hitLineInDirection(int direction);
               
            bool on_line;
            bool is_white_FL;
            bool is_white_FR;
            bool is_white_BL;
            bool is_white_BR;
};

#endif
