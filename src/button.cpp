#include "button.h"

button::button(uint8_t _pin) : state{button_state::waiting_for_push}, tick_holder{0},
                                                    pin{_pin}
{

}

bool button::read_button()
{
    bool state = !digitalRead(this->pin);

    return state;
}

void push_button::update_button()
{
    auto state = get_state();

    switch (state)
    {
    case button_state::waiting_for_push:
        if (read_button())
        {
            set_ticks(millis());
            state = button_state::debouncing;
        }
        break;

    case button_state::debouncing:
        if (millis() - get_ticks() > 30)
        {
            callback();
            state = button_state::waiting_for_release;
        }
        break;

    case button_state::waiting_for_release:
        if (!read_button())
        {
            state = button_state::waiting_for_push;
        }
        break;
    }
    set_state(state);
    // std::cout << "Push button update\n";
}

void hold_push_button::update_button()
{
    auto state = get_state();

    switch (state)
    {
    case button_state::waiting_for_push:
        if (read_button())
        {
            set_ticks(millis());
            state = button_state::debouncing;
        }
        break;

    case button_state::debouncing:
        if (millis() - get_ticks() > 30)
        {
            callback();
            set_ticks(millis());
            state = button_state::waiting_longer_press;
        }
        break;

    case button_state::waiting_longer_press:
        if (read_button() && (millis() - get_ticks() > 3000))
        { // and ticks greater than
            set_ticks(millis());

            state = button_state::waiting_for_release;
        }
        else if (!read_button())
        {
            state = button_state::waiting_for_push;
        }
        break;

    case button_state::waiting_for_release:
        if (!read_button())
        {
            state = button_state::waiting_for_push;
        }
        else if (read_button() && (millis() - get_ticks() > 100))
        {
            long_press_callback();
            set_ticks(millis());
        }

        break;
    }

    set_state(state);
}

void button_manager::main()
{
    for(uint8_t i = 0; i < interface_size; ++i){
        keyboard[i]->update_button();
    }
}