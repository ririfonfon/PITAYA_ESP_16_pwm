#ifndef variable_h
#define variable_h

#define PWM_FREQUENCY 5000 //
#define PWM_RESOLUTION 16  //

uint8_t PWM_GPIOPIN = 18;
uint8_t BTN_GPIOPIN = 39;
uint8_t CMD_GPIOPIN = 19;
uint8_t SQW_GPIOPIN = 26;


long previousMillis = 0;
bool cycle = true;

bool f_i = false;
bool f_o = false;
bool p = false;
bool n = false;
unsigned long currentp;

// DEFO
// long fade_in = 8;             // Seconds
// long fade_out = 8;            // Seconds
// long on = 60000;              // Milliseconds
// long off = 40000;             // Milliseconds

long fade_in = 10;             // Seconds
long fade_out = 10;            // Seconds
long on = 1000;              // Milliseconds
long off = 1000;             // Milliseconds
uint16_t High_value = 65535; // 65535= 100% donc 655,35 = 1% ,52428 = 80% , 58981 = 90%
long increm = 18 ;

int value = 0;


int btn_State = 1;

bool btn = false;

bool init_w = false;

#define MAX_CLIENT 6
int clientn = 0;
bool list[MAX_CLIENT] = {false}; // client

bool start = true;

int8_t time_zone = 1;

bool D_W[7] = {false,false,false,false,false,false,false};

uint8_t time_on_hour;
uint8_t time_on_minute;
uint8_t time_off_hour;
uint8_t time_off_minute;

String Message_on;
String Message_off;

#endif