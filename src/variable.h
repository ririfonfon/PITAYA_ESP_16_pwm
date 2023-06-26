#ifndef variable_h
#define variable_h

#define PWM_CHANNELS 1    //
#define PWM_FREQUENCY 5000 //
#define PWM_RESOLUTION 16  //

uint8_t PWM_GPIOPIN[1] = {32};
uint8_t BTN_GPIOPIN = 39;

long previousMillis = 0;
bool cycle = true;

bool f_i[PWM_CHANNELS] = {false};
bool f_o[PWM_CHANNELS] = {false};
bool p[PWM_CHANNELS + 1] = {false};
bool n[PWM_CHANNELS] = {false};
unsigned long currentp[PWM_CHANNELS];

// DEFO
uint8_t FOR_PWM_CHANNELS = 1; // Outputs
long fade_in = 8;             // Seconds
long fade_out = 8;            // Seconds
long decalage = 2000;         // Milliseconds
long on = 60000;              // Milliseconds
long off = 40000;             // Milliseconds
uint16_t High_value = 52428; // 65535= 100% donc 655,35 = 1% ,52428 = 80% , 58981 = 90%

int value[PWM_CHANNELS] = {0};

uint8_t ref[PWM_CHANNELS];

int btn_State = 1;

bool btn = false;

bool init_w = false;

#define MAX_CLIENT 6
int clientn = 0;
bool list[MAX_CLIENT] = {false}; // client

bool start = true;

uint8_t time_on_Hour;
uint8_t time_on_Minute;
uint8_t time_on_Second;

uint8_t time_off_Hour;
uint8_t time_off_Minute;
uint8_t time_off_Second;

int8_t time_zone = 1;

bool D_W[7] = {false,false,false,false,false,false,false};


#endif