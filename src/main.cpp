#include "setting.h"

DateTime cdt(DateTime(__DATE__, "00:00:00"));
DateTime oldCdt;
RTC_DS3231 rtc;
LedStripe leds(9, 12, 11, 10, 9, 6, 5, 4, 3, 2);
Motor motor(MOTOR_PIN_A, MOTOR_PIN_B);
ParenthLogger plog;
Routine *doCheckTask;
Routine *doUpdateTime;
TaskController taskController;

void logicCheckTask(void);
void logicUpdateTime(void);

void helperDriveMotor(Motor &motor, mtask_t motorTask);
void helperPrintDateTime(DateTime &dt);
void helperPrintTask(atask_t &task);

//#**********************************
//#*            SETUP               *
//#**********************************

void setup()
{
    { // Serial
        Serial.begin(9600);
        plog("\n> system start.");
    }
    { // Clock DS3231
        if (!rtc.begin())
        {
            while (1)
            {
                delay(100);
            }
        }
    }
    { // Led
        leds.startup();
        leds.flashs(10, 100, 50);
    }
    { // Motor
        motor.startup();
    }
    { // Routine
        doUpdateTime = new Routine(1000, logicUpdateTime);
        doCheckTask = new Routine(1000, logicCheckTask);
    }
    { // Task
        // 1. add task and eq date
        for (size_t i = 0; i < sizeof(TASKS) / sizeof(TASKS[0]); i++)
        {
            taskController.tasks.add_back(TASKS[i]);
        }
        auto itr = taskController.tasks.iterate_entire();
        do
        {
            EQ_DATE((*itr).dt);
        } while (itr++);
        // 2. set begin and end time
        taskController.begin = taskController.tasks.read_front().dt;
        taskController.end = taskController.tasks.read_back().dt;
        // 3. set itr
        taskController.itr = taskController.tasks.iterate_entire();
    }
    { // ? Summary

        { // print work time
            plog("\n> work time : ");
            helperPrintDateTime(taskController.begin);
            plog(" --- ");
            helperPrintDateTime(taskController.end);
        }
        { // print tasks
            plog("\n> task table : ");
            auto itr = taskController.tasks.iterate_entire();
            do
            {
                plog.useFormat("\n[%i] ").f(itr.index());
                helperPrintTask((*itr));
            } while (itr++);
        }
        plog("\n> loop start");
    }
}

void loop()
{
    { // Routine
        doUpdateTime->handle();
        doCheckTask->handle();
    }
}

//#**********************************
//#*         DEFINITION             *
//#**********************************
void logicUpdateTime()
{
    // cdt = cdt + TimeSpan(600); // simulation clock
    cdt = rtc.now(); // real clock
    EQ_DATE(cdt);
    plog("\ncurrent-time: ");
    helperPrintDateTime(cdt);
    plog(" next ");
    helperPrintDateTime((*taskController.itr).dt);
}
void logicCheckTask()
{
    if (oldCdt == cdt)
        return;
    if (cdt > taskController.begin && cdt <= taskController.end && cdt >= (*taskController.itr).dt)
    {
        oldCdt = cdt;
        mtask_t mtask = (*taskController.itr).motorTask;
        // drive
        // /*MOCK*/ plog("\n[MOCK] driving... ")(mtask.direction)(" for ")(mtask.duration)(" ms");
        /*REAL*/ helperDriveMotor(motor, mtask);
        // update itr
        if (!taskController.itr++)
        {
            taskController.itr = taskController.tasks.iterate_entire();
        }
        leds.writes(LOW, 9);
        leds.writes(HIGH, map(taskController.itr.index(), 0, taskController.tasks.len() - 1, 0, 9));
    }
}

void helperDriveMotor(Motor &motor, mtask_t motorTask)
{
    if (motorTask.direction == MOTORDIR::backward)
    {
        motor.backward(motorTask.duration);
    }
    else if (motorTask.direction == MOTORDIR::forward)
    {
        motor.forward(motorTask.duration);
    }
    else
    {
        motor.block(motorTask.duration);
    }
}
void helperPrintDateTime(DateTime &dt)
{
    char buffer[] = "DD/MM/YYYY@hh:mm:ss";
    dt.toString(buffer);
    plog(buffer, ansi_style::green_italic);
}
void helperPrintTask(atask_t &task)
{
    plog("at ");
    helperPrintDateTime(task.dt);
    const char *dirString[] = {"backward", "stop", "forward"};
    plog(" do ")(dirString[task.motorTask.direction + 1], ansi_style::green_italic)(" for ")(task.motorTask.duration, ansi_style::green_italic)(" ms.");
}

// EOF