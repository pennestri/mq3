/*
Author: Pietro Pennestri'
Mail:pietro.pennestri@gmail.com
Website: http://www.pennestri.me
Date: May 2nd 2015 

Description:
Calibration of an MQ3 shield on arduino board. 
The voltage is displayed when the sensor is exposed at a known 
alcohol concentration. Temperature is also recorded
for future adjustments.
*/

int mq3_analogPin = A5; // connected to the output pin of MQ3 
int val;
int tempPin = 1;
unsigned long time;
unsigned long time_in_second;
void setup(){
  Serial.begin(9600); // open serial at 9600 bps
}

void loop()
{
  // give ample warmup time for readings to stabilize
  float arduino_voltage = 5 ;
  int mq3_value = analogRead(mq3_analogPin);
  float voltage = mq3_value * (arduino_voltage / 1023.0);
  
  // get temperature
  val = analogRead(tempPin);
  float mv = ( val/1024.0)*5000; 
  float temperature = mv/10; // celsius
  
  //tieme
  time = millis();
  time_in_second = time/1000 ;
  
  //Serial.print("Voltage=");
  Serial.print(voltage);
  Serial.print("*");
  //Serial.print(" Temperature(C): ");
  Serial.print(temperature);
  Serial.print("*");
  //Serial.print(" Time(S): ");
  Serial.print(time_in_second);
  Serial.print("\n");
  
  delay(1000);    //slow down output 
}
