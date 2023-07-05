// platformio run --target uploadfs // cmd console download spiff

#include <Arduino.h>
#include <FastLED.h>

#define DEBUG 1

#include "variable.h"
#include "led.h"
#include "rtc_clock.h"
#include "wifi_serv_setup.h"
#include "deep_sleep.h"
#include "btn.h"
#include "pwm_loop.h"

void setup()
{
  // init led
  init_led();
  leds[0] = 0xFF0000;
  FastLED.show();
// init serial
#ifdef DEBUG
  delay(3000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Hello World");
#endif

  // EEPROM
  prefs.begin("stamp", false);
  init_eeprom();

  // RTC
  init_clock();

  // init btn
  init_btn();

  // init pwm
  ledcAttachPin(PWM_GPIOPIN, 0);
  ledcSetup(0, PWM_FREQUENCY, PWM_RESOLUTION);

  init_wifi();
  WiFi.mode(WIFI_OFF);

} // void setup()

void loop()
{
  check_btn();
  pwm_loop();
} // void loop()