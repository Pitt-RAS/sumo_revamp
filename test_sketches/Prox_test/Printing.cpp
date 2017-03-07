#include "Printing.h"

int proximity_sensors_front[5]        = {F_PROX1_PIN, F_PROX2_PIN, F_PROX3_PIN, F_PROX4_PIN, F_PROX5_PIN};
int proximity_sensors_front_weight[5] = {-90,         -45,         0,           45,          90};

ProxSense frontProx(proximity_sensors_front, proximity_sensors_front_weight);


Printing::Printing()
{
    GoOut();
}

void Printing::GoOut()
{
    int prox_front_error = frontProx.readAngle();

    Serial.println(prox_front_error);

    delay(100);
}

