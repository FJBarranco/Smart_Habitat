void Orchid()


{


	//=====================================================================================================================================================================================================


		// Notes On Orchid Condtions Research
	//==================================================================
		// Air Temp (max 80f min 65f ) 
		// Soil Temp (max 80f min 70f ) 
		// Air Moisture ( min 85% max 99% ) 
		// Soil Moisture ( moist, well-draining conditions ) 
		// Lighting (bright, indirect light, and Some shade time too)
		// (Extra: Orchids require shallow planting. 


	

	{
		Serial.begin(9600);
	}

	Soiltemp.begin(); // Soil Temp Sensor

	//==================================================Relay Setup========================================================================================================================================================


	//=== Heating Fans ================================ Relay 1
	pinMode(HeatingFan, OUTPUT);
	digitalWrite(HeatingFan, HIGH);

	//=== Cooling Fans (Intake) ======================= Relay 2
	pinMode(CoolingingFans_Intake, OUTPUT);
	digitalWrite(CoolingingFans_Intake, HIGH);

	//=== Cooling Fans/Dehumidifer (Exhaust) ========== Relay 3
	pinMode(CoolingingFans_Exhaust, OUTPUT);
	digitalWrite(CoolingingFans_Exhaust, HIGH);

	//=== Humidifer =================================== Relay 4
	pinMode(Humidifier, OUTPUT);
	digitalWrite(Humidifier, HIGH);

	//=== Sprinklers ================================== Relay 5
	pinMode(Sprinklers, OUTPUT);
	digitalWrite(Sprinklers, HIGH);

	//=== Soil Heater ================================= Relay 6
	pinMode(SoilHeater, OUTPUT);
	digitalWrite(SoilHeater, HIGH);

	//=== UV Lights =================================== Relay 7
	pinMode(UVLights, OUTPUT);
	digitalWrite(UVLights, HIGH);

	//=== Empty ======================================= Relay 8
	//pinMode(Empty, OUTPUT);
	//digitalWrite(Empty, HIGH);


	// =================================================GUI Setup======================================================================================================================================================


	pinMode(13, OUTPUT);
	tft.reset();


	// ====================================================== Reset the TFT Display ========================================================


	tft.begin(0x9341);                          // The address of your Display
	tft.setRotation(LCDROTATION);               // Need for the Mega, please changed for your choice or rotation initial
	tft.fillScreen(BLACK);

	// =====================================================================================================================================

	//=============Temp & Humid Moduel Formula=========================================================================================================================================================================
	// read with raw sample data.
	byte temperature = 0;
	byte humidity = 0;
	byte data[40] = { 0 };
	if (dht11.read(pinDHT11, &temperature, &humidity, data))


		//============= Serial Display (Testing) ============================================================================================================================================================================

		//======== Air Temp and Humid Display ========================

		Serial.print("Air Temperature: ");
	Serial.print((int)temperature); Serial.print(" *C, ");
	Serial.print("Air Humidity: ");
	Serial.print((int)humidity); Serial.println(" %");
	//delay(1000);

	//======== Soil Temp Display ================================= 

	Soiltemp.requestTemperatures(); // Send the command to get temperature readings 
	Serial.print("Soil Temp: ");
	Serial.print(Soiltemp.getTempCByIndex(0));
	//delay(1000);

	//========= Soil Moisture Display ============================

	SoilmoistsensorValue = analogRead(Soilmoistsensor);
	Serial.print(" Soil Moisture: ");
	Serial.println(SoilmoistsensorValue);
	//delay(1000);

	//======== Light Intensity ================================= (Not in use)

	LightSensorValue = analogRead(LightSensor); // read the value from the sensor
	Serial.println(LightSensorValue); // Display Value on Debugger


	//========================================================================================== GUI =================================================================================


	/*  ----------------------- (Line)  */
	tft.setTextSize(4.1);
	tft.setTextColor(WHITE);
	tft.setCursor(0, 55);
	tft.print("--------------------");


	/*  Temperature  */
	tft.setTextSize(3);
	tft.setTextColor(WHITE);
	tft.setCursor(35, 80);
	tft.print("Air Temperature: ");
	tft.setTextColor(YELLOW);
	tft.print((int)temperature); tft.print(" C");
	tft.setTextSize(1);
	tft.print("o");


	/*  Humidity  */
	tft.setTextSize(3);
	tft.setCursor(35, 105);
	tft.setTextColor(WHITE);
	tft.print("Air Humidity: ");
	tft.setTextColor(YELLOW);
	tft.print((int)humidity); tft.print(" %");



	/*  Soil Moisture  */
	tft.setTextSize(3);
	tft.setCursor(35, 130);
	tft.setTextColor(WHITE);
	tft.print("Soil Moisture: ");


	/* Soil Temperature  */
	tft.setTextSize(3);
	tft.setTextColor(WHITE);
	tft.setCursor(35, 155);
	tft.print("Soil Temperature: ");
	tft.setTextColor(YELLOW);
	tft.print((int)Soiltemp.getTempCByIndex(0)); tft.print(" C");
	tft.setTextSize(1);
	tft.print("o");


	//===================================================================== Soil Moisture Icon on =====================================================================


	if (SoilmoistsensorValue >= 300) // Dry on (Default = 400)
	{
		tft.setTextSize(3);
		tft.setCursor(295, 132);
		tft.setTextColor(RED);
		tft.print("Dry");
	}

	else  // Dry off 
	{
		tft.setCursor(295, 132);
		tft.print(" ");
	}

	//========================================================================

	if (SoilmoistsensorValue < 300) // Wet on (Default = 400)
	{
		tft.setTextSize(3);
		tft.setCursor(296, 132);
		tft.setTextColor(BLUE);
		tft.print("Wet");
	}

	else  // Wet off 
	{
		tft.setCursor(296, 132);
		tft.print(" ");
	}


	//======================== Relay Control (AI) ==========================================================================================================================

	//========================= HUMIDIFER ================================================================================

	if (humidity <= 85) // Change the value of minimum humidity depending on required parameters (default <= 50%)
	{
		digitalWrite(Humidifier, LOW); // Turns Humidifier Relay on
		tft.setTextSize(2);
		tft.setCursor(35, 230);
		tft.setTextColor(RED);
		tft.print("Humidifier Is Live.....");
	}

	if (humidity >= 99) // Change the value of maximum humidity depending on required parameters (default >= 55%)
	{
		digitalWrite(Humidifier, HIGH); // Turns Humidifer Relay off
		tft.setCursor(35, 230);
		tft.print(" ");
	}

	//========================= SPRINKLERS ================================================================================

	if (SoilmoistsensorValue >= 300)  // Change the value of minimum soil moisture depending on required parameters (default >= 400)
	{
		digitalWrite(Sprinklers, LOW); // Turns Sprinklers Relay on
		digitalWrite(Humidifier, HIGH); // Turns Humidifer Relay off (if humidifier on while spriklers turn on, then turn humidifer off)
		tft.setTextSize(2);
		tft.setCursor(35, 210);
		tft.setTextColor(BLUE);
		tft.print("Sprinklers Are Live.....");
	}

	if (SoilmoistsensorValue <= 299) // Change the value of maximum soil moisture depending on required parameters (default < 400)
	{
		digitalWrite(Sprinklers, HIGH); // Turns Sprinklers Relay off
		tft.setCursor(35, 210);
		tft.print(" ");
	}

	//======================= COOLING FANS (Intake & Exhaust) ============================================================

	if (temperature >= 30) // Change the value of maximum temperature (C) depending on required parameters (default >= 25c)
	{
		digitalWrite(CoolingingFans_Intake, LOW); // Turns Intake Cooling Fans Relay on
		digitalWrite(CoolingingFans_Exhaust, LOW); // Turns Intake Cooling Fans Relay on
		tft.setTextSize(2);
		tft.setCursor(35, 250);
		tft.setTextColor(BLUE);
		tft.print("Fans Are Live.....");
	}

	if (temperature <= 18)   // Change the value of minimum temperature (C) depending on required parameters (default < 24c)
	{
		digitalWrite(CoolingingFans_Intake, HIGH); // Turns Intake Cooling Fans Relay off
		digitalWrite(CoolingingFans_Exhaust, HIGH); // Turns Intake Cooling Fans Relay off
		tft.setCursor(35, 250);
		tft.print(" ");
	}

	//=========================== HEATER FANS ===========================================================================

	if (temperature <= 17) // Change the value of minimum temperature (C) depending on required parameters (default <= 23c)
	{
		digitalWrite(HeatingFan, LOW); // Turns Heater Fans Relay on
		tft.setTextSize(2);
		tft.setCursor(35, 270);
		tft.setTextColor(RED);
		tft.print("Air Heaters Are Live.....");
	}

	if (temperature >= 25)   // Change the value of maximum temperature (C) depending on required parameters (default > 25c)
	{
		digitalWrite(HeatingFan, HIGH); // Turns Heater Fans Relay off
		tft.setCursor(35, 270);
		tft.print(" ");
	}

	//========================= UV Lights ================================================================================

	if (LightSensorValue <= 700) // Change the value of maximum Lighting exposure depending on required parameters (default = )
	{
		digitalWrite(UVLights, LOW); // Turns UV Lights Relay on
	}

	if (LightSensorValue > 700) // Change the value of maximum Lighting exposure depending on required parameters (default = )
	{
		digitalWrite(UVLights, HIGH); // Turns UV Lights Relay off
	}

	//========================= Soil Heater ================================================================================

	if ((Soiltemp.getTempCByIndex(0)) <= 17) // Change the value of maximum Soil Temp depending on required parameters (default = 23c )
	{
		digitalWrite(SoilHeater, LOW); // Turns Soil Heater Relay on
		tft.setTextSize(2);
		tft.setCursor(35, 190);
		tft.setTextColor(RED);
		tft.print("Soil Heater is Live.....");
	}

	if ((Soiltemp.getTempCByIndex(0)) >= 25) // Change the value of maximum Soil Temp depending on required parameters (default = 24c )
	{
		digitalWrite(SoilHeater, HIGH); // Turns Soil Heater Relay off
		tft.setCursor(35, 190);
		tft.print(" ");
	}


	//=================================================================================================================================================================


	//============== Title ================

	tft.setTextSize(4);
	tft.setCursor(85, 20);
	tft.setTextColor(DarkGREEN);
	tft.print("Orchid Habitat");

	//======== Software Version ===========

	tft.setTextSize(2);
	tft.setCursor(330, 300);
	tft.setTextColor(WHITE);
	tft.print(FerniOS_Version);

	//=====================================

	delay(60000);
	tft.fillRect(20, 55, 540, 450, BLACK);
	Orchid();

}








