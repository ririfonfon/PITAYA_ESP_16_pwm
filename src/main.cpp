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
// init serial
#ifdef DEBUG
  Serial.begin(115200);
  Serial.println();
#endif

  // EEPROM
  EEPROM.begin(EEPROM_SIZE);
  init_eeprom();

  //init led
  init_led();

  //init btn
  init_btn();

  //init pwm
  for (int k = 0; k < PWM_CHANNELS; k++)
  {
    ledcAttachPin(PWM_GPIOPIN[k], k);
    ledcSetup(k, PWM_FREQUENCY, PWM_RESOLUTION);
  }

#ifdef DEBUG
  for (int k = 0; k > FOR_PWM_CHANNELS; k++)
  {
    Serial.println(ref[k]);
  }
#endif

  init_wifi();
  WiFi.mode(WIFI_OFF);

} //void setup()

void loop()
{
  check_btn();
  pwm_loop();
} //void loop()