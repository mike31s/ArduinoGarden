#include <Wire.h>

/*************************************************
//
//Function Name: writeI2CRegister8bit
//
//DESCRIPTION:  Writes specified header to I2C address
//
//Parameters:   int addr = I2C address, int value = the value going in
//
//Return values: none
//************************************************/  


void writeI2CRegister8bit(int addr, int value) 
{
	Wire.beginTransmission(addr);
	Wire.write(value);
	if (Wire.endTransmission() != 0) //check for data sent
		Serial.println("Wire.endTransmission: Failed");
}

/*************************************************
//
//Function Name: readI2CRegister16bit
//
//DESCRIPTION:  reads bit in 16 bit header
//
//Parameters:   int addr = I2C address, int reg = header bit
//
//Return values: unsigned int = bit value
//************************************************/  
unsigned int readI2CRegister16bit(int addr, int reg) 
{
	Wire.beginTransmission(addr);	//ask for register bit reg
	Wire.write(reg);
	Wire.endTransmission();	
	delay(20);
	Wire.requestFrom(addr, 2);	//request 2 bytes
	//while(Wire.available() == 0);
	
	unsigned int t = Wire.read() << 8;
	t = t | Wire.read();
	if (t == 65535)
		return 0;
	else
		return t;
}
/*************************************************
//
//Function Name: displayChirpValues
//
//DESCRIPTION:  Reads Chirp header and prints values
//
//Parameters:   none
//
//Return values: none
//************************************************/  

void displayChirpValues()
{
	Serial.print("Chirp Humidity: ");
	Serial.println(readI2CRegister16bit(0x20, 0)); //read capacitance register
	Serial.print("Chirp Temp: ");
	Serial.println(readI2CRegister16bit(0x20, 5)); //temperature register
	//Serial.print("Light: ");
	//writeI2CRegister8bit(0x20, 3); //request light measurement 
	//Serial.println(readI2CRegister16bit(0x20, 4)); //read light register
	//delay(500);
}
