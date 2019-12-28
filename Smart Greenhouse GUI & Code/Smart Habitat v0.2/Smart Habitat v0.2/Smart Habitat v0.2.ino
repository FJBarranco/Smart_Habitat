//Artificial Intel Formula For (Testing)
//Created By Fernando
String FerniOS_Version = "Ferni0S v0.4";

//=================================================  Header ============================================================================================================


#include <SimpleDHT.h> // Air Temp & Humid
#include <OneWire.h>  // Soil Temp
#include <DallasTemperature.h> // Soil Temp

//=====================Sensors====================================


int pinDHT11 = 53; // Temp. & Humid. Sensor pin 53
#define ONE_WIRE_BUS 51 // Soil Temp Sensor pin 51
int Soilmoistsensor = A8; // Soil Moisture Analog A8


//=====================Relay Control=============================


int HeatingFan = 44; // Heating Fan Intake Relay 1
int CoolingingFans_Intake = 46; // Cooling Fans Intake Relay 2
int CoolingingFans_Exhaust = 48; // Cooling Fans Exhaust/Dehumidifer Relay 3
int Humidifier = 50; // Humidifier Relay 4
int Sprinklers = 52; // Sprinklers Relay 5
int SoilHeater = 42; // Soil Heater Relay 6
//int UVLights = ; // UV Lights Relay 7
//int Empty = ; //  Relay 8


//=====================Data Pin/Analog Variables=============================


volatile byte relayState = LOW; // Relays
SimpleDHT11 dht11; // Air Temp & Humid
OneWire oneWire(ONE_WIRE_BUS); // Soil Temp
DallasTemperature Soiltemp(&oneWire);// Soil Temp
int SoilmoistsensorValue = 0; // Soil Moisture Sensor


//=============================================== GUI ======================================================================================================================================


//============== Libraries and variables of the OS ==========================


// *** SPFD5408 change -- Begin
#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>
// *** SPFD5408 change -- End

#include <EEPROM.h>                   //  To save button status on EEPROM

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#define LCDROTATION    3

/*  Touch  */

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin


#define TS_MINX 150 //  150
#define TS_MINY 120 //  120
#define TS_MAXX 920 //  920
#define TS_MAXY 940 //  940

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define MINPRESSURE 10
#define MAXPRESSURE 1000

/*  End Touch  */

/*  Colors - Assign human-readable names to some common 16-bit color values:
	16bit color picker: https://ee-programming-notepad.blogspot.co.uk/2016/10/16-bit-color-generator-picker.html
	HTML colors: http://htmlcolorcodes.com/                                                                    */

#define BLACK           0x0000
#define WHITE           0xFFFF
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x2685
#define CYAN            0x07FF
#define LIME            0x5FE0
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define TURQUOISE       0x0F1B
#define ORANGE          0xFBA0
#define PINK            0xF813
#define SKY             0x667F        // nice light blue
#define GREY            0xE73C
#define DarkTURQUOISE   0x3491
#define DarkGREY        0x39C7
#define DarkRED         0x8986
#define DarkGREEN       0x3446
#define DarkMAGENTA     0x612F
#define DarkBLUE        0x298B
#define DarkYELLOW      0x83E5
#define DarkORANGE      0xA347
#define DarkPINK        0xA1EF
#define GOLD            0xF3FF00      //  nice yellow
#define SALMON          0xFB2C        //  nice red
	
	//==================== Initialize TFT Display =========================
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


//==================================================Relay Setup========================================================================================================================================================


void setup()
{
	{
		Serial.begin(9600);
	}

	Soiltemp.begin(); // Soil Temp Sensor

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
	/*pinMode(UVLights, OUTPUT);
	digitalWrite(UVLights, HIGH);*/

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
}

