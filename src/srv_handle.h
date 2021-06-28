#ifndef srv_handle_h
#define srv_handle_h

#include <EEPROM.h>
#define EEPROM_SIZE 64

void eeprom_read()
{
    FOR_PWM_CHANNELS = EEPROM.read(1);
    fade = EEPROM.read(2);
    decalage = EEPROM.read(3);
    on = EEPROM.read(4);
    off = EEPROM.read(5);

#ifdef DEBUG
    Serial.println("EEPROM READ");
#endif
} //eeprom_read

void eeprom_write()
{
    EEPROM.write(1, FOR_PWM_CHANNELS);
    EEPROM.write(2, fade);
    EEPROM.write(3, decalage);
    EEPROM.write(4, on);
    EEPROM.write(5, off);

    EEPROM.write(62, 'O');
    EEPROM.write(63, 'K');
    EEPROM.commit();

#ifdef DEBUG
    Serial.println("EEPROM WRITE");
#endif
} //eeprom_write

void load_spec()
{
    eeprom_read();
    for (int i = 0; i < MAX_CLIENT; i++)
    {
        if (list[i])
        {
            webSocket.sendTXT(i, "ba:" + String(lround(FOR_PWM_CHANNELS)));
            webSocket.sendTXT(i, "bb:" + String(lround(fade)));
            webSocket.sendTXT(i, "bc:" + String(lround(decalage)));

            webSocket.sendTXT(i, "bd:" + String(lround(on)));
            webSocket.sendTXT(i, "be:" + String(lround(off)));
        }

    } // for client

} //load_spec

void save_spec()
{
    eeprom_write();

    btn = false;
    start = true;
    WiFi.mode(WIFI_OFF);
} //save_spec

void init_eeprom()
{
    if (EEPROM.read(62) != 'O' || EEPROM.read(63) != 'K')
    {

#ifdef DEBUG
        Serial.println("failed to initialise EEPROM");
        Serial.println("Formate EEPROM");
#endif

        for (int i = 0; i < EEPROM_SIZE; i++)
        {
            EEPROM.write(i, '\0');
            if (i % 50 == 0)
                delay(100);
        }
#ifdef DEBUG
        Serial.println("EEPROM content cleared!");
#endif

        eeprom_write();

    } //(EEPROM.read(62) != 'O' || EEPROM.read(63) != 'K')

    if (EEPROM.read(62) == 'O' && EEPROM.read(63) == 'K')
    {
        eeprom_read();
    } //(EEPROM.read(62) == 'O' && EEPROM.read(63) == 'K')
} //init_eeprom()

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
            } //if(Mem==0){

            if (LMem == 1)
            {
                save_spec();
            } //if(Mem==1){
        }     //serveur mem

    } //serveur args
    server.send(200, "text/plain", "OK");
} //srv_handle_set()

#endif