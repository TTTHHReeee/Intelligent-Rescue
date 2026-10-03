#ifndef __ENCODER_H
#define __ENCODER_H

//±àÂëÆ÷½á¹¹Ìå
typedef struct  
{
  int A;      
  int B; 
	int C; 
	int D; 
}Encoder;

int Read_Encoder(uint8_t TIMX);
void Get_Velocity_Form_Encoder(void);

#endif
