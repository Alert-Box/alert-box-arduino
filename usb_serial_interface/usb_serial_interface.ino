/**
 * This program enables the arduino to listen to the serial port, and
 * responding to some commands. Depending on the recieved command, the
 * arduino will print something on screen, set the leds to a color, etc.
 */
 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//beware, the modified version of LiquidCrystal_I2C.h must be used.

#include <Adafruit_NeoPixel.h>//for the RGB LEDs, we use the Neopixel library from Adafruit.
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LEDS_PIN 6
#define LEDS_COUNT 3



LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS_COUNT, LEDS_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

const String lcdCommand="lcd01";
const String ledCommand="led01";
const char separator=':';
const int cmdLength=5; //soon to be deprecated

//lcd commands constants
const int colLength=2;
const int rowLength=2;

//led commands constants
const int ledIdLength=2;
const int colorLength=3;

/**
 * This function pareses the string passed as an argument and searches for known commands.
 * Depending on the read command it also searches for arguments. Once all data have
 * been parsed, the corresponding commands are launched.
 */
void parseCMD(String s)
{
  if(s!=NULL)
  {
    //print message : lcd01:rw:cl:message
    if(s.substring(0,cmdLength).compareTo(lcdCommand)==0)
    {
      Serial.println("match lcd01");
      int row=s.substring(cmdLength+1,cmdLength+1+rowLength).toInt();
      int col=s.substring(cmdLength+1+rowLength+1,cmdLength+1+rowLength+1+colLength).toInt();
      lcd.setCursor(col,row);
      
      lcd.print(s.substring(cmdLength+1+rowLength+1+colLength+1));
    }
    //delete line : lcd02:ln (ln= line number)
    else if(s.substring(0,cmdLength).compareTo(lcdCommand)==0)
    {
      Serial.println("match lcd02");
      int ln=s.substring(cmdLength+1,cmdLength+1+rowLength).toInt();
      lcd.setCursor(ln,0);
      
      lcd.print("                    ");
    }
    //clear all : lcd03
    else if(s.substring(0,cmdLength).compareTo("lcd03")==0)
    {
      Serial.println("match lcd03");
      lcd.clear();
    }
    //turn screen off : lcd04
    else if(s.substring(0,cmdLength).compareTo("lcd04")==0)
    {
      Serial.println("match lcd04");
      lcd.noBacklight();
    }
    //turn screen off : lcd05
    else if(s.substring(0,cmdLength).compareTo("lcd05")==0)
    {
      Serial.println("match lcd05");
      lcd.backlight();
    }
    else if(s.substring(0,cmdLength).compareTo(ledCommand)==0)
    {
      Serial.println("match led01");
      int ledId=s.substring(cmdLength+1,cmdLength+1+ledIdLength).toInt();
      int R=s.substring(cmdLength+1+ledIdLength+1,cmdLength+1+ledIdLength+1+colorLength).toInt();
      int G=s.substring(cmdLength+1+ledIdLength+1+colorLength+1,cmdLength+1+ledIdLength+(1+colorLength)*2).toInt();
      int B=s.substring(cmdLength+1+ledIdLength+1+(colorLength+1)*2,cmdLength+1+ledIdLength+(1+colorLength)*3).toInt();
      strip.setPixelColor(ledId, R, G, B);
      strip.show();
    }
    else if(s.substring(0,cmdLength).compareTo("led00")==0)
    {
      Serial.println("match led01");
      int R=s.substring(cmdLength+1,cmdLength+1+colorLength).toInt();
      int G=s.substring(cmdLength+1+colorLength+1,cmdLength+(1+colorLength)*2).toInt();
      int B=s.substring(cmdLength+1+(colorLength+1)*2,cmdLength+(1+colorLength)*3).toInt();
      strip.setPixelColor(0, R, G, B);
      strip.setPixelColor(1, R, G, B);
      strip.setPixelColor(2, R, G, B);
      strip.show();
    }
    else
    {
      Serial.println("error:unknown command");
    }
  }
  
}


void loop()
{
  String s=Serial.readString();
  parseCMD(s);
}
