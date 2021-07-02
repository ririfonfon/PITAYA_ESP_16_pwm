#ifndef variable_h
#define variable_h

#define PWM_CHANNELS 15     //
#define PWM_FREQUENCY 60000 //
#define PWM_RESOLUTION 16   //

uint8_t PWM_GPIOPIN[16] = {32, 33, 25, 26, 27, 14, 12, 13, 23, 22, 21, 19, 18, 5, 4, 2};
uint8_t BTN_GPIOPIN = 15;

long previousMillis = 0;
bool cycle = true;

bool f_i[PWM_CHANNELS] = {false};
bool f_o[PWM_CHANNELS] = {false};
bool p[PWM_CHANNELS + 1] = {false};
bool n[PWM_CHANNELS] = {false};
unsigned long currentp[PWM_CHANNELS];

uint8_t FOR_PWM_CHANNELS = 4;
long fade_in = 8;        // fade_in * 2,6 = seconds
long fade_out = 8;        // fade_in * 2,6 = seconds
long decalage = 1000; // milliseconds
long on = 20000;      // milliseconds
long off = 20000;     // milliseconds

int value[PWM_CHANNELS] = {0};

uint8_t ref[PWM_CHANNELS];



int btn_State = 1;

bool btn = false;

bool init_w = false;

#define MAX_CLIENT 6
int clientn = 0;
bool list[MAX_CLIENT] = {false}; // client

bool start = true;

#endif