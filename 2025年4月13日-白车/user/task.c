#include "MyHeader.h"
int adcTz = 500;
int adcTy = 500;
void ADC_OLED(void) {
		int value[2] = {0};
		uint8_t i;
		for(i=0;i<2;i++){
				HAL_ADC_Start(&hadc1);
				if(HAL_ADC_PollForConversion(&hadc1,HAL_MAX_DELAY) == HAL_OK){			
						value[i]= HAL_ADC_GetValue(&hadc1);
				}	
		}
		OLED_ShowNum(0,0,value[0],4,16,1);
		OLED_ShowNum(0,15,value[1],4,16,1);
		OLED_Refresh();

}
uint8_t ADC_get(void)
{
	int value[2] = {0};
	uint8_t i;
	for(i=0;i<2;i++){
		HAL_ADC_Start(&hadc1);
		if(HAL_ADC_PollForConversion(&hadc1,HAL_MAX_DELAY) == HAL_OK){			
				value[i]= HAL_ADC_GetValue(&hadc1);
		}	
	}
	if(value[0] < adcTz && value[1] > adcTy){  //左边已经到达 返回2
			return 2;
	}
	else if(value[0] > adcTz && value[1]< adcTy){  //右边已经到达 返回3
			return 3;
	}
	else if(value[0] < adcTz && value[1]< adcTy){
			return 1;
	}
	else{
			return 0;
	}

}	
//新车新车新车新车新车新车新车新车新车新车//
void TS(void)  //弹射
{
    TIM8->CCR2=3000;
    HAL_Delay(100);
}
void HT(void)  //后退
{
    TIM8->CCR2=3300;  //左边    
}
void open(int ms)  //张开
{
    TIM8->CCR3=3000;//右边 
    TIM8->CCR4=4100; //                                                                                                                                                                                                                                                                             
    HAL_Delay(ms);
}
void close(void)  //闭合
{
    TIM8->CCR3=3700;//右边  
    TIM8->CCR4=3500; // 
    HAL_Delay(200);
}
void CatchBall(int ms) {   //抓到球以后挡板后退
    TIM8->CCR2=3500; 
}

