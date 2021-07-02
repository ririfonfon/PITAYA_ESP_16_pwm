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
    } //if (cycle)

    onboard_led.on = millis() % 2000 < 1000;
    onboard_led.update();

    for (int d = 0; d < FOR_PWM_CHANNELS; d++)
    {
        check_btn();
        if (!f[d] && !p[d] && currentMillis - previousMillis > (d + 1) * decalage)
        {
            f[d] = true;
#ifdef DEBUG
            Serial.print(" f[");
            Serial.print(d);
            Serial.print("] = ");
            Serial.print(f[d]);
            Serial.print(" at ");
            Serial.println(currentMillis);
#endif
        } //if (!f[d] && !p[d] && currentMillis - previousMillis > (d + 1) * decalage)if (!f[d] && !p[d] && currentMillis - previousMillis > (d + 1) * decalage)
    
        if (f[d])
        {
            fade_clock = millis() % fade < 1;
            if (fade_clock && f[d])
            {
                value[d] += 1;
            }
            if (value[d] > 65535)
            {
                value[d] = 65535;
                f[d] = false;
                p[d] = true;
                currentp[d] = currentMillis;

#ifdef DEBUG
                Serial.print(" currentp[");
                Serial.print(d);
                Serial.print("] at ");
                Serial.println(currentp[d]);
#endif
            }
        } //if (f[d])
    
        if (!p[FOR_PWM_CHANNELS] && !n[d] && p[d] && currentMillis - currentp[d] > on)
        {
            value[d] = 0;
            n[d] = true;
#ifdef DEBUG
            Serial.print(" value[");
            Serial.print(d);
            Serial.print("] = 0 at ");
            Serial.println(currentMillis);
#endif
        } //if (!n[d] && p[d] && currentMillis - currentp[d] > on)

        if (!p[FOR_PWM_CHANNELS] && n[FOR_PWM_CHANNELS - 1])
        {
            p[FOR_PWM_CHANNELS] = true;
            currentp[FOR_PWM_CHANNELS] = currentMillis;
#ifdef DEBUG
            Serial.print("currentp[");
            Serial.print(FOR_PWM_CHANNELS);
            Serial.print("] at ");
            Serial.println(currentp[FOR_PWM_CHANNELS]);
#endif
        }
    
        if (p[FOR_PWM_CHANNELS] && currentMillis - currentp[FOR_PWM_CHANNELS] > off)
        {
            previousMillis = currentMillis;
            for (int q = 0; q < FOR_PWM_CHANNELS; q++)
            {
                p[q] = false;
                f[q] = false;
                n[q] = false;
                p[FOR_PWM_CHANNELS] = false;
            }
            rnd();
        } //if (p[FOR_PWM_CHANNELS] && currentMillis - currentp[FOR_PWM_CHANNELS] > off)
    }     //for (int d = 0; d < FOR_PWM_CHANNELS; d++)

    for (int d = 0; d < FOR_PWM_CHANNELS; d++)
    {
        ledcWrite(d, value[ref[d]]);
    } //for(int d=0; d>FOR_PWM_CHANNELS;d++)
    check_btn();
}

#endif