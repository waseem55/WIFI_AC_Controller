/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  Rotate a servo using a slider!

  App project setup:
    Slider widget (0...180) on V3
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define COOL 1
#define OFF 2
#define HEAT 3
#define servo_pin 0

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "RK36x8fB_kBT_ht6kLbBHEkk5KKaisK1";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Seemo Al-Faheemo 2G";
char pass[] = "Seemo+Beeba";

Servo servo;
bool done = true;
int state;
int last_state = OFF;
unsigned long timer;

BLYNK_WRITE(V0)
{
  state = param.asInt();
  timer = millis();
  done = false;
  switch (state) {
    case OFF:
        if (last_state == COOL)
        {
          servo.write(85);
          //Serial.print("85");
        }
        else if (last_state == HEAT)
        {
          servo.write(95);
          //Serial.print("95");
        }
        else
        {
        servo.write(90);
        //Serial.print("90");
        }
      break;
    case COOL:
      servo.write(125);
      //Serial.print("125");
      break;
    case HEAT:
      servo.write(40);
      //Serial.print("50");
      break;
  }
}

void setup()
{
  Blynk.begin(auth, ssid, pass);
  servo.attach(0);
  //Serial.begin(9600);
}

void loop()
{
  Blynk.run();
  if (!done && (millis() > timer+1000))
  {
    done = true;
    switch (state){
      case OFF:
        if (last_state == HEAT)
        {
          servo.write(85);
          //Serial.print("80");
        }
        else if(last_state == COOL)
        {
          servo.write(90);
          //Serial.print("90");
        }
        last_state = OFF;
        break;
       case COOL:
        servo.write(120);
        //Serial.print("120");
        last_state = COOL;
        break;
       case HEAT:
        servo.write(50);
        //Serial.print("55");
        last_state = HEAT;
        break;
    }
  }
}
