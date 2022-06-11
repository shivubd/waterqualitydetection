
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 9
float Celcius=0;
OneWire oneWire(ONE_WIRE_BUS);

float sensorPin = A0;
float volt;
float ntu;
float accuvolt;
DallasTemperature sensors(&oneWire);
int sensorValue = 0; 

const int analogInPin = A1; 
float ph_value,sensor_value = 0;

#include <LiquidCrystal.h>
const int rs = 8, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String str;
SoftwareSerial espSerial(10,11);

 void setup(void)
{
  Serial.begin(9600);
  espSerial.begin(115200);
  sensors.begin();
  analogWrite(6,20);
  lcd.begin(16, 2);

  delay(2000);
}

void loop(void)
{
  volt = 0;
    for(int i=0; i<800; i++)
    {
        volt += ((float)analogRead(sensorPin)/1023)*5;
    }
    volt = volt/800;
    volt = round_to_dp(volt,2);
    accuvolt=volt*4.35;
    if( accuvolt< 2.5)
    {
      ntu = 3000;
    }
    else{
      ntu = -1120.4*square( accuvolt)+5742.3* accuvolt-4353.8; 
    }
    Serial.print(volt);
  Serial.println(ntu);
  
 
  
  sensors.requestTemperatures(); 
  Celcius=sensors.getTempCByIndex(0);
  Serial.print(" C  ");
  Serial.println(Celcius, 2);
  Serial.println("C");

  ph_value=analogRead(analogInPin);
  sensor_value=(ph_value-200)/35;
  Serial.print("ph_value =");
  Serial.println(sensor_value);

  
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("TURB: ");
  lcd.setCursor(5,0);
  lcd.print(ntu);
  lcd.setCursor(0,1);
  lcd.print("T: ");
  lcd.setCursor(2,1);
  lcd.print(Celcius);
  lcd.setCursor(8,1);
  lcd.print("pH: ");
  lcd.setCursor(11,1);
  lcd.print(sensor_value);

  str =String(sensor_value)+" "+String(ntu)+" "+String(Celcius, 2);
  espSerial.println(str);

  
}

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}
