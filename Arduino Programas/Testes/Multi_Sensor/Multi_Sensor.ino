#include "max6675.h" 

// Temperature Sensor1
int thermo1D0 = 5; // so
int thermo1CS = 6; 
int thermo1CLK = 7; // sck
float temp1 = 0; 
MAX6675 thermocouple1(thermo1CLK, thermo1CS, thermo1D0); 


// Temperature Sensor2
int thermo2D0 = 11; // so
int thermo2CS = 12; 
int thermo2CLK = 13; // sck
float temp2 = 0; 
MAX6675 thermocouple2(thermo2CLK, thermo2CS, thermo2D0); 



void setup()
{
  Serial.begin(9600); 

}

void loop()
{
  delay(100);
  temp1 = thermocouple1.readCelsius(); 
  Serial.print("Temperatura 1: ");
  Serial.println(temp1);

  delay(100);
  temp2 = thermocouple2.readCelsius();
  Serial.print("Remperatura 2: ");
  Serial.println(temp2);

}