uint8_t taskFlag = 0;  //任务调度函数
uint8_t mv_flag = 0;  //代码只执行一次标志 没有实际意义
uint8_t spin_flag = 0;  //旋转找球或者框
uint8_t xxx_flag = 0;   //代码只执行一次标志 没有实际意义
uint8_t rainy_flag = 0;   //ADC返回的flag
uint8_t isBallSuccess = 0;  //第一个球是否成功 成功返回1
uint8_t single_win_one = 0;  //代码只执行一次标志 没有实际意义
uint8_t single_win_two = 0;  //代码只执行一次标志 没有实际意义
char arrays[MAX_ITEMS][MAX_LENGTH] = {0}; // 存储分割后的字符串  
uint8_t task_WinBall(uint8_t task_ball) {   //找第一个球
		if (Uart2Flag == 1) {
				int count = 0; // 分割后的字符串数量
				split_into_arrays(RxBuffer2, arrays, &count);
				cord_x = arrayToInt(arrays[0]);
				cord_y = arrayToInt(arrays[1]);
				isBallSuccess = arrayToInt(arrays[2]); 
				FindFlag = 1;  //代表接受到数据
				WatingStart = true;  //开始计时
				WatingCount = 0;
				WatingTask = 3000;
				Uart2Flag = 0; // 重置标志
				Uart2_Rx_Cnt = 0;  
				memset(arrays, 0, sizeof(arrays));
				memset(RxBuffer2, 0x00, sizeof(RxBuffer2));
		}
		if(taskFlag == 0){  //找第一个球
				if (single_win_one == 0){
						UART = 2;
						printf("W%dL",task_ball);
						WatingCount = 0;
						WatingFlag = 0;
						kp_mode = 0;  //PID切换
						FindFlag = 0; 
						finishFlag = 0;
						CarMode = 5;
						MOTOR_A.Target = -0.13;
						MOTOR_B.Target = 0.13;  //逆时针
						single_win_one = 1;
				}
				if(spin_flag == 0){
						if(FindFlag == 1){  //找到球
								FindFlag = 0;
								spin_flag = 1;
								finishFlag = 0;
								CarMode = 1;
								target_cord_x = ball_target_x; //切换成找球x
								enMoveErrX = ball_en_err_x;
								enMoveErrY = ball_en_err_y;
						}
				}
				if(cord_x < 450) {
						open(0);
				}
				if(finishFlag == 1){  //到达指定球位置
						finishFlag = 0;	
						close();  //抓取
						UART = 2;
						printf("W0L");
						CatchBall(0);
						Buzz(100);
						taskFlag = 1;  //到达指定球位置
				}	
				if(WatingFlag == 1) {  //3s内没有接收到数据
						WatingFlag = 0;
						WatingCount = 0;
						single_win_one = 0;
						spin_flag = 0;
						UART = 2;
						printf("W7L");
				}
		}
		else if(taskFlag == 1){  //此时面向安全区 找安全区 并放下球
				pos_speed = frame_pos_speed;   //冲框的速度
				if (single_win_two == 0){
						UART = 2;
						printf("W2L");
						WatingCount = 0;
						WatingFlag = 0;
						WatingTask = 4000;
						kp_mode = 1;  //PID切换
						FindFlag = 0;
						finishFlag = 0;
						CarMode = 5;
						MOTOR_A.Target = 0.13;
						MOTOR_B.Target = -0.13;  //顺时针
						single_win_two = 1;
				}
				if(spin_flag == 1){
						if(FindFlag == 1){  //找到框
								FindFlag = 0;
								spin_flag = 0;
								finishFlag = 0;
								CarMode = 6;
								target_cord_x = frame_target_x; 
								enMoveErrX = frame_en_err_x;
								enMoveErrY = frame_en_err_y;
						}
				}
				if(finishFlag == 6){  //到达指定框位置
						finishFlag = 0;
						CarMode = 2;
						Drive_Motor_To_Distance(1);					
				}	
				if(WatingFlag == 1) {  //3s内没有接收到数据
						 while(1) {
								if(turnAngle(-90) == 1) {
										break;
								}
						}
						while(1) {
								pos_speed = 0.6;
								if(moveDistance(0.2) == 1){  //前进0.2m  距离框更近一点
										break;
								}
						}
						CarMode = 0;
						WatingFlag = 0;
						WatingCount = 0;
						single_win_two = 0;
						spin_flag = 1;
				}
				rainy_flag = ADC_get();
				if(CarMode == 2) {
						if(rainy_flag == 2) {  //左边已经到达
								while(1){
										CarMode = 0;
										Set_Pwm(0,0,0,0);
										Buzz(50);
									  CarMode = 5;
										MOTOR_A.Target = -0.05;
										MOTOR_B.Target =  0.08;  //左转
										Buzz(frame_adc_time);
										CarMode = 0;	
										Set_Pwm(0,0,0,0);
										finishFlag = 0;	
										spin_flag = 0;
										open(100);
										TS();
										HT();		
										xxx_flag = 1;
										taskFlag = 3;
										break;
								}
						}	
						else if(rainy_flag == 3) {  //右边已经到达
								while(1){
										CarMode = 0;
										Set_Pwm(0,0,0,0);
										Buzz(50);
									  CarMode = 5;
										MOTOR_A.Target =  0.08;
										MOTOR_B.Target = -0.05;  //右转
										Buzz(frame_adc_time);
										CarMode = 0;	
										Set_Pwm(0,0,0,0);
										finishFlag = 0;	
										open(100);
										TS();
										HT();		
										xxx_flag = 1;
										taskFlag = 3;
										break;
								}
						}	
						else if(rainy_flag == 1){
								CarMode = 0;	
								Set_Pwm(0,0,0,0);
								finishFlag = 0;	
								open(100);
								TS();
								HT();		
								xxx_flag = 1;
								taskFlag = 3;
						}		
				}
				if(finishFlag == 2){  
						finishFlag = 0;
						CarMode = 0;	
						Set_Pwm(0,0,0,0);
						Buzz(100);
						open(100);
						TS();
						HT();		
					  xxx_flag = 1;
						taskFlag = 3;
				}
		}
		else if(taskFlag == 3){  //
				pos_speed = 1;  //后退速度提高
				if(xxx_flag == 1){
					UART = 2;
					printf("W0L");
					xxx_flag = 0;
					finishFlag = 0;	
					CarMode = 2;
					Drive_Motor_To_Distance(-0.5);  //回中
					Buzz(100);
				}
				if(finishFlag == 2){
						finishFlag = 0;
						close();
						taskFlag = 4;
						target_z = 20;  //旋转去找下一个球
						CarMode = 3;
				}
		}
		else if(taskFlag == 4){ 
				if(finishFlag == 3) {
						finishFlag = 0;
						taskFlag = 0;  //安全球任务完成
						CarMode = 0;
						mv_flag = 0;
						spin_flag = 0;
						single_win_one = 0;
						single_win_two = 0;
						return 1;	
				}
		}
		return 0;
}
