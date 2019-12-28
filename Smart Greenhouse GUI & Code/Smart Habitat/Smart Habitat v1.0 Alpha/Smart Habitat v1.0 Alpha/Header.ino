//=================================================  Header ============================================================================================================


#include <SimpleDHT.h> // Air Temp & Humid
#include <OneWire.h>  // Soil Temp
#include <DallasTemperature.h> // Soil Temp

//=====================Sensors====================================


int pinDHT11 = 51; // Temp. & Humid. Sensor pin 53  
#define ONE_WIRE_BUS 53 // Soil Temp Sensor pin 51
int Soilmoistsensor = A15; // Soil Moisture Analog A15
int LightSensor = A8; // Light Intensity
int LightSensorValue = A8; // Light Intensity Value (Buffer)

//=====================Relay Control=============================


int HeatingFan = 44; // Heating Fan Intake Relay 1
int CoolingingFans_Intake = 46; // Cooling Fans Intake Relay 2
int CoolingingFans_Exhaust = 48; // Cooling Fans Exhaust/Dehumidifer Relay 3
int Humidifier = 50; // Humidifier Relay 4
int Sprinklers = 52; // Sprinklers Relay 5
int SoilHeater = 42; // Soil Heater Relay 6
int UVLights = 40; // UV Lights Relay 7
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

/*  Store Menu Variables  */
String CurrentPage;
String PrevPage;


