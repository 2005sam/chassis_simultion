#include<webots/robot.h>
#include<webots/motor.h>
#include<webots/distance_sensor.h>
#include<webots/compass.h>
#include<stdlib.h>
#include<dos.h>

#define TIME_STEP 64

WbDeviceTag distance_sensor[6];
WbDeviceTag motors[4];
void turn (void)
{
    WbDeviceTag compass_sensor=wb_robot_get_device("compass");
    wb_compass_enable(compass_sensor,2);
    double* north=wb_compass_get_values(compass_sensor);
    //wb_robot_step();
    double start_number=north[1];

    double target_number=-start_number;
    double cur_number=start_number;
    double previous_number=0.0;
    while (1){
        previous_number=cur_number;
        wb_motor_set_velocity(motors[0],-1.0);
        wb_motor_set_velocity(motors[1],-1.0);
        wb_motor_set_velocity(motors[2],1.0);
        wb_motor_set_velocity(motors[3],1.0);
        cur_number=wb_compass_get_values(compass_sensor)[1];
        wb_robot_step(TIME_STEP);
        if((cur_number<target_number&&previous_number>target_number)|| (cur_number>target_number&&previous_number<target_number))
            break;
        //(wb_distance_sensor_get_value(distance_sensor[0])<500)
         //   break;
    }
    
}


int main(int argc,char *argv[])
{
    wb_robot_init();
    char motor_names[4][10]={"rf_motor",
                             "rb_motor",
                             "lf_motor",
                             "lb_motor"};
    char distance_sensor_names[6][10]={"ds_R",
                                       "ds_L",
                                       "ds_RF",
                                       "ds_RB",
                                       "ds_LF",
                                       "ds_LB"};
    for(int i=0;i<4;i++){
        motors[i]=wb_robot_get_device(motor_names[i]);
        wb_motor_set_position(motors[i],INFINITY);
        wb_motor_set_velocity(motors[i],0.0);
    }
    for(int i=0;i<6;i++){
        distance_sensor[i]=wb_robot_get_device(distance_sensor_names[i]);
        wb_distance_sensor_enable(distance_sensor[i],TIME_STEP);
        wb_distance_sensor_enable(distance_sensor[i], TIME_STEP);

    }
    

    double right_speed=-10.0;
    double left_speed=10.0;
    char flag=0;
    while(wb_robot_step(TIME_STEP)!=-1){
        if(wb_distance_sensor_get_value(distance_sensor[2])>=1000.0 &&
            wb_distance_sensor_get_value(distance_sensor[4])>=1000.0){
            right_speed=-10.0;
            left_speed=-10.0;
            flag=0;
        }else{ 
            if(flag==1&&wb_distance_sensor_get_value(distance_sensor[1])<1000.0){
                turn();
            }
            if((wb_distance_sensor_get_value(distance_sensor[2])<1000.0&&
                  wb_distance_sensor_get_value(distance_sensor[4])>=1000.0)||flag==1){
                left_speed=10.0;
                right_speed=-10.0;
            }else{
                left_speed=-10.0;
                right_speed=10.0;
            }
            if(wb_distance_sensor_get_value(distance_sensor[0])<1000.0){
                left_speed=10.0;
                right_speed=-10.0;
                flag=1;
            }else if(wb_distance_sensor_get_value(distance_sensor[1])<1000){
                left_speed=-10.0;
                right_speed=10.0;
           }
    }
        
        

        wb_motor_set_velocity(motors[0],right_speed);
        wb_motor_set_velocity(motors[1],left_speed);
        wb_motor_set_velocity(motors[2],left_speed);
        wb_motor_set_velocity(motors[3],right_speed);
    }
    wb_robot_cleanup();
}
