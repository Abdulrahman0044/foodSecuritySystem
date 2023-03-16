/* YOU ARE LIKELY TO LOOK THROUGH MY CODE 
 *  Written by Abdulrahman Babatunde
 */
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#define DHTPIN 10
#define LASER_PIN 6
#define LIGHT A2 
#define LED_PIN A1
#define  LDR_OUTPUT  A3

  
// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

DHT_Unified dht(DHTPIN, DHTTYPE);

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

float BUZZER = 8;
float laserB = 7; 

int pos = 0;
int vOut = 0; 
int Temp_Value = 0;
float RH_Value = 0.0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  
  // Declare laser as an output 
  pinMode(LASER_PIN, OUTPUT);
  // Declare buzzer as an output
  pinMode(BUZZER, OUTPUT);
   pinMode(LDR_OUTPUT, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LIGHT, OUTPUT);
  pinMode(laserB,OUTPUT);
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  // two servos are to turn through the same degree, they are then connected on the same pin 
  // two servo objects are attached on the pin 9
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);
    //Once the servo objects turned through 90 degrees, 15ms after, the laser source are powered ON
    digitalWrite(LASER_PIN, LOW);
  digitalWrite(LASER_PIN, HIGH); //outdoor control laser is on
  
    }
  digitalWrite(LIGHT, HIGH);

  // Initialize device.
  dht.begin();
  Serial.println("SURPSCON");
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("SURPSCON");
 delay(500);
  
}


void loop() {

  // clear the lcd screen
  lcd.clear();
 
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
    lcd.setCursor(1,0);
    lcd.print("Temp. Error");
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("Temperature: ");
    lcd.print(event.temperature);
    lcd.print("°C");
    Serial.println("The temperature is: "); 
    Serial.println(event.temperature);
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
    lcd.setCursor(0,1);
    lcd.print("Hum. Error");
  }
  else {
     lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print(event.relative_humidity);
    lcd.print("%");
    Serial.println("The relative humidity is: ");
    Serial.println(event.relative_humidity);
  }
  
  Temp_Value = digitalRead(event.temperature);
  RH_Value = digitalRead(event.relative_humidity);
  if ( Temp_Value < 22 && RH_Value < 100)
  {
    digitalWrite(BUZZER, HIGH);
    delay(500);
    digitalWrite(BUZZER,LOW);
    digitalWrite(laserB, HIGH); // Indoor laser is turned on
  }
    else
    {
      digitalWrite(BUZZER, LOW);
      digitalWrite(laserB, LOW);
    }
    vOut = analogRead(LDR_OUTPUT);
      Serial.println("LDR output is: ");
      Serial.println(vOut);
      delay(1000);
    if (vOut >= 500)
    {
      digitalWrite(LED_PIN, HIGH); 
    }
    else {
      digitalWrite(LED_PIN, LOW);
    }
}
