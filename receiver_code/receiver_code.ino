//// RECIEVER CODE
#include <VirtualWire.h>
#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

DS3231 rtc(SDA, SCL);
Time t;
#define buz 9
#define led 4
#define servopin 3
int Hor;
int Min;
int Sec;
void setup()
{
Serial.begin(9600);
//vw_set_ptt_inverted(true); // Required for DR3100
vw_set_rx_pin(11);
vw_setup(4000); // Bits per sec
vw_rx_start(); // Start the receiver PLL running
Wire.begin();
rtc.begin();
Serial.begin(9600);
pinMode(buz, OUTPUT);
pinMode(led, OUTPUT);
pinMode(servopin, OUTPUT);
//myservo2.write(1250);
lcd.init(); // initialize the lcd
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("AUTOMATIC SPEED ");
lcd.setCursor(0,1);
lcd.print(" BREAKER SYSTEM ");
Buzzer();
lcd.clear();
// rtc.setDOW(THURSDAY); // Set Day-of-Week to SUNDAY
// rtc.setTime(13, 20, 00); // Set the time to 12:00:00 (24hr format)
// rtc.setDate(04 ,14, 2022); // Set the date to January 1st, 2014
// delay(2000);
//
}
//
void loop()
{
t = rtc.getTime();
Hor = t.hour;
Min = t.min;
Sec = t.sec;
// lcd.clear();
lcd.setCursor(0,0);
lcd.print("CURRENT TIME: ");
lcd.setCursor(5,1);
lcd.print(rtc.getTimeStr());
Serial.println(rtc.getTimeStr());
//// lcd.setCursor(0,0);
//// lcd.print("Time: ");
//// lcd.print(rtc.getTimeStr());
//// lcd.setCursor(0,1);
//// lcd.print("Date: ");
//// lcd.print(rtc.getDateStr());
//
if( Hor == 11 && (Min == 28|| Min == 29)) //Comparing the current time with the Alarm time
{

 uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
if (vw_get_message(buf, &buflen)) // Non-blocking
{
Serial.println(buf[0]);
if(buf[0]=='0')
{ 
  lcd.clear();
  lcd.print("EMERGENCY VEHICLE..... ");

digitalWrite(servopin,LOW);
delay(1000);
}
else{
lcd.clear();
Buzzer();
//delay(1000);
digitalWrite(servopin,HIGH);
lcd.print("SPEED BREAKER ");
lcd.setCursor(0,1);
lcd.print(" ACTIVATED ");
delay(1000);
}
}
}
else{
digitalWrite(servopin,LOW);
}
}

void Buzzer()
{
digitalWrite(buz,HIGH);
digitalWrite(led,HIGH);

delay(500);
digitalWrite(buz, LOW);
digitalWrite(led, LOW);

delay(500);
digitalWrite(buz,HIGH);
digitalWrite(led,HIGH);

delay(500);
digitalWrite(buz, LOW);
digitalWrite(led, LOW);

delay(500);
}
