#ifndef ENCODING_H
#define ENCODING_H

float EnReadFL();
float EnReadFR();
float EnReadBL();
float EnReadBR();
void EnWriteFL(float);
void EnWriteFR(float);
void EnWriteBL(float);
void EnWriteBR(float);
float EnVelocityFL();
float EnVelocityFR();
float EnVelocityBL();
float EnVelocityBR();
float EnExtropolateFL();
float EnExtrapolateFR();
float EnExtrapolateBL();
float EnExtrapolateBR();

#endif
