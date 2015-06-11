#include <LiquidCrystal.h>
#include <OneSheeld.h>
#include <GPSShield.h>
#include <SMSShield.h>
LiquidCrystal lcd(6, 7, 10, 11, 12, 13);
int buttonState = 0;  
boolean isMessageSent = false;
float get_latitude ;
float get_longitude ;
String latitude ;
String longitude ;
String sms_text ;
float volt_2_gl(float v){
  float a = 2.64581 ;
  float b = 0.59843 ;
  float gl = (v-a)/b ;
  return gl ;
}
void setup() {
  OneSheeld.begin(); // Start communication with 1Sheeld
  lcd.begin(1, 2);
  pinMode(9, INPUT);
  pinMode(4, OUTPUT);
  lcd.print("P. Pennestri'");
  lcd.setCursor(0, 1);
  lcd.print("L.S.S. I. Newton");
  delay(3000);
  lcd.clear();
  lcd.print("Warming Up");
  lcd.setCursor(0, 1);
  lcd.print("Don't Breath");  
  delay(30000);
  lcd.clear();
}

void loop() {
   buttonState = digitalRead(9); // read the state of the pushbutton value
   if (buttonState == HIGH) { 
   isMessageSent = false;
   lcd.print("Breath in");
   delay(15000);
   delay(15000);
   delay(15000);
   delay(5000);
   lcd.clear();
   digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(1000);              // wait for a second
   digitalWrite(4, LOW);    // turn the LED off by making the voltage LOW
   delay(1000);              // wait for a second
   int mq3_value1 = analogRead(A5);
   float voltage1 = mq3_value1 * (5.0 / 1023.0); // get mq3 voltage 
    
   if(voltage1<2.42){
    lcd.print("No alcohol");
    lcd.setCursor(0, 1);
    lcd.print("You can drive ");
    delay(15000);
    lcd.clear();
   }
   
   if(voltage1>=2.42){
     float response = volt_2_gl(voltage1);
     // send sms if response >= 0.5 g/l
     lcd.print(response);
     lcd.print(" g/l");
     lcd.setCursor(0, 1);
     lcd.print("DO NOT DRIVE!");
     delay(15000);
     delay(15000);
     delay(15000);
     delay(5000);
     lcd.clear();
     
          if(response>=0.5){
     
        if(!isMessageSent)
    {    
         lcd.print("SMS Sent");
         lcd.clear();
         get_latitude = GPS.getLatitude();
         latitude = String(get_latitude);
         get_longitude = GPS.getLongitude();
         longitude = String(get_longitude);
         sms_text = "I need HELP \n pick me up at \n https://www.google.it/maps/place/" + latitude + "+" + longitude  ;          
         
         SMS.send("3511012085", sms_text);  // send sms
         isMessageSent = true;  // Set the flag.  
        delay(10000);
    }
       
     }
     
     lcd.print("Going to idle state");
     lcd.setCursor(0, 1);
     lcd.print("Don't Breath");
     delay(15000);
     delay(15000);
     delay(15000);
     delay(5000);
   }} else{
     lcd.print("Ready to Start");
     delay(1000);
     lcd.clear();
   }



}
