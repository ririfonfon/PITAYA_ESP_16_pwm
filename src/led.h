#ifndef led_h
#define led_h

#define NUM_LEDS 1
#define DATA_PIN 27
CRGB leds[NUM_LEDS];
#define BRIGHTNESS 1

struct Led
{
  // state variables
  int led_state;
  bool on;

  // methods
  void update()
  {
    led_state = on ? 0x0000FF : 0x000000;
    leds[0] = led_state;
    FastLED.show();
  }
};

Led onboard_led = {0x000000, true};

void init_led()
{
  FastLED.addLeds<SK6812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  leds[0] = 0xFF0000;
  FastLED.show();
} // init_led

#endif