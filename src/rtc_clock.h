#ifndef rtc_clock
#define rtc_clock

#include <Wire.h>
// #include <RtcDS3231.h>
// #include <EepromAT24C32.h>
#include "M5_I2C_BM8563.h"
#include "RtcUtility.h"
#include "RtcDateTime.h"

I2C_BM8563 Rtc;
I2C_BM8563_DateTypeDef Rtcdate;
I2C_BM8563_TimeTypeDef Rtctime;

// RtcDS3231<TwoWire> Rtc(Wire);
// EepromAt24c32<TwoWire> RtcEeprom(Wire);

#define countof(a) (sizeof(a) / sizeof(a[0]))

char DaysOfWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// DS3231AlarmOne alarm_one = Rtc.GetAlarmOne();

void printDateTime(const RtcDateTime &dt)
{
    char datestring[20];

    snprintf_P(datestring,
               countof(datestring),
               PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
               dt.Day(),
               dt.Month(),
               dt.Year(),
               dt.Hour(),
               dt.Minute(),
               dt.Second());
    Serial.print(" -> ");
    Serial.print(DaysOfWeek[dt.DayOfWeek()]);
    Serial.print(" ");
    Serial.print(datestring);
}

void init_clock()
{
    //--------RTC SETUP ------------

    Rtc.begin(); // the available pins for SDA, SCL
    // Rtc.Begin(21, 22); // the available pins for SDA, SCL
    // RtcEeprom.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    RtcDateTime now;

#ifdef DEBUG
    Serial.print("compiled : ");
    Serial.print("\t");
    printDateTime(compiled);
    Serial.println();
#endif

    if (!Rtc.isEnable())
    {
        Serial.print("RTC communications error ");
    }
    else if (Rtc.isEnable())
    {
        Rtc.getDate(&Rtcdate);
        Rtc.getTime(&Rtctime);

        now = RtcDateTime(Rtcdate.month + ' ' + Rtcdate.date + ' ' + Rtcdate.year, Rtctime.hours + ':' + Rtctime.minutes + ':' + Rtctime.seconds);

#ifdef DEBUG
        Serial.print("now : ");
        Serial.print("\t\t");
        printDateTime(now);
        Serial.println();

        Serial.print("Pure now : ");
        Serial.print("\t\t");
        Serial.print(now.TotalSeconds());
        Serial.println();
        Serial.print("Pure compiled : ");
        Serial.print("\t");
        Serial.print(compiled.TotalSeconds());
        Serial.println();
#endif

        if (now < compiled)
        {
            Serial.println("RTC is older than compile time!  (Updating DateTime)");
            Rtc.SetDateTime(compiled);
        }

        // never assume the Rtc was last configured by you, so
        // just clear them to your needed state
        // Rtc.Enable32kHzPin(false);
        // Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);

        /* comment out on a second run to see that the info is stored long term */
        // Store something in memory on the Eeprom
    }
}

void alarm_set()
{

    Rtc.Enable32kHzPin(false);
    Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeAlarmBoth);

    DS3231AlarmOne alarm1(
        0,
        time_on_hour,
        time_on_minute,
        0,
        DS3231AlarmOneControl_HoursMinutesSecondsMatch);
    Rtc.SetAlarmOne(alarm1);
}

#endif