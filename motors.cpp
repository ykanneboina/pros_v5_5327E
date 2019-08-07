#include "main.h"
using namespace pros;

//Base motors
pros::Motor basefr(14, E_MOTOR_GEARSET_18, true);
pros::Motor basefl(13, E_MOTOR_GEARSET_18, true);
pros::Motor basebr(15, E_MOTOR_GEARSET_18, true);
pros::Motor basebl(18, E_MOTOR_GEARSET_18, true);

//angler & lift
pros::Motor ang(9, E_MOTOR_GEARSET_18, true);
pros::Motor lift(7, E_MOTOR_GEARSET_18, true);

//rollers
pros::Motor rolllef(1, E_MOTOR_GEARSET_18, true);
pros::Motor rollrig(2, E_MOTOR_GEARSET_18, true);

pros::Controller master (CONTROLLER_MASTER);
