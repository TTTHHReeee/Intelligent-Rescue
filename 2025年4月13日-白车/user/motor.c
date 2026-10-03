#include "MyHeader.h"

//电机的参数结构体
Motor_parameter MOTOR_A,MOTOR_B,MOTOR_C,MOTOR_D;  
int cord_x = 620,cord_y;  //存放图像x y
//速度控制PID参数
float Velocity_KP=700,Velocity_KI=700; 
//位置PID参数
float Position_KP=0.003,Position_KI=0.0001,Position_KD=0.0064;  //PID系数
//转向环PD参数
float Turn_KP =0.003,Turn_KD = 0.001;
//移动环PD参数
uint8_t kp_mode = 0;  //0为球 1为框
#define ball_Kp_x 0.0004
#define ball_Kp_y 0.0001
#define frame_Kp_x 0.0065
int MoreSpeed = 4;
int DownCordX = 450;  //减低速度的阈值
float Move_KP_X = ball_Kp_x,Move_KI_X = 0,Move_KD_X = 0.00005;
float Move_KP_Y =ball_Kp_y,Move_KD_Y = 0.00003;

//平滑处理后的三轴速度
Smooth_Control smooth_control;

/**************************************************************************
函数功能：运动学逆解，根据三轴目标速度计算各车轮目标转速
入口参数：X和Y、Z轴方向的目标运动速度
返回  值：无
**************************************************************************/
void Drive_Motor(float Vx,float Vy,float Vz)
{
			float amplitude = 2; //Wheel target speed limit //车轮目标速度限幅
	
			//Inverse kinematics //运动学逆解
			MOTOR_A.Target  = Vx - Vz * Wheel_spacing / 2.0f; //计算出左轮的目标速度
			MOTOR_B.Target =  Vx + Vz * Wheel_spacing / 2.0f; //计算出右轮的目标速度

			//Wheel (motor) target speed limit //车轮(电机)目标速度限幅
			MOTOR_A.Target=target_limit_float( MOTOR_A.Target,-amplitude,amplitude); 
			MOTOR_B.Target=target_limit_float( MOTOR_B.Target,-amplitude,amplitude); 
			MOTOR_C.Target=0; //Out of use //没有使用到
			MOTOR_D.Target=0; //Out of use //没有使用到
}

/**************************************************************************
函数功能：控制移动指定距离
          根据目标位移计算每个车轮的转动量并移动
入口参数：Dx, Dy - X和Y轴方向的目标位移（单位：米）
          Dtheta - Z轴旋转的目标角度（单位：弧度）
返回  值：无
**************************************************************************/
void Drive_Motor_To_Distance(float Dx)
{
		//记录车轮走过的距离 单位m
		MOTOR_A.DisEncoder = 0;  
		MOTOR_B.DisEncoder = 0;  
		// 1. 计算每个轮子需要的位移（逆运动学）
    float Wheel_A_Displacement = Dx;
    float Wheel_B_Displacement = Dx;

    // 2. 将位移转换为目标脉冲数（根据轮子的周长和编码器分辨率）
		MOTOR_A.Target = Wheel_A_Displacement / Wheel_perimeter * Encoder_precision;  //60000
		MOTOR_B.Target = Wheel_B_Displacement / Wheel_perimeter * Encoder_precision;
}


/**************************************************************************
Function: Assign a value to the PWM register to control wheel speed and direction
Input   : PWM
Output  : none
函数功能：赋值给PWM寄存器，控制车轮转速与方向
入口参数：PWM
返回  值：无
**************************************************************************/
void Set_Pwm(int motor_a,int motor_b,int motor_c,int motor_d)
{
	if(motor_a<0)		  PWMA2=16800,PWMA1=16800+motor_a;
	else 	            PWMA1=16800,PWMA2=16800-motor_a;
		
	if(motor_b<0)		  PWMB1=16800,PWMB2=16800+motor_b;
	else 	            PWMB2=16800,PWMB1=16800-motor_b;
			
	if(motor_c<0)		  PWMC1=16800,PWMC2=16800+motor_c;
	else 	            PWMC2=16800,PWMC1=16800-motor_c;
	
	if(motor_d<0)		  PWMD2=16800,PWMD1=16800+motor_d;
	else 	            PWMD1=16800,PWMD2=16800-motor_d;
}


/**************************************************************************
Function: Limit PWM value
Input   : Value
Output  : none
函数功能：限制PWM值 
入口参数：幅值
返回  值：无
**************************************************************************/
void Limit_Pwm(int amplitude)
{	
	    MOTOR_A.Motor_Pwm=target_limit_float(MOTOR_A.Motor_Pwm,-amplitude,amplitude);
	    MOTOR_B.Motor_Pwm=target_limit_float(MOTOR_B.Motor_Pwm,-amplitude,amplitude);
  		MOTOR_C.Motor_Pwm=target_limit_float(MOTOR_C.Motor_Pwm,-amplitude,amplitude);
	    MOTOR_D.Motor_Pwm=target_limit_float(MOTOR_D.Motor_Pwm,-amplitude,amplitude);
}	    

