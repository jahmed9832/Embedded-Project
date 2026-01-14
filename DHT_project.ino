#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTTYPE DHT22
#define DHTPIN1 2
#define DHTPIN2 3
#define DHTPIN3 4
// #define FANPIN 6

int enA = 9;
int in1 = 8;
int in2 = 7;

int regularSpeed = 100;              
int increasedSpeed = 255;            
float maxRH = 30.0;                  
unsigned long ventDuration = 3000; 

unsigned long lastVentTime = 0;
unsigned long ventStartTime = 0;
bool venting = false;

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
DHT dht3(DHTPIN3, DHTTYPE);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  dht1.begin();
  dht2.begin();
  dht3.begin();

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, regularSpeed);


  Serial.println(F("Dryer System Started"));
}

void loop() {
  float h1 = dht1.readHumidity();
  float h2 = dht2.readHumidity();
  float h3 = dht3.readHumidity();

  if (isnan(h1) || isnan(h2) || isnan(h3)) {
    Serial.println(F("Failed to read from one or more DHT sensors!"));
    return;
  }

  float maxHumidity = max(h1, max(h2, h3));

  if ((h1 > maxRH || h2 > maxRH || h3 > maxRH) && !venting) {
    venting = true;
    ventStartTime = millis();
    analogWrite(enA, increasedSpeed);
    Serial.println("High humidity detected — Venting started");
  }

  if (venting && millis() - ventStartTime >= ventDuration) {
    if (h1 <= maxRH && h2 <= maxRH && h3 <= maxRH) {
      venting = false;
      lastVentTime = millis();
      analogWrite(enA, regularSpeed);
      Serial.println("Venting finished — humidity normal");
    } else {
      ventStartTime = millis();
      Serial.println("Humidity still high — extending vent");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("R1:");
  lcd.print(h1,0);
  lcd.print("% R2:");
  lcd.print(h2,0);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("R3:");
  lcd.print(h3,0);
  lcd.print("% ");

  if (venting) {
    lcd.print("VntON");
    
  } else {
    unsigned long secondsSince = (millis() - lastVentTime) / 1000;
    lcd.print("LV:");
    lcd.print(secondsSince);
    lcd.print("s");
  }
  delay(1000); 
}
