/*
 * File:          my_controller2.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/motor.h>, etc.
 */
#include <webots/robot.h>
#include <webots/motor.h>

/*
 * You may want to add macros here.
 */
#define TIME_STEP 64

WbDeviceTag motor[3]; // Declare an array of WbDeviceTag for motors
float motor_speed_set[3] = {0.0, 0.0, 0.0}; // Initialize motor speeds to zero
/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */

char robot_contrail(void)
{
  for(int i=0; i<3; i++) {
    wb_motor_set_velocity(motor[i], motor_speed_set[i]); // Set motor speeds

  }
  return 1;
}

 char robot_turn(char direction)
 {
  for(int i=0;i<3;i++){
    motor_speed_set[i]=direction * 1.0; // Set speed based on direction
  }
  robot_contrail();
  return 1;
 }



int main(int argc, char **argv) {
  /* necessary to initialize webots stuff */
  wb_robot_init();
  char motor_names[3][10] = {"motor_F",
                              "motor_BL",
                              "motor_BR"};
  for(int i = 0; i < 3; i++) {
    motor[i] = wb_robot_get_device(motor_names[i]);
    wb_motor_set_position(motor[i], INFINITY); // Set to infinity for velocity control
    wb_motor_set_velocity(motor[i], 0.0); // Initialize velocity to zero
  }

  /*
   * You should declare here WbDeviceTag variables for storing
   * robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */

  /* main loop
   * Perform simulation steps of TIME_STEP milliseconds
   * and leave the loop when the simulation is over
   */
  while (wb_robot_step(TIME_STEP) != -1) {
    /*
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */
      robot_turn(1); // Example to turn the robot in one direction
    /* Process sensor data here */

    /*
     * Enter here functions to send actuator commands, like:
     * wb_motor_set_position(my_actuator, 10.0);
     */
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
