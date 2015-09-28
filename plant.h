#ifndef PLANT_H
#define PLANT_H

void writeI2CRegister8bit(int addr, int value); 
unsigned int readI2CRegister16bit(int addr, int reg);
void displayChirpValues();

int heatThreshhold = 1;
int humidityThreshhold = 200;
int status [4];
int plantSel = 0;

#endif
