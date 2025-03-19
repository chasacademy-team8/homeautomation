#include <Arduino.h>
#include <Arduino_LED_Matrix.h>
#include "matrix.h"

ArduinoLEDMatrix matrix;

void initMatrix()
{
    matrix.loadSequence(LEDMATRIX_ANIMATION_HEARTBEAT_LINE);
    matrix.begin();
    matrix.play(true);
}