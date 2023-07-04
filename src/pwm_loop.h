#ifndef pwm_loop_h
#define pwm_loop_h

void pwm_loop()
{
    bool fade_clock;
    unsigned long currentMillis = millis();

    if (cycle)
    {
        previousMillis = currentMillis;
        cycle = false;
    } // if (cycle)

    onboard_led.on = millis() % 2000 < 1000;
    onboard_led.update();

    check_btn();
    if (!f_i && !p)
    {
        f_i = true;
#ifdef DEBUG
        RtcDateTime now = Rtc.GetDateTime();
        printDateTime(now);
        Serial.println(" ");
        Serial.print(" f_i = ");
        Serial.print(f_i);
        Serial.print(" at ");
        Serial.println(currentMillis);
#endif
    } // if (!f_i[d] && !p[d] && currentMillis - previousMillis > (d + 1) * decalage)

    if (f_i)
    {
        if (fade_in != 0)
        {
            fade_clock = millis() % fade_in < 1;
            // fade_clock = true;
            if (fade_clock && f_i)
            {
                value += increm;
            }
            if (value > High_value)
            {
                value = High_value;
                f_i = false;
                p = true;
                currentp = currentMillis;

#ifdef DEBUG
                Serial.print("fade_in  currentp at ");
                Serial.println(currentp);
#endif
            }
        } // if (fade_in > 0)
        else if (fade_in <= 0)
        {
            value = High_value;
            f_i = false;
            p = true;
            currentp = currentMillis;

#ifdef DEBUG
            Serial.print("in cut currentp at ");
            Serial.println(currentp);
#endif
        } // else if (fade_in <= 0)
    }     // if (f_i[d])

    if (!f_o && !n && p && currentMillis - currentp > on)
    {
        f_o = true;
#ifdef DEBUG
        Serial.print(" f_o = ");
        Serial.print(f_o);
        Serial.print(" at ");
        Serial.println(currentMillis);
#endif
    } //(!p[FOR_PWM_CHANNELS] && !n[d] && p[d] && currentMillis - currentp[d] > on)

    if (f_o)
    {
        if (fade_out != 0)
        {
            fade_clock = millis() % fade_out < 1;
            if (fade_clock && f_o)
            {
                value -= increm;
            }
            if (value < 0)
            {
                value = 0;
                f_o = false;
                n = true;
                currentp = currentMillis;

#ifdef DEBUG
                Serial.print("fade_out  currentp at ");
                Serial.println(currentp);
#endif
            }
        } // if (fade_out != 0)
        else if (fade_out <= 0)
        {
            value = 0;
            f_o = false;
            n = true;
            currentp = currentMillis;

#ifdef DEBUG
            Serial.print("out cut currentp at ");
            Serial.println(currentp);
#endif
        } // else if (fade_out <= 0)
    }     // if (f_i[d])

    if (!p && n)
    {
        p = true;
        currentp = currentMillis;
#ifdef DEBUG
        Serial.print("currentp at ");
        Serial.println(currentp);
#endif
    }

    if (p && n && currentMillis - currentp > off)
    {
        previousMillis = currentMillis;

        f_i = false;
        f_o = false;
        n = false;
        p = false;

    } // if (p && n && currentMillis - currentp > off)

    ledcWrite(0, value);

    check_btn();
}

#endif