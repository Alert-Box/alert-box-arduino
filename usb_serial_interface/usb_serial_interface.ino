//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6



LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
Adafruit_NeoPixel strip = Adafruit_NeoPixel(3, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  
  /*
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
  lcd.setCursor(2,1);
  lcd.print("Ywrobot Arduino!");
   lcd.setCursor(0,2);
  lcd.print("Arduino LCM IIC 2004");
   lcd.setCursor(2,3);
  lcd.print("Power By Ec-yuan!");*/
}

String lcdCommand=String("lcd01");
String ledCommand=String("led01");
const char separator=':';
const int cmdLength=5;

//lcd commands constants
const int colLength=2;
const int rowLength=2;

//led commands constants
const int ledIdLength=2;
const int colorLength=3;


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
