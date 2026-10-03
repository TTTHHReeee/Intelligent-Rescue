#include "MyHeader.h"
float roll, yaw, pitch,gyro_yaw;

float move_speed_x = 1;  //坐标速度闭环中速度的最大值
float move_speed_y = 0.1;  //坐标速度闭环中速度的最大值
float pos_speed = ball_pos_speed;  //位置速度闭环中速度的最大值
float angle_speed = 0.5;  //角度速度闭环中速度的最大值

int enMoveErrX = ball_en_err_x;  //坐标闭环所允许的X坐标误差值
int enMoveErrY = ball_en_err_y;  //坐标闭环所允许的Y坐标误差值
int enPosErr = 5000;  //位置闭环所允许的脉冲误差值  一圈60000个脉冲
float enTurnErr = 2; //角度闭环所允许的角度误差值

float target_cord_x = ball_target_x;  //找到球时的X
float target_cord_y = 320;  //找到球时的Y
																																																																												
float target_z = 90.0;  //目标角度值  正数左转 负数右转

uint8_t moveFlagX = 0; //1代表到达X
uint8_t moveFlagY = 0;  //1代表到达Y
uint8_t CarMode = 0;  //1找球模式 2移动指定距离 3旋转指定角度
uint8_t finishFlag = 0;  //1代表已经到达指定球位置 2代表移动距离完成 3代表转动到指定角度

