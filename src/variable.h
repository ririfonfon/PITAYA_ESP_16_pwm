#ifndef variable_h
#define variable_h


#define PWM_CHANNELS 8      //
#define PWM_FREQUENCY 60000 //
#define PWM_RESOLUTION 16   //

uint8_t PWM_GPIOPIN[16] = {32, 33, 25, 26, 27 , 14 , 12 , 13 , 23 , 22 , 21 , 19 , 18 , 5 , 4 , 2};

long previousMillis = 0;
bool cycle = true;

bool f[PWM_CHANNELS] = {false};
bool p[PWM_CHANNELS+1] = {false};
bool n[PWM_CHANNELS] = {false};
unsigned long currentp[PWM_CHANNELS];

long fade = 1;        // fade * 2,6 = seconds  8
long decalage = 1000; // milliseconds  1000
long on = 6000;      // milliseconds  20000
long off = 6000;     // milliseconds  20000

int value[PWM_CHANNELS] = {0};

uint8_t ref[PWM_CHANNELS];

#endif