#include "MyHeader.h"


/**************************************************************************
Function: Read the encoder count
Input   : The timer
Output  : Encoder value (representing speed)
函数功能：读取编码器计数
入口参数：定时器
返回  值：编码器数值(代表速度)
**************************************************************************/

int Read_Encoder(uint8_t TIMX)
{
 int Encoder_TIM;    
 switch(TIMX)
 {
	case 2:  Encoder_TIM= (short)TIM2 -> CNT;   TIM2 -> CNT=0;  break;
	case 3:  Encoder_TIM= (short)TIM3 -> CNT;   TIM3 -> CNT=0;  break;
	case 4:  Encoder_TIM= (short)TIM4 -> CNT;   TIM4 -> CNT=0;  break;	
	case 5:  Encoder_TIM= (short)TIM5 -> CNT;   TIM5 -> CNT=0;  break;	
	default: Encoder_TIM=0;
 }
	return Encoder_TIM;
}
Encoder OriginalEncoder; //编码器原始数据
/**************************************************************************
函数功能：读取编码器数值，计算车轮速度（单位m/s），并计算累计距离（单位m）
入口参数：无
返回  值：无
**************************************************************************/
void Get_Velocity_Form_Encoder(void)
{
    // 获取编码器的原始数据
    float Encoder_A_pr, Encoder_B_pr, Encoder_C_pr, Encoder_D_pr; 

    OriginalEncoder.A = Read_Encoder(2);    
    OriginalEncoder.B = Read_Encoder(3);    
    OriginalEncoder.C = Read_Encoder(4);    
    OriginalEncoder.D = Read_Encoder(5);    

    // 根据不同小车型号决定编码器数值极性
    Encoder_A_pr = OriginalEncoder.A; 
    Encoder_B_pr = -OriginalEncoder.B;
    Encoder_C_pr =  OriginalEncoder.C;  
    Encoder_D_pr =  OriginalEncoder.D;

    // 编码器原始数据转换为车轮速度，单位m/s
    MOTOR_A.Encoder = Encoder_A_pr * CONTROL_FREQUENCY * Wheel_perimeter / Encoder_precision;  
    MOTOR_B.Encoder = Encoder_B_pr * CONTROL_FREQUENCY * Wheel_perimeter / Encoder_precision;  
    MOTOR_C.Encoder = Encoder_C_pr * CONTROL_FREQUENCY * Wheel_perimeter / Encoder_precision; 
    MOTOR_D.Encoder = Encoder_D_pr * CONTROL_FREQUENCY * Wheel_perimeter / Encoder_precision; 

		//记录走过的脉冲
		MOTOR_A.DisEncoder += Encoder_A_pr;  
		MOTOR_B.DisEncoder += Encoder_B_pr;  		
		MOTOR_C.DisEncoder += Encoder_C_pr;  
		MOTOR_D.DisEncoder += Encoder_D_pr;  
		
		//记录车轮走过的距离 单位m
    MOTOR_A.Distance += Encoder_A_pr * Wheel_perimeter / Encoder_precision;  
    MOTOR_B.Distance += Encoder_B_pr * Wheel_perimeter / Encoder_precision;  
    MOTOR_C.Distance += Encoder_C_pr * Wheel_perimeter / Encoder_precision;  
    MOTOR_D.Distance += Encoder_D_pr * Wheel_perimeter / Encoder_precision;  

//    // 输出速度和累计距离
//    printf("Speed (m/s): A = %.2f, B = %.2f, C = %.2f, D = %.2f\n", 
//            MOTOR_A.Encoder, MOTOR_B.Encoder, MOTOR_C.Encoder, MOTOR_D.Encoder);

//    printf("Distance (m): A = %.2f, B = %.2f, C = %.2f, D = %.2f\n", 
//            MOTOR_A.Distance, MOTOR_B.Distance, MOTOR_C.Distance, MOTOR_D.Distance);
}

