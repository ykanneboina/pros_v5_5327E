#include "main.h"
#include "motor.h"
//#include "motors.cpp"
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void drive(int fr, int fl, int br, int bl){
  basefr.move_velocity(fr);
  basefl.move_velocity(fl);
  basebr.move_velocity(br);
  basebl.move_velocity(bl);
}



void pidloop(int target){
  double fspeed = lift.get_actual_velocity();
  double rpm = fspeed*(15);
  double error = target - rpm;
  double errorprev = error;
  double errorT =+  error;
  double proportion = error/20;
  double kp = 0.2;
  double ki = 0.05;
  double kd = 0.5;
  double derivative = (error - errorprev)/ 20;
  double integral = integral + (error * 1);
  double pid = proportion*kp + integral*ki + derivative*kd;
  double velocity = pid*94;
  lift.move_velocity(velocity);

}

/*
//PDF VERSION
void myPID(int target){
  while(true){
    double rpm = (lift.get_actual_velocity()) * 15;
    double error = target - rpm;
    double integral = integral + error;
    double kI = error * 1;
    double power = ((error *kP) + (integral *kI));
    pros::delay(15);
  }
}
*/
/*
int inchToTicks (float inch){
  int ticks;
  ticks = inch * 99.82198;
  return ticks;
}
*/
/*
void pid(int target, float waitTime){
  float Kp = 0.2;
  int error;
  int proportion;
  int finalPower;
  bool timerBool = true;
  ClearTimer(T1);
  while(time1[T1]<waitTime){
    error = target - (lift.get_actual_velocity());
    proportion = Kp*error;
    finalPower = proportion; //proportion +deivative+integral
    lift.move_velocity(finalPower);
    pros::delay(40);

    if(error < 30){
      timerBool = false;
    }
    if(timerBool){
      ClearTimer(T1);
    }
  }
  lift.move_velocity(0);
}
*/


void opcontrol() {
  //pid(12);
/*
  while (true){
    basefr.move_velocity(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
    basefl.move_velocity(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
    basebr.move_velocity(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
    basebl.move_velocity(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
*/

 while(true)
 {
   while (master.get_digital(DIGITAL_R1) >= 1)
   {
     ang.move_velocity(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
   }

   int opposite = (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) * -1;
   drive(pros::E_CONTROLLER_ANALOG_RIGHT_Y,opposite, pros::E_CONTROLLER_ANALOG_RIGHT_Y, opposite);
     /*basefr.move_velocity(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
     basefl.move_velocity(opposite);
     basebr.move_velocity(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
     basebl.move_velocity(opposite); */
 }

// CODE FOR x AND y BUTTONS on rollers
    if (master.get_digital(DIGITAL_X) >= 1) { //if you press x, the motor will turn
    rolllef.move_voltage(12000);
    rollrig.move_voltage(12000);
    }
    else if(master.get_digital(DIGITAL_Y)>= 1){ //if you press y the motor will turn the opposite direction
      rolllef.move_voltage(-12000);
      rollrig.move_voltage(-12000);
    }
    else { //if you release or don't press any button the motor will stop
      rolllef.move_voltage(0);
      rollrig.move_voltage(0);
    }

//CODE FOR A and B BUTTONS for angler
    if (master.get_digital(DIGITAL_A) >= 1) {
    ang.move_voltage(12000);
    }
    else if(master.get_digital(DIGITAL_B)>= 1){
      ang.move_voltage(-12000);
    }
    else {
      ang.move_voltage(0);
    }

//CODE FOR up and down BUTTONS for lift

    if (master.get_digital(DIGITAL_UP) >= 1){
      pidloop(127);
    }
    else if(master.get_digital(DIGITAL_DOWN)>= 1){
      pidloop(-127);
    }

    /*
    if (master.get_digital(DIGITAL_UP) >= 1) {
    lift.move_voltage(12000);
    }
    else if(master.get_digital(DIGITAL_DOWN)>= 1){
      lift.move_voltage(-12000);
    }
    */
    else {
      lift.move_voltage(0);
    }

    pros::delay(2);
  }