/**************************************************************************
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
int Xianfu(int value,int Amplitude)
{	
	int temp;
	if(value>Amplitude) temp = Amplitude;
	else if(value<-Amplitude) temp = -Amplitude;
	else temp = value;
	return temp;		
}
/**************************************************************************
Function: Limiting function
Input   : Value
Output  : none
函数功能：限幅函数
入口参数：幅值
返回  值：无
**************************************************************************/
float target_limit_float(float insert,float low,float high)
{
    if (insert < low)
        return low;
    else if (insert > high)
        return high;
    else
        return insert;	
}
int target_limit_int(int insert,int low,int high)
{
    if (insert < low)
        return low;
    else if (insert > high)
        return high;
    else
        return insert;	
}
/**************************************************************************
函数功能：移动PD控制		
入口参数：real_coord:当前坐标；target_coord：目标坐标
返回  值：Pwm：移动控制PWM
**************************************************************************/	
float Move_PD_X(float real_coord,float target_coord)
{  
		static float Bias,Pwm,Integral_bias,Last_Bias;
		if(kp_mode == 0) {
				if(real_coord > DownCordX){
						Move_KP_X = ball_Kp_x * MoreSpeed;
				}
				else {
						Move_KP_X = ball_Kp_x;
				}
		}
		else if(kp_mode == 1){
				Move_KP_X = frame_Kp_x;
		}
		Bias=target_coord-real_coord;                                  //计算偏差
		Integral_bias+=Bias;	                                 //求出偏差的积分
		Integral_bias = target_limit_float(Integral_bias,-0.2,0.2);
    Pwm = (Move_KP_X*Bias)                        /* 比例环节 */
         +(Move_KI_X*Integral_bias)               /* 积分环节 */
         -(Move_KD_X*(Bias-Last_Bias));           /* 微分环节 */
		Last_Bias=Bias;                                       //保存上一次偏差 
		return Pwm;  
}
float Move_PD_Y(float real_coord,float target_coord)
{  
		static float Bias,Last_Bias,Pwm;
		if(kp_mode == 0) {
				if(real_coord > DownCordX){
						Move_KP_Y = ball_Kp_y * 2;
				}
				else {
						Move_KP_Y = ball_Kp_y;
				}
		}
		Bias = target_coord-real_coord;
		Pwm=Move_KP_Y*Bias - Move_KD_Y*(Bias-Last_Bias);
		Last_Bias=Bias; //保存上一次偏差
		return Pwm;
}
/**************************************************************************
函数功能：转向PD控制		
入口参数：real_angle_Z:当前角度；Tar_angle_Z：目标角度
返回  值：Pwm：转向控制PWM
**************************************************************************/	
float Turn_PD(float real_angle_Z,float Tar_angle_Z)
{  
		static float Bias,Last_Bias,Pwm;
		Bias = Tar_angle_Z-real_angle_Z;
		Pwm=Turn_KP*Bias+Turn_KD*(Bias-Last_Bias);
		Last_Bias=Bias; //保存上一次偏差
		return Pwm;
}
/**************************************************************************
函数功能：位置式PID控制器
入口参数：编码器测量位置信息，目标位置
返回  值：电机PWM
根据位置式离散PID公式 
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出
**************************************************************************/
int Position_PID_A (float position,int target)
{ 	
		static float Bias,Pwm,Integral_bias,Last_Bias;
		Bias=target-position;                                  //计算偏差
		Integral_bias+=Bias;	                                 //求出偏差的积分
		Integral_bias = target_limit_float(Integral_bias,-1000,1000);
    Pwm = (Position_KP*Bias)                        /* 比例环节 */
         +(Position_KI*Integral_bias)               /* 积分环节 */
         +(Position_KD*(Bias-Last_Bias));           /* 微分环节 */
		Last_Bias=Bias;                                       //保存上一次偏差 
		return Pwm;                                         //增量输出
}
int Position_PID_B (float position,int target)
{ 	
		static float Bias,Pwm,Integral_bias,Last_Bias;
		Bias=target-position;                                  //计算偏差
		Integral_bias+=Bias;	                                 //求出偏差的积分
		Integral_bias = target_limit_float(Integral_bias,-1000,1000);
    Pwm = (Position_KP*Bias)                        /* 比例环节 */
         +(Position_KI*Integral_bias)               /* 积分环节 */
         +(Position_KD*(Bias-Last_Bias));           /* 微分环节 */
		Last_Bias=Bias;                                       //保存上一次偏差 
		return Pwm;                                           //增量输出
}
int Position_PID_C (float position,int target)
{ 	
		static float Bias,Pwm,Integral_bias,Last_Bias;
		Bias=target-position;                                  //计算偏差
		Integral_bias+=Bias;	                                 //求出偏差的积分
		Integral_bias = target_limit_float(Integral_bias,-1000,1000);
    Pwm = (Position_KP*Bias)                        /* 比例环节 */
         +(Position_KI*Integral_bias)               /* 积分环节 */
         +(Position_KD*(Bias-Last_Bias));           /* 微分环节 */
		Last_Bias=Bias;                                       //保存上一次偏差 
		return Pwm;                                           //增量输出
}
int Position_PID_D (float position,int target)
{ 	
		static float Bias,Pwm,Integral_bias,Last_Bias;
		Bias=target-position;                                  //计算偏差
		Integral_bias+=Bias;	                                 //求出偏差的积分
		Integral_bias = target_limit_float(Integral_bias,-1000,1000);
    Pwm = (Position_KP*Bias)                        /* 比例环节 */
         +(Position_KI*Integral_bias)               /* 积分环节 */
         +(Position_KD*(Bias-Last_Bias));           /* 微分环节 */
		Last_Bias=Bias;                                       //保存上一次偏差 
		return Pwm;                                           //增量输出
}
/**************************************************************************
函数功能：增量式PI控制器
入口参数：编码器测量值(实际速度)，目标速度
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI_A (float Encoder,float Target)
{ 	
	 static float Bias,Pwm,Last_bias;
	 Bias=Target-Encoder; //Calculate the deviation //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias; 
	 if(Pwm>16800)Pwm=16800;
	 if(Pwm<-16800)Pwm=-16800;
	 Last_bias=Bias; //Save the last deviation //保存上一次偏差 
	 return Pwm;    
}
int Incremental_PI_B (float Encoder,float Target)
{  
	 static float Bias,Pwm,Last_bias;
	 Bias=Target-Encoder; //Calculate the deviation //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;  
	 if(Pwm>16800)Pwm=16800;
	 if(Pwm<-16800)Pwm=-16800;
	 Last_bias=Bias; //Save the last deviation //保存上一次偏差 
	 return Pwm;
}
int Incremental_PI_C (float Encoder,float Target)
{  
	 static float Bias,Pwm,Last_bias;
	 Bias=Target-Encoder; //Calculate the deviation //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias; 
	 if(Pwm>16800)Pwm=16800;
	 if(Pwm<-16800)Pwm=-16800;
	 Last_bias=Bias; //Save the last deviation //保存上一次偏差 
	 return Pwm; 
}
int Incremental_PI_D (float Encoder,float Target)
{  
	 static float Bias,Pwm,Last_bias;
	 Bias=Target-Encoder; //Calculate the deviation //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;  
	 if(Pwm>16800)Pwm=16800;
	 if(Pwm<-16800)Pwm=-16800;
	 Last_bias=Bias; //Save the last deviation //保存上一次偏差 
	 return Pwm; 
}

/**************************************************************************
Function: Floating-point data calculates the absolute value
Input   : float
Output  : The absolute value of the input number
函数功能：浮点型数据计算绝对值
入口参数：浮点数
返回  值：输入数的绝对值
**************************************************************************/
float float_abs(float insert)
{
	if(insert>=0) return insert;
	else return -insert;
}