#define TIMER_PERIOD_MS 10  // 定时器中断的时间周期（单位：ms）
uint16_t WatingTask = 3000;  //超时等待 ms
uint16_t WatingCount = 0;
uint8_t  WatingFlag = 0;
bool WatingStart = false;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM12)
	{
			if(WatingStart == true) {  //收到开始信号
					WatingCount += TIMER_PERIOD_MS;
					if (WatingCount >= WatingTask){
							WatingFlag = 1; 
							WatingCount = 0;
					}
			}
			//获取编码器数据
			Get_Velocity_Form_Encoder();
			//获取角度值
			MPU6050_DMP_Get_Date(&pitch, &roll, &yaw,&gyro_yaw);
		
			if(CarMode == 1 && finishFlag!= 1){  //
					if(cord_x-target_cord_x < enMoveErrX &&
							cord_x-target_cord_x > -enMoveErrX)
					{
							moveFlagX = 1;  //到达指定X
					}
					else{
							moveFlagX = 0;  
					}
					if(cord_y-target_cord_y < enMoveErrY &&
							cord_y-target_cord_y > -enMoveErrY)
					{
							moveFlagY = 1;  //到达指定Y
					}
					else{
							moveFlagY = 0;
					}
					if(moveFlagY == 1 && moveFlagX == 1){  
							Set_Pwm(0,0,0,0);//到达
							moveFlagX = 0;
							moveFlagY = 0;
							finishFlag = 1;
					}
//					if(moveFlagX == 1) {
//							Set_Pwm(0,0,0,0);//到达
//							moveFlagX = 0;
//							moveFlagY = 0;
//							finishFlag = 1;
//					}
					if(finishFlag!= 1){  //同时执行XY逼近
							float Vx = Move_PD_X(cord_x,target_cord_x);
							float Vy = Move_PD_Y(cord_y,target_cord_y);
							//限制目标速度
							Vx = target_limit_float(Vx,-0.4,move_speed_x);
							Vy = target_limit_float(Vy,-move_speed_y,move_speed_y);
							if(moveFlagX == 1) {
									Vx = 0;
							}
							if(moveFlagY == 1) {
									Vy = 0;
							}
							MOTOR_A.Target  = -Vx - Vy;
							MOTOR_B.Target  = -Vx + Vy;
						//速度闭环控制计算各电机PWM值，PWM代表车轮实际转速
							MOTOR_A.Motor_Pwm=Incremental_PI_A(MOTOR_A.Encoder, MOTOR_A.Target);
							MOTOR_B.Motor_Pwm=Incremental_PI_B(MOTOR_B.Encoder, MOTOR_B.Target);
							Limit_Pwm(16500) ;
							Set_Pwm(-MOTOR_A.Motor_Pwm, MOTOR_B.Motor_Pwm, MOTOR_C.Motor_Pwm, MOTOR_D.Motor_Pwm);//麦克纳姆轮小车 
					}

			}
			else if(CarMode == 2){  //移动指定距离
					if(MOTOR_A.DisEncoder-MOTOR_A.Target<enPosErr &&
							MOTOR_A.DisEncoder-MOTOR_A.Target>-enPosErr)
					{
							Set_Pwm(0,0,0,0);//到达
							finishFlag = 2;
					}
					else{
							//位置闭环控制			
							MOTOR_A.Motor_Pwm=Position_PID_A(MOTOR_A.DisEncoder, MOTOR_A.Target);
							MOTOR_B.Motor_Pwm=Position_PID_B(MOTOR_B.DisEncoder, MOTOR_B.Target);
				//			printf("A = %f,B = %f,C = %f,D = %f\n",MOTOR_A.Motor_Pwm,MOTOR_B.Motor_Pwm,MOTOR_C.Motor_Pwm,MOTOR_D.Motor_Pwm);
							//限制目标速度
							MOTOR_A.Motor_Pwm=target_limit_float(MOTOR_A.Motor_Pwm,-pos_speed,pos_speed);
							MOTOR_B.Motor_Pwm=target_limit_float(MOTOR_B.Motor_Pwm,-pos_speed,pos_speed);
						//速度闭环控制计算各电机PWM值，PWM代表车轮实际转速
							MOTOR_A.Motor_Pwm=Incremental_PI_A(MOTOR_A.Encoder, MOTOR_A.Motor_Pwm);
							MOTOR_B.Motor_Pwm=Incremental_PI_B(MOTOR_B.Encoder, MOTOR_B.Motor_Pwm);
							Limit_Pwm(16500) ;
							Set_Pwm(-MOTOR_A.Motor_Pwm, MOTOR_B.Motor_Pwm, MOTOR_C.Motor_Pwm, MOTOR_D.Motor_Pwm);//麦克纳姆轮小车 
					}		
			}		
			else if(CarMode == 3 && finishFlag!= 3)  //旋转固定角度
			{  
					if(yaw-target_z < enTurnErr &&
							yaw-target_z > -enTurnErr)
					{
							Set_Pwm(0,0,0,0);//到达
							finishFlag = 3;
					}
					else{
							//角度闭环控制			
							float Vz = Turn_PD(yaw, target_z);  
							//限制目标速度
							Vz = target_limit_float(Vz,-angle_speed,angle_speed);
//							printf("Vz = %f\n",Vz);
							MOTOR_A.Target  = -Vz;
							MOTOR_B.Target  = Vz;
						//速度闭环控制计算各电机PWM值，PWM代表车轮实际转速
							MOTOR_A.Motor_Pwm=Incremental_PI_A(MOTOR_A.Encoder, MOTOR_A.Target);
							MOTOR_B.Motor_Pwm=Incremental_PI_B(MOTOR_B.Encoder, MOTOR_B.Target);
							
							Limit_Pwm(16500) ;
							Set_Pwm(-MOTOR_A.Motor_Pwm, MOTOR_B.Motor_Pwm, MOTOR_C.Motor_Pwm, MOTOR_D.Motor_Pwm);//麦克纳姆轮小车 
					}
			}
			else if(CarMode == 5){
				//速度闭环控制计算各电机PWM值，PWM代表车轮实际转速
					MOTOR_A.Motor_Pwm=Incremental_PI_A(MOTOR_A.Encoder, MOTOR_A.Target);
					MOTOR_B.Motor_Pwm=Incremental_PI_B(MOTOR_B.Encoder, MOTOR_B.Target);
					Limit_Pwm(16500) ;
					Set_Pwm(-MOTOR_A.Motor_Pwm, MOTOR_B.Motor_Pwm, MOTOR_C.Motor_Pwm, MOTOR_D.Motor_Pwm);//麦克纳姆轮小车 
			}
	 }	  
}



