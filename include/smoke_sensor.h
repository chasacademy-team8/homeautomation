#ifndef SMOKE_SENSOR_H
#define SMOKE_SENSOR_H

//extern volatile bool smokeAlarm;

void initSmokeSensor();
bool isSmokeDetected();
void smokeInterrupt();

#endif