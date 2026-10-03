#ifndef __MOTOR_H
#define __MOTOR_H	

#define PWMA1   TIM10->CCR1 
#define PWMA2   TIM11->CCR1 

#define PWMB1   TIM9->CCR1 
#define PWMB2   TIM9->CCR2

#define PWMC1   TIM1->CCR1  
#define PWMC2   TIM1->CCR2 

#define PWMD1   TIM1->CCR3 
#define PWMD2   TIM1->CCR4

extern int MoreSpeed;
extern int DownSpeed;
typedef struct  
{
  int MOTOR_A;      
  int MOTOR_B; 
	int MOTOR_C; 
	int MOTOR_D; 
}Target;


//Motor speed control related parameters of the structure
//电机速度控制相关参数结构体
typedef struct  
{
	float Encoder;      //编码器数值，读取电机实时速度
	float Motor_Pwm;   //电机PWM数值，控制电机实时速度
	float Target;      //电机目标速度值，控制电机目标速度
	float Velocity_KP; //速度控制PID参数
	float	Velocity_KI; //速度控制PID参数
	float Distance;   //车轮走过的距离
	float DisEncoder;  //车轮走过的脉冲
}Motor_parameter;
#include "gpio.h"
extern float Turn_KP,Turn_KD;
extern uint8_t kp_mode;
//Smoothed the speed of the three axes
//平滑处理后的三轴速度
typedef struct  
{
	float VX;
	float VY;
	float VZ;
}Smooth_Control;

extern float Velocity_KP, Velocity_KI;	
extern Motor_parameter MOTOR_A, MOTOR_B, MOTOR_C, MOTOR_D;
extern Smooth_Control smooth_control;
extern int cord_x,cord_y;  //存放图像x y

void Drive_Motor(float Vx,float Vy,float Vz);
void Drive_Motor_To_Distance(float Dx);
float target_limit_float(float insert,float low,float high);
int target_limit_int(int insert,int low,int high);
void Smooth_control(float vx,float vy,float vz);
float float_abs(float insert);
void Set_Pwm(int motor_a,int motor_b,int motor_c,int motor_d);
void Limit_Pwm(int amplitude);
float Move_PD_X(float real_coord,float target_coord);
float Move_PD_Y(float real_coord,float target_coord);
float Turn_PD(float real_angle_Z,float Tar_angle_Z);		
int Position_PID_A (float position,int target);
int Position_PID_B (float position,int target);
int Position_PID_C (float position,int target);
int Position_PID_D (float position,int target);
int Incremental_PI_A (float Encoder,float Target);
int Incremental_PI_B (float Encoder,float Target);
int Incremental_PI_C (float Encoder,float Target);
int Incremental_PI_D (float Encoder,float Target);


#endif  


