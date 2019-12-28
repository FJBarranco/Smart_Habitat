//=================================================  Header ============================================================================================================

#include <SimpleDHT.h> // Air Temp & Humid
#include <OneWire.h>  // Soil Temp
#include <DallasTemperature.h> // Soil Temp
//#include <Stepper.h> // Stepper Motor (Not Used Yet)

//=====================Sensors====================================

#define ONE_WIRE_BUS 25 // Soil Temp Sensor pin 25
int pinDHT11 = 23; // Temp. & Humid. Sensor pin 23
int Soilmoistsensor = A15; // Soil Moisture Analog A15
int Voltagecheck = A14; // Voltage Checker Analog A14
int LightInt = 27; // Light Intensity Pin 27

//===================== Relay Control (Core) =============================

int HeatingFan = 38; // Heating Fan Intake Relay 8
int CoolingingFans_Intake = 40; // Cooling Fans Intake Relay 7
int CoolingingFans_Exhaust = 42; // Cooling Fans Exhaust/Dehumidifer Relay 6
int Humidifier = 52; // Humidifier Relay 5
int Sprinklers = 50; // Sprinklers Relay 4
int SoilHeater = 48; // Soil Heater Relay 3
int UVLights = 46; // UV Lights Relay 2
//int Florescent Bulb  = 44; // Florescent Light Bulb Relay 1 (Planned For v1.5)*****

//===================== Sensor Fixed or Fail Overide Button  ============================= (NEW! v1.4)

//const int buttonPin = 37; // Digital Pin 37
//int buttonState = 0; // Button State Variable (On or Off)

//===================== Relay Control (System controller) ============================= 

int TwelveVAlarm = 31; // Activates Alarm when voltage is under 12V Relay 1 (NEW! v1.4)
//int SensorFailAlarm = 29; // Alarm For sensor Fail Relay 2 (Planned For v1.5)*****


//============================ Back Up Power =========================================

//int BackUpPower = 33; // Switches To Back Up Power When under 5V Relay 2 (Planned For v1.5)*****

//=====================Data Pin/Analog Variables=============================

volatile byte relayState = LOW; // Relays
SimpleDHT11 dht11; // Air Temp & Humid
OneWire oneWire(ONE_WIRE_BUS); // Soil Temp
DallasTemperature Soiltemp(&oneWire);// Soil Temp
int SoilmoistsensorValue = 0; // Soil Moisture Sensor
int Soil_Temp = (Soiltemp.getTempCByIndex(0)); // Simplified Int Value (Soil Temp)

////=====================Stepper Motor Control=================================(Not Used Yet)
//
//// Number of steps per internal motor revolution 
//const float STEPS_PER_REV = 32;
//
////  Amount of Gear Reduction
//const float GEAR_RED = 64;
//
//// Number of steps per geared output rotation
//const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;
//
//// Define Variables
//
//// Number of Steps Required
//int StepsRequired;
//
//// Create Instance of Stepper Class
//// Specify Pins used for motor coils
//// The pins used are 8,9,10,11 
//// Connected to ULN2003 Motor Driver In1, In2, In3, In4 
//// Pins entered in sequence 1-3-2-4 for proper step sequencing
//
//Stepper steppermotor(STEPS_PER_REV, 22, 26, 24, 28);

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

/*  Store Menu Variables  */
//String CurrentPage;
//String PrevPage;


