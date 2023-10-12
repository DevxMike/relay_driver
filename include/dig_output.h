/*
 * digital_output.h
 *
 *  Created on: Oct 6, 2023
 *      Author: Michael
 */

#ifndef INC_APP_DIGITAL_OUTPUT_H_
#define INC_APP_DIGITAL_OUTPUT_H_

#include "Arduino.h"

class digital_output
{
private:
    uint8_t pin;
    bool state;

public:
    digital_output(uint8_t _pin) : pin{_pin}, state{ false } {}

    void init(){ pinMode(pin, OUTPUT); }

    void write(bool o)
    {
        state = o;

        digitalWrite(pin, state);
    }

    void toggle()
    {
        write(!state);
    }
};

#endif /* INC_APP_DIGITAL_OUTPUT_H_ */
