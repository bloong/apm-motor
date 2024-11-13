 
/* Define to prevent recursive inclusion */
#ifndef __MOTO_H
#define __MOTO_H

#include "main.h"
#include "stdbool.h"

 
typedef struct {
    double kp;
    double ki;
    double kd;
    double prev_error;
    double integral;
} PIDController;


typedef struct {
    PIDController position_pid;
    PIDController distance_pid;
    PIDController angle_pid;
} MotorControlSystem;

void pid_init(PIDController *pid, double kp, double ki, double kd);


double pid_update(PIDController *pid, double setpoint, double measured_value, double dt) ;


 
void motor_control_init(MotorControlSystem *mcs, double pos_kp, double pos_ki, double pos_kd,
                        double dist_kp, double dist_ki, double dist_kd,
                        double angle_kp, double angle_ki, double angle_kd);

double calculate_distance(double x1, double y1, double x2, double y2);
double motor_control_update(MotorControlSystem *mcs, double target_x, double target_y,
                            double current_x, double current_y, double current_angle, double dt);


void moto(bool ch1_P, bool ch1_N, bool ch2_P,  bool ch2_N, uint32_t dutyCycle_1, uint32_t dutyCycle_2);

void moto_stop() ;


#endif /*__MOTO_H */
