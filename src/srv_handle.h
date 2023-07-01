#ifndef srv_handle_h
#define srv_handle_h

#include <RtcDS3231.h>

#include <Preferences.h>
Preferences prefs;
// #include <EEPROM.h>
// #define EEPROM_SIZE 64

void eeprom_read()
{

    fade_in = prefs.getUInt("fade_in", 0);

    on = prefs.getUInt("on", 0);

    off = prefs.getUInt("off", 0);

    fade_out = prefs.getUInt("fade_out", 0);

    D_W[1] = prefs.getBool("d1", 0);
    D_W[2] = prefs.getBool("d2", 0);
    D_W[3] = prefs.getBool("d3", 0);
    D_W[4] = prefs.getBool("d4", 0);
    D_W[5] = prefs.getBool("d5", 0);
    D_W[6] = prefs.getBool("d6", 0);
    D_W[7] = prefs.getBool("d7", 0);

    int hou = prefs.getUInt("t_h_on", 0);
    int minu = prefs.getUInt("t_m_on", 0);
    RtcDateTime time_on(0, 0, 0, hou, minu, 0);

    int houf = prefs.getUInt("t_h_off", 0);
    int minuf = prefs.getUInt("t_m_off", 0);
    RtcDateTime time_off(0, 0, 0, houf, minuf, 0);

#ifdef DEBUG
    Serial.println("EEPROM READ");
    Serial.print(" fade_in : ");
    Serial.print(fade_in);
    Serial.print(" ");
    Serial.print(" on : ");
    Serial.print(on);
    Serial.print(" ");
    Serial.print(" off : ");
    Serial.print(off);
    Serial.print(" fade_out : ");
    Serial.print(fade_out);
    Serial.println(" ");
#endif
} // eeprom_read

void eeprom_write()
{
    int old_h = prefs.getUInt("t_h_on", 0);
    if (time_on.Hour() != old_h)
    {
        prefs.putUInt("t_h_on", time_on.Hour());
    }

    int old_m = prefs.getUInt("t_m_on", 0);
    if (time_on.Minute() != old_m)
    {
        prefs.putUInt("t_m_on", time_on.Minute());
    }

    int old_hf = prefs.getUInt("t_h_off", 0);
    if (time_off.Hour() != old_hf)
    {
        prefs.putUInt("t_h_off", time_off.Hour());
    }

    int old_mf = prefs.getUInt("t_m_off", 0);
    if (time_off.Minute() != old_mf)
    {
        prefs.putUInt("t_m_off", time_off.Minute());
    }

    int old_fi = prefs.getUInt("fade_in", 0);
    if (fade_in != old_fi)
    {
        prefs.putUInt("fade_in", fade_in);
    }

    int old_o = prefs.getUInt("on", 0);
    if (on != old_o)
    {
        prefs.putUInt("on", on);
    }

    int old_f = prefs.getUInt("off", 0);
    if (off != old_f)
    {
        prefs.putUInt("off", off);
    }

    int old_fo = prefs.getUInt("fade_out", 0);
    if (fade_out != old_fo)
    {
        prefs.putUInt("fade_off", fade_out);
    }

    int old_d1 = prefs.getBool("d1", 0);
    if (D_W[1] != old_d1)
    {
        prefs.putBool("d1", D_W[1]);
    }

    int old_d2 = prefs.getBool("d2", 0);
    if (D_W[2] != old_d2)
    {
        prefs.putBool("d2", D_W[2]);
    }

    int old_d3 = prefs.getBool("d3", 0);
    if (D_W[3] != old_d3)
    {
        prefs.putBool("d3", D_W[3]);
    }

    int old_d4 = prefs.getBool("d4", 0);
    if (D_W[4] != old_d4)
    {
        prefs.putBool("d4", D_W[4]);
    }

    int old_d5 = prefs.getBool("d5", 0);
    if (D_W[5] != old_d5)
    {
        prefs.putBool("d5", D_W[5]);
    }

    int old_d6 = prefs.getBool("d6", 0);
    if (D_W[6] != old_d6)
    {
        prefs.putBool("d6", D_W[6]);
    }

    int old_d7 = prefs.getBool("d7", 0);
    if (D_W[7] != old_d7)
    {
        prefs.putBool("d7", D_W[7]);
    }

#ifdef DEBUG
    Serial.println("EEPROM WRITE");
    Serial.print(" fade_in : ");
    Serial.print(fade_in);
    Serial.print(" ");
    Serial.print(" on : ");
    Serial.print(on);
    Serial.print(" ");
    Serial.print(" off : ");
    Serial.print(off);
    Serial.print(" fade_out : ");
    Serial.print(fade_out);
    Serial.println(" ");

#endif
} // eeprom_write

void load_spec()
{
    eeprom_read();
    for (int i = 0; i < MAX_CLIENT; i++)
    {
        if (list[i])
        {
            webSocket.sendTXT(i, "d1/" + String(D_W[1]));
            webSocket.sendTXT(i, "d2/" + String(D_W[2]));
            webSocket.sendTXT(i, "d3/" + String(D_W[3]));
            webSocket.sendTXT(i, "d4/" + String(D_W[4]));
            webSocket.sendTXT(i, "d5/" + String(D_W[5]));
            webSocket.sendTXT(i, "d6/" + String(D_W[6]));
            webSocket.sendTXT(i, "d7/" + String(D_W[7]));
            webSocket.sendTXT(i, "co/" + String(lround(time_on.Hour())) + ":" + String(lround(time_on.Minute())));
            webSocket.sendTXT(i, "cf/" + String(lround(time_off.Hour())) + ":" + String(lround(time_off.Minute())));
            webSocket.sendTXT(i, "bb:" + String(lround(fade_in)));
            webSocket.sendTXT(i, "bd:" + String(lround(on / 1000)));
            webSocket.sendTXT(i, "be:" + String(lround(off / 1000)));
            webSocket.sendTXT(i, "bf:" + String(lround(fade_out)));
        }

    } // for client

} // load_spec

void save_spec()
{
    eeprom_write();

    btn = false;
    start = true;
    WiFi.mode(WIFI_OFF);
    cycle = true;
    // pwm_loop();
} // save_spec

void init_eeprom()
{
    eeprom_read();
} // init_eeprom()

//////////////////////////////////////////srv_handle_set////////////////////////////////////////
void srv_handle_set()
{
    for (uint8_t i = 0; i < server.args(); i++)
    {

        //////////////////////////////////////////setting html///////////////////////////////////////////
        if (server.argName(i) == "mem")
        {
            int LMem = (uint8_t)strtol(server.arg(i).c_str(), NULL, 10);
#ifdef DEBUGSPEC
            Serial.print("mem=");
            Serial.println(LMem);
#endif

            if (LMem == 0)
            {
                load_spec();
            } // if(Mem==0){

            if (LMem == 1)
            {
                save_spec();
            } // if(Mem==1){
        }     // serveur mem

        ////////////////////// SET CLOCK
        if (server.argName(i) == "clock")
        {
            uint32_t clock = strtoull(server.arg(i).c_str(), NULL, 10);
            Serial.print("Clock: ");
            Serial.println(clock);

            RtcDateTime newClock;
            newClock.InitWithUnix32Time(clock);
            printDateTime(newClock);

            Rtc.SetDateTime(newClock);
        }

    } // serveur args
    server.send(200, "text/plain", "OK");
} // srv_handle_set()

#endif