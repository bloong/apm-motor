 
/* Includes */
#include "moto.h"
#include "pwm.h"



void moto(bool ch1_P, bool ch1_N, bool ch2_P,  bool ch2_N, uint32_t dutyCycle_1, uint32_t dutyCycle_2)
{
 	
	  pwm_init(ch1_P, ch1_N, ch2_P,  ch2_N, FREQUENCY, dutyCycle_1, dutyCycle_2);

}
 
void moto_stop() 
{
	 pwm_init(false, false, false,  false, FREQUENCY, 0, 0);
}
 

void pid_init(PIDController *pid, double kp, double ki, double kd) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->prev_error = 0;
    pid->integral = 0;
}

double pid_update(PIDController *pid, double setpoint, double measured_value, double dt) {
    double error = setpoint - measured_value;
    pid->integral += error * dt;
    double derivative = (error - pid->prev_error) / dt;
    double output = pid->kp * error + pid->ki * pid->integral + pid->kd * derivative;
    pid->prev_error = error;
    return output;
}



void motor_control_init(MotorControlSystem *mcs, double pos_kp, double pos_ki, double pos_kd,
                        double dist_kp, double dist_ki, double dist_kd,
                        double angle_kp, double angle_ki, double angle_kd) {
    pid_init(&mcs->position_pid, pos_kp, pos_ki, pos_kd);
    pid_init(&mcs->distance_pid, dist_kp, dist_ki, dist_kd);
    pid_init(&mcs->angle_pid, angle_kp, angle_ki, angle_kd);
}

double calculate_distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double motor_control_update(MotorControlSystem *mcs, double target_x, double target_y,
                            double current_x, double current_y, double current_angle, double dt) {
    // 位置环
    double position_error_x = target_x - current_x;
    double position_error_y = target_y - current_y;
    double distance_target = pid_update(&mcs->position_pid, calculate_distance(target_x, target_y, current_x, current_y), 0, dt);

    // 距离环
    double distance_error = distance_target - calculate_distance(current_x, current_y, target_x, target_y);
    double angle_target = pid_update(&mcs->distance_pid, distance_target, calculate_distance(current_x, current_y, target_x, target_y), dt);

    // 角度环
    double angle_error = angle_target - current_angle;
    double motor_output = pid_update(&mcs->angle_pid, angle_target, current_angle, dt);

    return motor_output;
}