#include <DHT.h>
#include "U8glib.h"
#include <Arduino.h>
#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI


int AcceptableTempLED = 12;
int HighHumidityLED = 11;
int HighTempLED = 10;

void setup() {
  Serial.begin(9600);
  u8g.setFont(u8g_font_9x15B);
  pinMode(AcceptableTempLED, OUTPUT);
  digitalWrite(AcceptableTempLED, HIGH);
  digitalWrite(HighHumidityLED, HIGH);
  digitalWrite(HighTempLED, HIGH);
  delay(1500);
  digitalWrite(AcceptableTempLED, LOW);
  digitalWrite(HighHumidityLED, LOW);
  digitalWrite(HighTempLED, LOW);
  dht.begin();
  Serial.begin(9600);
}


void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = (t * 9 / 5) + 32;  //Math from celsius to fahrenheit


  while (f < 60)  //If temp less than Degrees F
  {
    digitalWrite(AcceptableTempLED, HIGH);  //green LED on
    Serial.print(f);
    Serial.println();
    delay(2000);


    if (h > 36)  //If humidity greater than percent
    {
      digitalWrite(HighHumidityLED, HIGH);  //Blue LED on
      Serial.print(h);
      Serial.println();
      delay(2000);
      break;

    } else {
      digitalWrite(HighHumidityLED, LOW);
      Serial.print(h);
      Serial.println();
      delay(2000);

      break;
    }
  }

  while (f >= 60)  //If temp greater or equal than Degrees F
  {
    digitalWrite(HighTempLED, HIGH);  //Red LED on
    Serial.print(f);
    Serial.print("f");
    Serial.println();
    delay(2000);


    if (h >= 36)  //If humidity less than percent
    {
      digitalWrite(HighHumidityLED, HIGH);
      Serial.print(h);
      Serial.println();
      delay(2000);
      break;

    } else {
      digitalWrite(HighHumidityLED, LOW);
      Serial.print(h);
      Serial.println();
      delay(2000);

      break;
    }
  }



  u8g.firstPage();
  do {
    drawGraph(f, h);
  } while (u8g.nextPage());

  delay(2000);
}

void drawGraph(float f, float h) {
  u8g.drawStr(10, 10, "Temperature:");
  u8g.drawStr(50, 60, "Humidity");
  u8g.drawStr(75, 22, ".");  //Degree symbol stand in

  String tempString = String(f, 1);
  u8g.drawStr(40, 29, tempString.c_str());
  u8g.drawStr(83, 29, ("F"));

  String humidString = String(h, 1) + "%";
  u8g.drawStr(0, 60, humidString.c_str());
}