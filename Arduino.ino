#include <Wire.h>
#include "plant.h"
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

//define pins for analog sensors
int photoResistor = 0;
int thermister = 1;
int piezo = 2;

void setup()
{
  	Serial.begin(9600);
	Wire.begin();
	writeI2CRegister8bit(0x20, 6); //reset humidity sensor

 
	Serial.println("*****************************************");
	Serial.println("*Hello! Welcome to our Virtual Gardener!*");
	Serial.println("*Please select your plant!              *");
	Serial.println("*  #1 : Mushroom                        *");//Dry plant
	Serial.println("*  #2 : Sunflower                       *");//Normal plant
	Serial.println("*  #3 : Tomato                          *");//Wet plant
	Serial.println("*  #4 : Always Angry Cactus              *");//All fail
	Serial.println("*****************************************");
   	Wire.begin();
    matrix.begin(0x70);            // pass in the address

}

static const uint8_t PROGMEM
   smile_bmp[] =
   { B00111100,
     B01000010,
     B10100101,
     B10000001,
     B10100101,
     B10011001,
     B01000010,
     B00111100 },
   neutral_bmp[] =
   { B00111100,
     B01000010,
     B10100101,
     B10000001,
     B10111101,
     B10000001,
     B01000010,
     B00111100 },
   frown_bmp[] =
   { B00111100,
     B01000010,
     B10100101,
     B10000001,
     B10011001,
     B10100101,
     B01000010,
     B00111100 };

	 
void loop()
{
    matrix.clear();

	if(Serial.available() > 0)
	{
		plantSel = (Serial.read() - 48);
		delay(10);
		//Serial.println(plantSel);
		setPlant(plantSel);
		// All the below functions are just to confirm input data and value
		setStatus();
//		displayPlantStatus(); // Prints out the Array "status[]"
//		displayValues(); //prints out light, sound and temp readings
//		displayChirpValues(); // prints out humidity reading
//		Serial.print("heatThreshhold = ");
//		Serial.println(heatThreshhold);
//		Serial.print("humidityThreshhold = ");
//		Serial.println(humidityThreshhold);		
//		Serial.available() == 2;
//				Serial.println("***************************************");
//				Serial.println("***************************************");
//				Serial.println("***************************************");

    Serial.print("You Chose: ");
    Serial.println(plantSel);

    Serial.println("Based on our readings, your plant: ");
                 
                int gcount = getGood();
   
                if(gcount == 4)
                {
                    Serial.println("   -Is very HAPPY!!!");
                        setLED();
                }

                else
                {
                    //Light check
                    if(status[0] == 0)
                        Serial.println("   -Is UNHAPPY with it's LIGHT");
     
                    //Temperature check
                    if(status[1] == 0)
                        Serial.println("   -Is UNHAPPY with it's TEMPERATURE");
    
                    //Humidity check
                    if(status[2] == 0)
                        Serial.println("   -Is UNHAPPY with it's WATER");
     
                    //Sound check
                    if(status[3] == 0)
                        Serial.println("   -Is UNHAPPY with the amount of NOISE...SHHHH!");
                    
                    setLED();
                }

                Serial.available() == 2;
    }

}

int getGood()
{
     //1 = true... parameter satisfied
     //0 = false... parameter unsatisfied
  
     int goodcount = 0; 
     
     for(int x = 0; x<5; x++)
     {
         if(status[x] == 1)
           goodcount++;
     }
   
     return goodcount;
}
  		
void setLED()
{
     matrix.clear();
     matrix.setRotation(0);
   
     int gcount2 = getGood();
     
     //All Good
     if(gcount2 == 4)
     {
         matrix.clear();
         matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
         matrix.blinkRate(0);
         matrix.writeDisplay();
     }
  
     //1 or more params not satisfied
     if(gcount2 < 4 && gcount2 > 0)
     {
         matrix.clear();
         matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_ON);
         matrix.blinkRate(2);
         matrix.writeDisplay();
      }
  
      //No params satisfied
      if(gcount2 == 0)
      {
         matrix.clear();
         matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
         matrix.blinkRate(1);
         matrix.writeDisplay();
      }
}

