#include "/root/Development/home_security/src/sensors/temperature/temperature.h"

int first_run_temp = 0;

void temp() {
    digitalWrite(10, HIGH);
    delay(100);
    digitalWrite(10, LOW);
    if(first_run_temp == 0) {
        pressure.begin();
        setBasePressure(200);
        first_run_temp = 1;
    }
    current_temperaure = requestAverageTemperature(15);
    Serial.print("Temperature: ");
    Serial.println(current_temperaure);
}

void isHeatDanger() {
    if(current_temperaure > 40) {
        const struct TimeInfo t_info3 = createTInfo(1, 10, 1, 1, 10, 0, 0);
        const struct ExecConstraints ex_con3 = createExCons(NULL, NULL, 0, 3);
        const struct Job job3 = createJob(ex_con3, t_info3, 3);

        addTask(job3, que);
    }
}

void alertHeatDanger() {
    soundAlarm();
    Serial.print("Heat emergency activated\n");

    if(current_temperaure < 25) {
        //remove itself
        stopAlarm();
        removeTask(3);
        Serial.print("Heat emergency removed\n");
    }
}
