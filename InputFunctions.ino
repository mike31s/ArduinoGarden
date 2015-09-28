extern int photoResistor;
extern int thermister;
extern int piezo;

/*************************************************
//
//Function Name: displayValues
//
//DESCRIPTION:  Prints out analog values from sensors
//
//Parameters:   none
//
//Return values: none
//************************************************/  

void displayValues()
{
	Serial.print("Light: ");
	Serial.println(analogRead(photoResistor));
	checkLight();
	Serial.print("Thermister Temp: ");
	Serial.println(analogRead(thermister));
	checkKnock();
	Serial.print("Piezo: ");
	Serial.println(analogRead(piezo));			
	
	Serial.println("---");
	Serial.println();
	Serial.println();

}

/*************************************************
//
//Function Name: checkLight()
//
//DESCRIPTION:  Checks if enough light is present to be on
//
//Parameters:   none
//
//Return values: True if light is on False if off
//************************************************/  

bool checkLight()
{
	bool lightOn;
	//Serial.print("lightOn = ");	
	if (analogRead(photoResistor) > 300)
		{
			lightOn = true;
			//Serial.println("On");			
		}
	else
		{
			lightOn = false;
		//Serial.println("Off");			
		}
	return lightOn;
}

/*************************************************
//
//Function Name: checkKnock()
//
//DESCRIPTION:  Checks if someone is knocking
//
//Parameters:   none
//
//Return values: true if senses knock otherwise false
//************************************************/  

bool checkKnock()
{
	int value = analogRead(piezo);
		
	if (value >= 100)
	{
//		Serial.println("Knock!");
		//piezoSong();
		return true;
	}	
	return false;
}

/*************************************************
//
//Function Name: piezoSong()
//
//DESCRIPTION:  Plays a tune with the piezo
//
//Parameters:   none
//
//Return values: none
//************************************************/  
void piezoSong()
{
int speakerOut = 9;              
byte names[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};  
int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
byte melody[] = "2d2a1f2c2d2a2d2c2f2d2a2c2d2a1f2c2d2a2a2g2p8p8p8p";
// count length: 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
//                                10                  20                  30
int count = 0;
int count2 = 0;
int count3 = 0;
int MAX_COUNT = 24;


analogWrite(speakerOut, 0);    
	for (count = 0; count < MAX_COUNT; count++) 
	{
		for (count3 = 0; count3 <= (melody[count*2] - 48) * 30; count3++) 
		{
			for (count2=0;count2<8;count2++) 
			{
				if (names[count2] == melody[count*2 + 1]) 
				{      
					analogWrite(speakerOut,500);
					delayMicroseconds(tones[count2]);
					analogWrite(speakerOut, 0);
					delayMicroseconds(tones[count2]);
				}
				if (melody[count*2 + 1] == 'p') 
				{
          // make a pause of a certain size
				analogWrite(speakerOut, 0);
				delayMicroseconds(500);
				}
			}
		}
	}
}