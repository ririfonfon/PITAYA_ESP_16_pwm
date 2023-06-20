#ifndef rtc_clock
#define rtc_clock

#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS3231.h>
#include <EepromAT24C32.h>

RtcDS3231<TwoWire> Rtc(Wire);
EepromAt24c32<TwoWire> RtcEeprom(Wire);

// char Wdata[] = "What time is it in Greenwich?";

#define countof(a) (sizeof(a) / sizeof(a[0]))

RtcDateTime old;
RtcDateTime alarmTime;

char DaysOfWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
// char DaysOfWeek[7][12] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};

RtcDateTime now = Rtc.GetDateTime();

DS3231AlarmOne alarm_one = Rtc.GetAlarmOne();
RtcDateTime time_on(now.Year(),
                    now.Month(),
                    now.Day(),
                    alarm_one.Hour(),
                    alarm_one.Minute(),
                    alarm_one.Second());
RtcDateTime time_off(now.Year(),
                     now.Month(),
                     now.Day(),
                     time_off_Hour,
                     time_off_Minute,
                     time_off_Second);

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

void publishTimeOn(const RtcDateTime &dt)
{
    char datestring[20];

    snprintf_P(datestring,
               countof(datestring),
               PSTR("%02u:%02u:%02u"),
               dt.Hour(),
               dt.Minute(),
               dt.Second());
    // mqtt_topic = String(MQTT) + String(ID) + String(MQTT_TIME_ON);
    // mqtt_topic.toCharArray(mqtt_topic_char, mqtt_topic.length() + 1);
    // mqttClient.publish(mqtt_topic_char, 0, true, datestring);
}

void publishTimeOff(const RtcDateTime &dt)
{
    char datestring[20];

    snprintf_P(datestring,
               countof(datestring),
               PSTR("%02u:%02u:%02u"),
               dt.Hour(),
               dt.Minute(),
               dt.Second());
    // mqtt_topic = String(MQTT) + String(ID) + String(MQTT_TIME_OFF);
    // mqtt_topic.toCharArray(mqtt_topic_char, mqtt_topic.length() + 1);
    // mqttClient.publish(mqtt_topic_char, 0, true, datestring);
}

void init_clock()
{
    //--------RTC SETUP ------------

    Rtc.Begin(22, 21); // the available pins for SDA, SCL
    RtcEeprom.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);

#ifdef DEBUG
    Serial.print("compiled : ");
    Serial.print("\t");
    printDateTime(compiled);
    Serial.println();
#endif

    if (!Rtc.IsDateTimeValid())
    {
        if (Rtc.LastError() != 0)
        {
            // we have a communications error
            // see https://www.arduino.cc/en/Reference/WireEndTransmission for
            // what the number means
            Serial.print("RTC communications error = ");
            Serial.println(Rtc.LastError());
        }
        else
        {
            Serial.println("RTC lost confidence in the DateTime!");
            Rtc.SetDateTime(compiled);
        }
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
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
    Rtc.Enable32kHzPin(false);
    Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);

    /* comment out on a second run to see that the info is stored long term */
    // Store something in memory on the Eeprom
}


void alarm_set()
{

    Rtc.Enable32kHzPin(false);
    Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeAlarmBoth);

    // DS3231AlarmOne alarm1(
    //     01,
    //     18,
    //     18,
    //     00,
    //     DS3231AlarmOneControl_HoursMinutesSecondsMatch);
    // Rtc.SetAlarmOne(alarm1);

    // Alarm 1 set to trigger every day when
    // the hours, minutes, and seconds match

    // alarmTime = Rtc.GetDateTime() + 60; // into the future

    // Serial.print(" next alarm set to ");
    // printDateTime(alarmTime);
    // Serial.println(" ");

    // DS3231AlarmOne alarm1(
    //     alarmTime.Day(),
    //     alarmTime.Hour(),
    //     alarmTime.Minute(),
    //     alarmTime.Second(),
    //     DS3231AlarmOneControl_HoursMinutesSecondsMatch);
    // Rtc.SetAlarmOne(alarm1);

    DS3231AlarmOne alarm1(
        0,
        time_on_Hour,
        time_on_Minute,
        time_on_Second,
        DS3231AlarmOneControl_HoursMinutesSecondsMatch);
    Rtc.SetAlarmOne(alarm1);

    // Alarm 2 set to trigger at the top of the minute

    // DS3231AlarmTwo alarm2(
    //     0,
    //     0,
    //     0,
    //     DS3231AlarmTwoControl_HoursMinutesDayOfMonthMatch);
    // Rtc.SetAlarmTwo(alarm2);

    // throw away any old alarm state before we ran
    // Rtc.LatchAlarmsTriggeredFlags();
}

#endif