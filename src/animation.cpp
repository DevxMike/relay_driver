#include "animation.h"
#include "system.h"

enum{
    animation_init = 0,
    animation_prepare_buffer,
    animation_set_led
};

constexpr uint8_t diodes_per_circle = 24;

void animation_manager::main(){
    static uint8_t state = animation_init;
    static long t1, t2, t3, t4;
    uint8_t d1, d2, d3, d4;
    auto r = animation_manager::strip1.Color(255, 0, 0);
    auto g = animation_manager::strip1.Color(0, 255, 0);
    auto y = animation_manager::strip1.Color(255, 255, 0);
    auto off = animation_manager::strip1.Color(0, 0, 0);

    switch(state){
        case animation_init:
            animation_timer.set_timer(animation_timer_period, on_elapsed_handler);
            state = animation_prepare_buffer;
        break;

        case animation_prepare_buffer:
            t1 = buffer[0];
            t2 = buffer[1];
            t3 = buffer[2];
            t4 = buffer[3];

            

            for (int i = 0; i < 54; ++i){
                if (i >= 0 && i <= 23) // green button ring
                {
                    if(t1 == -1){
                        animation_manager::strip1.setPixelColor(i, g);
                    }
                    else{
                        d1 = (t1 / 1000) * (diodes_per_circle / (timer_period / 1000));

                        if(i < d1){
                            animation_manager::strip1.setPixelColor(i, g);
                        }
                        else{
                            animation_manager::strip1.setPixelColor(i, off);
                        }
                    }
                    if(t3 == -1){
                        animation_manager::strip2.setPixelColor(i, g);
                    }
                    else{
                        d3 = (t3 / 1000) * (diodes_per_circle / (timer_period/ 1000));

                        if (i < d3)
                        {
                            animation_manager::strip2.setPixelColor(i, g);
                        }
                        else
                        {
                            animation_manager::strip2.setPixelColor(i, off);
                        }
                    }
                }
                else if (i >= 24 && i < 30) // led strip
                {
                    if(button_callbacks::is_user_1_ready()){
                        animation_manager::strip1.setPixelColor(i, g);
                    }
                    else{
                        animation_manager::strip1.setPixelColor(i, r);
                    }

                    if(button_callbacks::is_user_2_ready()){
                        animation_manager::strip2.setPixelColor(i, g);
                    }
                    else{
                        animation_manager::strip2.setPixelColor(i, r);
                    }
                }
                else // yellow button ring
                {
                    if(t2 == -1){
                        animation_manager::strip1.setPixelColor(i, g);
                    }
                    else{
                        d2 = (t2 / 1000) * (diodes_per_circle / (timer_period/ 1000));

                        if (i < d2 + 30)
                        {
                            animation_manager::strip1.setPixelColor(i, g);
                        }
                        else
                        {
                            animation_manager::strip1.setPixelColor(i, off);
                        }
                    }
                    if(t4 == -1){
                        animation_manager::strip2.setPixelColor(i, g);  
                    }
                    else{
                        d4 = (t4 / 1000) * (diodes_per_circle / (timer_period / 1000));

                        if (i < d4 + 30)
                        {
                            animation_manager::strip2.setPixelColor(i, g);
                        }
                        else
                        {
                            animation_manager::strip2.setPixelColor(i, off);
                        }
                    }
                }
            }
            state = animation_set_led;
        break;

        case animation_set_led:
        animation_manager::strip1.show();
        animation_manager::strip2.show();
        state = animation_prepare_buffer;
        break;
    }

    animation_timer.update();
}