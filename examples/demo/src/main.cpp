#include <Arduino.h>
#include <ramp.hpp>
#define MONITOR Serial
#define LED_PIN 5
ramp demo_ramp;
void do_step(int value, void* state) {
    MONITOR.println(value);
    ledcWrite(0,value);
}

void setup() {
    MONITOR.begin(115200);
    delay(1000);
    MONITOR.println("start");
    ledcSetup(0,5000,8);
    ledcAttachPin(LED_PIN,0);
    demo_ramp.on_step(do_step);
}
void loop() {
    if(demo_ramp.done()) {
        if(0==demo_ramp.value()) {
            demo_ramp.begin_range(1,255,1,50);
        } else {
            demo_ramp.begin_range(254,0,1,50);
        }
    }
    demo_ramp.update();
}