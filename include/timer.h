#ifndef timer_h
#define timer_h

#include "button.h"

class timer{
private:
    cback_type on_period_elapsed_cback;
    unsigned long period;
    unsigned long current_time;
    bool timer_running;
    
public:
    timer(){}
    void set_timer(unsigned long p, cback_type on_period_elapsed)
    {
        period = p; 
        on_period_elapsed_cback = on_period_elapsed; 
        timer_running = true;
        current_time = millis();
    }
    void stop_timer(){
        timer_running = false;
    }
    void update(){
        if(timer_running){
            if(millis() - current_time >= period){
                current_time = millis();
                on_period_elapsed_cback();
            }
        }
    }

    unsigned long get_time_left(){
        if(timer_running) return period - (millis() - current_time);
        else return 0;
    }
    long get_elapsed(){
        if(timer_running) return (millis() - current_time);
        else return -1;
    }
};

#endif