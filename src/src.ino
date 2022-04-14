#include "/root/Development/home_security/src/sensors/task_list.h"


int hard;
void setup() {
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
//Possible serial output for testing
Serial.begin(9600);

    //JOB1
    //Exec, prio, period, periodic, deadl, dead_t, realease
    const struct TimeInfo t_info1 = createTInfo(1, 10, 4, 3, 1, 1, 0);

    //ptr, ptr, interuptable, func_type
    const struct ExecConstraints ex_con1 = createExCons(NULL, NULL, 0, 1);

    const struct Job job1 = createJob(ex_con1, t_info1, 1);

    //JOB2
    const struct TimeInfo t_info2 = createTInfo(1, 10, 1, 1, 2, 0, 0);
    const struct ExecConstraints ex_con2 = createExCons(NULL, NULL, 0, 2);
    const struct Job job2 = createJob(ex_con2, t_info2, 2);

    //job4
    const struct TimeInfo t_info4 = createTInfo(1, 10, 5, 2, 4, 1, 0);
    const struct ExecConstraints ex_con4 = createExCons(NULL, NULL, 0, 4);
    const struct Job job4 = createJob(ex_con4, t_info4, 4);

    //job5
    const struct TimeInfo t_info5 = createTInfo(1, 10, 5, 1, 2, 1, 0);
    const struct ExecConstraints ex_con5 = createExCons(NULL, NULL, 0, 5);
    const struct Job job5 = createJob(ex_con5, t_info5, 5);

    //Setting the instructions for the jobs
    //func_type, func_ptr
    addInstruction(1, temp);
    addInstruction(2, isHeatDanger);
    addInstruction(3, alertHeatDanger);
    addInstruction(4, laser);
    addInstruction(5, isLaserTriped);


    //Zeroing all lists
    zero();
    //Adding the tasks
    addTask(job1, que);
    addTask(job2, que);
    addTask(job4, que);
    addTask(job5, que);

    //chacking if the schudle is feasible
    //printf("Is feasible: %d\n", schedulerFeasibilty());

    //setting the desired algorithms
    algorithm_full = edfFull;
    algorithm_next = edfFull;

    //Making a full jobs schedule from tasks
    fullSchedule();
    hard = 0;

}

void loop() {
    scheduleNext(hard);
    runNext();
}
