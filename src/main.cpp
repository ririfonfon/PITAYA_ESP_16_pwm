#include <Arduino.h>

#define DEBUG 1

#include "variable.h"
#include "led.h"
#include "random.h"

void setup()
{
// init serial
#ifdef DEBUG
  Serial.begin(115200);
  Serial.println();
#endif

  //init led
  init_led();

  //init pwm
  for (int k = 0; k < PWM_CHANNELS; k++)
  {
    ledcAttachPin(PWM_GPIOPIN[k], k);
    ledcSetup(k, PWM_FREQUENCY, PWM_RESOLUTION);
  }

  // random output
  rnd();
#ifdef DEBUG
  for (int k = 0; k > PWM_CHANNELS; k++)
  {
    Serial.println(ref[k]);
  }
#endif
} //void setup()

void loop()
{
  bool fade_clock;
  unsigned long currentMillis = millis();

  if (cycle)
  {
    previousMillis = currentMillis;
    cycle = false;
  } //if (cycle)

  onboard_led.on = millis() % 2000 < 1000;
  onboard_led.update();

  for (int d = 0; d < PWM_CHANNELS; d++)
  {
    if (!f[d] && !p[d] && currentMillis - previousMillis > (d + 1) * decalage)
    {
      f[d] = true;
#ifdef DEBUG
      Serial.print(" f[");
      Serial.print(d);
      Serial.print("] = ");
      Serial.print(f[d]);
      Serial.print(" at ");
      Serial.println(currentMillis);
#endif
    } //if (!f[d] && !p[d] && currentMillis - previousMillis > (d + 1) * decalage)if (!f[d] && !p[d] && currentMillis - previousMillis > (d + 1) * decalage)
  }   //for (int d = 0; d < PWM_CHANNELS; d++)

  for (int d = 0; d < PWM_CHANNELS; d++)
  {
    if (f[d])
    {
      fade_clock = millis() % fade < 1;
      if (fade_clock && f[d])
      {
        value[d] += 1;
      }
      if (value[d] > 65535)
      {
        value[d] = 65535;
        f[d] = false;
        p[d] = true;
        currentp[d] = currentMillis;

#ifdef DEBUG
        Serial.print(" currentp[");
        Serial.print(d);
        Serial.print("] at ");
        Serial.println(currentp[d]);
#endif
      }
    } //if (f[d])
  }   //for (int d = 0; d < PWM_CHANNELS; d++)

  for (int d = 0; d < PWM_CHANNELS; d++)
  {
    if (!p[PWM_CHANNELS] && !n[d] && p[d] && currentMillis - currentp[d] > on)
    {
      value[d] = 0;
      n[d] = true;
#ifdef DEBUG
      Serial.print(" value[");
      Serial.print(d);
      Serial.print("] = 0 at ");
      Serial.println(currentMillis);
#endif
    } //if (!n[d] && p[d] && currentMillis - currentp[d] > on)

    if (!p[PWM_CHANNELS] && n[PWM_CHANNELS - 1])
    {
      p[PWM_CHANNELS] = true;
      currentp[PWM_CHANNELS] = currentMillis;
#ifdef DEBUG
      Serial.print("currentp[");
      Serial.print(PWM_CHANNELS);
      Serial.print("] at ");
      Serial.println(currentp[PWM_CHANNELS]);
#endif
    }
  } //for (int d = 0; d < PWM_CHANNELS; d++)

  for (int d = 0; d < PWM_CHANNELS; d++)
  {
    if (p[PWM_CHANNELS] && currentMillis - currentp[PWM_CHANNELS] > off)
    {
      previousMillis = currentMillis;
      for (int q = 0; q < PWM_CHANNELS; q++)
      {
        p[q] = false;
        f[q] = false;
        n[q] = false;
        p[PWM_CHANNELS] = false;
      }
      rnd();
    } //if (p[PWM_CHANNELS] && currentMillis - currentp[PWM_CHANNELS] > off)
  }   //for (int d = 0; d < PWM_CHANNELS; d++)

  for (int d = 0; d < PWM_CHANNELS; d++)
  {
    ledcWrite(d, value[ref[d]]);
  } //for(int d=0; d>PWM_CHANNELS;d++)

} //void loop()