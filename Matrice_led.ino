//#include <WiFi.h>
//#include <time.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "LiquidCrystal.h"
#include "Ultrasonic.h"
#include <SimpleDHT.h>




#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_H

#define MAX_DEVICES 4

#define CLK_PIN   13 // or SCK
#define DATA_PIN  11 // or MOSI
#define CS_PIN    9 // or SS

int dht = 7;
byte temp = 0;
byte humidite = 0;

// Arbitrary output pins
SimpleDHT11 dht11(dht);
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);


/**********  User Config Setting   ******************************/
//char* ssid = "SFR_ED9F";
//char* password = "2nx94rfr36r4nin1n6ql";

struct animations {
  textEffect_t anim_in;
  textEffect_t anim_out;
  const char* textOut;
  const int* values;
  uint16_t speed;
  uint16_t pause;
  textPosition_t just;
};

animations animList1[] =
{
  //{ PA_SCAN_HORIZX, PA_SCAN_HORIZX, "", 5,2, PA_LEFT},
  //{ PA_RANDOM, PA_CLOSING_CURSOR, "Love", 5,2, PA_CENTER},
  //{ PA_FADE, PA_FADE, "you", 15,1, PA_CENTER},
  //{ PA_SCROLL_LEFT, PA_SCROLL_LEFT, "TEST", 5, 0, PA_LEFT},
  { PA_FADE, PA_FADE, "temp : ",26, 15, 1, PA_CENTER } ,
  //{ PA_SCROLL_LEFT, PA_SCROLL_LEFT, "HUMI :", 5, 0, PA_LEFT} ,



  //{ PA_SCROLL_LEFT, PA_SCROLL_LEFT, heart, 5, 0, PA_LEFT}
};

animations animList2[] =
{
  //{ PA_SCAN_HORIZX, PA_SCAN_HORIZX, "Hello", 5,2, PA_LEFT},
  //{ PA_RANDOM, PA_CLOSING_CURSOR, "Love", 5,2, PA_CENTER},
  //{ PA_FADE, PA_FADE, "you", 15,1, PA_CENTER},
  //{ PA_SCROLL_LEFT, PA_SCROLL_LEFT, "TEST", 5, 0, PA_LEFT},
  //{ PA_OPENING, PA_CLOSING, "JESUS SAVES", 5,5, PA_CENTER} ,

  //{ PA_SCROLL_LEFT, PA_SCROLL_LEFT, heart, 5, 0, PA_LEFT}
};

void setup(void)
{
  Serial.begin(115200);
  P.setIntensity(7);
  P.displayClear();
  pinMode(dht, INPUT);

  for (uint8_t i = 0; i < ARRAY_SIZE(animList1); i++)
  {
    animList1[i].speed *= P.getSpeed(); animList1[i].pause *= 500;
  }
  for (uint8_t i = 0; i < ARRAY_SIZE(animList2); i++)
  {
    animList2[i].speed *= P.getSpeed(); animList2[i].pause *= 500;
  }
}

void loop(void)
{

  /*if (P.displayAnimate()) {
      P.displayReset();
    }*/ Serial.println("*******************");
  Serial.println("Simple DHT11...");


  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temp, &humidite, NULL) != SimpleDHTErrSuccess))
  {
    Serial.print("Read DHT11 failed, err=");
    Serial.println(err);
    delay(1000);
    return;
  }

  Serial.print("Sample OK : ");
  Serial.print((int)temp);
  Serial.print(" *C");

  Serial.print((int)humidite);
  Serial.print(" H");


  static uint8_t i = 0;

  if (P.displayAnimate())
  {
    if (i == ARRAY_SIZE(animList1) /*&& i == ARRAY_SIZE(animList2)*/) i = 0;
    {
      P.displayText(animList1[i].textOut, animList1[i].just, animList1[i].speed,
                    animList1[i].pause, animList1[i].anim_in, animList1[i].anim_out);
      /*P.displayText(animList2[i].textOut, animList2[i].just, animList2[i].speed,
                    animList2[i].pause, animList2[i].anim_in, animList2[i].anim_out);*/
      delay(500);
      i++;
    }
  }



  /*lcd.setCursor(14, 0);
    lcd.print(temp);

    lcd.setCursor(10, 1);
    lcd.print(humidite);*/



}