void loop() {
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
 


	
	//========================================================================================== GUI =================================================================================

	 //=========================== Function Icons on ===================================

		if (SoilmoistsensorValue >= 400) // Sprinklers on (Default >= 400)
		{
			tft.setTextSize(2);
			tft.setCursor(35, 210);
			tft.setTextColor(BLUE);
			tft.print("Sprinklers Are Live.....");
		}

		else // Sprinklers off 
		{
			tft.setCursor(35, 210);
			tft.print(" ");
		}

     //===================================================================================

		if (humidity <= 50) // Humidifier on (Default <= 50%)
		{
			tft.setTextSize(2);
			tft.setCursor(35, 230);
			tft.setTextColor(RED);
			tft.print("Humidifier Is Live.....");
		}

		else // Humidifier off 
		{
			tft.setCursor(35, 230);
			tft.print(" ");
		}

	//===================================================================================

		if (temperature <= 23) // Heaters on (Default <= 23C)
		{
			tft.setTextSize(2);
			tft.setCursor(35, 270);
			tft.setTextColor(RED);
			tft.print("Air Heaters Are Live.....");
		}


		else // Heaters off 
		{
			tft.setCursor(35, 270);
			tft.print(" ");
		}

	//===================================================================================

		if (temperature >= 25) // Fans on (Default >= 25C)
		{
			tft.setTextSize(2);
			tft.setCursor(35, 250);
			tft.setTextColor(BLUE);
			tft.print("Fans Are Live.....");
		}

		else // Fans off 
		{
			tft.setCursor(35, 250);
			tft.print(" ");
		}
		
	//===================================================================================

		if ((Soiltemp.getTempCByIndex(0)) <= 22) // Soil Heaters on (Default <= 22C)
		{
			tft.setTextSize(2);
			tft.setCursor(35, 190);
			tft.setTextColor(RED);
			tft.print("Soil Heater is Live.....");
		}


		else // Soil Heaters off 
		{
			tft.setCursor(35, 190);
			tft.print(" ");
		}
	
	//=================================================================================================================================================================


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


	if (SoilmoistsensorValue >= 400) // Dry on (Default = 400)
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

	if (SoilmoistsensorValue < 400) // Wet on (Default = 400)
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

	if (humidity <= 50) // Change the value of minimum humidity depending on required parameters (default <= 50%)
	{
		digitalWrite(Humidifier, LOW); // Turns Humidifier Relay on
	}

	if (humidity >= 55) // Change the value of maximum humidity depending on required parameters (default >= 55%)
	{
		digitalWrite(Humidifier, HIGH); // Turns Humidifer Relay off
	}

	//========================= SPRINKLERS ================================================================================

	if (SoilmoistsensorValue >= 400)  // Change the value of minimum soil moisture depending on required parameters (default >= 400)
	{
		digitalWrite(Sprinklers, LOW); // Turns Sprinklers Relay on
		digitalWrite(Humidifier, HIGH); // Turns Humidifer Relay off (if humidifier on while spriklers turn on, then turn humidifer off)
	}

	if (SoilmoistsensorValue <= 399) // Change the value of maximum soil moisture depending on required parameters (default < 400)
	{
		digitalWrite(Sprinklers, HIGH); // Turns Sprinklers Relay off
	}

	//======================= COOLING FANS (Intake & Exhaust) ============================================================

	if (temperature >= 25) // Change the value of maximum temperature (C) depending on required parameters (default >= 25c)
	{
		digitalWrite(CoolingingFans_Intake, LOW); // Turns Intake Cooling Fans Relay on
		digitalWrite(CoolingingFans_Exhaust, LOW); // Turns Intake Cooling Fans Relay on
	}

	if (temperature <= 24)   // Change the value of minimum temperature (C) depending on required parameters (default < 24c)
	{
		digitalWrite(CoolingingFans_Intake, HIGH); // Turns Intake Cooling Fans Relay off
		digitalWrite(CoolingingFans_Exhaust, HIGH); // Turns Intake Cooling Fans Relay off
	}

	//=========================== HEATER FANS ===========================================================================

	if (temperature <= 23) // Change the value of minimum temperature (C) depending on required parameters (default <= 23c)
	{
		digitalWrite(HeatingFan, LOW); // Turns Intake Cooling Fans Relay on
	}

	if (temperature >= 25)   // Change the value of maximum temperature (C) depending on required parameters (default > 25c)
	{
		digitalWrite(HeatingFan, HIGH); // Turns Intake Cooling Fans Relay off
	}

	//========================= UV Lights ================================================================================

	//if ( ) // Change the value of maximum Lighting exposure depending on required parameters (default = )
	//{
	//	digitalWrite( , LOW); // Turns UV Lights Relay on
	//}

	//if ( ) // Change the value of maximum Lighting exposure depending on required parameters (default = )
	//{
	//	digitalWrite( , HIGH); // Turns UV Lights Relay off
	//}

	//========================= Soil Heater ================================================================================

	if ((Soiltemp.getTempCByIndex(0)) <= 23) // Change the value of maximum Soil Temp depending on required parameters (default = 23c )
	{
		digitalWrite(SoilHeater, LOW); // Turns Soil Heater Relay on
	}

	if ((Soiltemp.getTempCByIndex(0)) >= 24) // Change the value of maximum Soil Temp depending on required parameters (default = 24c )
	{
		digitalWrite(SoilHeater, HIGH); // Turns Soil Heater Relay off
	}


	 //=================================================================================================================================================================


	 //============== Title ================

		tft.setTextSize(4);
		tft.setCursor(90, 20);
		tft.setTextColor(DarkGREEN);
		tft.print("Smart Habitat");

	 //======== Software Version ===========

		tft.setTextSize(2);
		tft.setCursor(330, 300);
		tft.setTextColor(WHITE);
		tft.print(FerniOS_Version);

     //=====================================

		//Refresh
		delay(10000);
		ClearPage();

	}

	// =============================== Clear Page Function ====================================

void  ClearPage() {                       //  Clear menus and Status bar
//  Serial.println("Clear Page");
	tft.fillRect(20, 55, 540, 450, BLACK);                        //  Clear Menu
}