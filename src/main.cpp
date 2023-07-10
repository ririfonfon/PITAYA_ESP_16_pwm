// platformio run --target uploadfs // cmd console download spiff

#include <Arduino.h>
#include <FastLED.h>

// #define DEBUG 1

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

// init serial
#ifdef DEBUG
  delay(3000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Hello World");
#endif

  // EEPROM
  init_eeprom();

  // RTC
  init_clock();

  // PINS
  init_pins();

  // init btn
  init_btn();

  // init pwm
  ledcAttachPin(PWM_GPIOPIN, 0);
  ledcSetup(0, PWM_FREQUENCY, PWM_RESOLUTION);

  // init wifi
  init_wifi();
  WiFi.mode(WIFI_OFF);

  // pause to setup mode btn
  leds[0] = 0x00FF00;
  FastLED.show();
  long nowdelay = millis() + 3000;
  while (nowdelay > millis())
  {
    check_btn();
  }

  check_day_time();
} // void setup()

void loop()
{
  check_btn();
  pwm_loop();
} // void loop()