#ifndef __ROBOTINIT_H
#define __ROBOTINIT_H

#define PI 3.14159265358979f

//Encoder accuracy
//编码器精度
extern float Encoder_precision; 
//Wheel circumference, unit: m
//轮子周长，单位：m
extern float Wheel_perimeter; 
//Drive wheel base, unit: m
//主动轮轮距，单位：m
extern float Wheel_spacing; 
//The wheelbase of the front and rear axles of the trolley, unit: m
//小车前后轴的轴距，单位：m
extern float Axle_spacing; 
//All-directional wheel turning radius, unit: m
//全向轮转弯半径，单位：m
extern float Omni_turn_radiaus; 
//Parameter structure of robot
//机器人参数结构体
typedef struct  
{
  float WheelSpacing;      //Wheelspacing, Mec_Car is half wheelspacing //轮距 麦轮车为半轮距
  float AxleSpacing;       //Axlespacing, Mec_Car is half axlespacing //轴距 麦轮车为半轴距	
  int GearRatio;           //Motor_gear_ratio //电机减速比
  int EncoderAccuracy;     //Number_of_encoder_lines //编码器精度(编码器线数)
  float WheelDiameter;     //Diameter of driving wheel //主动轮直径	
  float OmniTurnRadiaus;   //Rotation radius of omnidirectional trolley //全向轮小车旋转半径	
}Robot_Parament_InitTypeDef;



//The minimum turning radius of Ackermann models is determined by the mechanical structure: 
//the maximum Angle of the wheelbase, wheelbase and front wheels
//阿克曼车型的最小转弯半径，由机械结构决定：轮距、轴距、前轮最大转角
#define MINI_AKM_MIN_TURN_RADIUS 0.350f 

//Wheelspacing, Mec_Car is half wheelspacing
//轮距 麦轮是一半
#define MEC_wheelspacing         0.0930 //修正2021.03.30
#define Diff_wheelSpacing        0.065f

//Axlespacing, Mec_Car is half axlespacing
//轴距 麦轮是一半
#define MEC_axlespacing           0.085


//Motor_gear_ratio
//电机减速比
#define   HALL_30F    30
#define   MD36N_5_18  5.18
#define   MD36N_27    27
#define   MD36N_51    51
#define   MD36N_71    71
#define   MD60N_18    18
#define   MD60N_47    47

//Number_of_encoder_lines
//编码器精度
#define		Photoelectric_500 500
#define	  Hall_13           13
#define	  Hall_11           11

//Mecanum wheel tire diameter series
//麦轮轮胎直径
#define		Mecanum_60  0.060f
#define		Mecanum_75  0.075f
#define		Mecanum_100 0.100f
#define		Mecanum_127 0.127f
#define		Mecanum_152 0.152f
 
#define	  Black_WheelDiameter   0.065
//The encoder octave depends on the encoder initialization Settings
//编码器倍频数，取决于编码器初始化设置
#define   EncoderMultiples  4
//Encoder data reading frequency
//编码器数据读取频率
#define   CONTROL_FREQUENCY 100


void Robot_Select(void);
void Robot_Init(double wheelspacing, float axlespacing, float omni_turn_radiaus, float gearratio,float Accuracy,float tyre_diameter);

#endif
