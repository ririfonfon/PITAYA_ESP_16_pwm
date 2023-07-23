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

void printDateTimeBM(I2C_BM8563_DateTypeDef _rtcdate, I2C_BM8563_TimeTypeDef _rtctime)
{
    Serial.printf("date %04d/%02d/%02d time %02d:%02d:%02d day of week %01d\n",
                  _rtcdate.year,
                  _rtcdate.month,
                  _rtcdate.date,
                  _rtctime.hours,
                  _rtctime.minutes,
                  _rtctime.seconds,
                  _rtcdate.weekDay);
}

void Rtc_SetDateTime(RtcDateTime _datetime)
{
    Rtctime.hours = _datetime.Hour(); // Set the rtc clock time.
    Rtctime.minutes = _datetime.Minute();
    Rtctime.seconds = _datetime.Second();

    Rtcdate.weekDay = _datetime.DayOfWeek(); // Set the rtc clock date.
    Rtcdate.month = _datetime.Month();
    Rtcdate.date = _datetime.Day();
    Rtcdate.year = _datetime.Year();

    Rtc.setTime(&Rtctime); // Synchronize the set time to the rtc.
    Rtc.setDate(&Rtcdate); // Synchronize the set date to the rtc
}

RtcDateTime Rtc_GetDateTime()
{
    Rtc.getDate(&Rtcdate);
    Rtc.getTime(&Rtctime);
    String datertc, timertc;
    datertc = String(Rtcdate.month) + " " + String(Rtcdate.date) + " " + String(Rtcdate.year);
    timertc = String(Rtctime.hours) + ":" + String(Rtctime.minutes) + ":" + String(Rtctime.seconds);
    RtcDateTime Result = RtcDateTime(datertc.c_str(), timertc.c_str());
    return Result;
}

void init_clock()
{
    //--------RTC SETUP ------------

    Wire.begin(21, 22, 100000UL);

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
        now = Rtc_GetDateTime();

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
            Rtc_SetDateTime(compiled);
        }
    }
}

void alarm_set()
{

    // Rtc.Enable32kHzPin(false);
    // Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeAlarmBoth);

    // DS3231AlarmOne alarm1(
    //     0,
    //     time_on_hour,
    //     time_on_minute,
    //     0,
    //     DS3231AlarmOneControl_HoursMinutesSecondsMatch);
    // Rtc.SetAlarmOne(alarm1);

    I2C_BM8563_TimeTypeDef RtcAlarm;

    RtcAlarm.hours = time_on_hour;
    RtcAlarm.minutes = time_on_minute;
    RtcAlarm.seconds = 0;

    Rtc.SetAlarmIRQ(RtcAlarm);
}

#endif