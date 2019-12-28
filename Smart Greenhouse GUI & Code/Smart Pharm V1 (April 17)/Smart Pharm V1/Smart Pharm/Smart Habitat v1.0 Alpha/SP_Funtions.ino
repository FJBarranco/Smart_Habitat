

void DebugMode() // Developer ONLY! (Fernando)
{
	
	
		Serial.begin(9600); // Debugging Only
		

	//=============================================================== Debug Notes =============================================================
	//-UV Light Controller Not Working Correct
	//-Add Feature (Sensor Fail Detection and Text Message Alert)
	//-Add Feature (Battery Voltage Drop Detection and Text Message Alert) ------------------------**(Current)**
	//-Add Feature (Actuator Fail Detection and Text Message Alert)
	//========================================================================================================================================
		
	pinMode(13, OUTPUT);
	tft.reset();


	// ====================================================== Reset the TFT Display ==========================================================


	tft.begin(0x9341);                          // The address of your Display
	tft.setRotation(LCDROTATION);               // Need for the Mega, please changed for your choice or rotation initial
	tft.fillScreen(BLACK);
	

	//============================================================== Fail Overide or Fix Button =================================================================

	//pinMode(buttonPin, INPUT); //Initialize
	//buttonState = digitalRead(buttonPin); //Read Pin

	//============================================================== Sensors =================================================================
	//============================================ Soil Temp ================================================================================= 

	Soiltemp.requestTemperatures(); // Send the command to get temperature readings 
	Soiltemp.begin(); // Soil Temp Sensor

	//====================================== Temp & Humid Moduel =============================================================================
	
	byte temperature = 0;
	byte humidity = 0;
	byte data[40] = { 0 };
	if (dht11.read(pinDHT11, &temperature, &humidity, data))

	//==============Voltage Check=============================================================================================================
	
	int voltvalue = 0;
	float vout = 0.0;
	float vin = 0.0;
	float R1 = 30000.0;
	float R2 = 7500.0;
	pinMode(Voltagecheck, INPUT);
	int voltvalue = analogRead(Voltagecheck);
	vout = (voltvalue * 5.0) / 1024.0;
	vin = vout / (R2 / (R1 + R2));
	float vinreg = vin;

	//======== Light Intensity ================================= 

	// 1 = No Sun Light 
	// 0 = Sun Light    
	//int LightValue = digitalRead(LightInt);

	//=========================================================

	//============= Serial Display (Testing) ==================================================================================================

	//======== Air Temp and Humid Display ========================

	Serial.print("Air Temperature: ");
	Serial.print((int)temperature); Serial.print(" *C, ");
	Serial.print("Air Humidity: ");
	Serial.print((int)humidity); Serial.println(" %");

	//======== Soil Temp Display ================================= 

	Serial.print("Soil Temp: ");
	Serial.print(Soiltemp.getTempCByIndex(0));

	//========= Soil Moisture Display ============================

	SoilmoistsensorValue = analogRead(Soilmoistsensor);
	Serial.print(" Soil Moisture: ");
	Serial.println(SoilmoistsensorValue);

	//======== Light Intensity ================================= (Needs Revision)

	/*Serial.print("Light read: ");
	Serial.println(LightValue);
*/
	//====================== Voltage Checker ===================

	Serial.print("Main Battery Voltage");
	Serial.println(vinreg, 2);

	//=================================================================== Relay Setup ==========================================================


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

	//=== UV Lights =================================== Relay 7 (Needs Revising)
	pinMode(UVLights, OUTPUT);
	digitalWrite(UVLights, HIGH);

	//=== Empty ======================================= Relay 8
	/*pinMode(Empty, OUTPUT);
	digitalWrite(Empty, HIGH);*/

	//=================================================================== GUI ================================================================


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


	/*  Voltage Checker  */
	tft.setTextSize(2);
	tft.setCursor(405, 10);
	tft.setTextColor(WHITE);
	tft.print(vinreg);
	tft.print("v");
	

	//===================================================================== Soil Moisture Icon on =====================================================================


	if (SoilmoistsensorValue >= 300) // Dry on (Default = 300)
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

	if (SoilmoistsensorValue < 300) // Wet on (Default = 300)
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

			//======================== Relay Control (Core) ==========================================================================================================================

	
			//========================= UV Lights ================================================================================ (Needs Revesion)

	        // if (LightValue = 0) // Change the value of maximum Lighting exposure depending on required parameters (default = 0 )
			//{
			//	digitalWrite(UVLights, HIGH); // Turns UV Lights Relay off
			//}

			//if (LightValue = 1) // Change the value of maximum Lighting exposure depending on required parameters (default = 1)
			//{
			//	digitalWrite(UVLights, LOW); // Turns UV Lights Relay on
			//}


			//========================= HUMIDIFER ================================================================================

			if (humidity <= 50) // Change the value of minimum humidity depending on required parameters (default <= 50%)
			{
				digitalWrite(Humidifier, LOW); // Turns Humidifier Relay on
				tft.setTextSize(2);
				tft.setCursor(35, 230);
				tft.setTextColor(RED);
				tft.print("Humidifier Is Live.....");
			}

			if (humidity >= 55) // Change the value of maximum humidity depending on required parameters (default >= 55%)
			{
				digitalWrite(Humidifier, HIGH); // Turns Humidifer Relay off
				tft.setCursor(35, 230);
				tft.print(" ");
			}

			//========================= SPRINKLERS ================================================================================

			if (SoilmoistsensorValue >= 300)  // Change the value of minimum soil moisture depending on required parameters (default >= 300)
			{
				digitalWrite(Sprinklers, LOW); // Turns Sprinklers Relay on
				digitalWrite(Humidifier, HIGH); // Turns Humidifer Relay off (Wait for Sprinkler to turn off to turn Humidifier on)
				tft.setTextSize(2);
				tft.setCursor(35, 210);
				tft.setTextColor(BLUE);
				tft.print("Sprinklers Are Live.....");
			}

			if (SoilmoistsensorValue < 300) // Change the value of maximum soil moisture depending on required parameters (default < 300)
			{
				digitalWrite(Sprinklers, HIGH); // Turns Sprinklers Relay off
				tft.setCursor(35, 210);
				tft.print(" ");
			}

			//======================= COOLING FANS (Intake & Exhaust) ============================================================

			if (temperature >= 25) // Change the value of maximum temperature (C) depending on required parameters (default >= 25c)
			{
				digitalWrite(CoolingingFans_Intake, LOW); // Turns Intake Cooling Fans Relay on
				digitalWrite(CoolingingFans_Exhaust, LOW); // Turns Intake Cooling Fans Relay on
				tft.setTextSize(2);
				tft.setCursor(35, 250);
				tft.setTextColor(BLUE);
				tft.print("Fans Are Live.....");
			}

			if (temperature <= 24)   // Change the value of minimum temperature (C) depending on required parameters (default <= 24c)
			{
				digitalWrite(CoolingingFans_Intake, HIGH); // Turns Intake Cooling Fans Relay off
				digitalWrite(CoolingingFans_Exhaust, HIGH); // Turns Intake Cooling Fans Relay off
				tft.setCursor(35, 250);
				tft.print(" ");
			}

			//=========================== HEATER FANS ===========================================================================

			if (temperature <= 23) // Change the value of minimum temperature (C) depending on required parameters (default <= 23c)
			{
				digitalWrite(HeatingFan, LOW); // Turns Heater Fans Relay on
				tft.setTextSize(2);
				tft.setCursor(35, 270);
				tft.setTextColor(RED);
				tft.print("Air Heaters Are Live.....");
			}

			if (temperature >= 25)   // Change the value of maximum temperature (C) depending on required parameters (default >= 25c)
			{
				digitalWrite(HeatingFan, HIGH); // Turns Heater Fans Relay off
				tft.setCursor(35, 270);
				tft.print(" ");
			}

			//========================= Soil Heater ================================================================================

			if ((Soiltemp.getTempCByIndex(0)) <= 23) // Change the value of maximum Soil Temp depending on required parameters (default <= 23c )
			{
				digitalWrite(SoilHeater, LOW); // Turns Soil Heater Relay on
				tft.setTextSize(2);
				tft.setCursor(35, 190);
				tft.setTextColor(RED);
				tft.print("Soil Heater is Live.....");
			}

			if ((Soiltemp.getTempCByIndex(0)) >= 25) // Change the value of maximum Soil Temp depending on required parameters (default >= 25c )
			{
				digitalWrite(SoilHeater, HIGH); // Turns Soil Heater Relay off
				tft.setCursor(35, 190);
				tft.print(" ");
			}

			////=========================== Sensor Fail Detector ===========================================================================

			////=========================================== Sensor Fail Fix Switch or Bypass ===============================================

			//if (buttonState == HIGH) {
			//	// turn Alarm Off:
			//	digitalWrite(SensorFailAlarm, HIGH);

			////========================= Light Intensity (Fail Point) ================================================================================ (Needs Revesion)

			//// if (LightValue ) //  (default =  )
			////{
			////	digitalWrite(SensorFailAlarm, LOW); // 
			////}

			////========================= Humidity Sensor (Fail Point) ================================================================================

			//if (humidity = 0) // Fail Value
			//{
			//	digitalWrite(SensorFailAlarm, LOW); // 
			//}

			////========================= Moisture Sensor (Fail Point) ================================================================================

			//if (SoilmoistsensorValue = 0) // Fail Value
			//{
			//	digitalWrite(SensorFailAlarm, LOW); // 
			//}

			////======================= Temperature Sensor (Fail Point) ============================================================

			//if (temperature = 0) // Fail Value
			//{
			//	digitalWrite(SensorFailAlarm, LOW); // 
			//}

			////========================= Soil Temperature Sensor (Fail Point) ================================================================================
		
			//if (Soil_Temp = -127 ) // Fail Value
			//{
			//	digitalWrite(SensorFailAlarm, LOW); // 
			//}

			//======================== Relay Control (System Controller) ==========================================================================================================

			//=========================== 12V Alarm ===========================================================================

			if (vinreg < 12 ) // Change the value of Minimum Voltage, depending on required parameters (default < 12)
			{
				digitalWrite(TwelveVAlarm, LOW); // Turns Alarm and Warning Light On
			}

			else   // When Value of Voltage is Correct or Higher depending on required parameters (Correct Value is => 12)
			{
				digitalWrite(TwelveVAlarm, HIGH); // Turns Alarm and Warning Light Off
			}

			//=========================== Back Up Battery ==========================================================================================================================

			if (vinreg < 5) // Change the value of Minimum Voltage, depending on required parameters (default < 5)
			{
				digitalWrite(BackUpPower, LOW); // Switches to BackUp Power Bank 
			}

			else   // When Value of Voltage is Correct or Higher depending on required parameters (Correct Value is => 5)
			{
				digitalWrite(BackUpPower, HIGH); // Switches To Regular Battery
			}


			//=====================================================================================================================================================================


			//============== Title ================

			tft.setTextSize(4);
			tft.setCursor(80, 20);
			tft.setTextColor(DarkGREEN);
			tft.print("Developer Mode");

			//======== Software Version ===========

			tft.setTextSize(2);
			tft.setCursor(330, 300);
			tft.setTextColor(WHITE);
			tft.print(FerniOS_Version);

			//===================================== Delay, and Reload

			
			delay(30000); //Delay 30 sec
			tft.fillRect(20, 55, 540, 450, BLACK); //Reset Screen
			DebugMode(); //Return Screen

		}



		void Orchid() 
		{


			

			pinMode(13, OUTPUT);
			tft.reset();


			// ====================================================== Reset the TFT Display ==========================================================


			tft.begin(0x9341);                          // The address of your Display
			tft.setRotation(LCDROTATION);               // Need for the Mega, please changed for your choice or rotation initial
			tft.fillScreen(BLACK);


			//============================================================== Sensors =================================================================

			//============================================ Soil Temp ================================================================================= 

			Soiltemp.requestTemperatures(); // Send the command to get temperature readings 
			Soiltemp.begin(); // Soil Temp Sensor

			//====================================== Temp & Humid Moduel =============================================================================

			byte temperature = 0;
			byte humidity = 0;
			byte data[40] = { 0 };
			if (dht11.read(pinDHT11, &temperature, &humidity, data))

				//==============Voltage Check=============================================================================================================

			int voltvalue = 0;
			float vout = 0.0;
			float vin = 0.0;
			float R1 = 30000.0;
			float R2 = 7500.0;
			pinMode(Voltagecheck, INPUT);
			int voltvalue = analogRead(Voltagecheck);
			vout = (voltvalue * 5.0) / 1024.0;
			vin = vout / (R2 / (R1 + R2));
			float vinreg = vin;

			//======== Light Intensity ================================= 

			// 1 = No Sun Light
			// 0 = Sun Light
			int LightValue = digitalRead(LightInt);
			int Sunlight = LightValue;

			//=================================================================== Relay Setup ==========================================================


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

			//=== UV Lights =================================== Relay 7 (Needs Revising)
			pinMode(UVLights, OUTPUT);
			digitalWrite(UVLights, HIGH);

			//=================================================================== GUI ================================================================


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


			/*  Voltage Checker  */
			tft.setTextSize(2);
			tft.setCursor(405, 10);
			tft.setTextColor(WHITE);
			tft.print(vinreg);
			tft.print("v");


			//===================================================================== Soil Moisture Icon on =====================================================================


			if (SoilmoistsensorValue >= 300) // Dry on (Default = 300)
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

			if (SoilmoistsensorValue < 300) // Wet on (Default = 300)
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

			//========================= UV Lights ================================================================================ (Needs Revesion)

			// if (LightValue = 0) // Change the value of maximum Lighting exposure depending on required parameters (default = 0 )
			//{
			//	digitalWrite(UVLights, HIGH); // Turns UV Lights Relay off
			//}

			//if (LightValue = 1) // Change the value of maximum Lighting exposure depending on required parameters (default = 1)
			//{
			//	digitalWrite(UVLights, LOW); // Turns UV Lights Relay on
			//}

			//========================= HUMIDIFER ================================================================================

			if (humidity <= 85) // Change the value of minimum humidity depending on required parameters (default <= 85%)
			{
				digitalWrite(Humidifier, LOW); // Turns Humidifier Relay on
				tft.setTextSize(2);
				tft.setCursor(35, 230);
				tft.setTextColor(RED);
				tft.print("Humidifier Is Live.....");
			}

			if (humidity >= 99) // Change the value of maximum humidity depending on required parameters (default >= 99%)
			{
				digitalWrite(Humidifier, HIGH); // Turns Humidifer Relay off
				tft.setCursor(35, 230);
				tft.print(" ");
			}

			//========================= SPRINKLERS ================================================================================

			if (SoilmoistsensorValue >= 300)  // Change the value of minimum soil moisture depending on required parameters (default >= 300)
			{
				digitalWrite(Sprinklers, LOW); // Turns Sprinklers Relay on
				digitalWrite(Humidifier, HIGH); // Turns Humidifer Relay off  (Wait for Sprinkler to turn off to turn Humidifier on)
				tft.setTextSize(2);
				tft.setCursor(35, 210);
				tft.setTextColor(BLUE);
				tft.print("Sprinklers Are Live.....");
			}

			if (SoilmoistsensorValue < 300) // Change the value of maximum soil moisture depending on required parameters (default < 300)
			{
				digitalWrite(Sprinklers, HIGH); // Turns Sprinklers Relay off
				tft.setCursor(35, 210);
				tft.print(" ");
			}

			//======================= COOLING FANS (Intake & Exhaust) ============================================================

			if (temperature >= 30) // Change the value of maximum temperature (C) depending on required parameters (default >= 30c)
			{
				digitalWrite(CoolingingFans_Intake, LOW); // Turns Intake Cooling Fans Relay on
				digitalWrite(CoolingingFans_Exhaust, LOW); // Turns Intake Cooling Fans Relay on
				tft.setTextSize(2);
				tft.setCursor(35, 250);
				tft.setTextColor(BLUE);
				tft.print("Fans Are Live.....");
			}

			if (temperature <= 18)   // Change the value of minimum temperature (C) depending on required parameters (default < 18c)
			{
				digitalWrite(CoolingingFans_Intake, HIGH); // Turns Intake Cooling Fans Relay off
				digitalWrite(CoolingingFans_Exhaust, HIGH); // Turns Intake Cooling Fans Relay off
				tft.setCursor(35, 250);
				tft.print(" ");
			}

			//=========================== HEATER FANS ===========================================================================

			if (temperature <= 17) // Change the value of minimum temperature (C) depending on required parameters (default <= 17c)
			{
				digitalWrite(HeatingFan, LOW); // Turns Heater Fans Relay on
				tft.setTextSize(2);
				tft.setCursor(35, 270);
				tft.setTextColor(RED);
				tft.print("Air Heaters Are Live.....");
			}

			if (temperature >= 25)   // Change the value of maximum temperature (C) depending on required parameters (default >= 25c)
			{
				digitalWrite(HeatingFan, HIGH); // Turns Heater Fans Relay off
				tft.setCursor(35, 270);
				tft.print(" ");
			}


			//========================= Soil Heater ================================================================================

			if ((Soiltemp.getTempCByIndex(0)) <= 17) // Change the value of maximum Soil Temp depending on required parameters (default <= 17c )
			{
				digitalWrite(SoilHeater, LOW); // Turns Soil Heater Relay on
				tft.setTextSize(2);
				tft.setCursor(35, 190);
				tft.setTextColor(RED);
				tft.print("Soil Heater is Live.....");
			}

			if ((Soiltemp.getTempCByIndex(0)) >= 25) // Change the value of maximum Soil Temp depending on required parameters (default >= 25c )
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


			delay(60000); //Delay
			tft.fillRect(20, 55, 540, 450, BLACK); //Reset Screen
			Orchid(); //Return Screen

		}




		void ChickenEgg()
		{


			

			// Notes On Chicken Egg Condtions Research
			//==================================================================
			// Air Temp (max 105f min 100f ) 
			// Soil Temp (max 100f min 95f ) 
			// Air Moisture ( min 75% max 85% ) 
			// Soil Moisture ( Dry ) 
			// Lighting (UV Light needs to be on during Night)
			// (Extra: Use Egg Turner Addon) 



			pinMode(13, OUTPUT);
			tft.reset();


			// ====================================================== Reset the TFT Display ==========================================================


			tft.begin(0x9341);                          // The address of your Display
			tft.setRotation(LCDROTATION);               // Need for the Mega, please changed for your choice or rotation initial
			tft.fillScreen(BLACK);


			//============================================================== Sensors =================================================================

			//============================================ Soil Temp ================================================================================= 

			Soiltemp.requestTemperatures(); // Send the command to get temperature readings 
			Soiltemp.begin(); // Soil Temp Sensor

			//====================================== Temp & Humid Moduel =============================================================================

			byte temperature = 0;
			byte humidity = 0;
			byte data[40] = { 0 };
			if (dht11.read(pinDHT11, &temperature, &humidity, data))

				//==============Voltage Check=============================================================================================================

				int voltvalue = 0;
			float vout = 0.0;
			float vin = 0.0;
			float R1 = 30000.0;
			float R2 = 7500.0;
			pinMode(Voltagecheck, INPUT);
			int voltvalue = analogRead(Voltagecheck);
			vout = (voltvalue * 5.0) / 1024.0;
			vin = vout / (R2 / (R1 + R2));
			float vinreg = vin;

			//======== Light Intensity ================================= 

			// 1 = No Sun Light
			// 0 = Sun Light
			int LightValue = digitalRead(LightInt);
			int Sunlight = LightValue;

			//=================================================================== Relay Setup ==========================================================


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

			//=== Soil Heater ================================= Relay 6
			pinMode(SoilHeater, OUTPUT);
			digitalWrite(SoilHeater, HIGH);

			//=== UV Lights =================================== Relay 7 (Needs Revising)
			pinMode(UVLights, OUTPUT);
			digitalWrite(UVLights, HIGH);


			//=================================================================== GUI ================================================================


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


			/* Soil Temperature  */
			tft.setTextSize(3);
			tft.setTextColor(WHITE);
			tft.setCursor(35, 155);
			tft.print("Soil Temperature: ");
			tft.setTextColor(YELLOW);
			tft.print((int)Soiltemp.getTempCByIndex(0)); tft.print(" C");
			tft.setTextSize(1);
			tft.print("o");


			/*  Voltage Checker  */
			tft.setTextSize(2);
			tft.setCursor(405, 10);
			tft.setTextColor(WHITE);
			tft.print(vinreg);
			tft.print("v");


			//======================== Relay Control (AI) ==========================================================================================================================

			//========================= UV Lights ================================================================================ (Needs Revesion)

			// if (LightValue = 0) // Change the value of maximum Lighting exposure depending on required parameters (default = 0 )
			//{
			//	digitalWrite(UVLights, HIGH); // Turns UV Lights Relay off
			//}

			//if (LightValue = 1) // Change the value of maximum Lighting exposure depending on required parameters (default = 1)
			//{
			//	digitalWrite(UVLights, LOW); // Turns UV Lights Relay on
			//}

			//========================= HUMIDIFER ================================================================================  RELAY 4

			if (humidity <= 75) // Change the value of minimum humidity depending on required parameters (default <= 75%)     
			{
				digitalWrite(Humidifier, LOW); // Turns Humidifier Relay on
				tft.setTextSize(2);
				tft.setCursor(35, 230);
				tft.setTextColor(RED);
				tft.print("Humidifier Is Live.....");
			}

			if (humidity >= 85) // Change the value of maximum humidity depending on required parameters (default >= 85%)     
			{
				digitalWrite(Humidifier, HIGH); // Turns Humidifer Relay off
				tft.setCursor(35, 230);
				tft.print(" ");
			}

			//======================= COOLING FANS (Intake & Exhaust) ============================================================  RELAY 2 & RELAY 3

			if (temperature >= 41) // Change the value of maximum temperature (C) depending on required parameters (default >= 41c)
			{
				digitalWrite(CoolingingFans_Intake, LOW); // Turns Intake Cooling Fans Relay on
				digitalWrite(CoolingingFans_Exhaust, LOW); // Turns Intake Cooling Fans Relay on
				tft.setTextSize(2);
				tft.setCursor(35, 250);
				tft.setTextColor(BLUE);
				tft.print("Fans Are Live.....");
			}

			if (temperature <= 40)   // Change the value of minimum temperature (C) depending on required parameters (default < 40c)  
			{
				digitalWrite(CoolingingFans_Intake, HIGH); // Turns Intake Cooling Fans Relay off
				digitalWrite(CoolingingFans_Exhaust, HIGH); // Turns Intake Cooling Fans Relay off
				tft.setCursor(35, 250);
				tft.print(" ");
			}

			//=========================== HEATER FANS ===========================================================================  RELAY 1

			if (temperature <= 35) // Change the value of minimum temperature (C) depending on required parameters (default <= 35c)
			{
				digitalWrite(HeatingFan, LOW); // Turns Heater Fans Relay on
				tft.setTextSize(2);
				tft.setCursor(35, 270);
				tft.setTextColor(RED);
				tft.print("Air Heaters Are Live.....");
			}

			if (temperature >= 40)   // Change the value of maximum temperature (C) depending on required parameters (default > 40c)
			{
				digitalWrite(HeatingFan, HIGH); // Turns Heater Fans Relay off
				tft.setCursor(35, 270);
				tft.print(" ");
			}

			//========================= Soil Heater ================================================================================  RELAY 6

			if ((Soiltemp.getTempCByIndex(0)) <= 35) // Change the value of maximum Soil Temp depending on required parameters (default <= 35c )
			{
				digitalWrite(SoilHeater, LOW); // Turns Soil Heater Relay on
				tft.setTextSize(2);
				tft.setCursor(35, 190);
				tft.setTextColor(RED);
				tft.print("Soil Heater is Live.....");
			}

			if ((Soiltemp.getTempCByIndex(0)) >= 40) // Change the value of maximum Soil Temp depending on required parameters (default >= 40c )
			{
				digitalWrite(SoilHeater, HIGH); // Turns Soil Heater Relay off
				tft.setCursor(35, 190);
				tft.print(" ");
			}


			//=================================================================================================================================================================


			//============== Title ================

			tft.setTextSize(4);
			tft.setCursor(83, 20);
			tft.setTextColor(DarkGREEN);
			tft.print("Chicken Egg");

			//======== Software Version ===========

			tft.setTextSize(2);
			tft.setCursor(330, 300);
			tft.setTextColor(WHITE);
			tft.print(FerniOS_Version);

			//=====================================

			delay(60000); //Delay
			tft.fillRect(20, 55, 540, 450, BLACK); //Reset Screen
			ChickenEgg(); //Return Screen
		}