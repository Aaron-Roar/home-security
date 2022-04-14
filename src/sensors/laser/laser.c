#include "/root/Development/home_security/src/sensors/laser/laser_sensor.h"

int first_run_laser = 0;
int norm_laser = 0;
int laser_state = 0;

void setLaserState(int laser_value) {
    if(laser_value < (laser_norm/4)) {
        laser_state = 0;
    }
    else if(laser_value < (laser_norm/2)) {
        laser_state = 1;
    }
    else {
        laser_state = 2;
    }


}
void laser() {
    Serial.println("Function Laser!!");
    if(first_run_laser == 0) {
        calibrateLaser();
        first_run_laser = 1;
    }

    int laser_val = readAverageLaser(15);
    setLaserState(laser_val);
    Serial.print("Laser Value: ");
    Serial.println(laser_val);
    Serial.print("Laser State: ");
    Serial.println(laser_state);
}

void updateLed(int new_laser_state) {
    if(new_laser_state == 0) {
        Serial.println("green light");
        //grren Light on
        powerLed(0);
    }
    else if(new_laser_state == 1) {
        Serial.println("yellow light");
        //Yellow Light on
        powerLed(1);
    }
    else {
        Serial.println("red light");
        //Rde light on
        powerLed(2);
    }
}

int previous_laser_state = 0;
void isLaserTriped() {
    Serial.println("Function isLaserTriped!!");
    Serial.println("Laser Tripped\n");
    if(laser_state != previous_laser_state) {
        previous_laser_state = laser_state;
    }
        updateLed(laser_state);
}
