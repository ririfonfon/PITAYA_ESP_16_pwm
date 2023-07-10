#ifndef deep_sleep
#define deep_sleep

#include "esp_sleep.h"

// #define BUTTON_PIN_BITMASK 0x1

RTC_DATA_ATTR int bootCount = 0;

/*
Method to print the reason by which ESP32
has been awaken from sleep
*/
void print_wakeup_reason()
{
    esp_sleep_wakeup_cause_t wakeup_reason;

    wakeup_reason = esp_sleep_get_wakeup_cause();

    switch (wakeup_reason)
    {
    case ESP_SLEEP_WAKEUP_EXT0:
        Serial.println("Wakeup caused by external signal using RTC_IO");
        break;
    case ESP_SLEEP_WAKEUP_EXT1:
        Serial.println("Wakeup caused by external signal using RTC_CNTL");
        break;
    case ESP_SLEEP_WAKEUP_TIMER:
        Serial.println("Wakeup caused by timer");
        break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
        Serial.println("Wakeup caused by touchpad");
        break;
    case ESP_SLEEP_WAKEUP_ULP:
        Serial.println("Wakeup caused by ULP program");
        break;
    default:
        Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
        break;
    }
}

void deep_sleep_init()
{
    leds[0] = 0x000000;
    FastLED.show();
    ledcWrite(0, 0);
    digitalWrite(CMD_GPIOPIN, LOW);

    // Increment boot number and print it every reboot
    ++bootCount;
    Serial.println("Boot number: " + String(bootCount));

    // Print the wakeup reason for ESP32
    print_wakeup_reason();

    /*
    First we configure the wake up source
    We set our ESP32 to wake up for an external trigger.
    There are two types for ESP32, ext0 and ext1 .
    ext0 uses RTC_IO to wakeup thus requires RTC peripherals
    to be on while ext1 uses RTC Controller so doesnt need
    peripherals to be powered on.
    Note that using internal pullups/pulldowns also requires
    RTC peripherals to be turned on.
    */
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, 0); // 1 = High, 0 = Low DS3231 SQW
    // esp_sleep_enable_ext0_wakeup(GPIO_NUM_39, 0); // 1 = High, 0 = Low btn m5stamp

    // If you were to use ext1, you would use it like
    // esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK, ESP_EXT1_WAKEUP_ALL_LOW);

    // Latch RTC Alarm
    Rtc.LatchAlarmsTriggeredFlags();

    // Go to sleep now
    Serial.println("Going to sleep now");
    esp_deep_sleep_start();
    Serial.println("This will never be printed");
}

void check_day_time()
{
    RtcDateTime now = Rtc.GetDateTime();
    uint8_t dday = now.DayOfWeek();
    int8_t dmoins = dday - 1;
    if (dmoins == -1)
    {
        dmoins = 6;
    }
    uint16_t on_minutes = (time_on_hour * 60) + time_on_minute;
    uint16_t off_minutes = (time_off_hour * 60) + time_off_minute;
    uint16_t now_minutes = (now.Hour() * 60) + now.Minute();
#ifdef DEBUG
    Serial.println(" ");
    Serial.print("check_day_time D_W[day] = ");
    Serial.print(D_W[dday]);
    Serial.print(" D_W[moins] = ");
    Serial.print(D_W[dmoins]);
    Serial.print(" now_minutes = ");
    Serial.print(now_minutes);
    Serial.print(" on_minutes = ");
    Serial.print(on_minutes);
    Serial.print(" off_minutes = ");
    Serial.println(off_minutes);
#endif

    if (!D_W[dday] && !D_W[dmoins])
    {
        deep_sleep_init();
    }
    else if (!D_W[dday] && D_W[dmoins])
    {
        if (off_minutes < now_minutes)
        {
            deep_sleep_init();
        }
    }

    if (on_minutes > off_minutes)
    {
        if (now_minutes < on_minutes && now_minutes > off_minutes)
        {
            deep_sleep_init();
        }
    }
    else if (on_minutes < off_minutes)
    {
        if (now_minutes < on_minutes || now_minutes > off_minutes)
        {
            deep_sleep_init();
        }
    }
}

void init_pins()
{
    pinMode(SQW_GPIOPIN, INPUT);  // SQW DS3231
    pinMode(CMD_GPIOPIN, OUTPUT); // CMD Relais
    digitalWrite(CMD_GPIOPIN, LOW);
    pinMode(PWM_GPIOPIN, OUTPUT); // PWM
}

#endif