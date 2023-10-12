#ifndef button_h
#define button_h

#include <Arduino.h>

constexpr uint8_t interface_size = 7;

using cback_type = void (*)();

enum class button_state
{
    waiting_for_push,
    debouncing,
    waiting_for_release,
    waiting_longer_press
};

class button
{
private:
    button_state state;
    unsigned long tick_holder;
    uint8_t pin;

public:
    void init(){ pinMode(pin, INPUT_PULLUP); }
    button(uint8_t _pin);
    bool read_button();
    button_state get_state() { return state; };
    void set_state(button_state s) { state = s; };
    unsigned long get_ticks() { return tick_holder; }
    void set_ticks(unsigned long t) { tick_holder = t; }
    virtual void update_button() = 0;
};

class push_button : public button
{
private:
    cback_type on_btn_pressed;

protected:
    void callback() { on_btn_pressed(); }

public:
    push_button(uint8_t _pin, cback_type cback) : button(_pin), on_btn_pressed{cback} {}
    virtual void update_button();
};

class hold_push_button : public push_button
{
private:
    cback_type long_press_cback;

protected:
    void long_press_callback() { long_press_cback(); }

public:
    hold_push_button(uint8_t _pin, cback_type cback, cback_type lp_cback = nullptr) : push_button(_pin, cback)
    {
        if (lp_cback == nullptr)
        {
            long_press_cback = cback;
        }
        else
        {
            long_press_cback = lp_cback;
        }
    }
    virtual void update_button();
};

class button_manager
{
private:
    static push_button* keyboard[ interface_size ];

public:
    static void main();
};

#endif
