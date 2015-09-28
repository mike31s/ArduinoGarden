
/*************************************************
//
//Function Name: setStatus()
//
//DESCRIPTION:  takes readings and populates array status array
//
//Parameters:   none
//
//Return values: none
//************************************************/
void setStatus()
{	
	if (checkLight() == true)//check if has light
		status[0] = 1;
	else
		status[0] = 0;
		
	if (analogRead(thermister) > heatThreshhold)//check temp 
		status[1] = 1;
	else
		status[1] = 0;
	if (readI2CRegister16bit(0x20, 0) > humidityThreshhold)//check water
		status[2] = 1;
	else
		status[2] = 0;
	if (checkKnock() == false)//check sound		
		status[3] = 1;
	else
		status[3] = 0;

	if (plantSel == 4)
	{
		status[0] = 0;
		status[1] = 0;
		status[2] = 0;
		status[3] = 0;
	}
}

/*************************************************
//
//Function Name: displayPlantStatus()
//
//DESCRIPTION:  prints array associated with plant object
//
//Parameters:   none
//
//Return values: none
//************************************************/
void displayPlantStatus()
{
	setStatus();
	Serial.println("PLANT ARRAY: ");

	Serial.print("Light: ");
	Serial.println(status[0]);			
	Serial.print("Temp: ");
	Serial.println(status[1]);			
	Serial.print("Humidity: ");
	Serial.println(status[2]);			
	Serial.print("Sound: ");
	Serial.println(status[3]);	
	Serial.println("*********");
}

/*************************************************
//
//Function Name: setPlant()
//
//DESCRIPTION:  changes thresholds based on plant choice
	1 = dry plant 2 = normal plant 3 = wet plant
//
//Parameters:   int plantType identifier
//
//Return values: none
//************************************************/

void setPlant(int plantType)
{
	if (plantType == 1)
	{
		heatThreshhold = 50;
		humidityThreshhold = 200;
	}
	if (plantType == 2)
	{
		heatThreshhold = 1;
		humidityThreshhold = 200;
	}
	if (plantType == 3)
	{
		heatThreshhold = 10;
		humidityThreshhold = 250;
	}
	
	if (plantType == 4)
	{
		heatThreshhold = 1;
		humidityThreshhold = 200;
	}
	if ((plantType > 4) || (plantType < 1))
	{
		Serial.println("Invalid input, using default plant type	");		
		heatThreshhold = 1;
		humidityThreshhold = 200;
	}
}

