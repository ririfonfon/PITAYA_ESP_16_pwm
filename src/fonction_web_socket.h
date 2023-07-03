#ifndef fonction_web_socket_h
#define fonction_web_socket_h

#include "rtc_clock.h"

//////////////////////////////////////////websocket///////////////////////////////////////////////
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t lenght)
{
    IPAddress client_ip = webSocket.remoteIP(num);

    switch (type)
    {
    case WStype_DISCONNECTED:
        clientn -= 1;
        list[num] = false;

#ifdef DEBUG
        Serial.print(" nombre de clients : ");
        Serial.print(clientn);
        Serial.printf(" [%u] Disconnected \n", num);
#endif
        break;

    case WStype_CONNECTED:
    {
        clientn += 1;
        list[num] = true;

#ifdef DEBUG
        Serial.print(" nombre de clients : ");
        Serial.print(clientn);
        Serial.printf(" [%u] Connected from %d.%d.%d.%d url: %s\n", num, client_ip[0], client_ip[1], client_ip[2], client_ip[3], payload);
#endif
    }
    break;

    case WStype_TEXT:
    {
        //  is the start for this data

        if (payload[0] == 'b')
        {
#ifdef DEBUGsocket
            Serial.println("payload[0] == 'b'");
#endif
            if (payload[1] == 'b')
            {
                char *pEnd;
                fade_in = (strtol((const char *)&payload[2], &pEnd, 8)); // 2.6
#ifdef DEBUG
                Serial.println(" fade_in : ");
                Serial.print(fade_in);
#endif
            } // b
            else if (payload[1] == 'd')
            {
                char *pEnd;
                on = (strtol((const char *)&payload[2], &pEnd, 8)) * 1000;
#ifdef DEBUG
                Serial.println(" on : ");
                Serial.print(on);
#endif
            } // d
            else if (payload[1] == 'e')
            {
                char *pEnd;
                off = (strtol((const char *)&payload[2], &pEnd, 8)) * 1000;
#ifdef DEBUG
                Serial.println(" off : ");
                Serial.print(off);
#endif
            } // e
            else if (payload[1] == 'f')
            {
                char *pEnd;
                fade_out = (strtol((const char *)&payload[2], &pEnd, 8)); // 2.6
#ifdef DEBUG
                Serial.println(" fade_out : ");
                Serial.print(fade_out);
#endif
            } // e

        } // payload[0] == b

        if (payload[0] == 'c')
        {
            if (payload[1] == 'o')
            {
                int hou = ((payload[3] - '0') * 10) + (payload[4] - '0' );
                int minu = ((payload[6] - '0') * 10) + (payload[7] - '0');
                RtcDateTime time_on(0, 0, 0, hou, minu, 0);

#ifdef DEBUG
                Serial.print("time on  ");
                printDateTime(time_on);
                Serial.println(" ");
#endif
            }
            else if (payload[1] = 'f')
            {
                int hou = ((payload[3] - '0') * 10) + (payload[4] - '0');
                int minu = ((payload[6] - '0') * 10) + (payload[7] - '0');
                RtcDateTime time_off(0, 0, 0, hou, minu, 0);
#ifdef DEBUG
                Serial.print("time off  ");
                printDateTime(time_off);
                Serial.println(" ");
#endif
            }

        } // payload[0] == c

        if (payload[0] == 'd')
        {
            if (payload[1] == '1')
            {
                if (payload[3] == 'f')
                {
                    D_W[0] = true;
                }
                else
                {
                    D_W[0] = false;
                }
            }
            else if (payload[1] == '2')
            {
                if (payload[3] == 'f')
                {
                    D_W[1] = true;
                }
                else
                {
                    D_W[1] = false;
                }
            }
            else if (payload[1] == '3')
            {
                if (payload[3] == 'f')
                {
                    D_W[2] = true;
                }
                else
                {
                    D_W[2] = false;
                }
            }
            else if (payload[1] == '4')
            {
                if (payload[3] == 'f')
                {
                    D_W[3] = true;
                }
                else
                {
                    D_W[3] = false;
                }
            }
            else if (payload[1] == '5')
            {
                if (payload[3] == 'f')
                {
                    D_W[4] = true;
                }
                else
                {
                    D_W[4] = false;
                }
            }
            else if (payload[1] == '6')
            {
                if (payload[3] == 'f')
                {
                    D_W[5] = true;
                }
                else
                {
                    D_W[5] = false;
                }
            }
            else if (payload[1] == '7')
            {
                if (payload[3] == 'f')
                {
                    D_W[6] = true;
                }
                else
                {
                    D_W[6] = false;
                }
            }

        } // payload[0] == d

    } // WStype_TEXT:
    break;
    } // type
} // web socket

#endif