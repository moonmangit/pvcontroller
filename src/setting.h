#include "LedStripe.h"
#include <List.h>
#include <Motor.h>
#include <ParenthLogger.h>
#include <Routine.h>
#include <RTClib.h>
#include <SPI.h>
using namespace m2;

//#**********************************
//#*            HELPER              *
//#**********************************
#define EQ_DATE(dt) dt = DateTime(2000, 1, 1, dt.hour(), dt.minute(), dt.second())

//#**********************************
//#*             TYPE               *
//#**********************************
typedef struct AxisTask
{
    DateTime dt;
    mtask_t motorTask;
} atask_t;
struct TaskController
{
    List<atask_t> tasks;
    Iterator<atask_t> itr;
    DateTime begin;
    DateTime end;
};

//#**********************************
//#*             PIN                *
//#**********************************
#define MOTOR_PIN_A 7
#define MOTOR_PIN_B 8

//#**********************************
//#*             TASK               *
//#**********************************
const atask_t TASKS[] = {
    // need manual sort
    {DateTime(__DATE__, "06:30:00"), {backward, TIME2MS(0, 1, 40)}},
    {DateTime(__DATE__, "09:00:00"), {forward, TIME2MS(0, 0, 25)}},
    {DateTime(__DATE__, "12:00:00"), {forward, TIME2MS(0, 0, 25)}},
    {DateTime(__DATE__, "14:00:00"), {forward, TIME2MS(0, 0, 25)}},
    {DateTime(__DATE__, "16:00:00"), {forward, TIME2MS(0, 0, 25)}},
    {DateTime(__DATE__, "18:00:00"), {backward, TIME2MS(0, 0, 50)}},
};