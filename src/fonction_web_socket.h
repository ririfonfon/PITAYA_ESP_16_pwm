#ifndef fonction_web_socket_h
#define fonction_web_socket_h

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
                Serial.print(" fade_in : ");
                Serial.print(fade_in);
#endif
            } // b
            else if (payload[1] == 'd')
            {
                char *pEnd;
                on = (strtol((const char *)&payload[2], &pEnd, 8)) * 1000;
#ifdef DEBUG
                Serial.print(" on : ");
                Serial.print(on);
#endif
            } // d
            else if (payload[1] == 'e')
            {
                char *pEnd;
                off = (strtol((const char *)&payload[2], &pEnd, 8)) * 1000;
#ifdef DEBUG
                Serial.print(" off : ");
                Serial.print(off);
#endif
            } // e
            else if (payload[1] == 'f')
            {
                char *pEnd;
                fade_out = (strtol((const char *)&payload[2], &pEnd, 8)); // 2.6
#ifdef DEBUG
                Serial.print(" fade_out : ");
                Serial.print(fade_out);
#endif
            } // e

        } // payload[0] == b

        if (payload[0] == 'c')
        {
            if (payload[1] == 'o')
            {
                time_on = (strtol((const char *)&payload[3], &pEnd, 8)); // on_time
#ifdef DEBUG
                Serial.print(" on_time : ");
                Serial.print(time_on);
#endif
            }
            else if (payload[1] = 'f')
            {
                time_off = (strtol((const char *)&payload[3], &pEnd, 8)); // off_time
#ifdef DEBUG
                Serial.print(" off_time : ");
                Serial.print(time_off);
#endif
            }

        } // payload[0] == c

        if (payload[0] == 'd')
        {
            if (payload[1] == '1')
            {

            }
            else if (payload[1] == '2')
            {
                
            }
            else if (payload[1] == '3')
            {
                
            }
            else if (payload[1] == '4')
            {
                
            }
            else if (payload[1] == '5')
            {
                
            }
            else if (payload[1] == '6')
            {
                
            }
            else if (payload[1] == '7')
            {
                
            }

        } // payload[0] == d

    } // WStype_TEXT:
    break;
    } // type
} // web socket

#endif