/**************************************************************************
Function: Smoothing the three axis target velocity
Input   : Three-axis target velocity
Output  : none
函数功能：对三轴目标速度做平滑处理
入口参数：三轴目标速度
返回  值：无
**************************************************************************/
void Smooth_control(float vx,float vy,float vz)
{
	float step=0.05;

	if	   (vx>0) 	smooth_control.VX+=step;
	else if(vx<0)		smooth_control.VX-=step;
	else if(vx==0)	smooth_control.VX=smooth_control.VX*0.9f;
	
	if	   (vy>0)   smooth_control.VY+=step;
	else if(vy<0)		smooth_control.VY-=step;
	else if(vy==0)	smooth_control.VY=smooth_control.VY*0.9f;
	
	if	   (vz>0) 	smooth_control.VZ+=step;
	else if(vz<0)		smooth_control.VZ-=step;
	else if(vz==0)	smooth_control.VZ=smooth_control.VZ*0.9f;
	
	smooth_control.VX=target_limit_float(smooth_control.VX,-float_abs(vx),float_abs(vx));
	smooth_control.VY=target_limit_float(smooth_control.VY,-float_abs(vy),float_abs(vy));
	smooth_control.VZ=target_limit_float(smooth_control.VZ,-float_abs(vz),float_abs(vz));
}

